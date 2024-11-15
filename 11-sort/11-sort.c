#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

// 무작위 데이터 생성 함수
void generateRandomData(int list[]) {
    for (int i = 0; i < SIZE; i++)
        list[i] = rand() % 1000;
}

// 배열 출력 함수
void printArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n\n");
}

// 선택 정렬
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

// 삽입 정렬
void doInsertionSort(int list[]) {
    int totalComparisons = 0;
    int finalResult[SIZE];

    for (int attempt = 0; attempt < 20; attempt++) {
        generateRandomData(list); // 매회 무작위 데이터 생성
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

// 버블 정렬
void doBubbleSort(int list[]) {
    int totalMoves = 0;
    int finalResult[SIZE];

    for (int attempt = 0; attempt < 20; attempt++) {
        generateRandomData(list); // 매회 무작위 데이터 생성
        int moves = 0;
        int tempList[SIZE];
        for (int i = 0; i < SIZE; i++) tempList[i] = list[i]; // 배열 복사

        for (int i = SIZE - 1; i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if (tempList[j] > tempList[j + 1]) {
                    int temp;
                    SWAP(tempList[j], tempList[j + 1], temp);
                    moves += 3; // swap은 +3 이동 횟수
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