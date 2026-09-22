#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 100

/* ============================================================
 * 一、顺序队列：普通，不取模，会假溢出
 * ============================================================ */
typedef struct {
    int data[MaxSize];
    int front, rear;          /* front 队头，rear 队尾下一位置 */
} SeqQueue;

void Seq_InitQueue(SeqQueue* Q) { Q->front = Q->rear = 0; }
bool Seq_QueueEmpty(SeqQueue* Q) { return Q->front == Q->rear; }
bool Seq_QueueFull(SeqQueue* Q) { return Q->rear == MaxSize; }
int  Seq_QueueLength(SeqQueue* Q) { return Q->rear - Q->front; }   /* 新增：长度 */

bool Seq_EnQueue(SeqQueue* Q, int e) {                 /* 入队：队尾，不取模 */
    if (Seq_QueueFull(Q)) return false;
    Q->data[Q->rear++] = e;
    return true;
}
bool Seq_DeQueue(SeqQueue* Q, int* e) {                /* 出队：队头，不取模 */
    if (Seq_QueueEmpty(Q)) return false;
    *e = Q->data[Q->front++];
    return true;
}

/* ---------- 假溢出演示（容量 5 小数组，直观展示） ---------- */
void DemoSeqOverflow(void) {
    printf("  普通顺序队列（容量 5）假溢出演示：\n");
    int data[5];
    int front = 0, rear = 0;

    for (int i = 1; i <= 5; i++) data[rear++] = i;    /* 入队 1~5 */
    printf("    入队 1~5 后：front=%d rear=%d（数组已满）\n", front, rear);

    front = 2;                                         /* 出队 2 个 */
    printf("    出队 2 个后：front=%d rear=%d，实际还剩 %d 个元素\n",
        front, rear, rear - front);

    if (rear == 5)
        printf("    再入队：rear==5 判满，无法入队！\n");
    printf("    下标 0、1 空着却用不了 —— 这就是「假溢出」\n");
}

/* ============================================================
 * 二、循环队列（取模绕回）—— 解决假溢出
 * ============================================================ */
typedef struct {
    int data[MaxSize];
    int front, rear;
} CircQueue;

void Circ_InitQueue(CircQueue* Q) { Q->front = Q->rear = 0; }
bool Circ_QueueEmpty(CircQueue* Q) { return Q->front == Q->rear; }
bool Circ_QueueFull(CircQueue* Q) { return (Q->rear + 1) % MaxSize == Q->front; }
int  Circ_QueueLength(CircQueue* Q) { return (Q->rear - Q->front + MaxSize) % MaxSize; }

bool Circ_EnQueue(CircQueue* Q, int e) {               /* 入队：队尾，取模 */
    if (Circ_QueueFull(Q)) return false;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MaxSize;
    return true;
}
bool Circ_DeQueue(CircQueue* Q, int* e) {              /* 出队：队头，取模 */
    if (Circ_QueueEmpty(Q)) return false;
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MaxSize;
    return true;
}

/* ---------- 循环绕回演示（容量 5 小数组，和假溢出对比） ---------- */
void DemoCircLoop(void) {
    printf("  循环队列（容量 5，最多存 4 个）演示：\n");
    int data[5];
    int front = 0, rear = 0;

    for (int i = 10; i <= 40; i += 10) {               /* 入队 10,20,30,40 */
        data[rear] = i;
        rear = (rear + 1) % 5;
    }
    printf("    入队 10,20,30,40 后：front=%d rear=%d 判满=%s\n",
        front, rear, (rear + 1) % 5 == front ? "true" : "false");

    front = (front + 2) % 5;                           /* 出队 2 个 */
    printf("    出队 2 个后：front=%d rear=%d 长度=%d\n",
        front, rear, (rear - front + 5) % 5);

    for (int i = 50; i <= 60; i += 10) {               /* 再入队 50,60 */
        data[rear] = i;
        rear = (rear + 1) % 5;
    }
    printf("    再入队 50,60 后：front=%d rear=%d 长度=%d\n",
        front, rear, (rear - front + 5) % 5);
    printf("    rear 从 4 绕回 0，空位被重新利用 —— 假溢出被解决！\n");
}

/* ============================================================
 * 三、链式队列
 * ============================================================ */
typedef struct QNode {
    int data;
    struct QNode* next;
}QNode;

typedef struct {
    QNode* front;
    QNode* rear;
}LiQueue;

/*初始化*/
void LiInit(LiQueue* Q) {
    Q->front = Q->rear = (QNode*)malloc(sizeof(QNode));
    Q->front->next = NULL;
}

