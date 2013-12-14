#include <planck/kmalloc.h>
#include <stdint.h>
#include <string.h>

extern uint32_t *__brk_base, *__brk_limit;

void kmalloc_initialize()
{
    *__brk_base = 0;
}

void *malloc(size_t size)
{
    void *ptr = ((uint8_t*)__brk_base) + *__brk_base + 4;
    *__brk_base += size;
    return ptr;
}

void *realloc(void *address, size_t size)
{
    return NULL;
}

void *calloc(size_t size)
{
    void *ptr = malloc(size);
    memset(ptr, 0, size);
    return ptr;
}

void free(void *address)
{
    if (address >= __brk_base && address <= __brk_limit)
        return;
}
