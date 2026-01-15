#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
//structs

//a variable with the name data should exist here
//however I do not know what kind of data should be stored in this list
//so I declare no variable
typedef struct Node
{
	int key;
	struct Node* next;
} Node;

//function declarations
Node* createNode(int key);
void append(int key, Node* head);
void deleteNode(int key, Node* head);
void insertFirst(int key, Node* head);
void deleteFirst(Node* head);
void insertAfter(int k, int key, Node* head);
Node* find(int key, Node* head);
void printList(Node* head);

//helper functions declarations
static int isEmpty(Node* head);
static void linkNodes(Node* n1, Node* n2);
static Node* findPreviousNode(int key, Node* head);
static void insertAfterNode(Node* current, int key);



//Global variables
//declare first node of the list
//Node* head;


//helper function implementations
static int isEmpty(Node* head) { return (head->next == NULL ? 1 : 0); }

static void linkNodes(Node* n1, Node* n2) { n1->next = n2; }

//insert after current
static void insertAfterNode(Node* current, int key)
{
	Node* newNode = createNode(key);
	linkNodes(newNode, current->next);
	linkNodes(current, newNode);
}

//find previous node of the node with the given key
//return NULL if:	list is empty
//					if node with given key not found
static Node* findPreviousNode(int key, Node* head)
{
	if (isEmpty(head))
		return NULL;

	Node* prev = head;
	Node* current = head->next;

	while (current->key != key)
	{
		//if current->next == null and entered while then
		//current->key != key and there are no other nodes to check=>
		//a node with the given key was not found
		if (current->next == NULL)
			return NULL;
		prev = current;
		current = current->next;
	}
	return prev;
}


//function implementations
Node *createNode(int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
		return NULL;	//failed to allocate memory
	else
	{
		node->key = key;
		node->next = NULL;
		return node;
	}
}

//append node to the end of the list
void append(int key, Node* head)
{
	Node* newNode = createNode(key);
	Node *current = head;
	while (current->next != NULL) { current = current->next; }
	linkNodes(current, newNode);
}

void deleteNode(int key, Node* head)
{
	Node *prev = findPreviousNode(key, head);
	if (prev == NULL)	//list empty or node not found
		return;
	Node *tmp = prev->next;
	linkNodes(prev, tmp->next);
	free(tmp);
}

void insertFirst(int key, Node* head) { insertAfterNode(head, key); }

void deleteFirst(Node* head)
{
	//check if list is empty
	if(isEmpty(head))
		return;
	Node* first = head->next;
	linkNodes(head, first->next);
	free(first);
}

//insert after node whose key == k
void insertAfter(int k, int key, Node* head)
{
	Node* prev = findPreviousNode(k, head);
	if(prev == NULL)	//list empty or node not found
		return;
	Node *current = prev->next;
	insertAfterNode(current, key);
}

//find node given its key
Node* find(int key, Node* head)
{
	Node* prev = findPreviousNode(key, head);
	if (prev == NULL)	//list is empty or node with given key not found
		return NULL;
	return prev->next;
}

void printList(Node* head)
{
	Node* current = head;
	while (current->next != NULL)
	{
		printf("%d->", current->key);
		current = current->next;
	}
	printf("NULL\n");
}



int main()
{
	//global variable
	Node* head = createNode(0);

	int i = 1;
	while (i <= 10)
	{
		append(i, head);
		i++;
	}
	printList(head);

	//delete 8
	deleteNode(8, head);
	printList(head);

	//re-insert 8
	insertAfter(7, 8, head);
	printList(head);

	//delete 1
	deleteFirst(head);
	printList(head);
	//re-insert 1;
	insertFirst(1, head);
	printList(head);

	//insert 10
	append(10, head);
	printList(head);

	//I made findPreviousNode static so it is not visible outside of this file
	//insert 7 a 2nd time (after 6)
	/*Node* sevenPrev = findPreviousNode(7, head);
	insertAfterNode(sevenPrev, 7);
	printList(head);*/

}
