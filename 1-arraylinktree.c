#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

void GenerateArrayTree(int* tree) {
	int list[15] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

	for (int i = 0; i < 15; i++) {
		tree[i] = list[i];
	}

	for (int i = 0; i < 15; i++) {
		printf("%d ", tree[i]);
	}
	printf("\n");
}

void ArrayPreOrder(int* tree, int index, int size) {
	if (index >= size) return; 
	printf("%d ", tree[index]); 
	ArrayPreOrder(tree, 2 * index + 1, size);
	ArrayPreOrder(tree, 2 * index + 2, size); 
}

void ArrayInOrder(int* tree, int index, int size) {
	if (index >= size) return; 
	ArrayInOrder(tree, 2 * index + 1, size); 
	printf("%d ", tree[index]); 
	ArrayInOrder(tree, 2 * index + 2, size);
}

void ArrayPostOrder(int* tree, int index, int size) {
	if (index >= size) return; 
	ArrayPostOrder(tree, 2 * index + 1, size); 
	ArrayPostOrder(tree, 2 * index + 2, size);
	printf("%d ", tree[index]); 
}

void ArrayOrders(int* tree) {
	ArrayPreOrder(tree, 0, 15); // 배열트리 전위
	printf("\n");
	ArrayInOrder(tree, 0, 15); // 배열트리 중위
	printf("\n");
	ArrayPostOrder(tree, 0, 15); // 배열트리 후위
	printf("\n");
}

void PlaceNode(TreeNode** node, int data) {
	*node = (TreeNode*)malloc(sizeof(TreeNode)); 
	(*node)->data = data; 
	(*node)->left = NULL; 
	(*node)->right = NULL; 
}

void GenerateLinkTree(TreeNode** root) {
	PlaceNode(root, 1); // Root node
	PlaceNode(&(*root)->left, 2);
	PlaceNode(&(*root)->right, 9);
	PlaceNode(&(*root)->left->left, 3);
	PlaceNode(&(*root)->left->right, 5);
	PlaceNode(&(*root)->left->right->right, 8);
	PlaceNode(&(*root)->left->right->left, 7);
	PlaceNode(&(*root)->left->left->left, 4);
	PlaceNode(&(*root)->left->left->right, 6);
	PlaceNode(&(*root)->right->left, 10);
	PlaceNode(&(*root)->right->right, 13);
	PlaceNode(&(*root)->right->left->left, 11);
	PlaceNode(&(*root)->right->left->right, 12);
	PlaceNode(&(*root)->right->right->left, 14);
	PlaceNode(&(*root)->right->right->right, 15);
}

void LinkPreOrder(TreeNode* np) {
	if (np != NULL) {
		printf("[% 2d]", np->data); 
		LinkPreOrder(np->left);
		LinkPreOrder(np->right);
	}
}

void LinkInOrder(TreeNode* np) {
	if (np != NULL) {
		LinkInOrder(np->left); 
		printf("[% 2d]", np->data);
		LinkInOrder(np->right); 
	}
}

void LinkPostOrder(TreeNode* np) {
	if (np != NULL) {
		LinkPostOrder(np->left); 
		LinkPostOrder(np->right);
		printf("[% 2d]", np->data); 
	}
}

void LinkOrders(TreeNode* root) {
	LinkPreOrder(root); // 연결트리 전위
	printf("\n");
	LinkInOrder(root); // 연결트리 중위
	printf("\n");
	LinkPostOrder(root); // 연결트리 후위
	printf("\n");
}

int main() {
	int arr[15]; 
	TreeNode* root = NULL;

	GenerateArrayTree(arr);
	GenerateLinkTree(&root);

	ArrayOrders(arr);
	LinkOrders(root);

	return 0;
}