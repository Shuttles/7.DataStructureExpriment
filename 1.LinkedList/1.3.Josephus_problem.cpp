/*************************************************************************
	> File Name: 1.3.Josephus_problem.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月10日 星期日 23时42分50秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define max_n 100

typedef struct Vector {
    int *data;
    int length, size;
} Vector;

Vector *init_Vector(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int * )malloc(sizeof(int) * n);
    vec->size = n;
    vec->length = 0;
    return vec;
}

int expand(Vector *vec) {
    if (!vec) return 0;
    int new_size = vec->size;
    int *p;
    while (new_size) {
        p = (int *)realloc(vec->data, sizeof(int) * (vec->size + new_size));
        if (p) break;
        new_size /= 2;
    }
    if (!p) return 0;
    vec->size += new_size;
    vec->data = p;
    return 1;
}

int insert(Vector *vec, int ind, int val) {
    if (!vec) return 0;
    if (vec->length == vec->size) {
        if (!expand(vec)) return 0;
        printf("expand Vector size to %d successfully\n", vec->size);
    }
    if (ind < 0 || ind > vec->length) return 0;
    for (int i = vec->length; i > ind; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[ind] = val;
    vec->length += 1;
    return 1;
}

int erase(Vector *vec, int ind) {
    if (!vec) return 0;
    //if (!vec->length) return 0;  发现不需要这行代码
    if (ind < 0 || ind >= vec->length) return 0;
    for (int i = ind + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void clear_Vector(Vector *vec) {
    if (!vec) return ;
    free(vec->data);
    free(vec);
    return ;
}

void output(Vector *vec) {
    if (!vec) return ;
    printf("Vector(%d) = [", vec->size);
    for (int i = 0; i < vec->length; i++) {
        i && printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("]\n");
    return ;
}

void output_ans(int *ans) {                           //输出结果数组
    printf("正确的出列顺序为:[");
    for (int i = 1; ans[i]; i++) {
        (i == 1) || printf(",");
        printf("%d", ans[i]);
    }
    printf("]\n");
    return;
}


int main() {
    int ans[max_n + 5] = {0};
    int n, m;
    printf("请输入人数n和密码m:\n");
    scanf("%d%d", &n, &m);
    Vector *vec = init_Vector(n);
    //给顺序表每一项赋值
    for (int i = 0; i < n; i++) {
        insert(vec, i, i + 1);
    }
    output(vec);
    //int sum = n;
    int count1 = n;
    int ind = m, i = 1;
    ans[i++] = vec->data[ind - 1];
    vec->data[ind - 1] = 0;
    count1 -= 1;
    while (count1--) {
        int count2 = 1;
        while (count2 < m) {
            if (!vec->data[ind - 1]) {
                ind += 1;
                if (ind > vec->length) ind -= vec->length;
                continue;
            }
            ind += 1;
            if (ind > vec->length) ind -= vec->length;
            count2 += 1;
        }
        printf("ind = %d\n", ind);
        ans[i++] = vec->data[ind - 1];
        //printf("erase item at %d from the Vector = %d\n", ind, erase(vec, ind - 1));
        //output(vec);
        //printf("\n");
    }
    output_ans(ans);
    return 0;
}
