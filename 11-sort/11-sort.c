#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

// 무작위 데이터 100 생성
void generateRandomData(int list[]) {
    srand(time(0));
    for (int i = 0; i < SIZE; i++)
        list[i] = rand() % 1000;
}

// 출력 함수
void printArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n\n");
}

// 선택정렬
void doSelectionSort(int list[]) {
    printf("Selection Sort :\n");
    int i, j, least, temp;
    int tempList[SIZE];
    for (int i = 0; i < SIZE; i++) {
        tempList[i] = list[i]; // 원본배열 복사
    }

    for (i = 0; i < SIZE - 1; i++) {
        least = i;
        for (j = i + 1; j < SIZE; j++)
            if (tempList[j] < tempList[least]) least = j;
        SWAP(tempList[i], tempList[least], temp);

        // 10단계, 30단계, 50단계, 70단계, 90단계, 99단계 출력
        if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == 98) {
            printf("Step %d: ", i + 1);
            printArray(tempList);
        }
    }
    // 최종 정렬 결과 출력
    printf("Selection Sort Final Result:\n");
    printArray(tempList);
}

// 삽입정렬
void doInsertionSort(int list[]) {
    int totalComparisons = 0;
    int finalResult[SIZE];

    // 20번 시도 
    for (int attempt = 0; attempt < 20; attempt++) {
        int comparisons = 0;
        int tempList[SIZE];
        for (int i = 0; i < SIZE; i++) {
            tempList[i] = list[i]; // 원본배열 복사
        }

        // 삽입정렬 수행, 비교횟수 계산
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
        // 최종 결과는 마지막 시도의 정렬 결과
        for (int i = 0; i < SIZE; i++) {
            finalResult[i] = tempList[i];
        }
        totalComparisons += comparisons;
    }
    // 출력
    printf("Insertion Sort Compare Average: %d\n", totalComparisons / 20);
    printf("Insertion Sort Final Result:\n");
    printArray(finalResult);
}

// 버블정렬
void doBubbleSort(int list[]) {
    int totalMoves = 0;
    int finalResult[SIZE];

    // 20번 시도 
    for (int attempt = 0; attempt < 20; attempt++) {
        int moves = 0;
        int tempList[SIZE];
        for (int i = 0; i < SIZE; i++) {
            tempList[i] = list[i]; // 원본배열 복사
        }

        // 버블정렬 수행, 이동횟수 계산
        for (int i = SIZE - 1; i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if (tempList[j] > tempList[j + 1]) {
                    int temp;
                    SWAP(tempList[j], tempList[j + 1], temp);
                    moves += 3; // swap은 +3
                }
            }
        }
        // 최종 결과는 마지막 시도의 정렬 결과
        for (int i = 0; i < SIZE; i++) {
            finalResult[i] = tempList[i];
        }
        totalMoves += moves;
    }
    // 출력
    printf("Bubble Sort Move Average: %d\n", totalMoves / 20);
    printf("Bubble Sort Final Result:\n");
    printArray(finalResult);
}

int main() {
    int randomData[SIZE];
    generateRandomData(randomData);

    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}
