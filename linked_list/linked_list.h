#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct sll_node {
    int key;
    void* data;
    struct sll_node* next;
} sll_node;

sll_node* sll_create_node(int key);
void sll_append(int key, sll_node* head);
void sll_delete_node(int key, sll_node* head);
void sll_insert_first(int key, sll_node* head);
void sll_delete_first(sll_node* head);
void sll_insert_after(int k, int key, sll_node* head);
sll_node* sll_find(int key, sll_node* head);
void sll_print(sll_node* head);

#endif
