#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct LinkedStack {
    TreeNode* stack[100];
    int top;
} LinkedStackType;

void init(LinkedStackType* s) {
    s->top = -1;
}

int is_empty(LinkedStackType* s) {
    return s->top == -1;
}

void push(LinkedStackType* s, TreeNode* node) {
    s->stack[++(s->top)] = node;
}

TreeNode* pop(LinkedStackType* s) {
    return s->stack[(s->top)--];
}

TreeNode* create_node(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void PlaceNode(TreeNode* node, int direction, int data) {
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

    PlaceNode(root, 0, 2);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    PlaceNode(root, 1, 9);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right, 1, 13);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

void LinkInOrder(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;

    init(&s);

    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            printf("push(%d) ", nptr->data); // push
            nptr = nptr->left;
        }
        nptr = pop(&s);
        printf("pop(%d) ", nptr->data); // pop
        printf("visit(%d)\n", nptr->data); // visit
        nptr = nptr->right;
    }
}

int main() {
    TreeNode* root = create_node(1);

    GenerateLinkTree(root);
    LinkInOrder(root);

    return 0;
}`