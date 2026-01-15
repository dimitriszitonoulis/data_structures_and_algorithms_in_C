#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

//structs
typedef struct Node
{
	//if a node is null then its key, data and height cannot be accesse
	int key;
	void* data;
	int height;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
}Node;

//FUNCTION DECLARATION
//basic functions
Node* createNode(int key, void* data);
Node* insertAVL(Node* newNode, Node* root);
Node* findNode(int key, Node* root);

//helper functions
static int getNodeHeight(Node* n);
//static void fixHeight(Node* n);
static Node* leftRotation(Node* k2);
static Node* rightRotation(Node* k1);
static Node* leftRightRotation(Node* k3);
static Node* rightLeftRotation(Node* k1);

//FUNCTION IMPLEMENTATION
//Basic functions
Node* createNode(int key, void* data) {
	Node* n = (Node*)malloc(sizeof(Node));
	if (n == NULL)
		return NULL;
	else {
		n->key = key;
		n->data = data;
		n->height = 0;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
}

Node* findNode(int key, Node* root) {
	if (root == NULL)	return NULL;

	if (key < root->key)
		return findNode(key, root->left);
	else if (key > root->key)
		return findNode(key, root->right);
	else
		return root;
}

//helper function
static int getNodeHeight(Node* n) { 
	if (n == NULL) { return -1; }
	return n->height; 
}


//static void fixHeight(Node* n) {
//	if (getNodeHeight(n->left) > getNodeHeight(n->right))
//		n->height = getNodeHeight(n->left) + 1;
//	else if (getNodeHeight(n->left) < getNodeHeight(n->right))
//		n->height = getNodeHeight(n->right) + 1;
//}

//Parameter: node to be rotated with its left child
//return root of subtree (helps for double rotation)
static Node* leftRotation(Node* k2) {
	Node* k1 = k2->left;
	//fix connections
	k2->left = k1->right;
	k1->right = k2;

	
	//fix k1 and k2 heights
	//For k2:
	//if height of leftChild > rightChild then k2 height = leftChild + 1
	//else k2 height = rightChild + 1
	if (getNodeHeight(k2->left) > getNodeHeight(k2->right))
		k2->height = getNodeHeight(k2->left) + 1;
	else k2->height = getNodeHeight(k2->right) + 1;

	//same for k1
	if (getNodeHeight(k1->left) > getNodeHeight(k1->right))
		k1->height = getNodeHeight(k1->left) + 1;
	else k1->height = getNodeHeight(k2->right) + 1;

	return k1;
}

//Parameter: node to be rotated with its right child
//return root of subtree (helps for double rotation)
static Node* rightRotation(Node* k1) {
	Node* k2 = k1->right;
	//fix connections
	k1->right = k2->left;
	k2->left = k1;
	//fix heights (ORDER OF FUNCTION CALLS MATTERS -k1 is is child of k2-)
	
	
	if (getNodeHeight(k1->left) > getNodeHeight(k1->right))
		k1->height = getNodeHeight(k1->left) + 1;
	else k1->height = getNodeHeight(k1->right) + 1;

	//same for k1
	if (getNodeHeight(k2->left) > getNodeHeight(k2->right))
		k2->height = getNodeHeight(k2->left) + 1;
	else k2->height = getNodeHeight(k2->right) + 1;

	return k2;
}

//Parameter: node to be rotated with the left child of its right child
//first a rightRotation then a leftRotation
static Node* leftRightRotation(Node* k3) {
	k3->left = rightRotation(k3->left);
	return leftRotation(k3);
}
//Parameter: node to be rotated with the right child of its left child
//first a leftRotation then a rightRotation
static Node* rightLeftRotation(Node* k1) {
	k1->right = leftRotation(k1->right);
	return rightRotation(k1);
}

Node* insertAVL(Node* newNode, Node* root) {
	if (root == NULL)	//if AVLtree empty
		root = newNode;
	else {
		int oldkey;
		//insert left
		if (newNode->key < root->key) {
			root->left = insertAVL(newNode, root->left);
			//if AVL condition broken because of left child
			if (getNodeHeight(root->left) - getNodeHeight(root->right) == 2) {
				//if insert at left subtree of left child
				if (newNode->key < root->left->key)	//inserted at left subtree of left child
				{
					oldkey = root->key;
					root = leftRotation(root);
					printf("l rotation: root:%d newRoot:%d\n", oldkey, root->key);
				}
				else 								//inserted at right subtree of left child
				{
					oldkey = root->key;
					root = leftRightRotation(root);
					printf("lr rotation: root:%d newRoot:%d\n", oldkey, root->key);
				}
			}
		}
		//insert right
		else if (newNode->key > root->key) {	
			root->right = insertAVL(newNode, root->right);
			//if AVL condition broken because of right child
			if (getNodeHeight(root->right) - getNodeHeight(root->left) == 2) {
				if (newNode->key > root->right->key)	//inserted at right subtree of right child
				{
					oldkey = root->key;
					root = rightRotation(root);
					printf("r rotation: root:%d newRoot:%d\n", oldkey, root->key);
				}
				else									//inserted at left subtree of left child
				{
					oldkey = root->key;
					root = rightLeftRotation(root);
					printf("rl rotation: root:%d newRoot:%d\n", oldkey, root->key);
				}
			}			
		}
	}
	//fixHeight(root);

	if (getNodeHeight(root->left) > getNodeHeight(root->right))
		root->height = getNodeHeight(root->left) + 1;
	else
		root->height = getNodeHeight(root->right) + 1;

	return root;
}

//preorder traversal of AVL tree
void printTree(Node* root) {
	if (root == NULL) { return; }
	printf("%d ", root->key);
	printTree(root->left);
	printTree(root->right);
}

int main()
{
	int i;
	int j;
	Node* root = createNode(0, &j);
	for (i = 0; i < 16; i++) {
		Node* n = createNode(i, &j);
		root = insertAVL(n, root);
	}
	printTree(root);
	return 0;
}