/*判空*/
bool LiEmpty(LiQueue* Q) {
    return Q->front == Q->rear;
}

/*求长度*/
int LiLength(LiQueue* Q) {
    int n = 0;
    for (QNode* p = Q->front->next;p!=NULL;p = p->next)
        n++;
    return n;
}

/*入队（尾插）*/
bool LiEnQueue(LiQueue* Q, int e) {
    QNode* p = (QNode*)malloc(sizeof(QNode));
    if (p == NULL)return false;

    p->data = e;
    p->next = NULL;

    Q->rear->next = p;
    Q->rear = p;
    return true;
}

/*出队（头删）*/
bool LiDeQueue(LiQueue* Q, int* e) {
    if (LiEmpty(Q))return false;

    QNode* p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;

    if (Q->rear == p) {
        Q->rear = Q->front;
    }

    free(p);
    return true;
}

/* 取队头元素 */
bool LiGetHead(LiQueue* Q, int* e) {
    if (LiEmpty(Q)) return false;
    *e = Q->front->next->data;
    return true;
}

/* 清空队列，保留头结点 */
void LiClear(LiQueue* Q) {
    QNode* p = Q->front->next;
    while (p != NULL) {
        QNode* q = p;
        p = p->next;
        free(q);
    }
    Q->front->next = NULL;
    Q->rear = Q->front;
}

/* 销毁队列，释放头结点 */
void LiDestroy(LiQueue* Q) {
    LiClear(Q);
    free(Q->front);
    Q->front = Q->rear = NULL;
}

/* ============================================================
 * 唯一的 main 函数，一次跑完三种队列
 * ============================================================ */
int main(void) {
    int e;

    /* ---------- 顺序队列 ---------- */
    printf("========== 顺序队列 ==========\n");
    SeqQueue Q1;
    Seq_InitQueue(&Q1);
    printf("初始判空 = %s\n", Seq_QueueEmpty(&Q1) ? "true" : "false");

    Seq_EnQueue(&Q1, 10);
    Seq_EnQueue(&Q1, 20);
    Seq_EnQueue(&Q1, 30);
    printf("入队 10,20,30 后：front=%d rear=%d 长度=%d\n",
        Q1.front, Q1.rear, Seq_QueueLength(&Q1));

    Seq_DeQueue(&Q1, &e);
    printf("出队 = %d 后：front=%d rear=%d 长度=%d\n",
        e, Q1.front, Q1.rear, Seq_QueueLength(&Q1));
    printf("\n");
    DemoSeqOverflow();

    /* ---------- 循环队列 ---------- */
    printf("\n========== 循环队列 ==========\n");
    CircQueue Q2;
    Circ_InitQueue(&Q2);
    printf("初始判空 = %s\n", Circ_QueueEmpty(&Q2) ? "true" : "false");

    Circ_EnQueue(&Q2, 10);
    Circ_EnQueue(&Q2, 20);
    Circ_EnQueue(&Q2, 30);
    printf("入队 10,20,30 后：front=%d rear=%d 长度=%d\n",
        Q2.front, Q2.rear, Circ_QueueLength(&Q2));

    Circ_DeQueue(&Q2, &e);
    printf("出队 = %d 后：front=%d rear=%d 长度=%d\n",
        e, Q2.front, Q2.rear, Circ_QueueLength(&Q2));
    printf("\n");
    DemoCircLoop();

    /* ---------- 链式队列 ---------- */
    printf("\n========== 链式队列 ==========\n");
    LiQueue Q3;
    LiInit(&Q3);

    printf("初始判空 = %s，长度 = %d\n",
        LiEmpty(&Q3) ? "true" : "false", LiLength(&Q3));

    LiEnQueue(&Q3, 10);
    LiEnQueue(&Q3, 20);
    LiEnQueue(&Q3, 30);
    printf("入队 10,20,30 后：长度=%d 队头=%d 队尾=%d\n",
        LiLength(&Q3), Q3.front->next->data, Q3.rear->data);

    LiDeQueue(&Q3, &e);
    printf("出队 = %d 后：长度=%d 队头=%d 队尾=%d\n",
        e, LiLength(&Q3), Q3.front->next->data, Q3.rear->data);

    LiGetHead(&Q3, &e);
    printf("取队头 = %d\n", e);

    LiClear(&Q3);
    printf("清空后：判空=%s，长度=%d\n",
        LiEmpty(&Q3) ? "true" : "false", LiLength(&Q3));

    LiDestroy(&Q3);
    printf("链式队列已销毁。\n");

    return 0;
}
