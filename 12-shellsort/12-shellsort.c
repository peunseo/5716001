#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

// ���� �迭 ����
void generateRandomNumbers(int Array[]) {
	for (int i = 0; i < ARRAY_SIZE; i++)
		Array[i] = rand() % 1000;
}

// ���� ���� ����
void inc_insertion_sort(int list[], int first, int last, int gap, int* comp, int* move) {
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		(*move)++;  // key�� ���� �Ҵ��ϴ� �̵� ī��Ʈ
		for (j = i - gap; j >= first && key < list[j]; j = j - gap) {
			(*comp)++;  // �� Ƚ�� ����
			list[j + gap] = list[j];
			(*move)++;  // �̵� Ƚ�� ����
		}
		list[j + gap] = key;
		(*move)++;  // �̵� Ƚ�� ����
	}
}

// �� ���� �Լ�
void doShellSort(int list[], int n, int* comp, int* move) {
	int i, gap;
	int totalComp = 0, totalMove = 0;

	for (int repeat = 0; repeat < 20; repeat++) {  // 20ȸ �ݺ�
		generateRandomNumbers(list);  // �� ȸ �ٸ� �迭 ����
		*comp = 0;  // �� Ƚ�� �ʱ�ȭ
		*move = 0;  // �̵� Ƚ�� �ʱ�ȭ

		if (n == 2) {
			for (gap = ARRAY_SIZE / 2; gap > 0; gap = gap / 2) {
				for (i = 0; i < gap; i++)  // �κ� ����Ʈ�� ������ gap
					inc_insertion_sort(list, i, ARRAY_SIZE - 1, gap, comp, move);

				// ù ��° �ݺ������� ���
				if (repeat == 0) {
					printf("Sorting with gap = %d:\n", gap);
					for (int k = 0; k < 20; k++)  // �迭�� �Ϻθ� ���
						printf("%d ", list[k]);
					printf(" . . .\n\n");

					if (gap == 1) {
						printf("Sorted shellArray :\n");
						for (int i = 0; i < ARRAY_SIZE; i++)
							printf("%d ", list[i]);
						printf("\n\n");
					}
				}
			}
		}

		if (n == 3) {
			for (gap = ARRAY_SIZE / 3; gap > 0; gap = gap / 3) {
				for (i = 0; i < gap; i++)  // �κ� ����Ʈ�� ������ gap
					inc_insertion_sort(list, i, ARRAY_SIZE - 1, gap, comp, move);

				// ù ��° �ݺ������� ���
				if (repeat == 0) {
					printf("Sorting with gap = %d:\n", gap);
					for (int k = 0; k < 20; k++)  // �迭�� �Ϻθ� ���
						printf("%d ", list[k]);
					printf(" . . .\n\n");

					if (gap == 1) {
						printf("Sorted shellArray :\n");
						for (int i = 0; i < ARRAY_SIZE; i++)
							printf("%d ", list[i]);
						printf("\n\n");
					}
				}
			}
		}

		totalComp += *comp;
		totalMove += *move;
	}

	// ��� �� �� �̵� Ƚ�� ��� �� comp�� move�� ����
	*comp = totalComp / 20;
	*move = totalMove / 20;
}

// �ܼ� ���� ����
void doInsertionSort(int list[], int* comp, int* move) {
	int totalComp = 0, totalMove = 0;

	for (int repeat = 0; repeat < 20; repeat++) {  // 20ȸ �ݺ�
		generateRandomNumbers(list);  // �� ȸ �ٸ� �迭 ����
		*comp = 0;  // �� Ƚ�� �ʱ�ȭ
		*move = 0;  // �̵� Ƚ�� �ʱ�ȭ

		int i, j, key;
		for (i = 1; i < ARRAY_SIZE; i++) {
			key = list[i];
			(*move)++;  // key �Ҵ� �̵� ī��Ʈ
			for (j = i - 1; j >= 0 && list[j] > key; j--) {
				(*comp)++;  // �� Ƚ�� ����
				list[j + 1] = list[j];
				(*move)++;  // �̵� Ƚ�� ����
			}
			list[j + 1] = key;
			(*move)++;  // �̵� Ƚ�� ����
		}

		totalComp += *comp;
		totalMove += *move;

		if (repeat == 19) {
			printf("Sorted insertionArray :\n");
			for (int i = 0; i < ARRAY_SIZE; i++)
				printf("%d ", list[i]);
			printf("\n\n");
		}
	}
	// ��� �� �� �̵� Ƚ�� ��� �� comp�� move�� ����
	*comp = totalComp / 20;
	*move = totalMove / 20;
}

int main() {
	int array[ARRAY_SIZE];
	int comparisonCount, moveCount;

	srand(time(NULL));  // ���� �ʱ�ȭ

	// Shell Sort
	printf("Shell Sort (n/2):\n");
	doShellSort(array, 2, &comparisonCount, &moveCount);
	printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

	printf("Shell Sort (n/3):\n");
	doShellSort(array, 3, &comparisonCount, &moveCount);
	printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

	// Insertion Sort
	printf("Insertion Sort:\n");
	doInsertionSort(array, &comparisonCount, &moveCount);
	printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

	return 0;
}
