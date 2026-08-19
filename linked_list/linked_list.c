#include "linked_list.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sll_node {
    void*            data; /* the data the node stores */
    struct sll_node* next; /* the next node in the list */
} sll_node;

typedef struct sll_list {
    sll_node* head;
    sll_node* tail;
    size_t    size;
} sll_list;

static bool _is_empty(sll_list* list);

static void _link_nodes(sll_node* n1, sll_node* n2);

static sll_node* _create_node(void* data);

static sll_node* _find_previous(
    sll_list* list,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
);

static sll_status _insert_after(sll_node* current, void* data);

static bool _is_empty(sll_list* list) { return list->size == 0; }

static void _link_nodes(sll_node* n1, sll_node* n2) { n1->next = n2; }

static sll_node* _create_node(void* data) {
    sll_node* node = malloc(sizeof *node);

    if (node == NULL)
        return NULL;

    node->data = data;
    node->next = NULL;

    return node;
}

static sll_node* _find_previous(
    sll_list* list,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
) {

    if (_is_empty(list))
        return NULL;

    sll_node* prev    = list->head;
    sll_node* current = list->head->next;

    while (current != NULL) {
        if (comparison_func(current, argc, args))
            return prev;

        prev    = current;
        current = current->next;
    }

    return NULL;
}

static sll_status _insert_after(sll_node* current, void* data) {
    sll_node* new_node = _create_node(data);

    if (data == NULL)
        return SLL_ALLOCATION_ERROR;

    _link_nodes(new_node, current->next);
    _link_nodes(current, new_node);

    return SLL_SUCCESS;
}

sll_list* sll_initialize(void) {

    sll_list* list = malloc(sizeof *list);

    if (list == NULL)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

sll_node* sll_get_head(sll_list* list) { return list->head; }
sll_node* sll_get_tail(sll_list* list) { return list->tail; }
size_t sll_get_size(sll_list* list) { return list->size; }
// What will happen if the previous value has been allocated
// to the heap?
// It should be freed.
// void sll_set_data(sll_node* n, void* data) { n->data = data; }
void* sll_set_data(sll_node* n, void* data) {

    if (n->data == NULL)
        return NULL;

    void* tmp = n->data;
    n->data   = data;
    return tmp;
}
// void sll_set_data(sll_node* node, void* data) {
//     free(node->data);
//     node->data = data;
// }
void* sll_get_data(sll_node* n) { return n->data; }
sll_node* sll_get_next(sll_node* n) { return n->next; }

sll_status sll_append(sll_list* list, void* data) {
    sll_node* new_node = _create_node(data);

    if (new_node == NULL)
        return SLL_ALLOCATION_ERROR;

    if (_is_empty(list)) {
        list->head = new_node;
        list->tail = new_node;
        list->size++;
    } else {
        _link_nodes(list->tail, new_node);
        list->tail = new_node;
        list->size++;
    }

    return SLL_SUCCESS;
}

sll_status sll_insert_first(sll_list* list, void* data) {

    sll_node* new_node = _create_node(data);

    if (new_node == NULL)
        return SLL_ALLOCATION_ERROR;

    if (_is_empty(list)) {
        list->head = new_node;
        list->tail = new_node;
        list->size++;
        return SLL_SUCCESS;
    }

    _link_nodes(new_node, list->head);
    list->head = new_node;
    list->size++;

    return SLL_SUCCESS;
}

sll_status sll_insert_after(
    sll_list* list,
    void*     data,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
) {
    sll_node* prev = _find_previous(list, comparison_func, argc, args);
    // list empty or node not found
    if (prev == NULL) {
        if (_is_empty(list))
            return SLL_LIST_EMPTY;

        return SLL_NODE_NOT_FOUND;
    }

    sll_node*  current = prev->next;
    sll_status res     = _insert_after(current, data);

    if (res == SLL_ALLOCATION_ERROR)
        return SLL_ALLOCATION_ERROR;

    list->size++;
    return SLL_SUCCESS;
}

sll_status sll_delete_node(
    sll_list* list,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
) {

    if (_is_empty(list))
        return SLL_LIST_EMPTY;

    // does the head match?
    if (comparison_func(list->head, argc, args)) {
        return sll_delete_first(list);
    }

    sll_node* prev = _find_previous(list, comparison_func, argc, args);

    // list empty or node not found
    if (prev == NULL)
        return SLL_NODE_NOT_FOUND;

    sll_node* tmp = prev->next;

    if (tmp == list->tail) {
        list->tail = prev;
    }

    _link_nodes(prev, tmp->next);
    free(tmp);
    list->size--;

    return SLL_SUCCESS;
}

sll_status sll_delete_first(sll_list* list) {
    if (_is_empty(list))
        return SLL_LIST_EMPTY;

    sll_node* old_head = list->head;
    list->head         = old_head->next;

    // if list had only 1 node
    if (list->head == NULL) {
        list->tail = NULL;
    }

    free(old_head);
    list->size--;

    return SLL_SUCCESS;
}

sll_node* sll_find(
    sll_list* list,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
) {
    sll_node* prev = _find_previous(list, comparison_func, argc, args);

    // list is empty or previous node does not exist
    if (prev == NULL)
        return NULL;

    return prev->next;
}
