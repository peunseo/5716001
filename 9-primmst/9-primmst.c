#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

// �׷��� ����ü ����
typedef struct GraphType {
    int n; // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES]; // ���õ� ����
int distance[MAX_VERTICES]; // �ּ� ����ġ �迭

// �׷��� �ʱ�ȭ
void graph_init(GraphType* g) {
    g->n = 10; // ������ ���� 10
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i == j)
                g->weight[i][j] = 0; // �ڱ� �ڽ����� ���� ������ ����ġ�� 0
            else
                g->weight[i][j] = INF; // �������� ���Ѵ�� �ʱ�ȭ
        }
    }
    for (int i = 0; i < MAX_VERTICES; i++) {
        selected[i] = FALSE; // ���� ���� ���� �ʱ�ȭ
        distance[i] = INF;   // �ּ� ����ġ �ʱ�ȭ
    }
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w) {
    g->weight[start][end] = w;
    g->weight[end][start] = w;
}

// �׷����� ���� �Լ�
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

// �ּ� dist[v] ���� ���� ���� ��ȯ
int get_min_vertex(int n) {
    int v = -1;
    for (int i = 1; i <= n; i++) { // 1�� ���� ����
        if (!selected[i]) {
            if (v == -1 || distance[i] < distance[v]) {
                v = i;
            }
        }
    }
    return v;
}

// Prim Ž�� �� ���
void FindPrimMST(GraphType* g) {
    printf("Prim MST Algorithm\n");
    int u, v;
    int s = 1; // ���� ���� ���� (1�� �������� ����)

    distance[s] = 0;  // �ʱ�ȭ

    for (int i = 1; i <= g->n; i++) {
        u = get_min_vertex(g->n);
        selected[u] = TRUE;

        if (distance[u] == INF) return; // ������� ���� ���
        printf("���� %d �߰�\n", u);

        // ���õ� ������ ������ �������� ����ġ ������Ʈ
        for (v = 1; v <= g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v]) {
                if (g->weight[u][v] < distance[v]) {
                    distance[v] = g->weight[u][v];
                }
            }
        }
    }
}

// ���� �Լ�
int main(void)
{
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g); //�׷����� �����ϴ� �Լ�

    FindPrimMST(g); //Prim�� �̿��� MST�� ã��

    free(g);
    return 0;
}