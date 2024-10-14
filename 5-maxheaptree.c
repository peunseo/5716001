#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ELEMENTS 1000

// ����ü ����
typedef struct TreeNode {
    int data;
    struct TreeNode* left,* right;
    struct TreeNode* parent;
} TreeNode;

// ������ �Լ�
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

// Ʈ�� ��� �Լ�
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

// ������ ��� �Լ�
void printLevelOrder(TreeNode* root) {
    if (!root) {
        printf("Ʈ�� ����\n");
        return;
    }

    TreeNode* queue[MAX_ELEMENTS];
    int front = 0, rear = 0;

    queue[rear++] = root;

    int currentLevel = 1;
    printf("[%d] ", currentLevel);

    while (front < rear) {
        int levelSize = rear - front;  // ���� ��� ����
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

// �ִ� ���� ��带 �����ϴ� �Լ�
void heapifyUp(TreeNode* node, TreeNode* root) {
    while (node->parent && node->data > node->parent->data) {
        // ������ ��ȯ
        int temp = node->data;
        node->data = node->parent->data;
        node->parent->data = temp;
 
        printTree(root);  // Ʈ�� ���
        move++;

        node = node->parent;
    }
}

// �ִ� ���� ��带 �����ϴ� �Լ�
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

// �� �������� ���� �ٿ� �� �Լ�
void heapifyDown(TreeNode* node, int* movements, TreeNode* root) {
    while (1) {
        TreeNode* largest = node;
        if (node->left && node->left->data > largest->data)
            largest = node->left;
        if (node->right && node->right->data > largest->data)
            largest = node->right;

        if (largest == node) break;

        // ���� �Լ� ��� ���� �����͸� ��ȯ
        int temp = node->data;
        node->data = largest->data;
        largest->data = temp;

        (*movements)++;
        printTree(root);  // Ʈ�� ���
        node = largest;
    }
}

// �ִ� ������ ��Ʈ ��带 �����ϴ� �Լ�
void deleteMaxHeapNode(TreeNode** root) {
    if (*root == NULL) return;

    TreeNode* lastNode = *root;
    TreeNode* parent = NULL;

    // ������ ��� Ž��
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

    // �� ������
    int movements = 0;
    heapifyDown(*root, &movements, *root);
    printf("��尡 �̵��� Ƚ�� : %d\n", movements);
}

// ���� �������̽� �Լ�
void runUserInterface(TreeNode** root) {
    while (1) {
        char menu;
        int data;

        printf("\n");
        printf("-------------------\n");
        printf("| i : ��� �߰�   |\n");
        printf("| d : ��Ʈ ����   |\n");
        printf("| p : ������ ��� |\n");
        printf("| c : ����        |\n");
        printf("-------------------\n\n");
        printf("�޴� �Է� : ");
        scanf_s(" %c", &menu);

        switch (menu) {
        case 'i':
            printf("�߰��� �� �Է� : ");
            scanf_s("%d", &data);
            insertMaxHeapNode(root, data);
            printf("��尡 �̵��� Ƚ�� : %d\n", move);
            move = 0;
            break;
        case 'd':
            deleteMaxHeapNode(root);
            break;
        case 'p':
            printLevelOrder(*root);
            break;
        case 'c':
            printf("���α׷��� �����մϴ�.\n");
            exit(0);
            break;
        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }
}

// Ʈ�� ��ü��� ����
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ���� �Լ�
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // �ִ� ��Ʈ�� ����
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        insertMaxHeapNode(&root, inputData[i]);
    }

    // ���� �������̽�
    runUserInterface(&root);
    freeTree(root);
    return 0;
}