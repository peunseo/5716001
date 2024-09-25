#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;

typedef struct QueueNode {
    element data;
    struct QueueNode* link;
}QueueNode;

typedef struct {
    QueueNode* front, * rear;
    int size;
}QueueType;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(QueueType* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

int is_empty(QueueType* q) {
    return q->size == 0;
}

void enqueue(QueueType* q, element node) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->data = node;
    new_node->link = NULL;

    if (is_empty(q)) {
        q->front = q->rear = new_node;
    }
    else {
        q->rear->link = new_node;
        q->rear = new_node;
    }
    q->size++;
}

element dequeue(QueueType* q) {
    if (is_empty(q)) return NULL;

    QueueNode* temp = q->front;
    element data = temp->data;
    q->front = q->front->link;
    free(temp);
    q->size--;
    return data;
}

int GetSumOfNodes(TreeNode* root) {
    int sum = 0;
    if (root == NULL) return 0;

    QueueType q;
    init(&q);
    enqueue(&q, root);

    while (!is_empty(&q)) {
        TreeNode* current = dequeue(&q);
        sum += current->data;

        if (current->left) enqueue(&q, current->left);
        if (current->right) enqueue(&q, current->right);
    }
    return sum;
}

int GetNumOfNodes(TreeNode* root) {
    int count = 0;
    if (root == NULL) return 0;

    QueueType q;
    init(&q);
    enqueue(&q, root);

    while (!is_empty(&q)) {
        TreeNode* current = dequeue(&q);
        count++;

        if (current->left) enqueue(&q, current->left);
        if (current->right) enqueue(&q, current->right);
    }
    return count;
}

int GetHeightOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int height = 0;
    QueueType q;
    init(&q);
    enqueue(&q, root);
    enqueue(&q, NULL); 

    while (!is_empty(&q)) {
        TreeNode* current = dequeue(&q);

        if (current == NULL) {
            height++;
            if (!is_empty(&q)) {
                enqueue(&q, NULL);
            }
        }
        else {
            if (current->left) enqueue(&q, current->left);
            if (current->right) enqueue(&q, current->right);
        }
    }
    return height;
}

int GetNumOfLeafNodes(TreeNode* root) {
    int leaf_count = 0;
    if (root == NULL) return 0;

    QueueType q;
    init(&q);
    enqueue(&q, root);

    while (!is_empty(&q)) {
        TreeNode* current = dequeue(&q);

        if (current->left == NULL && current->right == NULL) {
            leaf_count++;
        }

        if (current->left) enqueue(&q, current->left);
        if (current->right) enqueue(&q, current->right);
    }
    return leaf_count;
}
TreeNode* create_node(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void placenode(TreeNode* node, int direction, int data) {
    if (node == NULL) return;

    TreeNode* new_node = create_node(data);
    if (direction == 0) {
        node->left = new_node;
    }
    else {
        node->right = new_node;
    }
}

void GenerateLinkTree(TreeNode* root) {
    if (root == NULL) return;

    placenode(root, 0, 2);
    placenode(root->left, 0, 3);
    placenode(root->left->left, 0, 4);
    placenode(root->left->left, 1, 6);
    placenode(root->left, 1, 5);
    placenode(root->left->right, 0, 7);
    placenode(root->left->right, 1, 8);

    placenode(root, 1, 9);
    placenode(root->right, 0, 10);
    placenode(root->right->left, 0, 11);
    placenode(root->right->left, 1, 12);
    placenode(root->right, 1, 13);
    placenode(root->right->right, 0, 14);
    placenode(root->right->right, 1, 15);
}

main() {
    TreeNode* root = create_node(1);

    GenerateLinkTree(root);

    printf("Sum of nodes : %d\n", GetSumOfNodes(root));
    printf("Number of nodes: %d\n", GetNumOfNodes(root));
    printf("Height of tree : %d\n", GetHeightOfNodes(root));
    printf("Number of leaf nodes: %d\n", GetNumOfLeafNodes(root));

	return 0;
}