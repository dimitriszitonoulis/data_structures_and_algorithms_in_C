#include <stdio.h>
#include <stdlib.h>
#include <time.h>	//for rng

void heapSort(int a[], int size);
void heapify(int a[], int size);
void trickleDown(int index, int a[], int size);

void heapSort(int a[], int size) {
	
	heapify(a, size);	//turn array to heap
	
	int i = size - 1;	//start from last position

	while (i > 0) {		//while not in 1st position
		int tmp = a[i];	
		a[i] = a[0];	//place 1st item in i-th position
		a[0] = tmp;		//place i-th item in 1st position

		trickleDown(0, a, i);	//heap occupies i positions of the array
		i -= 1;
	}
}

//turns a[] into heap
void heapify(int a[], int size) {
	int i;
	for (i = (size - 1) / 2; i >= 0; i--) {
		trickleDown(i, a, size);
	}
}

//starts from index-th level and goes down until top >= a[largerChild]
//or until reaching all the levels except the last one 
void trickleDown(int index, int a[], int size) {

	int top = a[index];		//save top of subtree that starts from index
	
	//start from i-th level
	//go down all the levels except the last one
	while (index < size / 2) {	//node has at least 1 child
		int leftChild = 2 * index + 1;
		int rightChild = leftChild + 1;

		int largerChild = leftChild;	//assign leftChild as largerChild
		if (rightChild < size)			//rightChild exists?
			largerChild = (a[leftChild] < a[rightChild] ? rightChild : leftChild);

		//if root >= a[largerChild], stop
		if (top >= a[largerChild])
			break;

		a[index] = a[largerChild];			//shift child up		
		index = largerChild;				//go down
	}
	a[index] = top;
}

int main() {

	srand(time(NULL));
	int i = 0;
	int a[10];
	int size = sizeof(a) / sizeof(a[0]);

	for (int i = 0; i < size; i++) {
		a[i] = rand() % 10;
	}

	printf("Unsorted array:\n");
	for (i = 0; i < size; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}

	heapSort(a, size);

	printf("\n");
	printf("Sorted array:\n");
	for (i = 0; i < size; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}


	return 0;
}