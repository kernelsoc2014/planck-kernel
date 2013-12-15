#include <planck/kmalloc.h>
#include <arch/early_printk.h>
#include <stdint.h>
#include <string.h>

extern void *__brk_base, *__brk_limit;

static uintptr_t brk_base;
static uintptr_t brk_limit;

void kmalloc_initialize()
{
    brk_base = (uintptr_t)&__brk_base;
    brk_limit = (uintptr_t)&__brk_limit;
}

void *malloc(size_t size)
{
    uintptr_t ptr = brk_base;

    brk_base += size;

    if (brk_base > brk_limit)
        early_printk("WARNING: sbrk limit reached!");

    return (void *)ptr;
}

void *malloc_page_aligned(size_t size)
{
    uintptr_t ptr = brk_base;

    ptr &= 0xfffffffffffff000;
    ptr += 0x1000;

    brk_base += ptr - brk_base + size;

    if (brk_base > brk_limit)
        early_printk("WARNING: sbrk limit reached!");

    return (void *)ptr;
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
    if (address >= brk_base && address <= brk_limit)
        return;
}
