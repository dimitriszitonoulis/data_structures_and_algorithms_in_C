#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>

typedef struct sll_node sll_node;

// Accessor methods:
size_t sll_get_priority(sll_node* n);
void* sll_get_data(sll_node* n);
sll_node* sll_get_next(sll_node* n);

/**
 * @brief Creates a new singly linked list node.
 *
 * Allocates memory for a new node and initializes its key and next pointer.
 *
 * @param key node priority.
 * @param data the data to store.
 *
 * @return Pointer to the newly created node.
 * @return NULL if memory allocation fails.
 */
sll_node* sll_create_node(size_t key, void* data);

/**
 * @brief Appends a node to the end of a singly linked list.
 *
 * Creates a new node and attaches it after the current last node.
 *
 * @param key Node priority.
 * @param data the data to store.
 * @param head Pointer to the head node of the list.
 */
void sll_append(size_t key, void* data, sll_node* head);

/**
 * @brief Inserts a new node at the beginning of the list.
 *
 * Inserts a node immediately after the head node.
 *
 * @param key node_priority
 * @param data the data to store.
 * @param head Pointer to the head node of the list.
 */
void sll_insert_first(size_t key, void* data, sll_node* head);

/**
 * @brief Inserts a new node after a node with a specific key.
 *
 * Searches for the first node containing key k and inserts a new node
 * immediately after it.
 *
 * @param k Key of the existing node.
 * @param key Value to store in the new node.
 * @param data the data to store.
 * @param head Pointer to the head node of the list.
 *
 * @note Does nothing if the target node is not found.
 */
void sll_insert_after(size_t k, size_t key, void* data, sll_node* head);

/**
 * @brief Deletes a node with a specific key from the list.
 *
 * Searches for the first occurrence of the given key and removes that node
 * from the linked list.
 *
 * @param key Key of the node to delete.
 * @param head Pointer to the head node of the list.
 *
 * @note Does nothing if the list is empty or the key is not found.
 */
void sll_delete_node(size_t key, sll_node* head);

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

/**
 * @brief Finds a node with a given key.
 *
 * Searches through the linked list and returns the first node whose key
 * matches the provided value.
 *
 * @param key Key value to search for.
 * @param head Pointer to the head node of the list.
 *
 * @return Pointer to the matching node.
 * @return NULL if the key is not found.
 */
sll_node* sll_find(size_t key, sll_node* head);

#endif
