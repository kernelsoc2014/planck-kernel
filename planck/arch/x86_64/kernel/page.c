#include <planck/kmalloc.h>
#include <arch/page.h>
#include <arch/early_printk.h>

static pml4_entry_t *kernel_pml4;

#define unlink_linked_list2(list, node, type, type2) {        \
    if (node->type##_prev)                                    \
        node->type##_prev->type##_next = node->type##_next;   \
    else                                                      \
        list->type2##_head = node->type##_next;               \
    if (node->type##_next)                                    \
        node->type##_next->type##_prev = node->type##_prev; }

#define insert_linked_list_new(node, at, type) { \
    node->type##_next = at->type##_next;         \
    node->type##_prev = at;                      \
    at->type##_next = node;                      \
    if (node->type##_next)                       \
        node->type##_next->type##_prev = node; }

#define insert_linked_list2(list, node, at, type, type2) { \
    unlink_linked_list2(list, node, type, type2)            \
    insert_linked_list_new(node, at, type) }

#define insert_linked_list(list, node, at, type) insert_linked_list2(list, node, at, type, type)
#define unlink_linked_list(list, node, type) unlink_linked_list2(list, node, type, type)

static int memory_region_compress(memory_region_t *region, memory_region_entry_t *node, uint8_t flags)
{
    memory_region_entry_t *prev = node->a_prev;

    if (prev->base + prev->size != node->base)
        return 0;

    if (flags & MRF_BIG_PAGE)
    {
        if ((node->base & PBF_BIG_PAGE) != (prev->base & PBF_BIG_PAGE))
            return 0;
    }

    prev->size += node->size;

    return 1;
}

static void memory_region_add_free(memory_region_t *region, memory_region_entry_t *rnode, uintptr_t address, size_t size)
{
    memory_region_entry_t *node = region->a_head, *tmp;

    if (node)
    {
        while (1)
        {
            if (node->base + node->size == address)
                break;

            if (!node->a_next)
                break;

            if (node->a_next->base > address)
                break;

            node = node->a_next;
        }
    }

    if (node && node->base + node->size == address)
    {
        node->size += size;

        if (node->s_next && memory_region_compress(region, node->a_next, 0))
        {
            tmp = node->a_next;
            unlink_linked_list(region, tmp, s);
            unlink_linked_list(region, tmp, a);
            free(tmp);
        }

        if (node->s_next && node->s_next->size < node->size)
        {
            tmp = node->s_next;

            while (tmp->s_next && tmp->size < node->size)
                tmp = tmp->s_next;

            insert_linked_list(region, node, tmp, s);
        }
    }
    else if (node && address + size == node->base)
    {
        node->base -= size;
        node->size += size;

        if (node->s_next && node->s_next->size < node->size)
        {
            tmp = node->s_next;

            while (tmp->s_next && tmp->size < node->size)
                tmp = tmp->s_next;

            insert_linked_list(region, node, tmp, s);
        }
    }
    else
    {
        tmp = rnode && rnode->size == size ? rnode : (memory_region_entry_t *)malloc(sizeof(memory_region_entry_t));

        tmp->base = address;
        tmp->size = size;

        if (node && tmp->base > node->base)
        {
            insert_linked_list_new(tmp, node, a);
        }
        else
        {
            tmp->a_next = region->a_head;

            if (tmp->a_next)
                tmp->a_next->a_prev = tmp;

            region->a_head = tmp;
        }

        node = region->s_head;

        while (node->s_next && tmp->size >= node->size)
            node = node->s_next;

        if (node && tmp->size >= node->size)
        {
            insert_linked_list_new(tmp, node, s);
        }
        else
        {
            tmp->s_next = region->s_head;

            if (tmp->s_next)
                tmp->s_next->s_prev = tmp;

            region->s_head = tmp;
        }
    }
}

static void memory_region_add_used(memory_region_t *region, memory_region_entry_t *rnode, uintptr_t address, size_t size, uint8_t flags)
{
    memory_region_entry_t *node = region->u_head, *tmp;

    if (node)
    {
        while (1)
        {
            if (node->base + node->size == address)
                break;

            if (!node->a_next)
                break;

            if (node->a_next->base > address)
                break;

            node = node->a_next;
        }
    }

    if (node && node->base + node->size == address)
    {
        node->size += size;

        if (node->a_next && memory_region_compress(region, node->a_next, flags))
        {
            tmp = node->a_next;
            unlink_linked_list2(region, tmp, a, u);
            free(tmp);
        }
    }
    else if (node && address + size == node->base)
    {
        node->base -= size;
        node->size += size;
    }
    else
    {
        tmp = rnode && rnode->size == size ? rnode : (memory_region_entry_t *)malloc(sizeof(memory_region_entry_t));

        tmp->base = address | flags;
        tmp->size = size;

        if (node && tmp->base > node->base)
        {
            insert_linked_list_new(tmp, node, a);
        }
        else
        {
            tmp->a_next = region->u_head;

            if (tmp->a_next)
                tmp->a_next->a_prev = tmp;

            region->u_head = tmp;
        }

        node = tmp;
    }
}

static uintptr_t memory_region_alloc(memory_region_t *region, uintptr_t address, size_t count, uint8_t flags)
{
    memory_region_entry_t *node;
    size_t page_size = flags & MRF_BIG_PAGE ? 0x200000 : 0x1000;
    size_t size = count * page_size;

    if (address != -1 && (address < region->base || address + size >= region->limit))
        return 0;

    if (address == -1)
    {
        node = region->s_head;

        if (!node)
            return 0;

        while (node->s_next && node->size < size)
            node = node->s_next;

        if (node->size < size)
            return 0;

        address = node->base;
    }
    else
    {
        node = region->a_head;

        if (!node)
            return 0;

        while (1)
        {
            if (!node->a_next)
                break;

            if (node->a_next->base > address)
                break;

            node = node->a_next;
        }

        if (node->base > address || address + size > node->base + node->size)
            return 0;
    }

    if (node->base == address)
    {
        if (node->size != size)
        {
            node->base += size;
            node->size -= size;
        }
        else
        {
            unlink_linked_list(region, node, s);
            unlink_linked_list(region, node, a);
        }

        memory_region_add_used(region, node, address, size, flags);
    }
    else
    {
        size_t remain = node->base + node->size - (address + size);

        node->size = address - node->base;

        memory_region_add_used(region, NULL, address, size, flags);
        memory_region_add_free(region, NULL, address + size, remain);
    }

    return address;
}

static void memory_region_free(memory_region_t *region, uintptr_t address, uint64_t count, uint8_t flags)
{
    memory_region_entry_t *node;
    size_t page_size = flags & MRF_BIG_PAGE ? 0x200000 : 0x1000;
    size_t size = count * page_size;

    if (address < region->base || address + size >= region->limit)
        return;

    node = region->u_head;

    if (!node)
        return;

    while (1)
    {
        if (!node->a_next)
            break;

        if (node->a_next->base > address)
            break;

        node = node->a_next;
    }

    if (node->base > address || address + size > node->base + node->size)
        return;

    if (node->base == address)
    {
        if (node->size != size)
        {
            node->base += size;
            node->size -= size;
        }
        else
        {
            unlink_linked_list2(region, node, a, u);
        }

        memory_region_add_free(region, node, address, size);
    }
    else
    {
        size_t remain = node->base + node->size - (address + size);

        node->size = address - node->base;

        memory_region_add_free(region, NULL, address, size);
        memory_region_add_used(region, NULL, address + size, remain, flags);
    }
}

memory_region_t *memory_region_create(uintptr_t base, uintptr_t limit)
{
    memory_region_t *region = (memory_region_t *)malloc(sizeof(memory_region_t));

    region->base = base;
    region->limit = limit;

    region->a_head = region->s_head = (memory_region_entry_t *)malloc(sizeof(memory_region_entry_t));
    region->a_head->base = region->base;
    region->a_head->size = region->limit - region->base;
    region->a_head->a_prev = NULL;
    region->a_head->s_prev = NULL;
    region->a_head->a_next = NULL;
    region->a_head->s_next = NULL;

    return region;
}

void page_init()
{
    kernel_pml4 = malloc_page_aligned(PAGE_TABLE_ENTRY_COUNT * sizeof(pml4_entry_t));

    memory_region_t *region = memory_region_create(0xFFFFFF0000000000, 0xFFFFFF8000000000);
    uintptr_t a = memory_region_alloc(region, -1, 1, MRF_NONE);
    uintptr_t b = memory_region_alloc(region, 0xFFFFFF0000002000, 3, MRF_NONE);
    uintptr_t c = memory_region_alloc(region, -1, 2, MRF_NONE);
    uintptr_t d = memory_region_alloc(region, -1, 1, MRF_NONE);

    early_printk("%lx %lx %lx %lx\n", a, b, c, d);

    for (memory_region_entry_t *e = region->s_head; e; e = e->s_next)
        early_printk("D_s: %lx %lx\n", e->base, e->size);

    for (memory_region_entry_t *e = region->a_head; e; e = e->a_next)
        early_printk("D_a: %lx %lx\n", e->base, e->size);

    for (memory_region_entry_t *e = region->u_head; e; e = e->a_next)
        early_printk("D_u: %lx %lx\n", e->base, e->size);

    memory_region_free(region, b, 3, 0);

    for (memory_region_entry_t *e = region->s_head; e; e = e->s_next)
        early_printk("D_s4: %lx %lx\n", e->base, e->size);

    for (memory_region_entry_t *e = region->a_head; e; e = e->a_next)
        early_printk("D_a4: %lx %lx\n", e->base, e->size);

    for (memory_region_entry_t *e = region->u_head; e; e = e->a_next)
        early_printk("D_u4: %lx %lx\n", e->base, e->size);

    uintptr_t e = memory_region_alloc(region, -1, 2, MRF_NONE);
    uintptr_t f = memory_region_alloc(region, -1, 1, MRF_NONE);

    early_printk("%lx %lx\n", e, f);

    while(1){}
}
