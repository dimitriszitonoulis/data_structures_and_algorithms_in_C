#include "linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
static sll_node* find_previous_node(int key, sll_node* head);

/**
 * @brief Inserts a new node after a specified node.
 *
 * Creates a new node containing the given key and inserts it directly
 * after the provided node.
 *
 * @param current Node after which the new node will be inserted.
 * @param key Value to store in the new node.
 */
static void insert_after_node(sll_node* current, int key);

static bool is_empty(sll_node* head) {
    return (head->next == NULL ? true : false);
}

static void link_nodes(sll_node* n1, sll_node* n2) { n1->next = n2; }

static sll_node* find_previous_node(int key, sll_node* head) {
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

static void insert_after_node(sll_node* current, int key) {
    sll_node* new_node = sll_create_node(key);
    link_nodes(new_node, current->next);
    link_nodes(current, new_node);
}

sll_node* sll_create_node(int key) {
    sll_node* node = (sll_node*)malloc(sizeof(sll_node));

    // failed to allocate memory
    if (node == NULL)
        return NULL;

    node->key  = key;
    node->next = NULL;
    return node;
}

void sll_append(int key, sll_node* head) {
    sll_node* newsll_node = sll_create_node(key);
    sll_node* current     = head;

    while (current->next != NULL) {
        current = current->next;
    }

    link_nodes(current, newsll_node);
}

void sll_insert_first(int key, sll_node* head) { insert_after_node(head, key); }

void sll_insert_after(int k, int key, sll_node* head) {
    sll_node* prev = find_previous_node(k, head);
    // list empty or node not found
    if (prev == NULL)
        return;
    sll_node* current = prev->next;
    insert_after_node(current, key);
}

void sll_delete_node(int key, sll_node* head) {
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

sll_node* sll_find(int key, sll_node* head) {
    sll_node* prev = find_previous_node(key, head);

    // list is empty or node with given key not found
    if (prev == NULL)
        return NULL;

    return prev->next;
}

void sll_print(sll_node* head) {
    sll_node* current = head;
    while (current->next != NULL) {
        printf("%d->", current->key);
        current = current->next;
    }
    printf("NULL\n");
}
