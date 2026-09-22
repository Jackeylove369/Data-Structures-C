#include<stdio.h>
#include<stdlib.h>

// 单链表结构定义
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode,*LinkList;

// 初始化带头结点的空链表
LinkList InitList(void) {
	LinkList L = (LinkList)malloc(sizeof(LNode));
	if (!L) { printf("内存分配失败\n");exit(1); }
	L->next = NULL;
	return L;
}

//尾插法:在链表末尾插入x（r为尾指针的地址）
void TailInsert(LinkList* r, int x) {
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (!s) { printf("内存分配失败\n");exit(1); }
	s->data = x;
	s->next = NULL;

	(*r)->next = s;//旧尾结点指向新结点
	*r = s;//更新尾指针
}

//打印链表
void Print(LinkList L) {
	LNode* p = L->next;//跳过头结点
	while (p != NULL) {
		printf("%d->",p->data);
		p = p->next;
	}
	printf("NULL\n");
}

//求链表长度（不含头结点）
int Length(LinkList L) {
	int len = 0;
	LNode* p = L->next;
	while (p != NULL) {
		len++;
		p = p->next;
	}
	return len;
}

void DestroyList(LinkList L) {
	LNode* p = L;
	while (p != NULL) {
		LNode* t = p;
		p = p->next;
		free(t);
	}
}

int main(void) {
	LinkList L = InitList();
	LinkList r = L; // 尾指针初始指向头结点

	// 依次尾插 10、20、30、40
	TailInsert(&r, 10);
	TailInsert(&r, 20);
	TailInsert(&r, 30);
	TailInsert(&r, 40);

	printf("依次尾插 10, 20, 30, 40 后：\n");
	printf("链表: ");
	Print(L);
	printf("长度 = %d\n", Length(L));
	printf("结果顺序完全一致：10 20 30 40\n\n");

	// 再尾插 99，验证它跑到最后
	TailInsert(&r, 99);
	printf("再尾插 99 后：\n");
	printf("链表: ");
	Print(L);

	DestroyList(L); // 释放内存
	return 0;
}
