#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

//structs
typedef struct BSTNode
{
	int key;
	int data;
	struct BSTNode* parent;
	struct BSTNode* left;
	struct BSTNode* right;
} BSTNode;

//global variables
BSTNode* root;


//FUNCTION DECLARATIONS
//basic functions
BSTNode* createNode(int key, int data);
int find(int key);						//returns the data of the node with the specified key
int insert(int key, int data);
int removeNode(int key);				//returns the data of the node with the specified key and deletes it
int minKeyData();
int maxKeyData();

//traverse functions
void inOrderTraversal(BSTNode* root);
void preOrderTraversal(BSTNode* root);
void postOrderTraversal(BSTNode* root);

//helper functions
static BSTNode* findNode(int key);				//returns the node with the specified key
static BSTNode* findSuccessor(BSTNode* node);
static BSTNode* rmNode(BSTNode* node);				//returns the node with the specified key and deletes it
static int minKeyData();
static int isEmpty();


//function IMPLEMENTATION
BSTNode* createNode(int key, int data)
{
	BSTNode* n = malloc(sizeof(BSTNode));

	if (n == NULL)
		return NULL;
	else
	{
		n->key = key;
		n->data = data;
		n->parent = NULL;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
}

//returns NULL if: node not found or empty tree
int find(int key)
{
	BSTNode* node = findNode(key);
	if (node == NULL || node->key != key)	//is tree empty or node not found?
		return FALSE;
	return node->data;
}

int insert(int key, int data)
{
	printf("__________________________________\n");
	printf("INSERT\n");

	BSTNode* node = createNode(key, data);
	//find node returns the parent of the node if a node with the specified key is not found
	BSTNode* parent = findNode(key);

	if (parent == NULL)	//if tree is empty
	{
		root = node;
		return TRUE;
	}
	//key already in tree
	if (key == parent->key) 
		return FALSE; 
	//insert node at the correct place
	if (key < parent->key)
	{
		parent->left = node;
		printf("put left (Entered 1st if in insert)\n");
	}
	else
	{
		printf("put right (Entered else in insert)\n");
		parent->right = node;
	}
	

	//asssign node's parent
	node->parent = parent;
	printf("after connection\n");
	printf("node = %d\n", node->key);
	printf("parent = %d\n", node->parent->key);

	printf("__________________________________\n");
	return TRUE;
}

//in 1st if it should return NULL instead of FALSE
//it could return void pointer and then typecast it to Node*
//then in the last lines insted of remove data it should return the whole void pointer 
// and not only the on that points to data
static int removeNode (int key)
{
	//search for the node
	BSTNode* node = findNode(key);	//if find() returns null then tree is empty or node not found

	if (node == NULL || node->key != key)	//tree is empty or node with specified key not found
		return FALSE;
	
	//send the found node to rmNode
	BSTNode* removed = rmNode(node);	//rmNode removes the node and returns its data
	
	if (removed != NULL)
	{
		int removedData = removed->data;
		//free(node);		//it is freed in rmNode
		return removedData;
	}

	return FALSE;
}

//if tree is empty it should return null not FALSE
static int minKeyData()
{
	BSTNode* current = root;
	if (current == NULL)	//if tree is empty
		return FALSE;		//something else should be put her but idk
	BSTNode* min = root;
	while (current != NULL)
	{	
		min = current;
		current = current->left;
	}
	return min->data;
}

static int maxKeyData()
{
	BSTNode* current = root;
	if (current == NULL)	//if tree is empty
		return FALSE;		//something else should be put her but idk
	BSTNode* max = root;
	while (current != NULL)
	{
		max = current;
		current = current->right;
	}
	return max->data;
}

int isEmpty() { return (root == NULL ? TRUE : FALSE); }

//removes node from tree and returns it
BSTNode* rmNode(BSTNode* node)
{
	BSTNode n;
	n = *(node);

	//1st case: node has no children
	if (node->left == NULL && node->right == NULL)
	{
		if (node == root)		//remove root
			root = NULL;
		else if (node->key < node->parent->key)	//is node left child?
			node->parent->left = NULL;
		else									//is node right child?
			node->parent->right = NULL;
		node->parent = NULL;	//remove connection with parent

		free(node);
		return &n;
	}

	//2nd case node has 1 child (or 2 children, it easily becomes the same problem as if node had 1 child)
	if (node->left == NULL)	//has right child
	{
		if (node == root)	//is node the root?
		{
			root = node-> right;			//place right child as root
			node->right->parent = NULL;		//remove its parent
		}
		else	//if node is not root
		{
			if (node->key < node->parent->key)	//if node is the left child of its father
				node->parent->left = node->right;
			else								//if node is the right child of its father
				node->parent->right= node->right;
			node->right->parent = node->parent;
		}
	}
	else if (node->right == NULL)	//has left child
	{
		if (node == root)			//is node the root?
		{
			root = node->left;				//place left child as root
			node->left->parent = NULL;		//remove its parent
		}
		else	//if node is not root
		{
			if (node->key < node->parent->key)	//if node is the left child of its father
				node->parent->left = node->left;
			else								//if node is the right child of its father
				node->parent->right = node->left;
		}
	}
	else	//node has 2 children
	{
		BSTNode* successor = findSuccessor(node);
		if (node == root)
			root = successor;
		else
		{
			if (node->key < node->parent->key)	//if node is the left child of its father
				node->parent->left = successor;
			else								//if node is the right child of its father
				node->parent->right = successor;
			successor->parent = node->parent;
		}
	}

	free(node);
	return &n;
}

void inOrderTraversal(BSTNode* root)
{
	if (root != NULL)
	{
		inOrderTraversal(root->left);
		printf("%d ", root->key);
		inOrderTraversal(root->right);
	}
}

void preOrderTraversal(BSTNode* root)
{
	if (root != NULL)
	{
		printf("%d ", root->key);
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}
}

void postOrderTraversal(BSTNode* root)
{
	if (root != NULL)
	{
		postOrderTraversal(root->left);
		postOrderTraversal(root->right);
		printf("%d ", root->key);
	}
}

//returns null if tree is empty
//return the leaf if a node with the specified key is not found
static BSTNode* findNode(int key)
{
	printf("**********************\n");
	printf("FINDNODE\n");
	if (isEmpty()) 
		return NULL;
	BSTNode* current = root;

	while (current->key != key)
	{
		BSTNode* next = current->left;		//visit left 
		if (key >= current->key)		//unless you must visit right child
		{
			printf("if (key >= current->key) = %d >= %d\n", key, current->key);
			next = current->right;
		}
		if (next == NULL)				//if a node with the given key was not found return the leaf
		{
			printf("if next == null\n");
			printf("current = %d\n", current->key);
			printf("**********************\n");
			return current;
		}

		printf("current = %d\n", current->key);
		printf("next = %d\n", next->key);
		
		current = next;
	}
	printf("**********************\n");
	return current;
}

static BSTNode* findSuccessor(BSTNode* node)
{
	BSTNode* succ = node->right;
	while (succ->left != NULL)
		succ = succ->left;
	return succ;
}

int main()
{
	//AUTO TO ARXEIO EINAI INMPLEMENTATION ENOS BST ARA THA XRHSIMOPOIEITHEI WS BIBLIOTHIKI
	//SE ENAN ALLO ARXEIO.
	//SE EKEINO TO ARXEIO EKEI POU THA XREIASTEI TO BST THA DHMHOURGHTHEI TO NODE
	
	//des insert an tree = empty tote aplws bazw to node ws root
	root = createNode(0, 0);
	printf("is root == null: %d\n", root == NULL);
	//int i = 5;
	//for (i = 5; i < 10; i++)
	//{
	//	insert(i, i);
	//	//insert(i / 2, i / 2);
	//}

	//insert nodes 1, 3, 2
	insert(1, 1);
	insert(3, 3);
	insert(2, 2);
	BSTNode* two = findNode(2);
	printf("%d\n", two->key);
	
	printf("In order traversal\n");
	inOrderTraversal(root);
	
	printf("\npre order traversal\n");
	preOrderTraversal(root);

	printf("\npost order traversal:\n");
	postOrderTraversal(root);

	printf("\n");
	printf("\nremove 1 = %d\n", removeNode(1));
	inOrderTraversal(root);


	printf("\nmin = %d\n", minKeyData());
	printf("\max = %d\n", maxKeyData());


	//Node* lc = createNode(1, 1);
	//Node* rc = createNode(2, 2);
	//
	//root->left = lc;
	//root->right = rc;
	//lc->parent = root;
	//rc->parent = root;

	//Node* current = createNode(3, 3);
	//rc->right = current;

	//current->parent = rc;

	//printf("%d\n", current->key);
	//printf("%d\n", current->parent->key);
	//printf("%d\n", current->right->parent->key);
	return 0;
}
