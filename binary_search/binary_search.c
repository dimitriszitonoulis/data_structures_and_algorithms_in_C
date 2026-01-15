#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


int binarySearch(int key, int a[], int size);

int binarySearch(int key, int a[], int size) {
	int left = 0;
	int right = size - 1;
	
	if (left >= right) { return -1; }

	while (1) {
		int mid = (left + right) / 2;
		//check if out of bounds
		if (mid >= size) { return -1; }	

		if (key < a[mid])
			right = mid;
		else if (key > a[mid])
			left = mid + 1;
		else
			return mid;
	}
}

int linearSearch(int key, int a[], int size) {
	int i;
	for (i = 0; i < size; i++)
		if (a[i] == key) { return key; }
	return -1;
}

int main() {

	int a[100000];
	int size = sizeof(a) / sizeof(a[0]);
	int i, n;

	for (i = 0; i < size; i++) {
		a[i] = i;
		//printf("a[%d] = %d\n", i, a[i]);
	}

	n = 7;

	if(linearSearch(n, a, size) == n)
		printf("%d is in the array(linear)\n", n);
	else
		printf("%d is in not the array(linear)\n", n);

	/*printf("Enter a number:\n");
	scanf("%d", &n);*/
	
	if (binarySearch(n, a, size) == n)
		printf("%d is in the array(binary)\n", n);
	else
		printf("%d is not in the array(binary)\n", n);
}