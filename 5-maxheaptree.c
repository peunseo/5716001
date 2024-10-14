#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ELEMENTS 1000

// 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left,* right;
    struct TreeNode* parent;
} TreeNode;

// 노드생성 함수
TreeNode* createNode(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        fprintf(stderr, "error\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = new_node->right = new_node->parent = NULL;
    return new_node;
}

int count = 0;
int move = 0;

// 트리 출력 함수
void printTree(TreeNode* root) {
    if (!root) return;

    TreeNode* queue[MAX_ELEMENTS];
    int front = 0, rear = 0, count = 0;

    queue[rear++] = root;
    
    if (count == 0) {
        while (front < rear) {
            TreeNode* current = queue[front++];
            printf("%d ", current->data);

            if (current->left) queue[rear++] = current->left;
            if (current->right) queue[rear++] = current->right;
        }
        printf("\n");
        
    }
    count = 1;
}

// 레벨별 출력 함수
void printLevelOrder(TreeNode* root) {
    if (!root) {
        printf("트리 공백\n");
        return;
    }

    TreeNode* queue[MAX_ELEMENTS];
    int front = 0, rear = 0;

    queue[rear++] = root;

    int currentLevel = 1;
    printf("[%d] ", currentLevel);

    while (front < rear) {
        int levelSize = rear - front;  // 레벨 노드 갯수
        for (int i = 0; i < levelSize; i++) {
            TreeNode* current = queue[front++];
            printf("%d ", current->data);

            if (current->left) queue[rear++] = current->left;
            if (current->right) queue[rear++] = current->right;
        }
        printf("\n");
        currentLevel++;
        if (front < rear) {
            printf("[%d] ", currentLevel);
        }
    }
}

// 최대 힙에 노드를 삽입하는 함수
void heapifyUp(TreeNode* node, TreeNode* root) {
    while (node->parent && node->data > node->parent->data) {
        // 데이터 교환
        int temp = node->data;
        node->data = node->parent->data;
        node->parent->data = temp;
 
        printTree(root);  // 트리 출력
        move++;

        node = node->parent;
    }
}

// 최대 힙에 노드를 삽입하는 함수
void insertMaxHeapNode(TreeNode** root, int key) {
    if (*root == NULL) {
        *root = createNode(key);
        return;
    }

    TreeNode* queue[MAX_ELEMENTS];
    int front = 0, rear = 0;

    queue[rear++] = *root;

    TreeNode* temp = NULL;
    while (front < rear) {
        temp = queue[front++];

        if (temp->left == NULL) {
            temp->left = createNode(key);
            temp->left->parent = temp;
            heapifyUp(temp->left, *root);
            break;
        }
        else {
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL) {
            temp->right = createNode(key);
            temp->right->parent = temp;
            heapifyUp(temp->right, *root);
            break;
        }
        else {
            queue[rear++] = temp->right;
        }
    }
   
}

// 힙 재정렬을 위한 다운 힙 함수
void heapifyDown(TreeNode* node, int* movements, TreeNode* root) {
    while (1) {
        TreeNode* largest = node;
        if (node->left && node->left->data > largest->data)
            largest = node->left;
        if (node->right && node->right->data > largest->data)
            largest = node->right;

        if (largest == node) break;

        // 스왑 함수 대신 직접 데이터를 교환
        int temp = node->data;
        node->data = largest->data;
        largest->data = temp;

        (*movements)++;
        printTree(root);  // 트리 출력
        node = largest;
    }
}

// 최대 힙에서 루트 노드를 삭제하는 함수
void deleteMaxHeapNode(TreeNode** root) {
    if (*root == NULL) return;

    TreeNode* lastNode = *root;
    TreeNode* parent = NULL;

    // 마지막 노드 탐색
    TreeNode* queue[MAX_ELEMENTS];
    int front = 0, rear = 0;
    queue[rear++] = *root;
    while (front < rear) {
        lastNode = queue[front++];
        if (lastNode->left) queue[rear++] = lastNode->left;
        if (lastNode->right) queue[rear++] = lastNode->right;
    }

    int deletedValue = (*root)->data;
    (*root)->data = lastNode->data;

    if (lastNode->parent) {
        if (lastNode->parent->left == lastNode)
            lastNode->parent->left = NULL;
        else
            lastNode->parent->right = NULL;
    }

    free(lastNode);

    // 힙 재정렬
    int movements = 0;
    heapifyDown(*root, &movements, *root);
    printf("노드가 이동된 횟수 : %d\n", movements);
}

// 유저 인터페이스 함수
void runUserInterface(TreeNode** root) {
    while (1) {
        char menu;
        int data;

        printf("\n");
        printf("-------------------\n");
        printf("| i : 노드 추가   |\n");
        printf("| d : 루트 삭제   |\n");
        printf("| p : 레벨별 출력 |\n");
        printf("| c : 종료        |\n");
        printf("-------------------\n\n");
        printf("메뉴 입력 : ");
        scanf_s(" %c", &menu);

        switch (menu) {
        case 'i':
            printf("추가할 값 입력 : ");
            scanf_s("%d", &data);
            insertMaxHeapNode(root, data);
            printf("노드가 이동된 횟수 : %d\n", move);
            move = 0;
            break;
        case 'd':
            deleteMaxHeapNode(root);
            break;
        case 'p':
            printLevelOrder(*root);
            break;
        case 'c':
            printf("프로그램을 종료합니다.\n");
            exit(0);
            break;
        default:
            printf("잘못된 선택입니다.\n");
        }
    }
}

// 트리 전체노드 해제
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// 메인 함수
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 최대 힙트리 생성
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        insertMaxHeapNode(&root, inputData[i]);
    }

    // 유저 인터페이스
    runUserInterface(&root);
    freeTree(root);
    return 0;
}