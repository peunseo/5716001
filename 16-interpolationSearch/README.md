![](./image1.png)
![](./image2.png)
![](./image3.png)



퀵 정렬 후 이진탐색이 비교 횟수가 적은 이유는,
정렬된 구조 덕분에 중간값을 기준으로 탐색 범위를 효율적으로 좁힐 수 있기 때문입니다.
이진탐색은 매 단계에서 비교 대상의 절반을 제거하므로 O(log n) 복잡도를 가지며, 
순차탐색의 O(n)보다 훨씬 적은 비교를 수행합니다.
