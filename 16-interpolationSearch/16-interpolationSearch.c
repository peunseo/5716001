#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int comparisoncount = 0;

// ���� �迭 ����
void generateRandomArray(int array[]) {
	for (int i = 0; i < SIZE; i++)
		array[i] = rand() % 10000;
}

// ���ĵ� �迭 ���
void printArray(int* array) {
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++)
		printf("%4d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%4d ", array[i]);
	printf("\n\n");
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
		} while (low <= right && list[low] < pivot);
		do {
			high--;
		} while (high >= left && list[high] > pivot);
		if (low < high) {
			SWAP(list[low], list[high], temp);
		}
	} while (low < high);
	SWAP(list[left], list[high], temp); // pivot�� high ��ġ ��ȯ
	return high;
}

// �� ����
void QuickSort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		QuickSort(list, left, q - 1);
		QuickSort(list, q + 1, right);
	}
}

// ����Ž��
int binarySearch(int array[], int key) {
	int left = 0, right = SIZE - 1, mid;
	int compareCount = 0;
	while (left <= right) {
		mid = (left + right) / 2;
		compareCount++;
		if (array[mid] == key) {
			compareCount++;
			return compareCount;
		}
		else if (array[mid] < key)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return compareCount;
}

// ����Ž�� 1000��, ��Ƚ�� ���
double getAverageBinarySearchCompareCount(int array[]) {
	int totalCompareCount = 0;
	for (int i = 0; i < 1000; i++) {
		int key = rand() % 10000;
		totalCompareCount += binarySearch(array, key);
	}
	return totalCompareCount / 1000.0;
}

// ����Ž��
int interpolationSearch(int array[], int key) {
	int compareCount = 0;
	int low = 0, high = SIZE - 1, j;
	while (low <= high && key >= array[low] && key <= array[high]) {
		compareCount++;
		if (low == high) {
			compareCount++;
			if (array[low] == key) return compareCount; break; // Ž�� ����
		}
		j = low + ((key - array[low]) * (high - low)) / (array[high] - array[low]);
		compareCount++;
		if (array[j] == key) {
			compareCount++;
			return compareCount;	// Ž�� ����
		}
		else if (array[j] < key) low = j + 1;
		else high = j - 1;
	}
	return compareCount;
}

// ����Ž�� 1000��, ��Ƚ�� ���
double getAverageInterpolationSearchComparecount(int array[]) {
	int totalCompareCount = 0;
	for (int i = 0; i < 1000; i++) {
		int key = rand() % 10000;
		totalCompareCount += interpolationSearch(array, key);
	}
	return totalCompareCount / 1000.0;
}

// ����
int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);
	QuickSort(array, 0, SIZE - 1);
	printArray(array);
	printf("Average Compare Count of Binary Search: %.2f\n",getAverageBinarySearchCompareCount(array));
	printf("Average Compare Count of Interpolation Search: %.2f\n",getAverageInterpolationSearchComparecount(array));
	return 0;
}