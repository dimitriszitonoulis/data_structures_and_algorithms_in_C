#include "linked_list.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct sll_node {
    size_t           key;  /* the priority of the node in the list */
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
static bool is_empty(sll_node* head);

/**
 * @brief Links two nodes together.
 *
 * Sets the next pointer of the first node to point to the second node.
 *
 * @param n1 Pointer to the first node.
 * @param n2 Pointer to the node that should follow n1.
 */
static void link_nodes(sll_node* n1, sll_node* n2);

/**
 * @brief Finds the node preceding a node with a given key.
 *
 * Searches the linked list for a node containing the specified key
 * and returns the node immediately before it.
 *
 * @param key The key value to search for.
 * @param head Pointer to the head node of the list.
 *
 * @return Pointer to the previous node if found.
 * @return NULL if the list is empty or no node contains the key.
 */
static sll_node* find_previous_node(size_t key, sll_node* head);

/**
 * @brief Inserts a new node after a specified node.
 *
 * Creates a new node containing the given key and inserts it directly
 * after the provided node.
 *
 * @param current node after which the new node will be inserted.
 * @param the data the node stores
 * @param key Value to store in the new node.
 */
static void insert_after_node(sll_node* current, size_t key, void* data);

static bool is_empty(sll_node* head) {
    return (head->next == NULL ? true : false);
}

static void link_nodes(sll_node* n1, sll_node* n2) { n1->next = n2; }

static sll_node* find_previous_node(size_t key, sll_node* head) {
    if (is_empty(head))
        return NULL;

    sll_node* prev    = head;
    sll_node* current = head->next;

    while (current->key != key) {
        // if current->next == null and entered while then
        // current->key != key and there are no other nodes to check=>
        // a node with the given key was not found
        if (current->next == NULL)
            return NULL;

        prev    = current;
        current = current->next;
    }
    return prev;
}

static void insert_after_node(sll_node* current, size_t key, void* data) {
    sll_node* new_node = sll_create_node(key, data);
    link_nodes(new_node, current->next);
    link_nodes(current, new_node);
}

// Accessor methods:
size_t sll_get_priority(sll_node* n) { return n->key; }
void* sll_get_data(sll_node* n) { return n->data; }
sll_node* sll_get_next(sll_node* n) { return n->next; }

// Node methods
sll_node* sll_create_node(size_t key, void* data) {
    sll_node* node = (sll_node*)malloc(sizeof(sll_node));

    // failed to allocate memory
    if (node == NULL)
        return NULL;

    node->key  = key;
    node->data = data;
    node->next = NULL;

    return node;
}

void sll_append(size_t key, void* data, sll_node* head) {
    sll_node* new_node = sll_create_node(key, data);
    sll_node* current  = head;

    while (current->next != NULL) {
        current = current->next;
    }

    link_nodes(current, new_node);
}

void sll_insert_first(size_t key, void* data, sll_node* head) {
    insert_after_node(head, key, data);
}

void sll_insert_after(size_t k, size_t key, void* data, sll_node* head) {
    sll_node* prev = find_previous_node(k, head);
    // list empty or node not found
    if (prev == NULL)
        return;
    sll_node* current = prev->next;
    insert_after_node(current, key, data);
}

void sll_delete_node(size_t key, sll_node* head) {
    sll_node* prev = find_previous_node(key, head);

    // list empty or node not found
    if (prev == NULL)
        return;

    sll_node* tmp = prev->next;
    link_nodes(prev, tmp->next);
    free(tmp);
}

void sll_delete_first(sll_node* head) {
    // check if list is empty
    if (is_empty(head))
        return;

    sll_node* first = head->next;
    link_nodes(head, first->next);
    free(first);
}

sll_node* sll_find(size_t key, sll_node* head) {
    sll_node* prev = find_previous_node(key, head);

    // list is empty or node with given key not found
    if (prev == NULL)
        return NULL;

    return prev->next;
}
