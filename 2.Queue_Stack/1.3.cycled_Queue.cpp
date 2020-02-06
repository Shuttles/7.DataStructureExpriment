/*************************************************************************
	> File Name: 1.3.cycled_Queue.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月13日 星期三 13时50分10秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int *data;
    int head, tail, length, count;                            //count代表循环队列的元素的个数
} Queue;

Queue *init_Queue(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->length = n;
    q->head = q->tail = q->count = 0;                         //q->tail指向第一个空的空间
    return q;
}

int empty(Queue *q) {
    return q->count == 0;
} 

int front(Queue *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    return q->data[q->head];    
}

void clear_Queue(Queue *q) {
    if (!q) return;
    free(q->data);
    free(q);
    return ;
}

int push(Queue *q, int val) {
    if (!q) return 0;
    if (q->count == q->length) return 0;
    q->data[q->tail] = val;
    q->tail += 1;
    if (q->tail == q->length) q->tail -= q->length;
    q->count += 1;
    return 1;
}

int pop(Queue *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    q->head++;
    if (q->head == q->length) q->head -= q->length;
    q->count -= 1;
    return 1;
}

void let_empty(Queue *q) {
    if (!q) return;
    if (empty(q)) return;
    while (!empty(q)) pop(q);
    return;
}

void output(Queue *q) {
    if (!q) return;
    printf("Queue(%d) = [", q->count);
    for (int i = q->head, j = 0; j < q->count; j++) {
        j && printf(", ");
        printf("%d", q->data[(i + j) % q->length]);
    }
    printf("]\n");
    return;
} 

int main() {
    #define max_op 20
    Queue *q = init_Queue(2);
    srand(time(0));
    int op, ind, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 10;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: 
            case 3: {
                int temp = push(q, val);
                printf("push %d to Queue ", val);
                temp ? printf("successfully\n") : printf("unsuccessfully\n");
                output(q);
                printf("\n");
            } break;
            case 4:
            case 5: {
                if (empty(q)) {
                    printf("The Stack is empty now, so it cannot  pop\n");
                    printf("\n");
                    continue;
                }
                printf("pop %d from Queue successfully\n", front(q));
                pop(q);
                output(q);
                printf("\n");
            } break;
            case 6:
            case 7: {
                empty(q) ? printf("The Queue is empty\n") : printf("The Queue is not empty\n");
                output(q);
                printf("\n");
            } break;
            case 8: 
            case 9: {
                printf("Let the Queue empty\n");
                let_empty(q);
                output(q);
                printf("\n");
            } break;
        }
    }
    clear_Queue(q);
    return 0;
}

