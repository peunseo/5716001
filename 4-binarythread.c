#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* right, * left;
	int is_thread;
} TreeNode;

typedef struct ThreadNode {
	int data;
	struct ThreadNode* right, * left;
	int is_thread;
} ThreadNode;

TreeNode* new_node(int data) {
	TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
	new_node->data = data;
	new_node->left = new_node->right = NULL;
	return new_node;
}

TreeNode* GenerateBinaryTree(int inputData[]) {
	TreeNode* root = NULL;

	for (int i = 0; i < 15; i++) {
		if (!root)
			root = new_node(inputData[i]);
		else {
			TreeNode* current = root;
			TreeNode* parent  = NULL;

			while (1) {
				parent = current;
				if (inputData[i] < current->data) {
					current = current->left;
					if (!current) {
						parent->left = new_node(inputData[i]);
						break;
					}
				}
				else {
					current = current->right;
					if (!current) {
						parent->right = new_node(inputData[i]);
						break;
					}
				}
			}
		}
	}
	return root;
}

ThreadNode* new_thread_node(int data) {
	ThreadNode* new_node = (ThreadNode*)malloc(sizeof(ThreadNode));
	new_node->data = data;
	new_node->left = new_node->right = NULL;
	new_node->is_thread = 0;
	return new_node;
}


ThreadNode* GenerateThreadTree(int inputData[]) {
	ThreadNode* root = NULL;
	for (int i = 0; i < 15; i++) {
		if (!root)
			root = new_thread_node(inputData[i]);
		else {
			ThreadNode* current = root;
			ThreadNode* parent = NULL;
			while (1) {
				parent = current;
				if (inputData[i] < current->data) {
					current = current->left;
					if (!current) {
						parent->left = new_thread_node(inputData[i]);
						break;
					}
				}
				else {
					current = current->right;
					if (!current) {
						parent->right = new_thread_node(inputData[i]);
						break;
					}
				}
			}
		}
	}
	return root;
}

// 이진 트리 중위 순회
void BinaryTreeInOrder(TreeNode* root) {
	if (root) {
		BinaryTreeInOrder(root->left);
		printf("%d ", root->data);
		BinaryTreeInOrder(root->right);
	}
}

// 스레드 트리 중위 순회
void ThreadTreeInOrder(ThreadNode* troot) {
	if (troot) {
		ThreadTreeInOrder(troot->left);
		printf("%d ", troot->data);
		ThreadTreeInOrder(troot->right);
	}
}

int main() {
	int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,7 };

	// 이진 트리 노드
	TreeNode* root = GenerateBinaryTree(inputData);
	printf("Binary tree inorder : ");
	BinaryTreeInOrder(root);
	printf("\n");

	// 스레드 트리 노드
	ThreadNode* troot = GenerateThreadTree(inputData);
	printf("Thread tree inorder : ");
	ThreadTreeInOrder(troot);
	printf("\n");

	free(root);
	free(troot);
	return 0;
}