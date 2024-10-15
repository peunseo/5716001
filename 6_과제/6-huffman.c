#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct Node {
    char character;
    int frequency;
    struct Node* left, * right;
} Node;

// �ּ� �� ����ü ����
typedef struct MinHeap {
    int size;
    int capacity;
    Node** array;
} MinHeap;

// ��带 ���� �Լ�
Node* createNode(char character, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// �ּ� �� ���� �Լ�
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node**)malloc(minHeap->capacity * sizeof(Node*));
    return minHeap;
}

// ��� ��ȯ �Լ�
void swapNode(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// �ּ� �� ��� �Լ�
void printHeap(MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->array[i]->frequency);
    }
    printf("\n");
}

// �ּ� �� ������ �Լ�
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// �ּ� ������ �ּڰ��� �����ϴ� �Լ�
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// �ּ� ���� ��� ���� �Լ�
void insertMinHeap(MinHeap* minHeap, Node* node) {
    if (minHeap->size >= minHeap->capacity) {
        return; // ���� �뷮�� �ʰ����� �ʵ���
    }

    // �� ��带 �߰��ϰ� ���� ũ�⸦ ������ŵ�ϴ�.
    minHeap->array[minHeap->size] = node;
    int i = minHeap->size;
    minHeap->size++;

    // �θ� ���� ���Ͽ� �� �Ӽ��� �����մϴ�.
    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// ������ Ʈ�� ���� �Լ�
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node* left, * right, * top;

    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i) {
        insertMinHeap(minHeap, createNode(characters[i], frequencies[i]));
        printHeap(minHeap);
    }

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);

        // Ʈ�� ���� ���: ���� ���� �ڽ� ��� ����
        printf("//%d + %d -> %d\n", left->frequency, right->frequency, top->frequency);
        printHeap(minHeap);
    }

    return extractMin(minHeap);
}

// ������ �ڵ� ��� �Լ�
void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;  // ���� �ڽ��� 1
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 0;  // ������ �ڽ��� 0
        printCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// ������ �ڵ� ���� �Լ�
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int* arr = (int*)malloc(size * sizeof(int));
    int top = 0;

    printCodes(root, arr, top);
    free(arr);
}

// ���� �Լ�
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    // ������ �ڵ� ���� �� ���
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
