#pragma once

/*
	Implement queue using a list.
*/
/*
* A simple queue node
* The data to be inserted is stored using a void pointer.
* This way the data can be of any type while the queue only stores a pointer to it.
* This also means that no matter the type each queue node has the same size.
* size of each node = 32 bits (sizeof void*) + sizeof(queue_node*)
* 
* CAUTION should be used when extracting the data as typecasting can lead to tricky to solve bugs
* Also, things get complicated when using arrays (or other structs) 
* as, in the case of arrays, data will take the price only of the first element of the array.
*/
typedef struct queue_node {
	void* data;
	struct queue_node* nextPtr;
} queue_node;

//function declarations
bool is_queue_empty(queue_node* headPtr);
void enqueue(queue_node** headPtr, queue_node** tailPtr, void* value);
void* dequeue(queue_node** headPtr, queue_node** tailPtr);
void printQueue(queue_node* currentPtr);
