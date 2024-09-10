#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

void GenerateArrayTree(int* tree) {
	int list[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

	for (int i = 0; i < 15; i++) {
		tree[i]= list[i];
	}
	for (int i = 0; i < 15; i++) {
		printf("%d ", tree[i]);
	}
	printf("\n");
}

void ArrayPreOrder(TreeNode* np) {
	
}

void ArrayInOrder(TreeNode* np) {
	
}

void ArrayPostOrder(TreeNode* np) {
	
}

void ArrayPreOrders(int tree) {
	ArrayPreOrder(tree);
	ArrayInOrder(tree);
	ArrayPostOrder(tree);
}

void PlaceNode(TreeNode* node, int direction, int data){

}

void GenerateLinkTree() {
	PlaceNode(root, 0, 2);

}

void LinkPreOrder(TreeNode* np){
	if (np != NULL) {
		LinkInOrder(np->left);
		printf("[% 2d]", np->data);
		LinkInOrder(np->right);
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

void LinkPreOrders(TreeNode * root) {
	LinkPreOrder(root);
	LinkInOrder(root);
	LinkPostOrder(root);
}

int main() {
	int arr[15];
	TreeNode* root = ;
	n1->data = 1;

	GenerateArrayTree(arr);
	GenerateLinkTree(root);

	ArrayOrders(arr);
	LinkOrders(root);

	return 0;
}