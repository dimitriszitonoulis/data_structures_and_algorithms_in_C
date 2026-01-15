#include <stdio.h>
#include <stdlib.h>
#include <time.h> //for rng

//function declarations
void selectionSort(int* a, int size);
void selectionSortImproved(int* a, int size);
void swap(int* a, int* b);

//functions
void selectionSort(int* a, int size) {

	int i, j, min;
	
	for (i = 0; i < size - 1; i++) {
		min = i;
		for (j = i + 1; j < size; j++) {
			if (*(a + j) < *(a + min)) {
				min = j;
			}
		}
		swap((a + i), (a + min));
	}
}

void selectionSortImproved(int* a, int size) {

}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main() {
	int i = 0;
	int a[10];
	int b[10];	//same as a[] (used for testing reps in improved version)
	int size = sizeof(a) / sizeof(a[0]);

	srand(time(NULL));

	for (i = 0; i < 10; i++) {
		a[i] = rand() % 10;
		b[i] = a[i];
	}

	printf("Unsorted array:\n");
	for (i = 0; i < 10; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}

	selectionSort(a, size);
	//bubbleSortImproved(b, size);

	printf("\n");
	printf("Sorted array:\n");
	for (i = 0; i < 10; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}

	return 0;
}