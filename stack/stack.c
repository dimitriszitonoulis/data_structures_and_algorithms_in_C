#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stackNode {
	void* data;
	struct stackNode* nextPtr;
} stackNode;

bool is_stack_empty(stackNode* topPtr);
void push(stackNode** topPtr, void* data);
void* pop(stackNode** topPtr);
void printStack(stackNode* currentPtr);

bool is_stack_empty(stackNode* topPtr) { return topPtr == NULL ? true : false; }

void push(stackNode** topPtr, void* data) {
	stackNode* newPtr = malloc(sizeof(stackNode));

	if (newPtr != NULL) {
		newPtr->data = data;
		newPtr->nextPtr = *topPtr;	//connect newPtr with the top
		*topPtr = newPtr;			//place newPtr at the top
	}
	else
		printf("stack overflow");
}

void* pop(stackNode** topPtr) {
	stackNode* tempPtr = *topPtr;
	void* popValue = (*topPtr)->data;
	*topPtr = (*topPtr)->nextPtr;	//top points to next node from top
	free(tempPtr);
	return popValue;
}

void printStack(stackNode* currentPtr) {

	if (currentPtr == NULL) {
		printf("stack is empty\n");
		return;
	}
	while (currentPtr != NULL) {
		printf("%d -> ", currentPtr->data);
		currentPtr = currentPtr->nextPtr;
	}
	printf("NULL\n");
}

int main() {

	int stack[8];
	int size = sizeof(stack) / sizeof(stack[0]);

	//points to top of stack
	stackNode* stackPtr = NULL;

	for (int i = 0;i < size; i++) {
		push(&stackPtr, i);
	}
	printStack(stackPtr);
	printf("poped value: %d\n", pop(&stackPtr));
	printf("poped value: %d\n", pop(&stackPtr));
	printf("poped value: %d\n", pop(&stackPtr));
	printStack(stackPtr);
}



//int stack[1000];
//
//int* sp;
//
//#define push(sp, n) (*((sp)++) = (n))
//#define pop(sp) (*--(sp))
//
//{
//	sp = stack; /* initialize */
//
//	push(sp, 10);
//	x = pop(sp);
//}