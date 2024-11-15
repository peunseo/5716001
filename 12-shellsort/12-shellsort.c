#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

// 랜덤 배열 생성
void generateRandomNumbers(int Array[]) {
	for (int i = 0; i < ARRAY_SIZE; i++)
		Array[i] = rand() % 1000;
}

// 쉘의 삽입 정렬
void inc_insertion_sort(int list[], int first, int last, int gap, int* comp, int* move) {
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		(*move)++;  // key에 값을 할당하는 이동 카운트
		for (j = i - gap; j >= first && key < list[j]; j = j - gap) {
			(*comp)++;  // 비교 횟수 증가
			list[j + gap] = list[j];
			(*move)++;  // 이동 횟수 증가
		}
		list[j + gap] = key;
		(*move)++;  // 이동 횟수 증가
	}
}

// 쉘 정렬 함수
void doShellSort(int list[], int n, int* comp, int* move) {
	int i, gap;
	int totalComp = 0, totalMove = 0;

	for (int repeat = 0; repeat < 20; repeat++) {  // 20회 반복
		generateRandomNumbers(list);  // 매 회 다른 배열 생성
		*comp = 0;  // 비교 횟수 초기화
		*move = 0;  // 이동 횟수 초기화

		if (n == 2) {
			for (gap = ARRAY_SIZE / 2; gap > 0; gap = gap / 2) {
				for (i = 0; i < gap; i++)  // 부분 리스트의 개수는 gap
					inc_insertion_sort(list, i, ARRAY_SIZE - 1, gap, comp, move);

				// 첫 번째 반복에서만 출력
				if (repeat == 0) {
					printf("Sorting with gap = %d:\n", gap);
					for (int k = 0; k < 20; k++)  // 배열의 일부만 출력
						printf("%d ", list[k]);
					printf(" . . .\n\n");
					
					// 최종 결과 출력
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
				for (i = 0; i < gap; i++)  // 부분 리스트의 개수는 gap
					inc_insertion_sort(list, i, ARRAY_SIZE - 1, gap, comp, move);

				// 첫 번째 반복에서만 출력
				if (repeat == 0) {
					printf("Sorting with gap = %d:\n", gap);
					for (int k = 0; k < 20; k++)  // 배열의 일부만 출력
						printf("%d ", list[k]);
					printf(" . . .\n\n");
					
					// 최종 결과 출력
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
	// 평균 비교 및 이동 횟수 계산 후 comp와 move에 저장
	*comp = totalComp / 20;
	*move = totalMove / 20;
}

// 단순 삽입 정렬
void doInsertionSort(int list[], int* comp, int* move) {
	int totalComp = 0, totalMove = 0;
	
	// 20회 반복
	for (int repeat = 0; repeat < 20; repeat++) {
		generateRandomNumbers(list);  // 매 회 다른 배열 생성
		*comp = 0;  // 비교 횟수 초기화
		*move = 0;  // 이동 횟수 초기화

		int i, j, key;
		for (i = 1; i < ARRAY_SIZE; i++) {
			key = list[i];
			(*move)++;  // key 할당 이동 카운트
			for (j = i - 1; j >= 0 && list[j] > key; j--) {
				(*comp)++;  // 비교 횟수 증가
				list[j + 1] = list[j];
				(*move)++;  // 이동 횟수 증가
			}
			list[j + 1] = key;
			(*move)++;  // 이동 횟수 증가
		}
		totalComp += *comp;
		totalMove += *move;
		
		// 최종 결과 출력
		if (repeat == 19) {
			printf("Sorted insertionArray :\n");
			for (int i = 0; i < ARRAY_SIZE; i++)
				printf("%d ", list[i]);
			printf("\n\n");
		}
	}
	// 평균 비교 및 이동 횟수 계산 후 comp와 move에 저장
	*comp = totalComp / 20;
	*move = totalMove / 20;
}

int main() {
	int array[ARRAY_SIZE];
	int comparisonCount, moveCount;

	srand(time(NULL));  // 난수 초기화

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
