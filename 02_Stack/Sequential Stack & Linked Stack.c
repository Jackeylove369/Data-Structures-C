#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MaxSize 100

// 1. 顺序栈：top指向栈顶元素，空栈是top=-1

typedef struct {
	int data[MaxSize];
	int top;
}SqStack;

/*初始化顺序栈：置空*/
void InitStack(SqStack* S) {
	S->top = -1;/*-1表示空栈*/
}

/*判空：top==-1说明没有元素*/
bool StackEmpty(SqStack* S) {
	return S->top == -1;
}

/*判满：top==MaxSize-1 说明数组已满*/
bool StackFull(SqStack* S) {
	return S->top == MaxSize - 1;
}

/*求栈长：栈顶下标+1就是元素个数*/
int StackLength(SqStack* S) {
	return S->top + 1;
}

/*入栈：先判断是否栈满，，在top+1，最后放元素*/
bool Push(SqStack* S, int e) {
	if (StackFull(S))return false;/*栈满，入栈失败*/
	S->data[++S->top] = e;/*先加后放*/
	return true;
}

/*出栈：先判断是否空，再取出栈顶元素，最后top-1*/
bool Pop(SqStack* S, int* e) {
	if (StackEmpty(S))return false;/*栈空，出栈失败*/
	*e = S->data[S->top--];/*先取后减*/
	return true;
}

/*读栈顶：只看不动，不改变top*/
bool GetTop(SqStack* S, int* e) {
	if (StackEmpty(S))return false;
	*e = S->data[S->top];/*只读不取*/
	return true;
}

/*打印顺序栈：从左到右，栈顶到栈底*/
void SqPrint(SqStack* S) {
	printf("[");
	for (int i = S->top;i >= 0;i--) {
		printf("%d%s", S->data[i], (i > 0) ? "," : "");
	}
	printf("](左为栈顶)\n");
}

// 2. 链栈
/*链栈结点：data存放数据，next指向下一个结点*/
typedef struct SNode {
	int data;
	struct SNode* next;
}SNode, * LiStack;

/*初始化链栈：空栈时栈顶指针为NULL*/
void LiInit(LiStack* S)
{
	*S = NULL;
}

/*判断链栈是否为空：空栈返回true*/
bool LiEmpty(LiStack S)
{
	return S == NULL;
}

/*返回链栈中的元素个数*/
int LiLength(LiStack S)
{
	int n = 0;
	for (SNode* p = S;p != NULL;p = p->next)
		n++;
	return n;
}

/*入栈：使用头插法插入新结点：成功true，失败false*/
bool LiPush(LiStack* S, int e) {
	SNode* p = (SNode*)malloc(sizeof(SNode));
	if (p == NULL)return false;
	p->data = e;
	p->next = *S;
	*S = p;
	return true;
}

/*出栈：删除栈顶结点，并通过e返回其值：成功true，失败false*/
bool LiPop(LiStack* S, int* e) {
	if (LiEmpty(*S))return false;
	SNode* p = *S;/*p指向被删除的栈顶结点*/
	*e = p->data;
	*S = p->next;/*栈顶指针后移*/
	free(p);/*释放栈顶结点*/
	return true;
}

/*读取栈顶元素，但不删除*/
bool LiGetTop(LiStack S, int* e) {
	if (LiEmpty(S))return false;
	*e = S->data;
	return true;
}

/*打印链栈：从左到右依次从栈顶到栈底*/
void LiPrint(LiStack S) {
	printf("[");
	for (SNode* p = S;p != NULL;p = p->next)
		printf("%d%s", p->data, p->next != NULL ? "," : "");
	printf("] (left is top)\n");
}

// 3. 测试
int main(void)
{
	int e;

	/* 测试顺序栈 */
	printf("========== 顺序栈 ==========\n");
	SqStack S;
	InitStack(&S);
	printf("empty = %s\n", StackEmpty(&S) ? "true" : "false");

	Push(&S, 10);
	Push(&S, 20);
	Push(&S, 30);
	printf("push 10,20,30 -> ");
	SqPrint(&S);
	printf("length = %d\n", StackLength(&S));

	GetTop(&S, &e);
	printf("getTop (no delete) = %d\n", e);

	Pop(&S, &e);
	printf("pop = %d -> ", e);
	SqPrint(&S);

	/* 测试链栈 */
	printf("\n========== 链栈 ==========\n");
	LiStack L;
	LiInit(&L);
	printf("empty = %s\n", LiEmpty(L) ? "true" : "false");

	LiPush(&L, 10);
	LiPush(&L, 20);
	LiPush(&L, 30);
	printf("push 10,20,30 -> ");
	LiPrint(L);
	printf("length = %d\n", LiLength(L));

	LiPop(&L, &e);
	printf("pop = %d -> ", e);
	LiPrint(L);

	return 0;
}
