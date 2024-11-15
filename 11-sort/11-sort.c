#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

// ������ ������ ���� �Լ�
void generateRandomData(int list[]) {
    for (int i = 0; i < SIZE; i++)
        list[i] = rand() % 1000;
}

// �迭 ��� �Լ�
void printArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n\n");
}

// ���� ����
void doSelectionSort(int list[]) {
    int tempList[SIZE];
    int temp;
    printf("Selection Sort :\n");

    for (int i = 0; i < SIZE; i++) tempList[i] = list[i]; 

    for (int i = 0; i < SIZE - 1; i++) {
        int least = i;
        for (int j = i + 1; j < SIZE; j++)
            if (tempList[j] < tempList[least]) least = j;
        SWAP(tempList[i], tempList[least], temp);

        if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == 98) {
            printf("Step %d : ", i + 1);
            printArray(tempList);
        }
    }
}

// ���� ����
void doInsertionSort(int list[]) {
    int totalComparisons = 0;
    int finalResult[SIZE];

    for (int attempt = 0; attempt < 20; attempt++) {
        generateRandomData(list); // ��ȸ ������ ������ ����
        int comparisons = 0;
        int tempList[SIZE];
        for (int i = 0; i < SIZE; i++) tempList[i] = list[i]; 

        for (int i = 1; i < SIZE; i++) {
            int key = tempList[i];
            int j = i - 1;
            while (j >= 0 && tempList[j] > key) {
                comparisons++;
                tempList[j + 1] = tempList[j];
                j--;
            }
            comparisons++;
            tempList[j + 1] = key;
        }

        for (int i = 0; i < SIZE; i++) finalResult[i] = tempList[i];
        totalComparisons += comparisons;
    }
    printf("Insertion Sort Compare Average : %d\n", totalComparisons / 20);
    printf("Insertion Sort Result:\n");
    printArray(finalResult);
}

// ���� ����
void doBubbleSort(int list[]) {
    int totalMoves = 0;
    int finalResult[SIZE];

    for (int attempt = 0; attempt < 20; attempt++) {
        generateRandomData(list); // ��ȸ ������ ������ ����
        int moves = 0;
        int tempList[SIZE];
        for (int i = 0; i < SIZE; i++) tempList[i] = list[i]; // �迭 ����

        for (int i = SIZE - 1; i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if (tempList[j] > tempList[j + 1]) {
                    int temp;
                    SWAP(tempList[j], tempList[j + 1], temp);
                    moves += 3; // swap�� +3 �̵� Ƚ��
                }
            }
        }

        for (int i = 0; i < SIZE; i++) finalResult[i] = tempList[i];
        totalMoves += moves;
    }
    printf("Bubble Sort Move Average : %d\n", totalMoves / 20);
    printf("Bubble Sort Result:\n");
    printArray(finalResult);
}

int main() {
    srand(time(0)); 
    int randomData[SIZE];

    generateRandomData(randomData);
    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}