#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

struct node {
	int data;
	struct node* left;
	struct node* right;
};

struct node* newNode (int data);
struct node* insert (struct node* node, int data);
struct node* build123 ();
void printTree (struct node* node);
bool lookup (struct node* node, int data);
int size (struct node* node);
int maxDepth (struct node* node);
int minValue (struct node* node);
int maxValue (struct node* node);
bool hasPathSum (struct node* node, int sum);
void printPaths (struct node* node);
void printPathsRecur (struct node* node, int path[], int pathLen);
void mirror (struct node* node);
void printBFS (struct node* node);
void doubleTree (struct node* node);
bool sameTree (struct node* a, struct node* b);
int countTrees (int numKeys);
bool isBSTRecur (struct node* node, int min, int max);
bool isBST (struct node* node);
struct node* treeToList (struct node* node);
struct node* append (struct node* a, struct node* b);
void PrintList (struct node* head);

int main () {
	struct node* root = build123 ();
	//struct node* root2 = build123 ();
	//printTree (root);
	//cout << lookup (root, 10) << endl;
	//cout << size(root) << endl;
	//cout << maxDepth(root) << endl;
	//cout << minValue(root) << endl;
	//cout << maxValue(root) << endl;
	//cout << hasPathSum (root, 23) << endl;
	//printPaths (root);
	//mirror (root);
	//doubleTree (root);
	//printBFS(root);
	//cout << sameTree (root1, root2) << endl;
	//cout<< countTrees (2) << endl;
	//cout << isBST (root2) << endl;
	struct node* head = treeToList (root);
	PrintList (head);
	int ch = _getch();
}

struct node* newNode (int data) {
	struct node* node = new (struct node);
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

struct node* insert (struct node* node, int data) {
	if (node == NULL) {
		return (newNode (data));
	}

	if (data <= node->data) {
		node->left = insert (node->left, data);
	}else {
		node->right = insert (node->right, data);
	}
	return (node);
}

struct node* build123 () {
	struct node* root = NULL; 
	root = insert (root, 5);
	root = insert (root, 4);
	root = insert (root, 8);
	root = insert (root, 3);
	root = insert (root, 6);
	root = insert (root, 9);
	/*
	root = newNode (8);
	root->left = newNode (7);
	root->right = newNode (8);
	*/
	return (root);
}

void printTree (struct node* node) {
	if (node == NULL) {
		return;
	}else {
		cout << node->data << endl;
		printTree(node->left);
		printTree(node->right);
	}
}

bool lookup (struct node* node, int data) {
	if (node == NULL) {
		return (false);
	} else {
		if (node->data == data) {
			return (true);
		}
		else {
			if (node->data < data)
				return (lookup (node->left, data));
			else
				return (lookup (node->right, data));
		}
	}
}

int size (struct node* node) {
	if (node == NULL)
		return (0);
	else {
		int numNodes = 1 + size (node->left) + size (node->right);
		return (numNodes);
	}
}

int maxDepth (struct node* node) {
	if (node == NULL) {
		return (0);
	} else {
		int depth = 1 + max (maxDepth(node->left), maxDepth (node->right));
		return (depth);
	}
}

int minValue (struct node* node) {
	if (node->left == NULL)
		return (node->data);
	else 
		minValue (node->left);
}

int maxValue (struct node* node) {
	while (node->right != NULL) {
		node = node->right;
	}
	return (node->data);
}

bool hasPathSum (struct node* node, int sum) {
	if (node == NULL) {
		return (sum == 0);
	} else {
		bool slt = hasPathSum(node->left, sum - node->data);
		bool srt = hasPathSum(node->right, sum - node->data);
		return (slt || srt);
	}
}

void printPaths (struct node* node) {
	int path[1000];
	printPathsRecur(node, path, 0);
}

void printPathsRecur (struct node* node, int path[], int pathLen) {
	if (node == NULL) {
		return;
	}
	path[pathLen] = node->data;
	pathLen++;
	if (node->left == NULL && node->right == NULL) {
		for (int iter=0; iter< pathLen; iter++)
			cout<< path[iter] << '\t';
		cout<<endl;
	}else {
		printPathsRecur (node->left, path, pathLen);
		printPathsRecur (node->right, path, pathLen);
	}
}

void mirror (struct node* node) {
	if (node == NULL) return;

	mirror (node->left);
	mirror (node->right);

	struct node* temp = node->left;
	node->left = node->right;
	node->right = temp;

}

void printBFS (struct node* node) {
	queue<struct node*> Q;
	struct node* current;
	int print[1000];
	int count = 0;
	int numZeros = 0;
	int level = 1;
	int limit = 1;
	int levCount = 0;

	struct node dummy;
	dummy.data=0;
	dummy.left = NULL;
	dummy.right = NULL;

	Q.push(node);
	while (!Q.empty()) {
		current = Q.front();
		Q.pop();
		print[count++] = current->data;

		if (current->data != 0) {
			if (current->left != NULL) Q.push(current->left);
			else Q.push(&dummy);

			if (current->right != NULL) Q.push(current->right);
			else Q.push(&dummy);
		}
	}

	for (int iter=0; iter<count; iter++) {
		cout<<print[iter]<<'\t';

		levCount++;
		if (print[iter] == 0)
			numZeros++;
		if (levCount == limit) {
			cout<<endl;
			numZeros = 2*numZeros;
			limit = pow(2.0, level)-numZeros;
			level++;
			levCount = 0;
		}
	}
}

void doubleTree (struct node* node) {
	if (node == NULL) return;

	struct node* duplicate = newNode(node->data);
	struct node* temp = node->left;
	node->left = duplicate;
	duplicate->left = temp;
	doubleTree (duplicate->left);
	doubleTree (node->right);
}

bool sameTree (struct node* a, struct node* b) {
	if (a == NULL && b == NULL)
		return (true);
	else {
		if (a != NULL && b != NULL)
			return (a->data == b->data && sameTree(a->left, b->left) && sameTree(a->right, b->right));
		else
			return (false);
	}
}

int countTrees (int numKeys) {
	int numTrees = 0;
	if (numKeys <= 1)
		return (1);
	else { 
		for (int iter = 1; iter<=numKeys; iter++) {
			numTrees = numTrees + countTrees(iter-1) * countTrees (numKeys-iter);
		}
		return(numTrees);
	}
}

bool isBSTRecur(struct node* node, int min, int max) {
	if (node == NULL)
		return (true);
	else {
		bool leftTree = isBSTRecur(node->left, min, node->data);
		bool rightTree = isBSTRecur(node->right, node->data+1, max);
		bool selfTree = (min <= node->data && node->data < max);
		return (leftTree && rightTree && selfTree);
	}
}

bool isBST (struct node* node) {
	return (isBSTRecur(node, INT_MIN, INT_MAX));
}

struct node* append (struct node* a, struct node* b) {
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	else {
		struct node* aLast = a->left;
		struct node* bLast = b->left;

		aLast->right = b;
		a->left = bLast;
		b->left = aLast;
		bLast->right = a;
		return (a);
	}

}

struct node* treeToList (struct node* node) {
	struct node* leftList = NULL;
	struct node* rightList = NULL;
	if (node->left != NULL) {
		leftList = treeToList (node->left);
	}
	if (node->right != NULL) {
		rightList = treeToList (node->right);
	}
	node->left = node; node->right = node;
	struct node* partialList = append(leftList, node);
	return (append(partialList, rightList));

}

void PrintList (struct node* head) {
	struct node* current = head;

	while (current != NULL) {
		cout << current->data << endl; 
		current = current->right;
		if (current == head) 
			break;
	}

}