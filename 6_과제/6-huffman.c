#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    char character;
    int frequency;
    struct Node* left, * right;
} Node;

// 최소 힙 구조체 정의
typedef struct MinHeap {
    int size;
    int capacity;
    Node** array;
} MinHeap;

// 노드를 생성 함수
Node* createNode(char character, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 최소 힙 생성 함수
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node**)malloc(minHeap->capacity * sizeof(Node*));
    return minHeap;
}

// 노드 교환 함수
void swapNode(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// 최소 힙 출력 함수
void printHeap(MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->array[i]->frequency);
    }
    printf("\n");
}

// 최소 힙 재정렬 함수
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

// 최소 힙에서 최솟값을 추출하는 함수
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// 최소 힙에 노드 삽입 함수
void insertMinHeap(MinHeap* minHeap, Node* node) {
    if (minHeap->size >= minHeap->capacity) {
        return; // 힙의 용량을 초과하지 않도록
    }

    // 새 노드를 추가하고 힙의 크기를 증가시킵니다.
    minHeap->array[minHeap->size] = node;
    int i = minHeap->size;
    minHeap->size++;

    // 부모 노드와 비교하여 힙 속성을 유지합니다.
    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// 허프만 트리 구축 함수
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

        // 트리 구조 출력: 현재 노드와 자식 노드 정보
        printf("//%d + %d -> %d\n", left->frequency, right->frequency, top->frequency);
        printHeap(minHeap);
    }

    return extractMin(minHeap);
}

// 허프만 코드 출력 함수
void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;  // 왼쪽 자식은 1
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 0;  // 오른쪽 자식은 0
        printCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// 허프만 코드 생성 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int* arr = (int*)malloc(size * sizeof(int));
    int top = 0;

    printCodes(root, arr, top);
    free(arr);
}

// 메인 함수
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    // 허프만 코드 생성 및 출력
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
