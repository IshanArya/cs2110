/*
 * CS 2110 Spring 2019
 * Author:
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this to print out stuff*/
#include <stdio.h>
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"
/* include this for any boolean methods */
#include <stdbool.h>

/*Function Headers
 * Here is a place to put all of your function headers
 * Remember to declare them as static
 */

/* Our freelist structure - our freelist is represented as a singly linked list
 * the size_list orders the free blocks by size in ascending order
 */

metadata_t *size_list;

/* Set on every invocation of my_malloc()/my_free()/my_realloc()/
 * my_calloc() to indicate success or the type of failure. See
 * the definition of the my_malloc_err enum in my_malloc.h for details.
 * Similar to errno(3).
 */
enum my_malloc_err my_malloc_errno;

/* MALLOC
 * See PDF for documentation
 */




static void set_canary(metadata_t* block) {
    unsigned long canary = ((uintptr_t)block ^ CANARY_MAGIC_NUMBER) + 1890;
    block->canary = canary;
    unsigned long *endCanary = (unsigned long *)((uint8_t *)(block + 1) + block->size);
    *endCanary = canary;
}

// static metadata_t* find_right(metadata_t* given) { //assumes given is not in the size_list
//     metadata_t *current = size_list;
//     while (current != NULL) {
//         if(given->size < current->size) {
//             return current;
//         }

//         current = current->next;
//     }

//     return NULL;
// }

static metadata_t* find_left(metadata_t *given) { //assumes given is not in the size_list
    if(size_list == NULL || size_list->size > given->size) {
        return NULL;
    }
    metadata_t *current = size_list;

    while (current->next != NULL && current->next->size < given->size) {
        current = current->next;
    }

    return current;
}

static void add_to_size_list(metadata_t *add_block) {
    if(size_list == NULL) {
        size_list = add_block;
        size_list->next = NULL;
        return;
    }
    metadata_t *left = find_left(add_block);

    if(left == NULL) {
        add_block->next = size_list;
        size_list = add_block;
        return;
    }

    add_block->next = left->next;
    left->next = add_block;
}

static void remove_from_size_list(metadata_t *remove_block) {
    if(size_list == remove_block) {
        size_list = remove_block->next;
        return;
    }
    metadata_t *current = size_list;
    while (current != NULL) {
        if (current->next == remove_block) {
            current->next = remove_block->next;
            return;
        }

        current = current->next;
    }
}

static void merge(metadata_t* left, metadata_t* right) {
    left->size += right->size + TOTAL_METADATA_SIZE;
}

static metadata_t *getMerged(metadata_t* check) {
    metadata_t *current = size_list;
    while (current != NULL) {
        metadata_t *next = current->next;
        void *nextSpace =
            (uint8_t *)current + current->size + TOTAL_METADATA_SIZE;
        if (check == nextSpace) {
            remove_from_size_list(current);
            merge(current, check);
            check = current;
            check->next = NULL;
        }
        nextSpace = (uint8_t *)check + check->size + TOTAL_METADATA_SIZE;

        if (current == nextSpace) {
            remove_from_size_list(current);
            merge(check, current);
        }

        current = next;
    }

    return check;
}

/**
 * @param block = the block to split
 * @param size = the size requested by the user
**/
static metadata_t *split_block(metadata_t *block, size_t size) {
    remove_from_size_list(block);
    size_t splitSize = block->size - size - TOTAL_METADATA_SIZE;
    metadata_t *newBlock = (metadata_t *)((uint8_t *)block + splitSize + TOTAL_METADATA_SIZE);
    block->next = NULL;
    block->size = splitSize;
    set_canary(block);
    add_to_size_list(block);

    newBlock->size = size;
    newBlock->next = NULL;

    return newBlock;
}

static metadata_t *getNewMemory(void) {
    metadata_t *newMemory = my_sbrk(SBRK_SIZE);
    if(newMemory == NULL) {
        return NULL;
    }
    newMemory->size = SBRK_SIZE - TOTAL_METADATA_SIZE;
    newMemory->next = NULL;

    return newMemory;
}

void *my_malloc(size_t size) {
    my_malloc_errno = NO_ERROR;
    if(size == 0) {
        my_malloc_errno = NO_ERROR;
        return NULL;
    }
    if(size > SBRK_SIZE - TOTAL_METADATA_SIZE) {
        my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
        return NULL;
    }

    metadata_t *current = size_list;
    while(current != NULL) {
        if(current->size == size) {
            remove_from_size_list(current);
            current->next = NULL;
            set_canary(current);
            return (current + 1);
        }

        if(current->size - MIN_BLOCK_SIZE > size) {
            current = split_block(current, size);
            set_canary(current);
            return (current + 1);
        }
        current = current->next;
    }

    metadata_t *newMemory = getNewMemory();
    if(newMemory == NULL) {
        my_malloc_errno = OUT_OF_MEMORY;
        return NULL;
    }
    newMemory = getMerged(newMemory);
    add_to_size_list(newMemory);

    return my_malloc(size);
}

/* REALLOC
 * See PDF for documentation
 */
void *my_realloc(void *ptr, size_t size) {
    if(ptr == NULL) {
        return my_malloc(size);
    }
    metadata_t *block = (metadata_t *)ptr - 1;
    unsigned long *endCanary =
        (unsigned long *)((uint8_t *)(block + 1) + block->size);

    if (block->canary != *endCanary) {
        my_malloc_errno = CANARY_CORRUPTED;
        return NULL;
    }

    if(size == 0) {
        my_free(ptr);
        return NULL;
    }

    void *newMemory = my_malloc(size);
    metadata_t *newMemoryMetadata = (metadata_t *)newMemory - 1;
    size_t copyingSize = block->size > newMemoryMetadata->size ? newMemoryMetadata->size : block->size;
    memcpy(newMemory, ptr, copyingSize);
    my_free(ptr);
    return newMemory;
}

/* CALLOC
 * See PDF for documentation
 */
void *my_calloc(size_t nmemb, size_t size) {
    void *newMemory = my_malloc(nmemb * size);
    if(newMemory == NULL) {
        return NULL;
    }

    metadata_t *block = (metadata_t *)newMemory - 1;

    memset(newMemory, 0, block->size);

    return newMemory;
}

/* FREE
 * See PDF for documentation
 */
void my_free(void *ptr) {
    my_malloc_errno = NO_ERROR;
    if(ptr == NULL) {
        return;
    }
    metadata_t *block = (metadata_t *)ptr - 1;

    unsigned long *endCanary =
        (unsigned long *)((uint8_t *)(block + 1) + block->size);

    if(block->canary != *endCanary) {
        my_malloc_errno = CANARY_CORRUPTED;
        return;
    }

    block = getMerged(block);
    add_to_size_list(block);
}
