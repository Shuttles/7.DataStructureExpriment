/*************************************************************************
	> File Name: 2.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年12月03日 星期二 21时59分32秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) ({\
    __typeof(a) _a = (a);\
    __typeof(b) _b = (b);\
    _a > _b ? _a : _b;\
})

int expand(int *arr, int n) {
    int length;
    if (n & 1) length = n + 1;
    int new_length = length * 2;
    arr = (int *)realloc(arr, sizeof(int) * new_length);
    if (!arr) return 0;
    if (n & 1) arr[n] = 0;
    for (int i = 0; i < length; i++) {
        arr[i + length] = arr[i];
        arr[i] = 0;
    }
     
    for (int i = 0; i < new_length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return new_length;
}

int Build_Winner_Tree(int *arr, int n) {
    int length = expand(arr, n);
    if (!length) return 0;
    for (int i = 0; i < length; i++) printf("%d ", arr[i]);
    printf("\n");
    for (int i = (length >> 1) - 1; i > 0; i--) {
        int lchild = i << 1, rchild = i << 1 | 1;
        arr[i] = MAX(arr[lchild], arr[rchild]);
    }
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 1;
}


void output(int *arr, int n) {
    printf("arr(%d) = [", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
    return;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) 
        scanf("%d", &arr[i]);
    output(arr, n);
    if (Build_Winner_Tree(arr, n)) {
        printf("锦标赛排序成功！\n");
        printf("最高分为:%d\n", arr[1]);
    } else {
        printf("锦标赛排序不成功！\n");
    }
    return 0;
}
