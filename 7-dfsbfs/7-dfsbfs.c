#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

// 그래프 구조체 정의
typedef struct GraphMatType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

// 그래프 생성
GraphMatType* create_graph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}

// 그래프 삭제
void destroy_graph(GraphMatType* g) {
    free(g);
}

// 그래프 초기화
void init_graph(GraphMatType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

// vertex 생성
void insert_vertex_graph(GraphMatType* g,int v) {
    if (g->n >= MAX_VERTICES) {
        fprintf(stderr, "Over number of vertex\n");
        return;
    }
    (g->n)++;
}

// edge 생성
void insert_edge_graph(GraphMatType* g, int s, int e) {
    if (s >= g->n || e >= g->n) {
        fprintf(stderr, "vertex number error\n");
        return;
    }
    g->adj_mat[s][e] = 1;
    g->adj_mat[e][s] = 1;
}

// 그래프 연결
void generate_graph(GraphMatType* g) {
    // 정점 생성
    for (int i = 0; i < 11; i++)
        insert_vertex_graph(g,i);

    // 정점 연결
    insert_edge_graph(g, 0, 2);
    insert_edge_graph(g, 0, 4);
    insert_edge_graph(g, 0, 5);
    insert_edge_graph(g, 0, 6);
    insert_edge_graph(g, 0, 9);
    insert_edge_graph(g, 1, 4);
    insert_edge_graph(g, 1, 5);
    insert_edge_graph(g, 1, 7);
    insert_edge_graph(g, 1, 10);
    insert_edge_graph(g, 2, 3);
    insert_edge_graph(g, 2, 4);
    insert_edge_graph(g, 3, 4);
    insert_edge_graph(g, 3, 5);
    insert_edge_graph(g, 4, 5);
    insert_edge_graph(g, 4, 6);
    insert_edge_graph(g, 4, 7);
    insert_edge_graph(g, 6, 7);
    insert_edge_graph(g, 6, 8);
    insert_edge_graph(g, 7, 10);
    insert_edge_graph(g, 8, 9);
    insert_edge_graph(g, 8, 10);
}

// 깊이 우선 탐색
void dfs(GraphMatType* g, int start, int target) {
    // 스택 활용
    int stack[MAX_VERTICES];
    int top = -1;
    int visited[MAX_VERTICES] = { 0 };
    int movecount = 0;

    stack[++top] = start;
    printf("%d ", start);   // 시작 값 출력
    visited[start] = 1;

    while (top != -1) {
        int vertex = stack[top];

        if (vertex == target) {
            printf("\n탐색 성공: %d\n", target);
            printf("방문한 노드의 수: %d\n", movecount);
            return;
        }

        int found = 0;
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[vertex][i] == 1) {
                if (!visited[i] || i == target) {
                    stack[++top] = i;
                    printf("%d ", i);
                    if (!visited[i]) {
                        visited[i] = 1;
                        movecount++;
                    }
                    found = 1;
                    break;
                }
            }
        }
        if (!found) {
            top--;
            if (top >= 0) {
                printf("%d ", stack[top]);
                movecount++;
            }
        }
    }
    printf("\n탐색 실패! %d를 발견하지 못했습니다 \n", target);
    printf("방문한 노드의 수 : %d\n", movecount);
}

// 너비 우선 탐색
void bfs(GraphMatType* g, int start, int target) {
    // 큐 활용
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;
    int visited[MAX_VERTICES] = { 0 };
    int movecount = 0;

    queue[rear++] = start;
    visited[start] = 1;

    while (front != rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);

        if (vertex == target) {
            printf("\n탐색 성공 : %d\n", target);
            printf("방문한 노드의 수 : %d\n", movecount);
            return;
        }
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[vertex][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
                movecount++;
            }
        }
    }
    printf("\n탐색 실패! %d를 발견하지 못했습니다\n", target);
    printf("방문한 노드의 수 : %d\n", movecount);
}

// 유저 인터페이스
void user_interface(GraphMatType* g) {
    printf("-----------------------\n");
    printf("| 1 : 깊이 우선 탐색  |\n");
    printf("| 2 : 너비 우선 탐색  |\n");
    printf("| 3 : 종료            |\n");
    printf("-----------------------\n\n");

    while (1) {
        int menu;
        printf("메뉴 입력 : ");
        scanf_s("%d", &menu);

        int start, target;

        switch (menu) {
        case 1:
            printf("시작 번호와 탐색할 값 입력 : ");
            scanf_s("%d %d", &start, &target);
            dfs(g, start, target);
            printf("\n");
            break;
        case 2:
            printf("시작 번호와 탐색할 값 입력 : ");
            scanf_s("%d %d", &start, &target);
            bfs(g, start, target);
            printf("\n");
            break;
        case 3:
            printf("[프로그램 종료]\n");
            exit(0);
            break;
        default:
            printf("[잘못된 입력 >> 재입력]\n");
            printf("\n");
        }
    }
}

// 메인 함수
int main() {
    GraphMatType* g = create_graph();
    init_graph(g);
    generate_graph(g);

    user_interface(g);

    destroy_graph(g);
    return 0;
}