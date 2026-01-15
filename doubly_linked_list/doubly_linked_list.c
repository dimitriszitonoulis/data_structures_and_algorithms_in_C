#include <stdio.h>
#include <stdlib.h>

//structs

//a variable with the name data should exist here
//however I do not know what kind of data should be stored in this list
//so I declare no variable
typedef struct Node
{
	int key;
	struct Node* prev;
	struct Node *next;
} Node;

//Global variables
//declare first node of the list
Node *head;
Node *tail;

//declaration of functions
int isEmpty();
void linkToNext(Node* n1, Node* n2);			
void linkToPrev(Node* n1, Node* n2);			
Node* createNode(int key);						
void deleteNode(Node *node);						
void delete(int key);							
void insertFirst(int key);						
void deleteFirst();								
void insertLast(int key);								
void deleteLast();								
void insertAfterNode(Node* current, int key);	
void insertAfter(int k, int key);				
void insertBeforeNode(Node* node, int key);		
void insertBefore(int k, int key);				
//Node* findPreviousNode(int key);
Node* find(int key);							
void printList();

//functions 
int isEmpty() { return (head->next == tail ? 1 : 0); }

//void linkNodes(Node* n1, Node* n2) { n1->next = n2; n2->prev = n1; }

void linkToNext(Node* n1, Node* n2) { n1->next = n2; }

void linkToPrev(Node* n1, Node* n2) { n1->prev = n2; }

Node* createNode(int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

//deletes given node
void deleteNode(Node *node)
{
	if (node == NULL) 
		return;
	linkToNext(node->prev, node->next);
	linkToPrev(node->next, node->prev);
	node->prev = node->next = NULL;
	free(node);
}

//deletes node with the specified key
//uses delete node
void delete(int key)
{
	Node* node = find(key);
	deleteNode(node);
	//does free work or should I also use it here?
}

void insertFirst(int key) { insertAfterNode(head, key); }

void deleteFirst()
{
	if(isEmpty()) { return; }
	Node* first = head->next;
	deleteNode(first);
	//does free work or should I also use it here?
}

void insertLast(int key) { insertBeforeNode(tail, key); }

void deleteLast()
{
	if (isEmpty()) { return; }
	Node* last = tail->prev;
	deleteNode(last);
}
//insert after node
void insertAfterNode(Node *node, int key)
{
	Node* newNode = createNode(key);
	
	linkToPrev(newNode, node);			//node <-- newNode
	linkToNext(newNode, node->next);	//newNode --> (node->next)
	
	linkToNext(node, newNode);			//node --> newNode
	linkToPrev(newNode->next, newNode);	//newNode <-- (newNode->next)
}

//insert after node whose key == k
void insertAfter(int k, int key)
{
	Node* node = find(k);	//find node with k as key
	if(node == NULL)	//list empty or node not found
		return;
	insertAfterNode(node, key);
}


void insertBeforeNode(Node* node, int key)
{
	Node* newNode = createNode(key);
	linkToPrev(newNode, node->prev);			//(node->prev) <-- newNode
	linkToNext(newNode, node);					//newNode --> node
	linkToPrev(node, newNode);					//node --> newNode
	linkToNext(newNode->prev, newNode);			//newNode <-- (newNode->next)
}

void insertBefore(int k, int key)
{
	Node* node = find(k);
	if (node == NULL) return;
	insertBeforeNode(node, key);
}

/*
//find previous node of the node with the given key
//return NULL if:	list is empty
//					if not found node with given key
Node* findPreviousNode(int key)
{
	if (isEmpty())
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
*/

//find node given its key
Node* find(int key)
{
	if (isEmpty())
		return NULL;
	Node* current = head->next;
	while (current->key != key)
	{
		if (current->next == tail)	//if node not found
			return NULL;
		current = current->next;
	}
	return current;
}

void printList()
{
	Node* current = head;
	while (current->next != NULL)
	{
		printf("(%d)<->", current->key);
		current = current->next;
	}
	printf("NULL\n");
}

int main()
{
	//global variables
	head = createNode(0);
	tail = createNode(0);
	linkToNext(head, tail);
	linkToPrev(tail, head);
	//linkNodes(head, tail);
	//head->next = tail;
	//tail->prev = head;

	int i = 1;
	while (i < 10)
	{
		insertLast(i);
		i++;
	}
	printList();

	//delete 8
	delete(8);
	printList();
	//re-insert 8
	insertAfter(7, 8);
	printList();
	//delete 1
	deleteFirst();
	printList();
	//re-insert 1;
	insertFirst(1);
	printList();
	//insert 10
	insertLast(10);
	printList();
	//delete10
	deleteLast();
	printList();

	delete(7);
	printList();

	insertAfter(6, 7);
	printList();
}
