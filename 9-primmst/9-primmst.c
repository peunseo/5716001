#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

// 그래프 구조체 정의
typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES]; // 선택된 정점
int distance[MAX_VERTICES]; // 최소 가중치 배열

// 그래프 초기화
void graph_init(GraphType* g) {
    g->n = 10; // 정점의 개수 10
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i == j)
                g->weight[i][j] = 0; // 자기 자신으로 가는 간선의 가중치는 0
            else
                g->weight[i][j] = INF; // 나머지는 무한대로 초기화
        }
    }
    for (int i = 0; i < MAX_VERTICES; i++) {
        selected[i] = FALSE; // 정점 선택 여부 초기화
        distance[i] = INF;   // 최소 가중치 초기화
    }
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w) {
    g->weight[start][end] = w;
    g->weight[end][start] = w;
}

// 그래프를 생성 함수
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);

    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 7, 8);

    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);

    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);

    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 5, 10, 17);

    insert_edge(g, 7, 8, 13);

    insert_edge(g, 8, 10, 15);

    insert_edge(g, 9, 10, 10);
}

// 최소 dist[v] 값을 갖는 정점 반환
int get_min_vertex(int n) {
    int v = -1;
    for (int i = 1; i <= n; i++) { // 1번 정점 시작
        if (!selected[i]) {
            if (v == -1 || distance[i] < distance[v]) {
                v = i;
            }
        }
    }
    return v;
}

// Prim 탐색 및 출력
void FindPrimMST(GraphType* g) {
    printf("Prim MST Algorithm\n");
    int u, v;
    int s = 1; // 시작 정점 설정 (1번 정점에서 시작)

    distance[s] = 0;  // 초기화

    for (int i = 1; i <= g->n; i++) {
        u = get_min_vertex(g->n);
        selected[u] = TRUE;

        if (distance[u] == INF) return; // 연결되지 않은 경우
        printf("정점 %d 추가\n", u);

        // 선택된 정점과 인접한 정점들의 가중치 업데이트
        for (v = 1; v <= g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v]) {
                if (g->weight[u][v] < distance[v]) {
                    distance[v] = g->weight[u][v];
                }
            }
        }
    }
}

// 메인 함수
int main(void)
{
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g); //그래프를 생성하는 함수

    FindPrimMST(g); //Prim을 이용해 MST를 찾음

    free(g);
    return 0;
}