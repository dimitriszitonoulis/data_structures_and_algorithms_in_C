#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rQuickSelect(int a[], int left, int right, int k);
int partition(int a[], int left, int right);
void swap(int* a, int* b);
int chooseRandomPivot(int left, int right);

int rQuickSelect(int a[], int left, int right, int k) {
	if (left == right) return (a[left]);
	
	int pivot = chooseRandomPivot(left, right);	//random pivot
	swap(&a[left], &a[pivot]);
	int q = partition(a, left, right);
	int nel = q - left + 1;				//number of elements smaller thn pivot
	if (k <= nel)
		return rQuickSelect(a, left, q, k);	//check left side
	//check right side not for k-th element but for (k-nel)-th element 
	return rQuickSelect(a, q+1, right, k - nel);
}

int partition(int a[], int left, int right) {
	
	int l = left - 1;
	int r = right;
	int pivot = a[left];

	while (1) {
		while (a[++l] < pivot);
		while (a[--r] > pivot);
		if (l < r) swap(&a[l], &a[r]);
		else return r;
	}
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int chooseRandomPivot(int left, int right) {
	srand(time(NULL));
	return rand() % (right + left - 1) + left;
}