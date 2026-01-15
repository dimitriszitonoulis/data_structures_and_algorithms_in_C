#include <stdio.h>
#include <stdlib.h>
#include <time.h>	//for rng

//function declarations
void bubbleSort(int* a, int size);
void bubbleSortImproved(int* a, int size);
void swap(int* a, int* b);

//functions
void bubbleSort(int* a, int size)
{
	int i, j;

	int reps = 0;

	for (i = size - 1; i >= 1; i--)	//start from end of array
		for (j = 0; j < i; j++) {
			//start from 1st element up to i-th 
			if (*(a + j) > *(a + j + 1))
				swap((a + j), (a + j + 1));
			reps++;
		}

	printf("\nreps = %d (normal bubblesort)\n", reps);
}

void bubbleSortImproved(int* a, int size)
{
	int i, j, isSwapped;
	int reps = 0;

	for (i = size - 1; i >= 1; i--) {	//start from end of array
		
		isSwapped = 0;
		
		for (j = 0; j < i; j++) {		//start from 1st element up to i-th 
			if (*(a + j) > *(a + j + 1)) {
				swap((a + j), (a + j + 1));
				isSwapped = 1;
			}
		}

		if (!isSwapped)	//check if anything was swapped
			break;

		reps++;
	}
	printf("\nreps = %d (improved bubblesort)\n", reps);

}

void swap(int* a, int* b){
	int tmp = *a;
	/*printf("**********************************\n");
	printf("*a = %d\n", *(a));
	printf("*b = %d\n", *(b));
	printf("*tmp = %d\n", tmp);*/

	*a = *b;
	*b = tmp;

	/*printf("*a = %d\n", *(a));
	printf("*b = %d\n", *(b));
	printf("*tmp = %d\n", tmp);

	printf("**********************************\n");*/
}

int main()
{
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

	bubbleSort(a, size);
	bubbleSortImproved(b, size);
	
	printf("\n");
	printf("Sorted array:\n");
	for (i = 0; i < 10; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}

	return 0;
}