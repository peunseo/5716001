#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t), movecount += 3 )

int comparisoncount = 0;
int movecount = 0;
int totalcomparisons = 0;
int totalmovecount = 0;
int rounds = 0;
int isfirst = 0;

// 랜덤 배열 생성
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 1000;
}

// 배열 출력
void printarray(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
}

// 비교하며 swap 정렬
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    movecount++;  // pivot을 초기화한 이동

    do {
        do {
            low++;
            comparisoncount++; // low와 pivot 비교
        } while (low <= right && list[low] < pivot);
        do {
            high--;
            comparisoncount++; // high와 pivot 비교
        } while (high >= left && list[high] > pivot);
        if (low < high) {
            SWAP(list[low], list[high], temp); // swap 매크로 호출 시 이동
            movecount += 3;
        }
    } while (low < high);

    SWAP(list[left], list[high], temp); // pivot과 high 위치 교환
    movecount += 3;

    if (rounds % 10 == 0 && isfirst == 0) {
        for (int i = 40; i < 60; i++)
            printf("%d ", list[i]);
        printf("\n\n");
    }
    rounds++;
    return high;
}

// 반복적 퀵 정렬
void doQuickSort(int list[], int left, int right) {
    int stack[SIZE]; // 스택을 사용하여 인덱스를 저장
    int top = -1; // 스택 초기화

    // 처음 범위를 스택에 푸시
    stack[++top] = left;
    stack[++top] = right;

    // 스택이 비어있지 않은 동안 반복
    while (top >= 0) {
        // 현재 범위 pop
        right = stack[top--];
        left = stack[top--];

        if (left < right) {
            comparisoncount++; // left < right 비교
            int q = partition(list, left, right);

            // 오른쪽 부분을 스택에 푸시
            stack[++top] = q + 1; // 오른쪽 부분
            stack[++top] = right;  // 현재 오른쪽 경계

            // 왼쪽 부분을 스택에 푸시
            stack[++top] = left;   // 현재 왼쪽 경계
            stack[++top] = q - 1; // 왼쪽 부분
        }
    }
}

// 메인
int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisoncount = 0;
        movecount = 0;
        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);
            printf("Result\n");
            printarray(array, SIZE);
            isfirst++;
        }
        else {
            doQuickSort(array, 0, SIZE - 1);
        }
        totalcomparisons += comparisoncount;
        totalmovecount += movecount;
    }
    printf("\n\nAverage Comparisons: %.2f\n", totalcomparisons / 20.0);
    printf("Average Moves: %.2f\n", totalmovecount / 20.0);
    return 0;
}
