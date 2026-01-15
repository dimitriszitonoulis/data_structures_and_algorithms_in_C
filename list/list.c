#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;			//could use void* data but then typecasting to the desired type is required
	struct Node *next;
} Node;


Node* createNode(int data);
void append(int data, Node* head);		//add last
void deleteNode(int data, Node* head);	//deletes node based on data
void printList(Node* head);


Node *createNode(int data)
{
	Node *node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
		return NULL;
	else
	{
		node->data = data;
		node->next = NULL;
		return node;
	}
}

void append(int data, Node* head)
{
	Node* newNode = createNode(data);
	Node *current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = newNode;
}

void deleteNode(int data, Node* head)
{
	Node* current = head;
	Node* prev = NULL;
	while (current->next != NULL && current->data != data)
	{
		prev = current;
		current = current->next;
	}

	if (current == NULL)
	{
		printf("node not found");
		return;
	}
	if (prev == NULL)
		head = current->next;
	else
		prev->next = current->next;
	free(current);
}

void printList(Node *head)
{
	Node* current = head;
	while (current->next != NULL)
	{
		printf("%d->", current->data);
		current = current->next;
	}

	printf("NULL\n");
}

int main()
{
	Node* head = createNode(1);

	int i = 2;

	while (i <= 10)
	{
		append(i, head);
		i++;
	}

	printList(head);
}
