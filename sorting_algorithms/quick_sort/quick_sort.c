#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int a[], int left, int right);			//right = (size of a) - 1
void randomQuickSort(int a[], int left, int right);	
int partition(int a[], int left, int right);
void swap(int* n1, int* n2);
int chooseRandomPivot(int left, int right);

void quickSort(int a[], int left, int right) {
	if (left >= right)	return;		//at most 1 element
	
	int q = partition(a, left, right);
	quickSort(a, left, q);
	quickSort(a, q+1, right);
}

void randomQuickSort(int a[], int left, int right) {
	if (left >= right)	return;

	int pivot = chooseRandomPivot(left, right);
	swap(&a[left], &a[pivot]);
	int q = partition(a, left, right);
	randomQuickSort(a, left, q);
	randomQuickSort(a, q+1, right);
}

int partition(int a[], int left, int right) {
	int pivot = a[left];
	int l = left - 1;	//go out of bounds (to the left) by 1
	int r = right + 1;		//go out of bounds (to the right) by 1
	//could put right + 1 but then the parameter right should be = size of a - 1

	while (1) {
		while (a[++l] <= pivot && l < right);	//use ++l instead of l++ because I went out of bound before
		while (a[--r] > pivot && r > left);
		if (l < r) swap(&a[l], &a[r]);
		else return r;
	}
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//choose randomly between a and b
int chooseRandomPivot(int left, int right) {
	srand(time(NULL));
	return rand() % (right + left -1) + left;
}

int main() {
	srand(time(NULL));
	int a[16];
	int i;
	int size = sizeof(a) / sizeof(a[0]);

	printf("Unsorted Array:\n");
	for (i = 0; i < size; i++) {
		a[i] = rand() % size;
		printf("a[%d] = %d\n", i, a[i]);
	}
	printf("\n");

	quickSort(a, 0, size);

	printf("Sorted Array:\n");
	for (i = 0; i < size; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}
}