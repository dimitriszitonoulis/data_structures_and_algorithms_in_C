#include "linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// helper functions
static int is_empty(sll_node* head);
static void link_nodes(sll_node* n1, sll_node* n2);
static sll_node* find_previous_node(int key, sll_node* head);
static void insert_after_node(sll_node* current, int key);

static int is_empty(sll_node* head) {
    return (head->next == NULL ? true : false);
}

static void link_nodes(sll_node* n1, sll_node* n2) { n1->next = n2; }

// insert after current
static void insert_after_node(sll_node* current, int key) {
    sll_node* new_node = sll_create_node(key);
    link_nodes(new_node, current->next);
    link_nodes(current, new_node);
}

// find previous node of the node with the given key
// return NULL if:	list is empty
//					if node with given key not found
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

// function implementations
sll_node* sll_create_node(int key) {
    sll_node* node = (sll_node*)malloc(sizeof(sll_node));
    if (node == NULL)
        return NULL; // failed to allocate memory
    else {
        node->key  = key;
        node->next = NULL;
        return node;
    }
}

// append node to the end of the list
void sll_append(int key, sll_node* head) {
    sll_node* newsll_node = sll_create_node(key);
    sll_node* current     = head;
    while (current->next != NULL) {
        current = current->next;
    }
    link_nodes(current, newsll_node);
}

void sll_delete_node(int key, sll_node* head) {
    sll_node* prev = find_previous_node(key, head);
    if (prev == NULL) // list empty or node not found
        return;
    sll_node* tmp = prev->next;
    link_nodes(prev, tmp->next);
    free(tmp);
}

void sll_insert_first(int key, sll_node* head) { insert_after_node(head, key); }

void sll_delete_first(sll_node* head) {
    // check if list is empty
    if (is_empty(head))
        return;
    sll_node* first = head->next;
    link_nodes(head, first->next);
    free(first);
}

// insert after node whose key == k
void sll_insert_after(int k, int key, sll_node* head) {
    sll_node* prev = find_previous_node(k, head);
    if (prev == NULL) // list empty or node not found
        return;
    sll_node* current = prev->next;
    insert_after_node(current, key);
}

// find node given its key
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
