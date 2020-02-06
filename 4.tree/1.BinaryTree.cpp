/*************************************************************************
	> File Name: 1.BinaryTree.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月20日 星期三 14时28分12秒
 ************************************************************************/
//1h 2019.11.20 最大bug在于构建二叉排序树时里面递归时忘了root->lchild = xxx和root->rchild = xxx;
//23min 2019.11.20 最大bug在于insert_BinaryTree()函数里调用insert_Node时忘了加上tree->root = ，导致地址丢失
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

typedef struct BinaryTree {
    Node *root;
    int n;
} BinaryTree;

Node *init_Node(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->lchild = node->rchild = NULL;
    return node;
}

BinaryTree *init_BinaryTree() {
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->root = NULL;
    tree->n = 0;
    return tree;
} 

void clear_Node(Node *root) {
    if (!root) return;
    clear_Node(root->lchild);
    clear_Node(root->rchild);
    free(root);
    return;
}

void clear_BinaryTree(BinaryTree *tree) {
    if (!tree) return;
    clear_Node(tree->root);
    free(tree);
    return;
}

Node *insert_Node(Node *root, int val, int *flag) {
    if (!root) {
        *flag = 1;
        return init_Node(val);
    }
    if (root->data == val) return root;
    if (val < root->data) root->lchild = insert_Node(root->lchild, val, flag);
    else root->rchild = insert_Node(root->rchild, val, flag);
    return root;
}

void insert_BinaryTree(BinaryTree *tree, int val) {
    if (!tree) return;
    int flag = 0;
    tree->root = insert_Node(tree->root, val, &flag);
    tree->n += flag;
    return;
}

void output_Node(Node *root) {
    if (!root) return;
    printf("%d(", root->data);
    output_Node(root->lchild);
    printf(",");
    output_Node(root->rchild);
    printf(")");
    return;
}

void output_BinaryTree(BinaryTree *tree) {
    if (!tree) return;
    printf("BinaryTree(%d) = ", tree->n);
    output_Node(tree->root);
    printf("\n");
    return;
}

void pre_order_Node(Node *root) {
    if (!root) return;
    printf("%d ", root->data);
    pre_order_Node(root->lchild);
    pre_order_Node(root->rchild);
    return;
}

void pre_order_BinaryTree(BinaryTree *tree) {
    if (!tree) return;
    printf("pre_order_BinaryTree(%d) = ", tree->n);
    pre_order_Node(tree->root);
    printf("\n");
    return;
}

void in_order_Node(Node *root) {
    if (!root) return;
    in_order_Node(root->lchild);
    printf("%d ", root->data);
    in_order_Node(root->rchild);
    return;
}

void in_order_BinaryTree(BinaryTree *tree) {
    if (!tree) return;
    printf("in_order_BinaryTree(%d) = ", tree->n);
    in_order_Node(tree->root);
    printf("\n");
    return;
}

void post_order_Node(Node *root) {
    if (!root) return;
    post_order_Node(root->lchild);
    post_order_Node(root->rchild);
    printf("%d ", root->data);
    return;
}

void post_order_BinaryTree(BinaryTree *tree) {
    if (!tree) return;
    printf("post_order_BinaryTree(%d) = ", tree->n);
    post_order_Node(tree->root);
    printf("\n");
    return;
}

int main() {
    BinaryTree *tree = init_BinaryTree();
    #define max_op 5
    srand(time(0));
    int val;
    for (int i = 0; i < max_op; i++) {
        val = rand() % 100;
        insert_BinaryTree(tree, val);
    }
    output_BinaryTree(tree);
    pre_order_BinaryTree(tree);
    in_order_BinaryTree(tree);
    post_order_BinaryTree(tree);
    clear_BinaryTree(tree);
    return 0;
}
