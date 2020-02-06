/*************************************************************************
	> File Name: 1.4.LinkedQueue.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月13日 星期三 14时33分55秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

typedef struct LinkedQueue {
    QueueNode head;
    int length;
    QueueNode *tail;
} LinkedQueue;

QueueNode *init_QueueNode(int val) {
    QueueNode *p = (QueueNode *)malloc(sizeof(QueueNode));
    p->data = val;
    p->next = NULL;
    return p;
}

LinkedQueue *init_LinkedQueue() {
    LinkedQueue *q = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    q->head.next = NULL;
    q->length = 0;
    q->tail = &(q->head);
    return q;
}

void clear_QueueNode(QueueNode *p) {
    if (!p) return;
    free(p);
    return;
}

void clear_LinkedQueue(LinkedQueue *q) {
    if (!q) return;
    QueueNode *p = q->head.next, *r;
    while (p) {
        r = p->next;
        clear_QueueNode(p);
        p = r;
    }
    free(q);
    return;
}

int empty(LinkedQueue *q) {
    if (!q) return 1;
    return q->length == 0;
}

int front(LinkedQueue *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    return q->head.next->data;
}

int push(LinkedQueue *q, int val) {
    if (!q) return 0;
    QueueNode *p = init_QueueNode(val);
    q->tail->next = p;
    q->tail = p;
    q->length += 1;
    return 1;
}

int pop(LinkedQueue *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    QueueNode *p = q->head.next;
    q->head.next = p->next;
    clear_QueueNode(p);
    if (q->length == 1) q->tail = &(q->head);
    q->length -= 1;
    return 1;
}

void let_empty(LinkedQueue *q) {
    if (!q) return ;
    if (empty(q)) return;
    while (!empty(q)) pop(q);
    return;
}

void output(LinkedQueue *q) {
    if (!q) return;
    printf("LinkedQueue(%d) = [", q->length);
    QueueNode *p = q->head.next;
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL]\n");
    return;
}

int main() {
    #define max_op 20
    LinkedQueue *q = init_LinkedQueue();
    srand(time(0));
    int op, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 10;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1: 
            case 2: 
            case 3:
            case 4: {
                printf("Push %d at the LinkedQueue ", val);
                int temp = push(q, val);
                temp ? printf("successfully\n") : printf("unsuccessfully\n");
                output(q);
                printf("\n");
            } break;
            case 5: 
            case 6: {
                if (empty(q)) {
                    printf("The LinkedQueue is empty, so it cannot pop\n\n");
                    continue;
                }
                printf("Pop %d from the LinkedQueue successfully\n", front(q));
                pop(q);
                output(q);
                printf("\n");
            } break;
            case 7: {
                empty(q) ? printf("The LinkedQueue is empty\n") : printf("The LinkedQueue is not empty\n");
                output(q);
                printf("\n");
            } break;
            case 8: 
            case 9: {
                printf("Let the LinkedQueue empty\n");
                let_empty(q);
                output(q);
                printf("\n");
            } break;
        }
    }
    clear_LinkedQueue(q);
    return 0;
}
