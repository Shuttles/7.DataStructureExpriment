/*************************************************************************
	> File Name: 10.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月24日 星期日 17时09分42秒
 ************************************************************************/

#include <iostream>
using namespace std;

int main() {
    FILE *fp = fopen("8.aa", "r");
    while (feof(fp) == 0) {
        char ch = fgetc(fp);
        int a = (int)ch;
        printf("%d", a);
    }
    printf("\n");
    fclose(fp);
    return 0;
}
