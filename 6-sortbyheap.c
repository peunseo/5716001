//#include <stdio.h>
//
//// 스왑 함수
//void swap(int* a, int* b) {
//    int temp = *a;
//    *a = *b;
//    *b = temp;
//}
//
////  힙 재정렬 함수
//void resortHeap(int inputData[], int n, int i) {
//    int largest = i;
//    int left = 2 * i + 1; // 왼쪽 자식
//    int right = 2 * i + 2; // 오른쪽 자식
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
//// 최대 힙 구성 함수
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
//// 최대 힙 생성&정렬 함수
//void BuildMaxHeapAndSort(int inputData[], int n) {
//    BuildMaxHeap(inputData, n);
//
//    // 초기 상태 출력
//    for (int i = 0; i < n; i++) {
//        printf("%d ", inputData[i]);
//    }
//    printf("\n");
//
//    for (int i = n - 1; i > 0; i--) {
//        swap(&inputData[0], &inputData[i]);
//        // 힙 재정렬
//        resortHeap(inputData, i, 0);
//
//        // 현재 상태 출력
//        for (int j = 0; j < i; j++) {
//            printf("%d ", inputData[j]);
//        }
//        printf("\n");
//    }
//}
//
//// 메인 함수
//int main() {
//    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
//    int size = sizeof(inputData) / sizeof(inputData[0]);
//
//    // 힙 정렬 실행
//    printf("<Sort>\n");
//    BuildMaxHeapAndSort(inputData, size);
//
//    // 정렬된 결과 출력
//    printf("\nSorted Array:\n");
//    for (int i = 0; i < size; i++) {
//        printf("%d ", inputData[i]);
//    }
//    printf("\n");
//    return 0;
//}