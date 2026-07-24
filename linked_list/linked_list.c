#include "linked_list.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct sll_node {
    void*            data; /* the data the node stores */
    struct sll_node* next; /* the next node in the list */
} sll_node;

/**
 * @brief Checks whether a singly linked list is empty.
 *
 * Determines if the list contains any nodes after the head node.
 *
 * @param head Pointer to the head node of the list.
 * @return true if the list is empty, false otherwise.
 */
static bool _is_empty(sll_node* head);

/**
 * @brief Links two nodes together.
 *
 * Sets the next pointer of the first node to point to the second node.
 *
 * @param n1 Pointer to the first node.
 * @param n2 Pointer to the node that should follow n1.
 */
static void _link_nodes(sll_node* n1, sll_node* n2);

static sll_node* _find_previous(
    sll_node* head,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
);

static void _insert_after(sll_node* current, void* data);

static bool _is_empty(sll_node* head) {
    return (head->next == NULL ? true : false);
}

static void _link_nodes(sll_node* n1, sll_node* n2) { n1->next = n2; }

static sll_node* _find_previous(
    sll_node* head,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
) {

    if (_is_empty(head))
        return NULL;

    sll_node* prev    = head;
    sll_node* current = head->next;

    while (current != NULL) {
        if (comparison_func(current, argc, args))
            return prev;

        prev    = current;
        current = current->next;
    }

    return NULL;
}

static void _insert_after(sll_node* current, void* data) {
    sll_node* new_node = sll_create_node(data);
    _link_nodes(new_node, current->next);
    _link_nodes(current, new_node);
}

// TODO inorder to implement this I might need to malloc again
// void sll_set_data(sll_node* n, void* data) { n->data = data; }
void* sll_get_data(sll_node* n) { return n->data; }
sll_node* sll_get_next(sll_node* n) { return n->next; }

// Node methods
sll_node* sll_create_node(void* data) {
    sll_node* node = (sll_node*)malloc(sizeof(sll_node));

    if (node == NULL)
        return NULL;

    // node->key  = key;
    node->data = data;
    node->next = NULL;

    return node;
}

void sll_append(void* data, sll_node* head) {
    sll_node* new_node = sll_create_node(data);
    sll_node* current  = head;

    while (current->next != NULL) {
        current = current->next;
    }

    _link_nodes(current, new_node);
}

// FIXME right now head is a placeholder
// and is not actually the 1st node.
// This should be changed by creating a list "class"
// void sll_insert_first(void* data, sll_node* head) { _insert_after(head,
// data); }
void sll_insert_first(void* data, sll_node* head) { _insert_after(head, data); }

void sll_insert_after(
    void*     data,
    sll_node* head,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
) {
    sll_node* prev = _find_previous(head, comparison_func, argc, args);
    // list empty or node not found
    if (prev == NULL)
        return;

    sll_node* current = prev->next;
    _insert_after(current, data);
}

void sll_delete_node(
    sll_node* head,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
) {
    sll_node* prev = _find_previous(head, comparison_func, argc, args);

    // list empty or node not found
    if (prev == NULL)
        return;

    sll_node* tmp = prev->next;
    _link_nodes(prev, tmp->next);
    free(tmp);
}

void sll_delete_first(sll_node* head) {
    // check if list is empty
    if (_is_empty(head))
        return;

    sll_node* first = head->next;
    _link_nodes(head, first->next);
    free(first);
}

sll_node* sll_find(
    sll_node* head,
    bool (*comparison_func)(sll_node* node, size_t argc, void* args[]),
    size_t argc,
    void*  args[]
) {
    sll_node* prev = _find_previous(head, comparison_func, argc, args);

    // list is empty or previous node does not exist
    if (prev == NULL)
        return NULL;

    return prev->next;
}
