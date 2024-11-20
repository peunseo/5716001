#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int sorted[SIZE]; // �߰� ���� �ʿ�
int comparisonCount = 0;
int moveCount = 0;
int totalComparisons = 0;
int totalMoves = 0;
int rounds = 0;
int isFirst = 0;

// ���� �迭 ����
void generateRandomArray(int Array[]) {
	for (int i = 0; i < SIZE; i++)
		Array[i] = rand() % 1000;
}

// ���� ��� ��� �Լ�
void printArray(int list[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
}

// i�� ���ĵ� ���ʸ���Ʈ�� ���� �ε���
// j�� ���ĵ� �����ʸ���Ʈ�� ���� �ε���
// k�� ���ĵ� ����Ʈ�� ���� �ε���
// �պ� �� ���ĵǴ� ����
void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	rounds++; // merge ȣ�� Ƚ�� ����

	// ���� ���ĵ� list�� �պ�
	while (i <= mid && j <= right) {
		comparisonCount++; // �� Ƚ�� ����
		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
			moveCount++; // �̵� Ƚ�� ����
		}
		else {
			sorted[k++] = list[j++];
			moveCount++; // �̵� Ƚ�� ����
		}
	}

	// ���� �ִ� ���ڵ��� �ϰ� ����
	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
			moveCount++; // �̵� Ƚ�� ����
		}
	}
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
			moveCount++; // �̵� Ƚ�� ����
		}
	}

	// �迭 sorted[]�� �ӽ� �迭 ����Ʈ�� �迭 list[]�� �纹��
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
		moveCount++; // �̵� Ƚ�� ����
	}

	if (rounds % 10 == 0 && isFirst == 0) { //10���� �ѹ��� ���
		for (int i = 0; i < 10; i++) //0 ~ 9��
			printf("%3d ", list[i]);
		printf("| ");
		for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) //�߾�-1 ~ �߾�+10
			printf("%3d ", list[i]);
		printf("\n\n");
	}
}

// �պ� ���� �Լ�
void doMergeSort(int list[], int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;   // ����Ʈ�� �յ����
		doMergeSort(list, left, mid);		// �� �κи���Ʈ ����
		doMergeSort(list, mid + 1, right);	// �� �κи���Ʈ ����
		merge(list, left, mid, right); // �պ�
	}
}

// ����
int main() {
	int array[SIZE];

	for (int i = 0; i < 20; i++) {
		generateRandomArray(array);
		comparisonCount = 0;
		moveCount = 0;

		if (i == 0) {
			printf("Merge Sort Run\n");
			doMergeSort(array, 0, SIZE - 1);

			printf("Result\n");
			printArray(array, SIZE);
			isFirst++;
		}
		else {
			doMergeSort(array, 0, SIZE - 1);
		}

		totalComparisons += comparisonCount;
		totalMoves += moveCount;
	}

	printf("\n\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
	printf("Average Moves: %.2f\n", totalMoves / 20.0);

	return 0;
}