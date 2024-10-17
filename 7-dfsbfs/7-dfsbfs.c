#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

// �׷��� ����ü ����
typedef struct GraphMatType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

// �׷��� ����
GraphMatType* create_graph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}

// �׷��� ����
void destroy_graph(GraphMatType* g) {
    free(g);
}

// �׷��� �ʱ�ȭ
void init_graph(GraphMatType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

// vertex ����
void insert_vertex_graph(GraphMatType* g,int v) {
    if (g->n >= MAX_VERTICES) {
        fprintf(stderr, "Over number of vertex\n");
        return;
    }
    (g->n)++;
}

// edge ����
void insert_edge_graph(GraphMatType* g, int s, int e) {
    if (s >= g->n || e >= g->n) {
        fprintf(stderr, "vertex number error\n");
        return;
    }
    g->adj_mat[s][e] = 1;
    g->adj_mat[e][s] = 1;
}

// �׷��� ����
void generate_graph(GraphMatType* g) {
    // ���� ����
    for (int i = 0; i < 11; i++)
        insert_vertex_graph(g,i);

    // ���� ����
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

// ���� �켱 Ž��
void dfs(GraphMatType* g, int start, int target) {
    // ���� Ȱ��
    int stack[MAX_VERTICES];
    int top = -1;
    int visited[MAX_VERTICES] = { 0 };
    int movecount = 0;

    stack[++top] = start;
    printf("%d ", start);   // ���� �� ���
    visited[start] = 1;

    while (top != -1) {
        int vertex = stack[top];

        if (vertex == target) {
            printf("\nŽ�� ����: %d\n", target);
            printf("�湮�� ����� ��: %d\n", movecount);
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
    printf("\nŽ�� ����! %d�� �߰����� ���߽��ϴ� \n", target);
    printf("�湮�� ����� �� : %d\n", movecount);
}

// �ʺ� �켱 Ž��
void bfs(GraphMatType* g, int start, int target) {
    // ť Ȱ��
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
            printf("\nŽ�� ���� : %d\n", target);
            printf("�湮�� ����� �� : %d\n", movecount);
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
    printf("\nŽ�� ����! %d�� �߰����� ���߽��ϴ�\n", target);
    printf("�湮�� ����� �� : %d\n", movecount);
}

// ���� �������̽�
void user_interface(GraphMatType* g) {
    printf("-----------------------\n");
    printf("| 1 : ���� �켱 Ž��  |\n");
    printf("| 2 : �ʺ� �켱 Ž��  |\n");
    printf("| 3 : ����            |\n");
    printf("-----------------------\n\n");

    while (1) {
        int menu;
        printf("�޴� �Է� : ");
        scanf_s("%d", &menu);

        int start, target;

        switch (menu) {
        case 1:
            printf("���� ��ȣ�� Ž���� �� �Է� : ");
            scanf_s("%d %d", &start, &target);
            dfs(g, start, target);
            printf("\n");
            break;
        case 2:
            printf("���� ��ȣ�� Ž���� �� �Է� : ");
            scanf_s("%d %d", &start, &target);
            bfs(g, start, target);
            printf("\n");
            break;
        case 3:
            printf("[���α׷� ����]\n");
            exit(0);
            break;
        default:
            printf("[�߸��� �Է� >> ���Է�]\n");
            printf("\n");
        }
    }
}

// ���� �Լ�
int main() {
    GraphMatType* g = create_graph();
    init_graph(g);
    generate_graph(g);

    user_interface(g);

    destroy_graph(g);
    return 0;
}