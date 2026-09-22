#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
	int data;// 作为数据域，存放数值
	struct LNode* next;// 作为指针域，指向下一个结点
}LNode, * LinkList;

// L作为头结点，不存放数据，作为插入删除的入口
LinkList InitList(void) {
	LinkList L = (LinkList)malloc(sizeof(LNode));// 创建头结点
	if (!L) { printf("内存分配失败\n"); exit(1); }// 内存分配失败的保护
	L->next = NULL;// 头结点的next置空，空链表
	return L;
}

void HeadInsert(LinkList L, int x) {
	LNode* s = (LNode*)malloc(sizeof(LNode));// 申请一个新结点
	if (!s) { printf("内存分配失败\n"); exit(1); }
	s->data = x;// 填入数据

	// 核心操作：
	s->next = L->next;// 新结点指向“原来的第一个结点”
	L->next = s;      // 头结点指向新结点，s 成为新的首结点
}

// 打印链表：从第一个数据结点开始，一直到NULL
// 			p从L->next开始
void Print(LinkList L) {
	LNode* p = L->next;// 跳过头结点，指向真正的第一个数据结点
	while (p != NULL) {
		printf("%d->", p->data);
		p = p->next;// 指针后移
	}
	printf("NULL\n");
}

// 求链表长度，统计数据结点的个数（不含头结点）
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

	// 依次头插 10、20、30、40
	// 由于头插是“后插的在前”，最终顺序应为 40 -> 30 -> 20 -> 10
	HeadInsert(L, 10);
	HeadInsert(L, 20);
	HeadInsert(L, 30);
	HeadInsert(L, 40);

	printf("依次头插 10, 20, 30, 40 后：\n");
	printf("链表: ");
	Print(L);
	printf("长度 = %d\n", Length(L));
	printf("结果逆序了：40 30 20 10\n\n");

	// 再插一个 99，验证它一定会跑到最前面（头插的特性）
	HeadInsert(L, 99);
	printf("再头插 99 后：\n");
	printf("链表: ");
	Print(L);

	DestroyList(L);             // 释放所有结点，避免内存泄漏
	return 0;
}
