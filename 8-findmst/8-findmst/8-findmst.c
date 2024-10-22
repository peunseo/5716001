#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

void set_init(int n){
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int curr){
	if (parent[curr] == -1)
		return curr; 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

void set_union(int a, int b){
	int root1 = set_find(a); // 노드 a의 루트를 찾는다. 
	int root2 = set_find(b); // 노드 b의 루트를 찾는다. 
	if (root1 != root2) // 합친다. 
		parent[root1] = root2;
}

// 간선 구조체
struct Edge {
	int start, end, weight;
};

// 그래프 구조체
typedef struct GraphType {
	int n;
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// 힙 구조체
typedef struct {
	struct Edge heap[2 * MAX_VERTICES];
	int heap_size;
} MinHeap;

// 그래프 초기화
void graph_init(GraphType* g) {
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// 최소 힙 초기화
void minheap_init(MinHeap* h) {
	h->heap_size = 0;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

// qsort()에 사용되는 함수
int compare(const void* a, const void* b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

// 그래프 생성
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

// quick 기반 kruskal
void QuickKruskal(GraphType* g)
{
	printf("Quick Based Kruskal \n");
	int edge_accepted = 0; // 현재까지 선택된 간선의 수	
	int uset, vset; // 정점 u와 정점 v의 집합 번호
	struct Edge e;

	set_init(g->n); // 집합 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	int i = 0;
	while (edge_accepted < (g->n - 1) && i < g->n) // 간선의 수 < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start); // 정점 u의 집합 번호 
		vset = set_find(e.end); // 정점 v의 집합 번호
		if (uset != vset) { // 서로 속한 집합이 다르면
			printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset); // 두개의 집합을 합친다.
		}
		i++;
	}
}

// 최소 힙 삽입
void minheap_insert(MinHeap* h, struct Edge edge) {
	int i = h->heap_size++;
	while (i > 0) {
		int parent = (i - 1) / 2;
		if (h->heap[parent].weight <= edge.weight) break;
		h->heap[i] = h->heap[parent];
		i = parent;
	}
	h->heap[i] = edge;
}

// 최소 힙 삭제
struct Edge minheap_delete(MinHeap* h) {
	struct Edge minEdge = h->heap[0];
	struct Edge lastEdge = h->heap[--h->heap_size];
	int parent = 0;
	int child;

	while ((child = 2 * parent + 1) < h->heap_size) {
		if (child + 1 < h->heap_size && h->heap[child].weight > h->heap[child + 1].weight) {
			child++;
		}
		if (lastEdge.weight <= h->heap[child].weight) break;
		h->heap[parent] = h->heap[child];
		parent = child;
	}
	h->heap[parent] = lastEdge;
	return minEdge;
}

// minheap 기반 kruskal
void MinHeapKruskal(GraphType* g) {
	printf("\nMinHeap Based Kruskal \n");
	int edge_accepted = 0; // 현재까지 선택된 간선의 수
	int uset, vset; // 정점 u와 정점 v의 집합 번호
	struct Edge e;

	MinHeap h;
	minheap_init(&h); // 힙 초기화
	set_init(g->n); // 집합 초기화

	// 모든 간선을 최소 힙에 삽입
	for (int i = 0; i < g->n; i++) {
		minheap_insert(&h, g->edges[i]);
	}

	// 간선 선택
	while (edge_accepted < (g->n - 1) && h.heap_size > 0) {
		e = minheap_delete(&h); // 최소 힙에서 간선 삭제
		uset = set_find(e.start); // 정점 u의 집합 번호 
		vset = set_find(e.end); // 정점 v의 집합 번호
		if (uset != vset) { // 서로 속한 집합이 다르면
			printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset); // 두 개의 집합을 합친다.
		}
	}
}

// 메인
int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	GenerateGraph(g);

	QuickKruskal(g); // quick 기반 kruskal
	MinHeapKruskal(g); // minheap 기반 kruskal

	free(g);
	return 0;
}