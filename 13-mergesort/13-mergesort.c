#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int sorted[SIZE]; // 추가 공간 필요
int comparisonCount = 0;
int moveCount = 0;
int totalComparisons = 0;
int totalMoves = 0;
int rounds = 0;
int isFirst = 0;

// 랜덤 배열 생성
void generateRandomArray(int Array[]) {
	for (int i = 0; i < SIZE; i++)
		Array[i] = rand() % 1000;
}

// 최종 결과 출력 함수
void printArray(int list[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
}

// i는 정렬된 왼쪽리스트에 대한 인덱스
// j는 정렬된 오른쪽리스트에 대한 인덱스
// k는 정렬될 리스트에 대한 인덱스
// 합병 및 정렬되는 과정
void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	rounds++; // merge 호출 횟수 증가

	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right) {
		comparisonCount++; // 비교 횟수 증가
		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
			moveCount++; // 이동 횟수 증가
		}
		else {
			sorted[k++] = list[j++];
			moveCount++; // 이동 횟수 증가
		}
	}

	// 남아 있는 레코드의 일괄 복사
	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
			moveCount++; // 이동 횟수 증가
		}
	}
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
			moveCount++; // 이동 횟수 증가
		}
	}

	// 배열 sorted[]의 임시 배열 리스트를 배열 list[]로 재복사
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
		moveCount++; // 이동 횟수 증가
	}

	if (rounds % 10 == 0 && isFirst == 0) { //10번에 한번만 출력
		for (int i = 0; i < 10; i++) //0 ~ 9값
			printf("%3d ", list[i]);
		printf("| ");
		for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) //중앙-1 ~ 중앙+10
			printf("%3d ", list[i]);
		printf("\n\n");
	}
}

// 합병 정렬 함수
void doMergeSort(int list[], int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;   // 리스트의 균등분할
		doMergeSort(list, left, mid);		// 앞 부분리스트 정렬
		doMergeSort(list, mid + 1, right);	// 뒤 부분리스트 정렬
		merge(list, left, mid, right); // 합병
	}
}

// 메인
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