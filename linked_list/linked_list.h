#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct sll_node sll_node;
typedef struct sll_list sll_list;
typedef enum {
    SLL_SUCCESS = 0,
    SLL_ALLOCATION_ERROR,
    SLL_NODE_NOT_FOUND,
    SLL_LIST_EMPTY
} sll_status;

sll_list* sll_initialize(void);

// Accessor methods:
sll_node* sll_get_head(sll_list* list);
sll_node* sll_get_tail(sll_list* list);
size_t sll_get_size(sll_list* list);
// void sll_set_data(sll_node* n, void* data);
void* sll_get_data(sll_node* n);
sll_node* sll_get_next(sll_node* n);

sll_status sll_append(sll_list* list, void* data);

sll_status sll_insert_first(sll_list* list, void* data);

sll_status sll_insert_after(
    sll_list* list,
    void*     data,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
);

sll_status sll_delete_node(
    sll_list* list,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
);

sll_status sll_delete_first(sll_list* list);

sll_node* sll_find(
    sll_list* list,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
);

#endif
