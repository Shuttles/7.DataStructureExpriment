/*************************************************************************
	> File Name: 1.search.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年12月03日 星期二 15时05分17秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(a, b) {\
    __typeof(a) temp = a;\
    a = b; b = temp;\
}

typedef struct player {
    int num;
    int scores;
} player;

void downUpdate(player *arr, int n, int ind) {
    while ((ind << 1) <= n) { //当这个结点的左孩子存在时
        int max_val = ind, lchild = ind << 1, rchild = ind << 1 | 1;  //定位左右孩子的数组下标(右孩子不一定存在，需要判断)
        if (arr[max_val].scores < arr[lchild].scores) max_val = lchild;//如果左孩子的值大，则将下标赋给max_val
        if (rchild <= n && arr[max_val].scores < arr[rchild].scores) max_val = rchild;//如果右孩子存在并且右孩子的值更大，将下标赋给max_val
        if (max_val == ind) break; //如果max_val == ind 说明此时这个结点大于它的左右孩子，即调整完毕
        swap(arr[ind].scores, arr[max_val].scores); //如果没有调整完毕，则将它的左右孩子中较大的和它交换
        ind = max_val; //将这个结点的下标记录下来
    }
    return ;
}

void Build_heap(player *arr, int n) {
    arr -= 1;
    //从倒数第一个非叶子结点开始建堆
    for (int i = n >> 1; i >= 1; i--) {
        downUpdate(arr, n, i); //向下调整
    }
    return;
}

void Sequence(player *arr, player *max, int n) {
    max[0].num = max[1].num = arr[0].num;
    max[0].scores = max[1].scores = arr[0].scores;
    for (int i = 1; i < n; i++) {
        if (arr[i].scores <= max[0].scores) continue;
        max[1].num = max[0].num;
        max[1].scores = max[0].scores;
        max[0].num = arr[i].num;
        max[0].scores = arr[i].scores;
    }
    return;
}

void output(player *arr, int n) {
    printf("每位选手得分为\n");
    for (int i = 0; i < n; i++) {
        printf("%d号选手: %d分  ", arr[i].num, arr[i].scores);
        if (!(i % 5)) printf("\n");
    }
    printf("\n");
    return;
}

int main() {
    srand(time(0));
    #define max_op 512
    player *arr = (player *)malloc(sizeof(player) * max_op);
    for (int i = 0; i < max_op; i++) {
        arr[i].num = i + 1;
        arr[i].scores = rand() % 1000;
    }
    output(arr, max_op);
    int x;
    printf("按1选择顺序查找，按2选择锦标赛查找，按3选择建堆查找\n");
    scanf("%d", &x);
    switch (x) {
        case 1: {
            player max[2];
            Sequence(arr, max, max_op);
            printf("顺序查找的结果为:\n");
            printf("最高分为%d号选手， 其分数为%d\n", max[0].num, max[0].scores);
            printf("次高分为%d号选手， 其分数为%d\n", max[1].num, max[1].scores);
        } break;
        case 2: {
            
        } break;
        case 3: {
            Build_heap(arr, max_op);
            int num, scores;  //用来存储次高分的编号与分数
            //建堆之后，次大值一定为根节点的左右孩子中的一个
            if (arr[1].scores > arr[2].scores) {
                num = arr[1].num;
                scores = arr[1].scores;
            } else {
                num = arr[2].num;
                scores = arr[2].scores;
            }
            printf("建堆查找的结果为:\n");
            printf("最高分为%d号选手, 其分数为%d\n", arr[0].num, arr[0].scores);
            printf("次高分为%d号选手，其分数为%d\n", num, scores);
        } break;
    }
    free(arr);
    return 0;
}

