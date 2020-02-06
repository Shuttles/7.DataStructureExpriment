/*************************************************************************
	> File Name: 1.2.LinkedStack.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月13日 星期三 14时04分44秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct LinkedStack {
    StackNode head;
    int length;
    StackNode *top;
}LinkedStack;

StackNode *init_StackNode(int val) {
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->data = val;
    p->next = NULL;
    return p;
}

LinkedStack *init_LinkedStack() {
    LinkedStack *s = (LinkedStack *)malloc(sizeof(LinkedStack));
    s->head.next = NULL;
    s->length = 0;
    s->top = &(s->head);//初始栈顶指针指向虚拟头结点
}

void clear_StackNode(StackNode *p) {
    if (!p) return ;
    free(p);
    return ;
}

void clear_LinkedStack(LinkedStack *s) {
    if (!s) return;
    StackNode *p = s->head.next, *q;
    while (p) {
        q = p->next;
        clear_StackNode(p);
        p = q;
    }
    free(s);
}

int empty(LinkedStack *s) {
    if (!s) return 1;
    return s->length == 0;
}

int top(LinkedStack *s) {
    if (!s) return 0;
    if (empty(s)) return 0;
    return s->top->data;
}

int push(LinkedStack *s, int val) {
    if (!s) return 0;
    StackNode *p = init_StackNode(val);
    s->top->next = p;
    s->top = p;
    s->length += 1;
    return 1;
}

int pop(LinkedStack *s) {
    if (!s) return 0;
    if (empty(s)) return 0;
    StackNode *p = &(s->head);
    while (p->next != s->top) p = p->next;
    clear_StackNode(s->top);
    s->top = p;
    p->next = NULL;
    s->length -= 1;
    return 1;
}

void let_empty(LinkedStack *s) {
    if (!s) return ;
    if (empty(s)) return;
    while (!empty(s)) pop(s);
    return;
}

void output(LinkedStack *s) {
    if (!s) return;
    printf("The LinkedStack(%d) = [", s->length);
    StackNode *p = s->head.next;
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL]\n");
    return ;
}

int main() {
    LinkedStack *s = init_LinkedStack();
    #define max_op 20
    srand(time(0));
    int op, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 10;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2:
            case 3: {
                printf("Push %d at the LinkedStack ", val);
                int temp = push(s, val);
                temp ? printf("successfully\n") : printf("unsuccessfully\n");
                output(s);
                printf("\n");
            } break;
            case 4: 
            case 5:
            case 6: {
                if (empty(s)) {
                    printf("The LinkedStack is empty,so it cannot pop\n");
                    printf("\n");
                    continue;
                }
                printf("Pop %d at the LinkedStack ", top(s));
                int temp = pop(s);
                temp ? printf("successfully\n") : printf("unsuccessfully\n");
                output(s);
                printf("\n");
            } break;
            case 7:
            case 8: {
                printf("Let the LinkedStack empty\n");
                let_empty(s);
                output(s);
                printf("\n");
            } break;
            case 9: {
                empty(s) ? printf("The LinkedStack is empty\n") : printf("The LinkedStack is not empty\n");
                output(s);
                printf("\n");
            } break;
        }
    }
    clear_LinkedStack(s);
    return 0;
}
