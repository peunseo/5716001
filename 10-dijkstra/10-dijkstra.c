//#include <stdio.h>
//#include <stdlib.h>
//#include <limits.h>
//
//#define TRUE 1
//#define FALSE 0
//#define MAX_VERTICES 11
//#define INF 1000000
//
//// ���� ����ü ����
//typedef struct Edge {
//    int vertex, weight;
//    struct Edge* next;
//} Edge;
//
//// �׷��� ����ü ����
//typedef struct GraphType {
//    int n;
//    Edge* adj_list[MAX_VERTICES];
//} GraphType;
//
//int distances[MAX_VERTICES];
//int visited[MAX_VERTICES];
//int visitOrder[MAX_VERTICES];
//
//// �׷��� �ʱ�ȭ
//void graph_init(GraphType* g) {
//    g->n = 0;
//    for (int i = 1; i < MAX_VERTICES; i++) {
//        g->adj_list[i] = NULL;
//    }
//}
//
//// ���� �߰�
//void insert_edge(GraphType* g, int start, int end, int weight) {
//    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
//    new_edge->vertex = end;
//    new_edge->weight = weight;
//    new_edge->next = g->adj_list[start];
//    g->adj_list[start] = new_edge;
//}
//
//// �湮���� ���� ���� �� �ּ� �Ÿ� ���� ����
//int shortest_path(int* distance, int n, int* visited) {
//    int min = INF;
//    int minIndex = -1;
//
//    for (int i = 1; i <= n; i++) {
//        if (distance[i] < min && !visited[i]) { // �ּ� �Ÿ� ���� ã��
//            min = distance[i];
//            minIndex = i;
//        }
//    }
//    return minIndex;    // �ּ� �Ÿ� ���� �ε��� ��ȯ
//}
//
//// ���ͽ�Ʈ�� �˰��� ����
//void Dijkstra(GraphType* g) {
//    
//    // �ʱ� �Ÿ� �� �湮 ���� ���� (�ʱ�ȭ)
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
//        // ������� �Ÿ� ���
//        printf("Distance : ");
//        for (int i = 1; i <= g->n; i++) {
//            if (distances[i] == INF)
//                printf("* ");
//            else
//                printf("%d ", distances[i]);
//        }
//
//        // �湮 ���� ���
//        printf("\nFound    : ");
//        for (int i = 1; i <= g->n; i++) {
//            printf("%d ", visited[i]);
//        }
//        printf("\n\n");
//
//        // ���� ������ �Ÿ� ������Ʈ
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
//    // ���� �湮 ������ ���
//    printf("Found Order : ");
//    for (int i = 1; i <= g->n; i++) {
//        if (visitOrder[i] != -1) {
//            printf("%d ", visitOrder[i]);
//        }
//    }
//    printf("\n");
//}
//
//// �׷��� ����
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
//// ����
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