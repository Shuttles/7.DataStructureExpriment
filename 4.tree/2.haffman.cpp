/*************************************************************************
	> File Name: 2.haffman.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月23日 星期六 11时24分33秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define max_n 1000
#define swap(a, b) {\
    __typeof(a) temp = a;\
    a = b, b = temp;\
}
double prepared[128];

typedef struct Node {
    char ch;
    double p; //代表当前结点出现的概率
    struct Node *next[2]; 
} Node;

typedef struct Code {
    char ch;
    char *str;
} Code;

typedef struct HaffmanTree {
    Node *root;
    int n; //到底有多少种字符
    Code *codes;
} HaffmanTree;

typedef struct Data {
    char ch;
    double p;
} Data;

Data arr[max_n + 5];

Node *getNewNode(Data *obj) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->ch = (obj ? obj->ch : 0);
    p->p = (obj ? obj->p : 0);
    p->next[0] = p->next[1] = NULL;
    return p;
}

HaffmanTree *getNewTree(int n) {
    HaffmanTree *tree = (HaffmanTree *)malloc(sizeof(HaffmanTree));
    tree->codes = (Code *)malloc(sizeof(Code) * n);
    tree->root = NULL;
    tree->n = n;
    return tree;
}

void clear_Node(Node *root) {
    if (!root) return;
    clear_Node(root->next[0]);
    clear_Node(root->next[1]);
    free(root);
    return;
}

void clear_HaffmanTree(HaffmanTree *tree) {
    if (!tree) return;
    clear_Node(tree->root);
    free(tree);
    return;
}

int extractCodes(Node *root, Code *arr, int k, int l, char *buff) {
    buff[l] = 0;
    if (root->next[0] == NULL && root->next[1] == NULL) {
        //如果这个结点是叶子结点
        arr[k].ch = root->ch;
        arr[k].str = strdup(buff);
        return 1;
    }
    int delta = 0; //在相关子树中编码了多少个字符
    buff[l] = '0';
    delta += extractCodes(root->next[0], arr, k + delta, l + 1, buff);//在左子树中编码了多少字符
    buff[l] = '1';
    delta += extractCodes(root->next[1], arr, k + delta, l + 1, buff); //在右子树中编码了多少字符
    return delta;
}

void insertOnce(Node **arr, int n) {
    for (int j = n; j >= 1; j--) {
        if (arr[j]->p > arr[j - 1]->p) {
            swap(arr[j], arr[j - 1]);
            continue;
        }
        break;
    }
    return;
}

HaffmanTree *build(Data *arr, int n) {
    //形参为装有待编码字符及其频次的数组 还有编码字符的个数
    Node **nodes = (Node **)malloc(sizeof(Node *) * n);
    for (int i = 0; i < n; i++) {
        nodes[i] = getNewNode(arr + i);
    }
    //插入排序，由出现概率从大到小排序
    for (int i = 1; i < n; i++) {
        insertOnce(nodes, i);
    }
    //进行结点提取
    for (int i = n - 1; i >= 1; i--) {
        Node *p = getNewNode(NULL);
        p->next[0] = nodes[i];
        p->next[1] = nodes[i - 1];
        p->p = p->next[0]->p + p->next[1]->p;
        nodes[i - 1] = p;
        insertOnce(nodes, i - 1);
    }
    char *buff = (char *)malloc(sizeof(char) * n);
    HaffmanTree *tree = getNewTree(n);
    tree->root = nodes[0];          //至此haffmantree基本建立完成
    //下面就是读取每个结点的编码存入haffmantree的codes字段中
    extractCodes(tree->root, tree->codes, 0, 0, buff);
    free(nodes);
    free(buff);
    return tree;
}

int file_conut() {                                     //统计文件中出现的字符及其频次函数， 返回值为字符的种类数
    FILE *src;
    src = fopen("6.source", "r");
    printf("将要被压缩的文件内容为：\n");
    while (feof(src) == 0) {
        char ch = fgetc(src); 
        putchar(ch);
        prepared[(int)ch] += 1;
    } 
    printf("\n");
    int j = 0;
    for (int i = 0; i < 128; i++) {
        if (!prepared[i]) continue;
        arr[j].ch = (char)i;
        arr[j].p = prepared[i];
        j += 1;
    }
    fclose(src);
    return j;
}

void save_hfmcode(HaffmanTree *tree, int n) {
    FILE *hfmcode;
    hfmcode = fopen("4.HufCode", "w");
    for (int i = 0; i < n; i++) {
        fprintf(hfmcode, "%c : %s\n", tree->codes[i].ch, tree->codes[i].str);
    }
    fclose(hfmcode);
    return;
}

void Haffman_Compress(HaffmanTree *tree, int n) {
    FILE *src;
    FILE *compress;
    if ((src = fopen("6.source", "r")) == NULL) {
        printf("cannot open the file\n");
        return ;
    }
    if ((compress = fopen("5.CodeFile", "w")) == NULL) {
        printf("cannot open the file\n");
        return;
    }
    while (feof(src) == 0) {
        char ch = fgetc(src);
        for (int i = 0 ; i < n; i++) {
            if (tree->codes[i].ch != ch) continue;
            fprintf(compress, "%s", tree->codes[i].str);
            break;
        }
    }
    fclose(src);
    fclose(compress);
    return;
}

void Decompress(HaffmanTree *tree, int n) {
    FILE *decom;
    FILE *compress;
    compress = fopen("5.CodeFile", "r");
    decom = fopen("7.after_decompression", "w");
    char str[1000] = {0};
    while (feof(compress) == 0) {
        int i = 0;
        char ch = '0';
        while (1 && !feof(compress)) {
            fscanf(compress, "%c", &ch);
            str[i] = ch;
            int flag = 0;
            for (int j = 0; j < n; j++) {
                if (strcmp(str, tree->codes[j].str)) continue;
                fprintf(decom, "%c", tree->codes[j].ch);
                memset(str, 0, sizeof(str));
                flag = 1;
                break;
            }
            if (!flag) {
                i++;
                continue;
            }
            break;
        }
    }
    fclose(compress);
    fclose(decom);
    return;
}

/*
void save_hfmnode(Node *);

void save_hfmtree(HaffmanTree *tree) {
    if (!tree) return;
    FILE *save = fopen("8.HufTree", "w");
    save_hfmnode(tree->root);
    fclose(save);
    return ;
}

void save_hfmnode(Node *root) {
    if (!root) return;
    save_hfmnode(root->next[0]);
    save_hfmnode(root->next[1]);
    fprintf(save, "%c", root->ch);
    return;
}
*/

int main() {
    int n;
    n = file_conut();
    //建立HaffmanTree,传入参数为arr数组(要编码的字符和出现的频次)和要编码的字符个数n
    HaffmanTree *tree = build(arr, n);
    save_hfmcode(tree, n);
    Haffman_Compress(tree, n);
    Decompress(tree, n);
    //save_hfmtree(tree);
    for (int i = 0; i < n; i++) {
        printf("%c : %s\n", tree->codes[i].ch, tree->codes[i].str);
    }
    clear_HaffmanTree(tree);
    return 0;
}
