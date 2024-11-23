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

// ���� �迭 ����
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % 1000;
}

// �迭 ���
void printarray(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
}

// ���ϸ� swap ����
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    movecount++;  // pivot�� �ʱ�ȭ�� �̵�

    do {
        do {
            low++;
            comparisoncount++; // low�� pivot ��
        } while (low <= right && list[low] < pivot);
        do {
            high--;
            comparisoncount++; // high�� pivot ��
        } while (high >= left && list[high] > pivot);
        if (low < high) {
            SWAP(list[low], list[high], temp); // swap ��ũ�� ȣ�� �� �̵�
            movecount += 3;
        }
    } while (low < high);

    SWAP(list[left], list[high], temp); // pivot�� high ��ġ ��ȯ
    movecount += 3;

    if (rounds % 10 == 0 && isfirst == 0) {
        for (int i = 40; i < 60; i++)
            printf("%d ", list[i]);
        printf("\n\n");
    }
    rounds++;
    return high;
}

// �ݺ��� �� ����
void doQuickSort(int list[], int left, int right) {
    int stack[SIZE]; // ������ ����Ͽ� �ε����� ����
    int top = -1; // ���� �ʱ�ȭ

    // ó�� ������ ���ÿ� Ǫ��
    stack[++top] = left;
    stack[++top] = right;

    // ������ ������� ���� ���� �ݺ�
    while (top >= 0) {
        // ���� ���� pop
        right = stack[top--];
        left = stack[top--];

        if (left < right) {
            comparisoncount++; // left < right ��
            int q = partition(list, left, right);

            // ������ �κ��� ���ÿ� Ǫ��
            stack[++top] = q + 1; // ������ �κ�
            stack[++top] = right;  // ���� ������ ���

            // ���� �κ��� ���ÿ� Ǫ��
            stack[++top] = left;   // ���� ���� ���
            stack[++top] = q - 1; // ���� �κ�
        }
    }
}

// ����
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
