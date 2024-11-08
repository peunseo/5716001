//#include <stdio.h>
//#include <stdlib.h>
//#include <limits.h>
//
//#define TRUE 1
//#define FALSE 0
//#define MAX_VERTICES 11
//#define INF 1000000
//
//// 간선 구조체 정의
//typedef struct Edge {
//    int vertex, weight;
//    struct Edge* next;
//} Edge;
//
//// 그래프 구조체 정의
//typedef struct GraphType {
//    int n;
//    Edge* adj_list[MAX_VERTICES];
//} GraphType;
//
//int distances[MAX_VERTICES];
//int visited[MAX_VERTICES];
//int visitOrder[MAX_VERTICES];
//
//// 그래프 초기화
//void graph_init(GraphType* g) {
//    g->n = 0;
//    for (int i = 1; i < MAX_VERTICES; i++) {
//        g->adj_list[i] = NULL;
//    }
//}
//
//// 간선 추가
//void insert_edge(GraphType* g, int start, int end, int weight) {
//    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
//    new_edge->vertex = end;
//    new_edge->weight = weight;
//    new_edge->next = g->adj_list[start];
//    g->adj_list[start] = new_edge;
//}
//
//// 방문하지 않은 정점 중 최소 거리 정점 선택
//int shortest_path(int* distance, int n, int* visited) {
//    int min = INF;
//    int minIndex = -1;
//
//    for (int i = 1; i <= n; i++) {
//        if (distance[i] < min && !visited[i]) { // 최소 거리 정점 찾기
//            min = distance[i];
//            minIndex = i;
//        }
//    }
//    return minIndex;    // 최소 거리 정점 인덱스 반환
//}
//
//// 다익스트라 알고리즘 구현
//void Dijkstra(GraphType* g) {
//    
//    // 초기 거리 및 방문 상태 설정 (초기화)
//    for (int i = 1; i <= g->n; i++) {
//        distances[i] = INF;
//        visited[i] = FALSE;
//        visitOrder[i] = -1;
//    }
//
//    distances[1] = 0;
//
//    for (int count = 1; count <= g->n; count++) {
//        int u = shortest_path(distances, g->n, visited);
//        if (u == -1) break;
//
//        visited[u] = TRUE;
//        visitOrder[count] = u;
//
//        // 현재까지 거리 출력
//        printf("Distance : ");
//        for (int i = 1; i <= g->n; i++) {
//            if (distances[i] == INF)
//                printf("* ");
//            else
//                printf("%d ", distances[i]);
//        }
//
//        // 방문 상태 출력
//        printf("\nFound    : ");
//        for (int i = 1; i <= g->n; i++) {
//            printf("%d ", visited[i]);
//        }
//        printf("\n\n");
//
//        // 인접 정점의 거리 업데이트
//        Edge* edge = g->adj_list[u];
//        while (edge != NULL) {
//            int v = edge->vertex;
//            if (!visited[v]) {
//                int newDist = distances[u] + edge->weight;
//                if (newDist < distances[v]) {
//                    distances[v] = newDist;
//                }
//            }
//            edge = edge->next;
//        }
//    }
//
//    // 최종 방문 순서로 출력
//    printf("Found Order : ");
//    for (int i = 1; i <= g->n; i++) {
//        if (visitOrder[i] != -1) {
//            printf("%d ", visitOrder[i]);
//        }
//    }
//    printf("\n");
//}
//
//// 그래프 생성
//void GenerateGraph(GraphType* g) {
//    g->n = 10;
//
//    insert_edge(g, 1, 2, 3);
//    insert_edge(g, 1, 6, 11);
//    insert_edge(g, 1, 7, 12);
//
//    insert_edge(g, 2, 3, 5);
//    insert_edge(g, 2, 4, 4);
//    insert_edge(g, 2, 5, 1);
//    insert_edge(g, 2, 6, 7);
//    insert_edge(g, 2, 7, 8);
//
//    insert_edge(g, 3, 4, 2);
//    insert_edge(g, 3, 7, 6);
//    insert_edge(g, 3, 8, 5);
//
//    insert_edge(g, 4, 5, 13);
//    insert_edge(g, 4, 8, 14);
//    insert_edge(g, 4, 10, 16);
//
//    insert_edge(g, 5, 6, 9);
//    insert_edge(g, 5, 9, 18);
//    insert_edge(g, 5, 10, 17);
//
//    insert_edge(g, 7, 8, 13);
//
//    insert_edge(g, 8, 10, 15);
//
//    insert_edge(g, 9, 10, 10);
//}
//
//// 메인
//int main(void) {
//    GraphType* g;
//    g = (GraphType*)malloc(sizeof(GraphType));
//    graph_init(g);
//
//    GenerateGraph(g);
//    Dijkstra(g);
//
//    free(g);
//    return 0;
//}