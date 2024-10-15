//#include <stdio.h>
//
//// ���� �Լ�
//void swap(int* a, int* b) {
//    int temp = *a;
//    *a = *b;
//    *b = temp;
//}
//
////  �� ������ �Լ�
//void resortHeap(int inputData[], int n, int i) {
//    int largest = i;
//    int left = 2 * i + 1; // ���� �ڽ�
//    int right = 2 * i + 2; // ������ �ڽ�
//
//    if (left < n && inputData[left] > inputData[largest]) {
//        largest = left;
//    }
//    if (right < n && inputData[right] > inputData[largest]) {
//        largest = right;
//    }
//    if (largest != i) {
//        swap(&inputData[i], &inputData[largest]);
//        resortHeap(inputData, n, largest);
//    }
//}
//
//// �ִ� �� ���� �Լ�
//void BuildMaxHeap(int inputData[], int n) {
//    for (int i = 1; i <= n; i++) {
//        int child = i - 1;
//        while (child > 0) {
//            int parent = (child - 1) / 2;
//            if (inputData[child] > inputData[parent]) {
//                swap(&inputData[child], &inputData[parent]);
//            }
//            child = parent;
//        }
//
//        for (int j = 0; j < i-1; j++) {
//            printf("%d ", inputData[j]);
//        }
//        printf("\n");
//    }
//}
//
//// �ִ� �� ����&���� �Լ�
//void BuildMaxHeapAndSort(int inputData[], int n) {
//    BuildMaxHeap(inputData, n);
//
//    // �ʱ� ���� ���
//    for (int i = 0; i < n; i++) {
//        printf("%d ", inputData[i]);
//    }
//    printf("\n");
//
//    for (int i = n - 1; i > 0; i--) {
//        swap(&inputData[0], &inputData[i]);
//        // �� ������
//        resortHeap(inputData, i, 0);
//
//        // ���� ���� ���
//        for (int j = 0; j < i; j++) {
//            printf("%d ", inputData[j]);
//        }
//        printf("\n");
//    }
//}
//
//// ���� �Լ�
//int main() {
//    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
//    int size = sizeof(inputData) / sizeof(inputData[0]);
//
//    // �� ���� ����
//    printf("<Sort>\n");
//    BuildMaxHeapAndSort(inputData, size);
//
//    // ���ĵ� ��� ���
//    printf("\nSorted Array:\n");
//    for (int i = 0; i < size; i++) {
//        printf("%d ", inputData[i]);
//    }
//    printf("\n");
//    return 0;
//}