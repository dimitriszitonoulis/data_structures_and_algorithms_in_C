#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct sll_node {
    int key;               /* the priority of the node in the list */
    void* data;            /* the date the node holds, must be typecasted */
    struct sll_node* next; /* the next node in the list */
} sll_node;

/**
 * @brief Creates a new singly linked list node.
 *
 * Allocates memory for a new node and initializes its key and next pointer.
 *
 * @param key Value to store in the node.
 *
 * @return Pointer to the newly created node.
 * @return NULL if memory allocation fails.
 */
sll_node* sll_create_node(int key);

/**
 * @brief Appends a node to the end of a singly linked list.
 *
 * Creates a new node and attaches it after the current last node.
 *
 * @param key Value to store in the new node.
 * @param head Pointer to the head node of the list.
 */
void sll_append(int key, sll_node* head);

/**
 * @brief Inserts a new node at the beginning of the list.
 *
 * Inserts a node immediately after the head node.
 *
 * @param key Value to store in the new first node.
 * @param head Pointer to the head node of the list.
 */
void sll_insert_first(int key, sll_node* head);

/**
 * @brief Inserts a new node after a node with a specific key.
 *
 * Searches for the first node containing key k and inserts a new node
 * immediately after it.
 *
 * @param k Key of the existing node.
 * @param key Value to store in the new node.
 * @param head Pointer to the head node of the list.
 *
 * @note Does nothing if the target node is not found.
 */
void sll_insert_after(int k, int key, sll_node* head);

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
void sll_delete_node(int key, sll_node* head);

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
sll_node* sll_find(int key, sll_node* head);

/**
 * @brief Prints the contents of the linked list.
 *
 * Outputs each node's key in order, followed by NULL.
 *
 * Example output:
 * @code
 * 1->2->3->NULL
 * @endcode
 *
 * @param head Pointer to the head node of the list.
 */
void sll_print(sll_node* head);

#endif
