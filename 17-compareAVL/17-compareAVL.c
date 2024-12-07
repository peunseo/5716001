#include <stdio.h>
#include <stdlib.h>
#include <time.h>	

int compareCount = 0; // �� Ƚ��
int searchCount = 0;  // Ž�� Ƚ��

// ����ü ����
typedef struct Node {
    int key;
    struct Node* left, * right;
    int height;
}Node;

// ��� ����
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Ʈ�� ���� ���
int height(Node* n) { return n ? n->height : 0; }

// ���� ��� ���
int balance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }

// ������ ȸ��
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// ���� ȸ��
Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T = x->left;

    x->left = y;
    y->right = T;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// AVL ����
Node* avlInsert(Node* node, int key) {
    if (!node) return createNode(key);
    if (key < node->key) node->left = avlInsert(node->left, key);
    else if (key > node->key) node->right = avlInsert(node->right, key);
    else return node;

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
    int bal = balance(node);

    if (bal > 1 && key < node->left->key) return rotateRight(node); // LL
    if (bal < -1 && key > node->right->key) return rotateLeft(node);  // RR
    if (bal > 1 && key > node->left->key) { // LR
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bal < -1 && key < node->right->key) { // RL
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

// �ּҰ� ��� ã��
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// AVL ����
Node* avlDelete(Node* root, int key) {
    if (!root) return root;
    if (key < root->key) root->left = avlDelete(root->left, key);
    else if (key > root->key) root->right = avlDelete(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = avlDelete(root->right, temp->key);
    }

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));
    int bal = balance(root);

    if (bal > 1 && balance(root->left) >= 0) return rotateRight(root);
    if (bal > 1 && balance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (bal < -1 && balance(root->right) <= 0) return rotateLeft(root);
    if (bal < -1 && balance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

// BST ����
Node* bstInsert(Node* node, int key) {
    if (!node) return createNode(key);
    if (key < node->key) node->left = bstInsert(node->left, key);
    else if (key > node->key) node->right = bstInsert(node->right, key);
    return node;
}

// BST ����
Node* bstDelete(Node* root, int key) {
    if (!root) return root;
    if (key < root->key) root->left = bstDelete(root->left, key);
    else if (key > root->key) root->right = bstDelete(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = bstDelete(root->right, temp->key);
    }
    return root;
}

// Ž��
Node* search(Node* root, int data, int* compareCount) {
    (*compareCount)++;  // �� Ƚ�� ����
    if (root == NULL || root->key == data) return root;
    (*compareCount)++; 
    if (data < root->key) return search(root->left, data, compareCount);  // ���� ���� Ʈ�� Ž��
    return search(root->right, data, compareCount);  // ������ ���� Ʈ�� Ž��
}


// AVL Batch
Node* doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;     // A�� 0~2
        int B = rand() % 1000;  // B�� 0~999
        if (A == 0) root = avlInsert(root, B);  // A�� 0�̸� B�� �߰�
        else if (A == 1) root = avlDelete(root, B); // 1�̸� ����  
        else {
            int localCompareCount = 0;
            search(root, B, &localCompareCount);  // Ž�� ȣ�� �� �� Ƚ�� ����
            compareCount += localCompareCount;  // ��ü �� Ƚ���� �ջ�
            searchCount++;  // Ž�� Ƚ�� ����
        }
    }
    return root;
}

// Binary Batch
Node* doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;     // A�� 0~2
        int B = rand() % 1000;  // B�� 0~999
        if (A == 0) root = avlInsert(root, B);  // A�� 0�̸� B�� �߰�
        else if (A == 1) root = avlDelete(root, B); // 1�̸� ����  
        else {
            int localCompareCount = 0;
            search(root, B, &localCompareCount);  // Ž�� ȣ�� �� �� Ƚ�� ����
            compareCount += localCompareCount;  // ��ü �� Ƚ���� �ջ�
            searchCount++;  // Ž�� Ƚ�� ����
        }
    }
    return root;
}

// �޸� ����
void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// ����
int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // �������� ���õ� AVL�� ���� 2000ȸ Batch �۾��� �����Ѵ�.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // ������ȸ�ϸ� AVLƮ���� ��������� ��� �����͸� free
    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;

    // �������� ���õ� Binary Search Tree Batch�� �����Ѵ�.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}