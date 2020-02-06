/*************************************************************************
	> File Name: 2019.1.Josephus_problem.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月10日 星期日 16时43分26秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define max_n 100
int n;

typedef struct ListNode {                         //定义一个结点类型的结构体
    int data, code;
    struct ListNode *next;
} ListNode;

typedef struct LinkedList {                       //定义一个链表类型的结构体
    ListNode head;
    int length;
} LinkedList;

ListNode *init_ListNode(int val) {                //初始化一个data为val, code自定义的结点 
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = val;
    printf("请输入该人的密码:");
    scanf("%d", &(p->code));
    p->next = NULL;
    return p;
}

LinkedList *init_LinkedList() {                   //初始化一个链表
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

LinkedList *creat_JosephusCircle(int n) {             //创建一个有n个结点的约瑟夫环
    LinkedList *l = init_LinkedList();
    ListNode *p = &(l->head), *q;
    int count = n;
    int val = 1;
    while (count--) {
        q = init_ListNode(val);
        q->next = p->next;
        p->next = q;
        p = q;
        val += 1;
    }
    p->next = l->head.next;
    l->length = n;
    return l;
}

void clear_ListNode(ListNode *p) {                //销毁结点 
    if (!p) return;
    free(p);
    return;
}

void clear_LinkedList(LinkedList *l) {            //销毁链表
    if (!l) return;
    ListNode *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_ListNode(p);
        p = q;
    }
    return;
}

void output(int *ans) {                           //输出结果数组
    printf("正确的出队顺序为[");
    for (int i = 1; ans[i]; i++) {
        (i == 1) || printf(",");
        printf("%d", ans[i]);
    }
    printf("]\n");
    return;
}

int main() {
    int ans[max_n + 5] = {0};  //定义一个数组来存正确出列顺序
    int i = 1;
    printf("请输入人数n:\n");
    scanf("%d", &n);
    LinkedList *l = creat_JosephusCircle(n);     //创建一个有n个结点的循环链表
    ListNode *p = &(l->head), *q = p->next;

    int count1 = n;
    while (count1--) {
        int count2 = p->next->code;
        //处理特殊情况
        if (!count2) {
            printf("ERROR\n");
            return 0;
        }
        while (count2--) p = p->next;
        while (q->next != p) q = q->next;
        ans[i++] = p->data;
        //删除节点
        q->next = p->next;
        clear_ListNode(p);
        p = q;
    }
    //输出结果数组
    output(ans);
    return 0;
}
