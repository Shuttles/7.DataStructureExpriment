/*************************************************************************
	> File Name: 1.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年12月04日 星期三 10时12分31秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(a, b) {\
    __typeof(a) temp = a;\
    a = b; b = temp;\
}


void select_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;  //将当前下标定义为最小值下标
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) min = j; //如果有小于当前最小值的关键字，将此关键字的下标赋值给min
        }
        if (min- i) swap(arr[i], arr[min]);//如果min不等于i说明找到最小值，交换
    }
}


void quick_sort(int *arr, int left, int right) {
    int i, j, t, temp;
    if (right < left) return; //如果right<left说明以及快排完成了
    temp = arr[left];//先把基准数存起来
    i = left;
    j = right;
    while (i != j) { //当i、j指针没有碰上时一直循环
        while (arr[j] >= temp && i < j) 
            j--;
        while (arr[i] <= temp && i < j) 
            i++;
        if (i < j) swap(arr[i], arr[j]);
    }
    //最后基准数归位
    arr[left] = arr[j];
    arr[j] = temp;
    //底下就是分治思想的体现了，(利用递归)把左边和右边分别进行快速排序
    quick_sort(arr, left, i - 1);
    quick_sort(arr, i + 1, right);
    return;
}


void insert_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] >= arr[i - 1]) continue; //如果已经有序，那么这一位就不用排序了
        int temp = arr[i];  //设置哨兵
        int j;
        for (j = i - 1; j >= 0 && arr[j] > temp; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    } 
    return;
}

void output(int *arr, int n) {
    printf("arr(%d) = [", n);
    for (int i = 0; i < n; i++) {
        i && printf(", ");
        printf("%d", arr[i]);
    }
    printf("]\n");
}

int main() {
    #define max_op 10
    srand(time(0));
    int *arr = (int *)malloc(sizeof(int) * max_op);
    for (int i = 0; i < max_op; i++) {
        arr[i] = rand() % 100;
    }
    output(arr, max_op);
    int x;
    printf("输入1进行直接插入排序， 输入2进行快速排序，输入3进行直接选择排序\n");
    scanf("%d", &x);
    switch (x) {
        case 1: {
            printf("直接插入排序的结果为: ");
            insert_sort(arr, max_op);
            output(arr, max_op);
            printf("\n");
        } break;
        case 2: {
            printf("快速排序的结果为: ");
            quick_sort(arr, 0, max_op - 1);
            output(arr, max_op);
            printf("\n");
        } break;
        case 3: {
            printf("直接选择排序的结果为: "); 
            select_sort(arr, max_op);
            output(arr, max_op);
            printf("\n");
        } break;
    }
    return 0;
}
