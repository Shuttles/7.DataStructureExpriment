#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define INFINITY INT16_MAX
#define MAX_N 500

int n, m, k;

typedef struct Graph {
    int mat[MAX_N + 5][MAX_N + 5];   //图的邻接矩阵
    int n;                           //图的总共顶点数
    int visited[MAX_N + 5];          //标志这个顶点是否被访问过的标志数组
} Graph;

void init(Graph *g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->mat[i][j] = INFINITY;
        }
    }
    memset(g->visited, 0, sizeof(g->visited));
    return;
}

void insert(Graph *g, int x, int y, int weight) {
    if (x < 0 || x >= g->n || y < 0 || y >= g->n) return;
    g->mat[x][y] = weight;
    g->mat[y][x] = weight;
    return;
}

void output(Graph *g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%d         ", g->mat[i][j]);
        }
        printf("\n");
    }
    return;
}

typedef struct Queue {
    int *data;
    int head, tail, length;
} Queue;

void init_queue(Queue *q, int length_input) {
    q->data = (int *)malloc(sizeof(int) * length_input);
    q->length = length_input;
    q->head = 0;
    q->tail = -1;
    return;
}

void push(Queue *q, int x) {
    if (q->tail + 1 < q->length) {
        q->tail++;
        q->data[q->tail] = x;
    }
    return;
}

int front(Queue *q) {
    return q->data[q->head];
}

void pop(Queue *q) {
    q->head++;
}

int empty(Queue *q) {
    if (q->head > q->tail)   return 1;
    return 0;
}

void clear_queue(Queue *q) {
    free(q->data);
    free(q);
}

void dfs(Graph *g, int vertex) {
    printf("%d ", vertex);            //首先访问这个顶点
    g->visited[vertex] = 1;           //设置标记访问数组为1表示这个顶点以及访问过了
    for (int i = 0; i < n; i++) {     //遍历这个顶点的邻接顶点
        if (g->mat[vertex][i] == INFINITY) continue;  //如果没有边则跳过
        if (g->visited[i]) continue;
        g->visited[i] = 1;           //如果这个邻接顶点没有被访问过则继续递归深搜这个顶点
        dfs(g, i);
    }
    return ;
}


void bfs(Graph *g, int start_vertex) {
    Queue *queue = (Queue *)malloc(sizeof(Queue));     //利用队列来解决广搜
    init_queue(queue, g->n);
    push(queue, start_vertex);                         //首先将开始访问的顶点入队列
    g->visited[start_vertex] = 1;                      //标记这个顶点已访问
    while (!empty(queue)) {                             //循环终止的条件为队列空
        int vertex = front(queue);
        printf("%d ", vertex);                          //访问这个顶点
        pop(queue);                                    //使这个顶点出队列
        for (int i = 0; i < n; i++) {                  //依次访问这个顶点的邻接顶点
            if (g->mat[vertex][i] == INFINITY) continue;  //如果没有边则跳过
            if (g->visited[i]) continue;                //如果这个邻接顶点没有被访问过
            g->visited[i] = 1;
            push(queue, i);                             //使这个顶点入队列
        }
    }
    return;
}

void get_Adj(Graph *g, int temp) {
    printf("%d号的邻接顶点有: ", temp);
    for (int i = 0; i < n; i++) {
        if (g->mat[temp][i] == INFINITY) continue;
        printf("%d ", i);
    }
    printf("\n");
    return;
}

int main() {
    printf("请输入图的顶点个数和边数\n");
    scanf("%d%d", &n, &m);
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    init(graph, n);
    printf("请分别输入每一条边(由某个顶点指向某个顶点)以及它们的权重\n");
    for (int i = 0; i < m; i++) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        insert(graph, x, y, w);
    }
    printf("您刚刚输入的图的邻接矩阵表现为:\n");
    output(graph);
    printf("输入一个顶点编号，你可以得到它的邻接顶点\n");
    int temp;
    scanf("%d", &temp);
    get_Adj(graph, temp);
    printf("请输入最先开始遍历的顶点编号\n");
    scanf("%d", &k);
    printf("深度优先遍历的顺序为:\n");
    dfs(graph, k);
    printf("\n");
    memset(graph->visited, 0, sizeof(graph->visited));
    printf("广度优先遍历的顺序为:\n");
    bfs(graph, k);
    return 0;
}
