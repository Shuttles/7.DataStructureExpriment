/*************************************************************************
	> File Name: 1.Cubetastic.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月17日 星期日 23时51分22秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define max_n 10000

int m;
int matrix[max_n + 5][max_n + 5];
void get_Cubetastic() {
    int x = 0, y = (m - 1) / 2;
    matrix[x][y] = 1;//首先确定第一行中间位置为1;
    for (int i = 2; i <= m * m; i++) {
        if (!((i - 1) % m)) {
            x = x + 1;          //如果上个数字是m的倍数，则放在上个数字的下面  
            if (x >= m) x -= m;
            matrix[x][y] = i;
        } else {                //如果上一个数字不是m的倍数
            x = (x - 1 + m) % m;//获得下一步的坐标
            y = (y - 1 + m) % m;
            matrix[x][y] = i;
        }
    }
    return;
}

void output(int matrix[max_n + 5][max_n + 5]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            j && printf("  ");
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
    return;
}

int main() {
    printf("请输入一个奇数m， 您将得到一个m阶魔方阵\n");
    scanf("%d", &m);
    while (!(m & 1)) { //如果m是偶数
        printf("您输入的m不是一个奇数，请重新输入:\n");
        scanf("%d", &m);
    }
    get_Cubetastic();
    printf("您输入的奇数产生的魔方阵如下:\n");
    output(matrix);
    return 0;
}
