#include <arch/memorymanager.h>
#include <planck/kmalloc.h>

#define UnlinkLinkedListEx(list, node, type, type2) {       \
    if (node->type##Prev)                                   \
        node->type##Prev->type##Next = node->type##Next;    \
    else                                                    \
        list->type2##Head = node->type##Next;               \
    if (node->type##Next)                                   \
        node->type##Next->type##Prev = node->type##Prev; }

#define InsertLinkedListNew(node, at, type) {  \
    node->type##Next = at->type##Next;         \
    node->type##Prev = at;                     \
    at->type##Next = node;                     \
    if (node->type##Next)                      \
        node->type##Next->type##Prev = node; }

#define InsertLinkedListEx(list, node, at, type, type2) { \
    UnlinkLinkedListEx(list, node, type, type2)           \
    InsertLinkedListNew(node, at, type) }

#define InsertLinkedList(list, node, at, type) InsertLinkedListEx(list, node, at, type, type)
#define UnlinkLinkedList(list, node, type) UnlinkLinkedListEx(list, node, type, type)

static int MemoryRegionCompress(MemoryRegion *region, MemoryRegionEntry *node, uint8_t flags)
{
    MemoryRegionEntry *prev = node->APrev;

    if (prev->Base + prev->Size != node->Base)
        return 0;

    if (flags & kPageSuperPage)
    {
        if ((node->Base & kPageSuperPage) != (prev->Base & kPageSuperPage))
            return 0;
    }

    prev->Size += node->Size;

    return 1;
}

static void MemoryRegionAddFree(MemoryRegion *region, MemoryRegionEntry *rnode, uintptr_t address, size_t size)
{
    MemoryRegionEntry *node = region->AHead, *tmp;

    if (node)
    {
        while (1)
        {
            if (node->Base + node->Size == address)
                break;

            if (!node->ANext)
                break;

            if (node->ANext->Base > address)
                break;

            node = node->ANext;
        }
    }

    if (node && node->Base + node->Size == address)
    {
        node->Size += size;

        if (node->SNext && MemoryRegionCompress(region, node->ANext, 0))
        {
            tmp = node->ANext;
            UnlinkLinkedList(region, tmp, S);
            UnlinkLinkedList(region, tmp, A);
            free(tmp);
        }

        if (node->SNext && node->SNext->Size < node->Size)
        {
            tmp = node->SNext;

            while (tmp->SNext && tmp->Size < node->Size)
                tmp = tmp->SNext;

            InsertLinkedList(region, node, tmp, S);
        }
    }
    else if (node && address + size == node->Base)
    {
        node->Base -= size;
        node->Size += size;

        if (node->SNext && node->SNext->Size < node->Size)
        {
            tmp = node->SNext;

            while (tmp->SNext && tmp->Size < node->Size)
                tmp = tmp->SNext;

            InsertLinkedList(region, node, tmp, S);
        }
    }
    else
    {
        tmp = rnode && rnode->Size == size ? rnode : (MemoryRegionEntry *)malloc(sizeof(MemoryRegionEntry));

        tmp->Base = address;
        tmp->Size = size;

        if (node && tmp->Base > node->Base)
        {
            InsertLinkedListNew(tmp, node, A);
        }
        else
        {
            tmp->ANext = region->AHead;

            if (tmp->ANext)
                tmp->ANext->APrev = tmp;

            region->AHead = tmp;
        }

        node = region->SHead;

        while (node->SNext && tmp->Size >= node->Size)
            node = node->SNext;

        if (node && tmp->Size >= node->Size)
        {
            InsertLinkedListNew(tmp, node, S);
        }
        else
        {
            tmp->SNext = region->SHead;

            if (tmp->SNext)
                tmp->SNext->SPrev = tmp;

            region->SHead = tmp;
        }
    }
}

static void MemoryRegionAddUsed(MemoryRegion *region, MemoryRegionEntry *rnode, uintptr_t address, size_t size, uint8_t flags)
{
    MemoryRegionEntry *node = region->UHead, *tmp;

    if (node)
    {
        while (1)
        {
            if (node->Base + node->Size == address)
                break;

            if (!node->ANext)
                break;

            if (node->ANext->Base > address)
                break;

            node = node->ANext;
        }
    }

    if (node && node->Base + node->Size == address)
    {
        node->Size += size;

        if (node->ANext && MemoryRegionCompress(region, node->ANext, flags))
        {
            tmp = node->ANext;
            UnlinkLinkedListEx(region, tmp, A, U);
            free(tmp);
        }
    }
    else if (node && address + size == node->Base)
    {
        node->Base -= size;
        node->Size += size;
    }
    else
    {
        tmp = rnode && rnode->Size == size ? rnode : (MemoryRegionEntry *)malloc(sizeof(MemoryRegionEntry));

        tmp->Base = address | flags;
        tmp->Size = size;

        if (node && tmp->Base > node->Base)
        {
            InsertLinkedListNew(tmp, node, A);
        }
        else
        {
            tmp->ANext = region->UHead;

            if (tmp->ANext)
                tmp->ANext->APrev = tmp;

            region->UHead = tmp;
        }

        node = tmp;
    }
}

uintptr_t MemoryRegionAlloc(MemoryRegion *region, uintptr_t address, size_t count, uint8_t flags)
{
    MemoryRegionEntry *node;
    size_t page_size = flags & kPageSuperPage ? 0x200000 : 0x1000;
    size_t size = count * page_size;

    if (address != -1 && (address < region->Base || address + size >= region->Limit))
        return 0;

    if (address == -1)
    {
        node = region->SHead;

        if (!node)
            return 0;

        while (node->SNext && node->Size < size)
            node = node->SNext;

        if (node->Size < size)
            return 0;

        address = node->Base & 0xFFFFFFFFFFFFF000;
    }
    else
    {
        node = region->AHead;

        if (!node)
            return 0;

        while (1)
        {
            if (!node->ANext)
                break;

            if (node->ANext->Base > address)
                break;

            node = node->ANext;
        }

        if (node->Base > address || address + size > node->Base + node->Size)
            return 0;
    }

    if (node->Base == address)
    {
        if (node->Size != size)
        {
            node->Base += size;
            node->Size -= size;
        }
        else
        {
            UnlinkLinkedList(region, node, S);
            UnlinkLinkedList(region, node, A);
        }

        MemoryRegionAddUsed(region, node, address, size, flags);
    }
    else
    {
        size_t remain = node->Base + node->Size - (address + size);

        node->Size = address - node->Base;

        MemoryRegionAddUsed(region, NULL, address, size, flags);
        MemoryRegionAddFree(region, NULL, address + size, remain);
    }

    return address;
}

void MemoryRegionFree(MemoryRegion *region, uintptr_t address, uint64_t count, uint8_t flags)
{
    MemoryRegionEntry *node;
    size_t page_size = flags & kPageSuperPage ? 0x200000 : 0x1000;
    size_t size = count * page_size;

    if (address < region->Base || address + size >= region->Limit)
        return;

    node = region->UHead;

    if (!node)
        return;

    while (1)
    {
        if (!node->ANext)
            break;

        if (node->ANext->Base > address)
            break;

        node = node->ANext;
    }

    if (node->Base > address || address + size > node->Base + node->Size)
        return;

    if (node->Base == address)
    {
        if (node->Size != size)
        {
            node->Base += size;
            node->Size -= size;
        }
        else
        {
            UnlinkLinkedListEx(region, node, A, U);
        }

        MemoryRegionAddFree(region, node, address, size);
    }
    else
    {
        size_t remain = node->Base + node->Size - (address + size);

        node->Size = address - node->Base;

        MemoryRegionAddFree(region, NULL, address, size);
        MemoryRegionAddUsed(region, NULL, address + size, remain, flags);
    }
}

void MemoryRegionCreate(MemoryRegion *region, uintptr_t base, uintptr_t limit)
{
    region->Base = base;
    region->Limit = limit;

    region->AHead = region->SHead = (MemoryRegionEntry *)malloc(sizeof(MemoryRegionEntry));
    region->AHead->Base = region->Base;
    region->AHead->Size = region->Limit - region->Base;
    region->AHead->APrev = NULL;
    region->AHead->SPrev = NULL;
    region->AHead->ANext = NULL;
    region->AHead->SNext = NULL;
}
