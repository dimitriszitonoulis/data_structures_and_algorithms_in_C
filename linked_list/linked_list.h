#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct sll_node sll_node;

// Accessor methods:
void* sll_get_data(sll_node* n);
sll_node* sll_get_next(sll_node* n);

/**
 * @brief Creates a new singly linked list node.
 *
 * Allocates memory for a new node and initializes its key and next pointer.
 *
 * @param data the data to store.
 *
 * @return Pointer to the newly created node.
 * @return NULL if memory allocation fails.
 */
sll_node* sll_create_node(void* data);

/**
 * @brief Appends a node to the end of a singly linked list.
 *
 * Creates a new node and attaches it after the current last node.
 *
 * @param key Node priority.
 * @param data the data to store.
 * @param head Pointer to the head node of the list.
 */
void sll_append(void* data, sll_node* head);

/**
 * @brief Inserts a new node at the beginning of the list.
 *
 * Inserts a node immediately after the head node.
 *
 * @param key node_priority
 * @param data the data to store.
 * @param head Pointer to the head node of the list.
 */
void sll_insert_first(void* data, sll_node* head);

void sll_insert_after(void* data, sll_node* head,
                      bool (*comparison_func)(sll_node* node, size_t argc,
                                              void* args[]),
                      size_t argc, void* args[]);

void sll_delete_node(sll_node* head,
                     bool (*comparison_func)(sll_node* node, size_t argc,
                                             void* args[]),
                     size_t argc, void* args[]);

/**
 * @brief Deletes the first node in the list.
 *
 * Removes the first element after the head node.
 *
 * @param head Pointer to the head node of the list.
 *
 * @note Does nothing if the list is empty.
 */
void sll_delete_first(sll_node* head);

sll_node* sll_find(sll_node* head,
                   bool (*comparison_func)(sll_node* node, size_t argc,
                                           void* args[]),
                   size_t argc, void* args[]);

#endif
