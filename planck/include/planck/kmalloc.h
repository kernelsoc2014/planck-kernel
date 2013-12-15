#pragma once

#include <planck/compiler.h>
#include <stddef.h>

__BEGIN_DECLS

void kmalloc_initialize();

void *malloc(size_t size);
void *malloc_page_aligned(size_t size);
void *realloc(void *address, size_t size);
void *calloc(size_t size);
void free(void *address);

__END_DECLS

