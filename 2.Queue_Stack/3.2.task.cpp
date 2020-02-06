/*************************************************************************
	> File Name: 2.task.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月13日 星期三 11时20分44秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
typedef struct Task {
    int num;
    int time;
} Task;

typedef struct Queue {
    Task *task;
    int head, tail, size, cnt;
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->task = (Task *)malloc(sizeof(Task) * n);
    q->size = n;
    q->head = q->tail = q->cnt = 0;
    return q;
}

int push(Queue *q, int val) {
    if (!q) return 0;
    if(q->cnt == q->size) {
        return ERROR;
    }
    q->task->time[q->tail++] = val;
    if (q->tail == q->size) q->tail -= q->size;
    q->cnt++;
    return OK;
}

void output(Queue *q) {
    if (!q) return ;
    printf("Queue = ");
	for (int i = q->head, j = 0; j < q->cnt; j++) {
        j && printf(", ");
        printf("%d ", q->data[(i + j) % q->size]);
    }
    printf("\n");
    return ;
}

int front(Queue*q){
    if (!q) return 0;
    return q->data[q->head];
}

int empty(Queue*q){
    if (!q) return 0;
    return q->cnt == 0;
}
int pop(Queue*q){
    if (!q) return 0;
    if (empty(q)) return 0;
    q->head++;
    if (q->head == q->size) q->head -= q->size;
    q->cnt--;
    return 1;
}


void clear(Queue *q) {
    if (!q) return;
    free(q->data);
    free(q);
    return;
}

int main() 
{
	Queue *list = init(5); 
	int a,b,c,d,e;
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
	int count = 0, k;
	int wt = 0, it = 0, st = 0, sum = 0;
	double sumba;
	push(list,a);
	push(list,b);
	push(list,c);
	push(list,d);
	push(list,e);


	for(k=list->head;k<=list->tail;k++)
	{
		it=count;
		st=it+front(list);
		count+=front(list);
		pop(list);
		wt=it; 
		sum+=wt;
		printf("开始时间：%d--结束时间：%d--等待时间:%d\n",it,st,wt);
	}
    sumba=sum/5.0;
	printf("平均等待时间：%f\n",sumba);



	int x[5],i,j,t;
	x[0]=a,x[1]=b,x[2]=c,x[3]=d,x[4]=e;
	for(j=0;j<4;j++)
	for(i=0;i<4-j;i++)
	if(x[i]>x[i+1])
	{
		t=x[i];x[i]=x[i+1];x[i+1]=t;	
	}
	double g=(x[0]+x[1]+x[2]+x[3]+x[4])/5.0;
	printf("最优平均等待时间：%f\n",g);
	printf("任务序列：");
	for(i=0;i<5;i++)
	{
		printf("%d\n",x[i]);
	}
return 0;    
}
