#include <stdio.h>
#include <stdlib.h>


//IMPLEMENTATION OF MAX HEAP

typedef struct Node
{
	int key;
	void* data;	//must typecast to what data is being stored at a node
} Node;

//Basic functions
int isEmpty(int currentSize);
Node* createNode(int key, void* data);
int insert(int key, void* data, Node* heap[], int* currentSizePtr, int maxSize);
void* removeFromHeap(Node* heap[], int* currentSizePtr, int maxSize);

//Helper functions
void trickleUp(Node* heap[], int index, int maxSize);
void trickleDown(Node* heap[], int index, int maxSize);
int isHeap(Node* heap[], int maxSize, int parent);

int isEmpty(int currentSize) { return currentSize == 0; }

Node* createNode(int key, void* data) {
	Node* n = (Node*)malloc(sizeof(Node));
	if (n == NULL)
		return NULL;
	else{
		n->key = key;
		n->data = data;
		return n;
	}
}

//return 0 if problem else 1
int insert(int key, void* data, Node* heap[], int* currentSizePtr, int maxSize) {
	if (*(currentSizePtr) == maxSize) return 0;

	Node* newNode = createNode(key, data);
	heap[*(currentSizePtr)] = newNode;					//place newNode at the last position of the heap
	trickleUp(heap, (*(currentSizePtr))++, maxSize);	//increase currentSize by reference
	return 1;
}

//return the data of the root of the heap
void* removeFromHeap(Node* heap[], int* currentSizePtr, int maxSize) {
	Node* root = heap[0];					//save root
	heap[0] = heap[(*(currentSizePtr))--];	//place last item as root & increase currentSize by reference
	trickleDown(heap, 0, *currentSizePtr);
	void* data = root->data;	//return the data of root
	free(root);
	return data;
}

//trickle up Node* at heap[currentSize]
void trickleUp(Node* heap[], int index, int maxSize) {
	int parent = (index - 1) / 2;	//find parent of index
	Node* bottom = heap[index];		//save the node at the bottom

	//while parent < index and index not root move parent down
	while (index > 0 && heap[parent]->key < bottom->key) {
		heap[index] = heap[parent];	//move parent down
		index = parent;				//go to parent
		parent = (parent - 1) / 2;
	}
	heap[index] = bottom;
}

void trickleDown(Node* heap[], int index, int currentSize) {
	int largerChild;
	Node* top = heap[index];	//save top of subtree that starts from index
	
	//repeat until reaching level before last
	while (index < currentSize / 2) {	//node has at least 1 child
		int leftChild = 2 * index + 1;
		int rightChild = leftChild + 1;
		
		largerChild = leftChild;	//assign left child as larger child

		if (rightChild >= currentSize)	break;	//check if right is out of bounds

		if (heap[leftChild]->key < heap[rightChild]->key)	//find larger child
			largerChild = rightChild;

		if (top->key >= heap[largerChild]->key)	break;

		heap[index] = heap[largerChild];	//shift child up
		index = largerChild;				//move down
	}
	heap[index] = top;	//place top at index
}

//checks if heap[] is max heap
//Gia kapoio logo den briskei pant to 1o paradeigma gia to opoio den isxyei o soros
int isHeap(Node* heap[], int maxSize, int parent) {
	int left = 2 * parent + 1;
	int right = left + 1;

	/*
	printf("----------------------------------------\n");
	//to see in which recursion call we are on
	static int rec = 0;
	printf("recursion call is: %d\n", rec++);

	//to see parent, left child and right child
	printf("parent = %d, heap[parent] = %d\n", parent, heap[parent]->key);
	
	if (left < maxSize)
		printf("left = %d, heap[left]->key = %d\n", left, heap[left]->key);
	else
		printf("left > maxSize");

	if (right < maxSize)
		printf("right = %d, heap[right]->key = %d\n", right, heap[right]->key);
	else
		printf("right = maxSize\n");

	*/

	//maybe a similar check for left is necessary
	if (right > maxSize) {	//if reached the end of the heap with no problems
		printf("is max heap\n");
		return 1;
	}
	if (heap[parent]->key < heap[left]->key) {
		printf("Not heap\n");
		printf("%d < %d\n", heap[parent]->key, heap[left]->key);
		return 0;
	}
	if (heap[parent]->key < heap[right]->key) {
		printf("Not heap\n");
		printf("%d < %d\n", heap[parent]->key, heap[right]->key);
		return 0;
	}

	isHeap(heap, maxSize, left);
	isHeap(heap, maxSize, right);
}

int main() {

	Node* heap[16];
	int maxSize = sizeof(heap) / sizeof(heap[0]);
	int currentSize = 0;

	int i, j;
	printf("Heap:\n");
	for (i = 0; i < maxSize; i++) {
		for (j = 0; j < currentSize; j++)	//to print the heap after each insertion
			printf("%d, ", (heap[j]->key));
		printf("\n");
		insert(i, &i, heap, &currentSize, maxSize);
	}
	isHeap(heap, maxSize, heap[0]->key);


//Test if isHeap works
/*
//---------------------------------------------------------------------------------
	Node* a[16];
	int mx = sizeof(heap) / sizeof(heap[0]);
	int cr = 0;
	printf("a:\n");
	for (i = 0; i < mx; i++) {
		int j = 0;
		while (j < i) {
			printf("%d, ", (a[j]->key));
			j++;
		}
		printf("\n");
		Node* n = createNode(i, &i);
		a[i] = n;
	}

	printf("parent = %d\n", a[0]->key);
	printf("left = %d, right = %d\n", 2 * a[0]->key + 1, a[0]->key + 2);
	isHeap(a, mx, a[0]->key);
//---------------------------------------------------------------------------------
*/

	return 0;
}