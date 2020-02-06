/*************************************************************************
	> File Name: 1.1.zhongzhuiqiuzhi.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月12日 星期二 22时09分34秒
 ************************************************************************/
 //第一版写到2019.11.13 凌晨3:31 我的想法是用二维数组来存多位数，后来发现这种方法不好转后缀表达式(因为有可能操作数和操作符的asiII码重复)
 //2019.11.13 17:20经过朱霄大佬的指点发现可以不用二维数组来表示，而是还用字符数组来存表达式，碰到操作符就把之前的数算出来，存到操作数栈中；
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#define ERROR INT32_MIN
#define max_n 100

char input[max_n + 5][max_n +5];                                       //定义二维数组来存表达式

typedef struct Stack {
    int *data;
    int size, top;
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
    if (!s) return 1;
    return s->top == -1;
}

int top(Stack *s) {
    if (!s) return 0;
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

void output(Stack *s) {
    if (!s) return ;
    for (int i = 0; i <= s->top; i++) {
        if (s->data[i]) {
            printf("%d ", s->data[i]);
        } else {
            printf("%c ", s->data[i]);
        }
    }
    printf("\n");
    return;
}

int is_num(char input[]) {
    for (int i = 0; input[i]; i++) {
        if (input[i] < 48 || input[i] > 57) return 0;            //表明这个肯定不是数
    }
    return 1;
}

int transform_num(char input[]) {
    int ans = 0;
    int len = strlen(input);
    for (int i = 0; input[i]; i++) {
        ans += (input[i] & 15) * pow(10, len - i - 1);
    }
    return ans;
}

int precede(char a, char b) {                          //用来判断运算符优先级的函数
    switch (a) {
        case '+': 
        case '-': {
            switch (b) {
                case '*':
                case '/':
                case '(': return 0;
                default : return 1;
            }
        } break;
        case '*': 
        case '%':
        case '/': {
            switch (b) {
                case '(': return 0;
                default: return 1;
            }
        } break;
        case '(': {
            switch (b) {
                case ')': return -1;
                case '#': return ERROR;
                default : return 0;
            }
        } break;
        case ')': {
            switch (b) {
                case '(': return ERROR;
                default: return 1;
            }
        } break;
        /*
        case '#': {
            switch (b) {
                case '#': return -1;
                case ')': return ERROR;
                default: return 0;
            }
        } break;
        */
    }
    return ERROR;
}

int operate(char op, int a, int b) {                   //用来进行最底层运算的函数
    switch (op) {
        case '+': return a + b;
        case '-': return b - a;
        case '*': return a * b;
        case '/': return b / a;
        case '%': return b % a;
        default : {
            printf("wjlytsl\n");
            return ERROR;
        } 
    }
    return ERROR;
}

void calc(Stack *OPND, Stack *OPTR) {                  //用来计算两个操作数和一个操作符的函数
    if (!OPND || !OPTR) return;
    int a = top(OPND);
    pop(OPND);
    int b = top(OPND);
    pop(OPND);
    push(OPND, operate(top(OPTR), a, b));
    pop(OPTR);
    return;
}

int n, m;

void get_value1(Stack * OPND, Stack *OPTR) {
    int i = 0;
    while (i < n) {                          //外循环控制整个表达式的读取
        if (is_num(input[i])) {              //如果是数字
            push(OPND, transform_num(input[i]));
            i++;
        } else {                                       //如果是操作符
            if (empty(OPTR) || precede(top(OPTR), input[i][0]) == 0) {     //如果栈空或者这个操作符比栈顶操作符优先级高，就入栈;
                push(OPTR, input[i][0]);
                i++;
            } else if (precede(top(OPTR), input[i][0]) == -1){             //如果他俩优先级相同说明是(和)，就删除他俩;
                pop(OPTR);
                i++;
            } else {                                                     //如果不是上述两种情况就让操作数前两个数和操作符栈顶操作符进行运算并压到操作数栈中
                calc(OPND, OPTR);
            }
        }        
    }
    while (!empty(OPTR)) {                             //如果操作符栈中还有操作符就继续计算表达式
        calc(OPND, OPTR);
    }
    return ;
}


int get_value3(Stack *expression3) {
    Stack *ans = init_Stack(n);
    int i = 0;
    while (i <= expression3->top) {
        if (is_num(input[i])) {                        //如果是数字
            push(ans, input[i]);
            i++;
        } else {
            int a = top(expression3);
            pop(expression3);
            int b = top(expression3);
            pop(expression3);
            push(ans)
        }
    }
    while (!empty(expression3)) {
            
    }
    int ans = top(expression3);
    clear_Stack(ans);
    return ans;
}


Stack *transform3() {
    Stack *OPND = init_Stack(n);
    Stack *OPTR = init_Stack(n);
    int i = 0;
    while (i < n) {
        if (is_num(input[i])) {
            push(OPND, transform_num(input[i]));
            i++;
        } else {
            if (input[i][0] == '(') {
                push(OPTR, input[i][0]);
                i++;
            } else if (input[i][0] == ')') {
                        while (top(OPTR) != '(') {
                            push(OPND, top(OPTR));
                            pop(OPTR);
                        }
                        pop(OPTR);
                        i++;
                    } else  {
                        printf("%d\n", top(OPTR));
                        while ((!empty(OPTR)) && (top(OPTR) != '(') && (precede(top(OPTR), input[i][0]) != 0)) {
                            push(OPND, top(OPTR));
                            pop(OPTR);
                        }
                        push(OPTR, input[i][0]);
                        i++;
                    }    
        }
    }
    while (!empty(OPTR)) {
        push(OPND, top(OPTR));
        pop(OPTR);
    }
    clear_Stack(OPTR);
    return OPND; 
}


int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", input[i]);
    }
    Stack *OPND = init_Stack(n);
    Stack *OPTR = init_Stack(n);                       //建两个栈分别来存操作数和操作符
    get_value1(OPND, OPTR);                     //调用表达式求值函数求值 
    printf("该中缀表达式的正确结果 = %d\n", top(OPND));
    Stack *expression3 = transform3();
    printf("该中缀表达式的后缀表达式 = ");
    output(expression3);
    clear_Stack(OPND);
    clear_Stack(OPTR);                                      //回收动态分配的内存以防内存泄漏
    return 0;
}

