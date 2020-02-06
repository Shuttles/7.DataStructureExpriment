/*************************************************************************
	> File Name: 1.1.Sequence_Stack.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月13日 星期三 13时48分22秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Stack {
    int *data;
    int size;
    int top;
} Stack;

Stack *init_Stack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->size = n;
    s->top = -1;
    return s;
}


void clear_Stack(Stack *s) {
    if (!s) return;
    free(s->data);
    free(s);
    return;
}

int empty(Stack *s) {
    if (!s) return 0;
    return s->top == -1;
}

int full(Stack *s) {
    if (!s) return 0;
    return s->top + 1 == s->size;
}

int top(Stack *s) {
    if (empty(s)) return 0;
    return s->data[s->top];
}


int push(Stack *s, int val) {
    if (!s) return 0;
    if (s->top + 1 == s->size) return 0;
    s->data[++s->top] = val;
    return 1;
}

int pop(Stack *s) {
    if (!s) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void let_empty(Stack *s) {
    if (!s) return;
    if (empty(s)) return;
    while (!empty(s)) pop(s);
    return;
}

void output(Stack *s) {
    if (!s) return;
    printf("Stack = [");
    for (int i = 0; i <= s->top; i++) {
        (i != 0) && printf(", ");
        printf("%d", s->data[i]);
    }
    printf("]\n");
    return;
}

int main() {
    Stack *s = init_Stack(2);
    srand(time(0));
    #define max_op 20
    int op, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 10;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2:
            case 3: {
                int temp = push(s, val);
                printf("push %d to Stack ", 
                      val);
                temp ? printf("successfully\n") : printf("unsuccessfully\n");
                output(s);
                printf("\n");
            } break;
            case 4: 
            case 5: 
            case 6: {
                if (empty(s)) {
                    printf("The Stack is empty now, so it cannot  pop\n");
                    continue;
                }
                printf("pop %d from the Stack  ", top(s));
                int temp = pop(s);
                temp ? printf("successfully\n") : printf("unsuccessfully\n");
                output(s);
                printf("\n");
            } break;
            case 7: 
            case 8: {
                empty(s) ? printf("The Stack is empty\n") : printf("The Stack is not empty\n");
                output(s);
                printf("\n");
            } break;
            case 9:{
                printf("Let the Stack empty\n");
                let_empty(s);
                output(s);
                printf("\n");
            } break;
        }
    }
    clear_Stack(s);
    return 0;
}

