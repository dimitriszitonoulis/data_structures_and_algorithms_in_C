#include <stdio.h>
#include <stdlib.h>
//for rng
#include <time.h>

void insertionSort(int* a, int size);
void insertionSortImproved(int* a, int size);
void swap(int* a, int* b);

void insertionSort(int* a, int size) {
	int i, j;
	
	for (i = 1; i < size; i++) {
		int tmp = *(a + i);		//save a[i]
		j = i;		//start inner loop from i-th position upf to the 1st
		while (j > 0 && *(a + (j - 1)) >= tmp) {//if a[j-1] > a[i] then move a[j-1] to a[j]
			*(a + j) = *(a + (j - 1));
			j--;
		}
		*(a + j) = tmp;	//place a[i] at the available spot
	}

}

void insertionSortImproved(int* a, int size) {

}

int main()
{
	int i = 0;
	int a[10];
	int b[10];	//same as a (used for testing reps in improved version)
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

	insertionSort(a, size);
	//bubbleSortImproved(b, size);

	printf("\n");
	printf("Sorted array:\n");
	for (i = 0; i < 10; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}

	return 0;
}