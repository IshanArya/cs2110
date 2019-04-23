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
    unsigned long *endCanary = (block + sizeof(metadata_t) + block->size);
    *endCanary = canary;
}

static metadata_t* find_right(metadata_t* given) { //assumes given is not in the size_list
    metadata_t *current = size_list;
    while (current != NULL) {
        if(given->size < current->size) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

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
    set_canary(left);
}

/**
 * @param block = the block to split
 * @param size = the size requested by the user
**/
static void split_block(metadata_t *block, size_t size) {
    remove_from_size_list(block);
    metadata_t *newBlock = block + size + TOTAL_METADATA_SIZE;
    newBlock->next = NULL;
    newBlock->size = block->size - size - TOTAL_METADATA_SIZE;
    set_canary(newBlock);
    add_to_size_list(newBlock);

    block->size = size;
    block->next = NULL;
    set_canary(block);
}

void *my_malloc(size_t size) {
    int numberOfBytes = sizeof(size) * sizeof(size_t);
    if(numberOfBytes == 0) {
        my_malloc_errno = NO_ERROR;
        return NULL;
    }
    if(numberOfBytes > SBRK_SIZE - TOTAL_METADATA_SIZE) {
        my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
        return NULL;
    }

    metadata_t *current = size_list;
    while(current != NULL) {
        if(current->size == size) {

        }
    }
}

/* REALLOC
 * See PDF for documentation
 */
void *my_realloc(void *ptr, size_t size) {
    UNUSED_PARAMETER(ptr);
    UNUSED_PARAMETER(size);
    return NULL;
}

/* CALLOC
 * See PDF for documentation
 */
void *my_calloc(size_t nmemb, size_t size) {
    UNUSED_PARAMETER(nmemb);
    UNUSED_PARAMETER(size);
    return NULL;
}

/* FREE
 * See PDF for documentation
 */
void my_free(void *ptr) {
    UNUSED_PARAMETER(ptr);
}
