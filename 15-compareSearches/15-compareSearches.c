#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int compareCount = 0;

// ���� �迭 ����
void generateRandomArray(int array[]) {
	for (int i = 0; i < SIZE; i++)
		array[i] = rand() % 1000;
}

// ��� �Լ�
void printArray(int* array) {
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++)
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%3d ", array[i]);
	printf("\n");
}

// ����Ž��
double getAverageLinearSearchCompareCount(int array[]) {
	int totalCompareCount = 0;

	for (int i = 0; i < 100; i++) {
		int target = array[rand() % SIZE];
		int compareCount = 0;
		for (int j = 0; j < SIZE; j++) {
			compareCount++;
			if (array[j] == target) break; 
		}
		totalCompareCount += compareCount;
	}
	return totalCompareCount / 100.0; 
}

// ���ϸ� swap ����
int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];

	do {
		do {
			low++;
			compareCount++; // low�� pivot ��
		} while (low <= right && list[low] < pivot);
		do {
			high--;
			compareCount++; // high�� pivot �� 
		} while (high >= left && list[high] > pivot);
		if (low < high) {
			SWAP(list[low], list[high], temp); 
		}
	} while (low < high);
	SWAP(list[left], list[high], temp); // pivot�� high ��ġ ��ȯ
}

// ������ �� ��Ƚ��
void getQuickSortCompareCount(int list[]) {
	int stack[SIZE]; 
	int top = -1;

	stack[++top] = 0;       // left
	stack[++top] = SIZE - 1; // right

	while (top >= 0) {
		int right = stack[top--];
		int left = stack[top--];

		if (left < right) {
			compareCount++; // left < right ��
			int q = partition(list, left, right);

			stack[++top] = q + 1;
			stack[++top] = right;

			stack[++top] = left;
			stack[++top] = q - 1;
		}
	}
}

// ����Ž��
double getAverageBinarySearchCompareCount(int array[]) {
	int totalCompareCount = 0;
	int compareCount = 0;

	for (int i = 0; i < 100; i++) {
		int target = array[rand() % SIZE]; 
		int compareCount = 0;

		// ���� Ž��
		int left = 0, right = SIZE - 1;
		while (left <= right) {
			compareCount++;
			int mid = (left + right) / 2;
			if (array[mid] == target) {	break; }
			else if (array[mid] < target) { left = mid + 1; }
			else {right = mid - 1;}
		}
		totalCompareCount += compareCount;
	}
	return totalCompareCount / 100.0; 
}

// ����
int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);

	printf("Average Linear Search Compare Count: %.2f\n", getAverageLinearSearchCompareCount(array));

	getQuickSortCompareCount(array);
	printf("Quick Sort Compare Count: %d\n", compareCount);

	printf("Average Binary Search Compare Count: %.2f\n\n",getAverageBinarySearchCompareCount(array));

	printArray(array);
	return 0;
}