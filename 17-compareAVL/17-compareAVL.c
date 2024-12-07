#include <stdio.h>
#include <stdlib.h>
#include <time.h>	

int compareCount = 0; // 비교 횟수
int searchCount = 0;  // 탐색 횟수

// 구조체 정의
typedef struct Node {
    int key;
    struct Node* left, * right;
    int height;
}Node;

// 노드 생성
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// 트리 높이 계산
int height(Node* n) { return n ? n->height : 0; }

// 균형 계수 계산
int balance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }

// 오른쪽 회전
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// 왼쪽 회전
Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T = x->left;

    x->left = y;
    y->right = T;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// AVL 삽입
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

// 최소값 노드 찾기
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// AVL 삭제
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

// BST 삽입
Node* bstInsert(Node* node, int key) {
    if (!node) return createNode(key);
    if (key < node->key) node->left = bstInsert(node->left, key);
    else if (key > node->key) node->right = bstInsert(node->right, key);
    return node;
}

// BST 삭제
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

// 탐색
Node* search(Node* root, int data, int* compareCount) {
    (*compareCount)++;  // 비교 횟수 증가
    if (root == NULL || root->key == data) return root;
    (*compareCount)++; 
    if (data < root->key) return search(root->left, data, compareCount);  // 왼쪽 하위 트리 탐색
    return search(root->right, data, compareCount);  // 오른쪽 하위 트리 탐색
}


// AVL Batch
Node* doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;     // A는 0~2
        int B = rand() % 1000;  // B는 0~999
        if (A == 0) root = avlInsert(root, B);  // A가 0이면 B를 추가
        else if (A == 1) root = avlDelete(root, B); // 1이면 삭제  
        else {
            int localCompareCount = 0;
            search(root, B, &localCompareCount);  // 탐색 호출 시 비교 횟수 전달
            compareCount += localCompareCount;  // 전체 비교 횟수에 합산
            searchCount++;  // 탐색 횟수 증가
        }
    }
    return root;
}

// Binary Batch
Node* doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;     // A는 0~2
        int B = rand() % 1000;  // B는 0~999
        if (A == 0) root = avlInsert(root, B);  // A가 0이면 B를 추가
        else if (A == 1) root = avlDelete(root, B); // 1이면 삭제  
        else {
            int localCompareCount = 0;
            search(root, B, &localCompareCount);  // 탐색 호출 시 비교 횟수 전달
            compareCount += localCompareCount;  // 전체 비교 횟수에 합산
            searchCount++;  // 탐색 횟수 증가
        }
    }
    return root;
}

// 메모리 해제
void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// 메인
int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;

    // 과제에서 제시된 Binary Search Tree Batch를 수행한다.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}