#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Item {
	int key;
	void* data;		//must be typecasted to the desirable data
} Item;


//function declaration
//Item* createItem(int key, void* data);
int ht_insert(Item item, Item hashTable[], size_t size);
int ht_delete(int key, Item item[], size_t size);
Item ht_find(int key, Item item[], size_t size);


//helper function declarations
void ht_initialize(Item* items, size_t size);
static int hash(int key, size_t size);

//function implementation

//Item* createItem(int key, void* data) {
//	Item* i = (Item*)malloc(sizeof(Item));
//	if (i == NULL)
//		return NULL;
//	else {
//		i->key = key;
//		i->data = data;
//		return i;
//	}
//}

//assumes item not NULL
int ht_insert(Item item, Item hashTable[], size_t size) {
	int h = hash(item.key, size);
	int seenPositions = 0;

	while (hashTable[h].data != NULL && seenPositions < size) {
		if (hashTable[h].key == -1) { break; }
		seenPositions++;	
		h = (h + 1) % size;	//go to next position and wrap around if necessary
	}
	if (seenPositions < size) {
		hashTable[h] = item;
		return TRUE;
	}
	return FALSE;
}

//TO DO write declaration
int ht_delete(int key, Item item[], size_t size) {
	int h = hash(key, size);
	int seenPositions = 0;

	while (item[h].data != NULL && seenPositions < size) {
		if (item[h].key == key) {
			//Don't use free, it might be stack memory
			//also placing {-1, NULL} is better 
			//because of how all the other functions are writen
			item[h] = (Item){ -1, NULL };	
			return TRUE;
		}
		seenPositions++;
		h = (h + 1) % size;
	}
	return FALSE;
}

Item ht_find(int key, Item item[], size_t size) {
	int h = hash(key, size);
	int seenPositions = 0;
	while (item[h].data != NULL && seenPositions < size) {	//while not empty position
		if (item[h].key == key)	//if item found
			return item[h];
		//if not found
		seenPositions++;	//to prevent infinite loop if item not found
		h = (h + 1) % size;	//go to next position and wrap around if necessary
	}
	return (Item) { -1, NULL };	//maybe I could return NULL pointer
}

//helper function implementation
static int hash(int key, size_t size) { return key % size; }

void ht_initialize(Item* items, size_t size) {
	for (size_t i = 0; i < size; i++) {
		items[i].key = -1;
		items[i].data = NULL;
	}
}

int main() {
	
	Item a[17];
	int size = sizeof(a) / sizeof(Item);
	
	/*size_t size = 10000;
	Item* a = (Item*)malloc(size * sizeof(Item));*/
	ht_initialize(a, size);

	a[15] = (Item){ 1, "people" };
	a[14].data = "hello";
	printf("a[14].data = %s\n", (char*)(a[14].data));
	printf("a[15].data = %s\n", (char*)(a[15].data));

	//print keys
	for (int i = 0; i < size; i++){
		printf("a[%d].key = %d\n", i, a[i].key);
	}

	//insert into hashtable and check if inserted
	if (ht_insert((Item) { 2, "HELLO" }, a, size))
		printf("inserted into hashtable\n");
	else
		printf("Not inserted in hashtable\n");
	

	printf("a[2] = %s\n", (char*)(a[2].data));
	

	printf("\n\n");
	printf("Hash table keys: \n");
	for (size_t i = 0; i < size; i++)
	{
		if (a[i].data != NULL)
			printf("a[%zu].key = %s\n", i, (char*)(a[i].data));
		else
			printf("a[%zu].key = NULL\n", i);
	}


	Item pos2 = ht_find(2, a, size);
	printf("item with key = 2 has data: %s\n", (char*)(pos2.data));

	if (ht_delete(2, a, size))
		printf("deleted from hashtable\n");
	else
		printf("Not deleted from hashtable\n");

	//print ht just to be sure
	for (size_t i = 0; i < size; i++)
	{
		if (a[i].data != NULL)
			printf("a[%zu].key = %s\n", i, (char*)(a[i].data));
		else
			printf("a[%zu].key = NULL\n", i);
	}

	return 0;
}

