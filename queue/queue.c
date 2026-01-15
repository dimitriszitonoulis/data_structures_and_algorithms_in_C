#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

bool is_queue_empty(queue_node* headPtr) { return headPtr == NULL ? true : false; }

/*
Input:
	headPtr: A pointer to pointer to  the head of the queue.
		This is done because the queue might be empty in which case 
		the new element must be placed at the top of the queue as the head.
		IN SORT, the pointer to the head is passed by value in order to be altered if needed.
		
	tailPtr: A pointer to pointer to the tail of the queue. 
			This is done similarly to the headPtr =>
			the tailPtr is passed by value.
	data: The data to be inserted to the queue.
			void* is used so that the data can take any type
Output: 
	None
Logic:
	Allocate memory for the new node
	If the queue is empty place the new node as head
	Else place the new node after the tail at the end of the queue
*/
void enqueue(queue_node** headPtr, queue_node** tailPtr, void* data) {
	queue_node* newPtr = malloc(sizeof(queue_node));

	//check if malloc returned NULL
	if (newPtr == NULL) {
		printf("Not inserted. Memory allocation failed.\n");
		return;
	}

	//assign values to data and nextPtr
	newPtr->data = data;
	newPtr->nextPtr = NULL;

	//if queue empty place newPtr as head
	if (is_queue_empty(*headPtr))
		*headPtr = newPtr;	//pass by value
	else	// if queue not empty place newPtr after the tail of the queue
		(*tailPtr)->nextPtr = newPtr;
	(*tailPtr) = newPtr;	//pass by value
}


/*
Input:
	headPtr: A pointer to pointer to the head of the queue
	tailPtr: A pointer to a pointer to the tail of the queue
Output:
	The data stored at the deleted node
Logic:
	Save the data of the node that is about to be deleted to a void pointer.
	Place the next node as the haed of the queue.

*/
void* dequeue(queue_node** headPtr, queue_node** tailPtr) {
	void* data = (*headPtr)->data;
	queue_node* tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;		//place head->nextPtr as head

	if (*headPtr == NULL) { *tailPtr = NULL; }	//if there was only one node at queue

	free(tempPtr);
	return data;
}

//prints integers
void printQueue(queue_node* currentPtr) {
	if (currentPtr == NULL)
		printf("queue is empty");

	while (currentPtr != NULL) {
		printf("%d -> ", *(int*)currentPtr->data);
		currentPtr = currentPtr->nextPtr;
	}
	printf("NULL\n");
}

int main() {

	queue_node* headPtr = NULL;
	queue_node* tailPtr = NULL;

	for (int i = 0; i < 16; i++) {
		int* value = malloc(sizeof(int));
		if (value != NULL) {
			*value = i;
			enqueue(&headPtr, &tailPtr, value);
		}
	}
	printQueue(headPtr);

	printf("data removed is: %d \n", *(int*)dequeue(&headPtr, &tailPtr));
	printf("data removed is: %d \n", *(int*)dequeue(&headPtr, &tailPtr));
	printf("data removed is: %d \n", *(int*)dequeue(&headPtr, &tailPtr));
	printf("data removed is: %d \n", *(int*)dequeue(&headPtr, &tailPtr));
	
	printQueue(headPtr);
}