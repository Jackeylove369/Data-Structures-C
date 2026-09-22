#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MaxSize 100
/* 顺序表（Sequential List）
 * 本质：一段连续的内存 + 一个长度计数器
 *   data[MaxSize] : 静态数组，元素在内存中紧挨着存放。
 *   length        : 当前实际元素个数（不是最大下标！）
 *
 * 两大特性：
 *   - 随机存取：只要知道下标，就能 O(1) 直接定位元素
 *   - 插入/删除：需要搬动后续元素，平均 O(n)*/

typedef struct {
    int data[MaxSize];//存放元素的连续数组
    int	length;//当前元素个数，空表时为0
}SqList;

void InitList(SqList* L) {
    L->length = 0;
}

int GetByIndex(SqList* L, int index) {
    if (index < 0 || index >= L->length) {
        printf("下标%d越界！合法范围是0~%d\n", index, L->length - 1);
        return -1;
    }
    return L->data[index];//直达无需遍历
}

/* KEY: 按「位序」取值（取"第几个"元素）
 * 参数：i —— 位序，合法范围 1 ~ length
 * 返回：第 i 个元素的值；越界返回 -1
 * 要点：位序 i 必须先减 1 才能当数组下标*/
int GetByPos(SqList* L, int i) {
    if (i<1 || i>L->length) {
        printf("位序%d越界！合法范围是1~%d\n", i, L->length);
        return -1;
    }
    return L->data[i - 1];//位序->下标要-1
}

/*   KEY: 按下标「插入」
 *   参数：index —— 插入位置，合法范围 0 ~ length
 *                    （可以插到末尾 length 处，等价于"追加"）
 *         x     —— 待插入的元素值
 *   返回：成功 true；越界或表满 false
 *   思路：先把 data[index..length-1] 整体「右移一格」，腾出空位再放 x。
 *         必须从后往前搬，否则前面的元素会被覆盖。
 *   复杂度：O(n) */
bool InsertByIndex(SqList* L, int index, int x) {
    if (index<0 || index>L->length)return false; //下标合法范围0~length
    if (L->length >= MaxSize)return false; //表满，无法插入

    //从后往前搬：data[length-1]->data[length]，直到data[index]->data[index+1]
    for (int j = L->length;j > index;j--)
        L->data[j] = L->data[j - 1];

    L->data[index] = x; //空出来的下标index位置放入新元素
    L->length++; //元素个数+1
    return true;
}

/*   KEY: 按下标「删除」
 *   参数：index —— 待删元素下标，合法范围 0 ~ length-1
 *         e     —— 出参，带回被删元素的值
 *   返回：成功 true；越界 false
 *   思路：把 data[index+1..length-1] 整体「左移一格」，覆盖掉 index。
 *         必须从前往后搬，否则后面的元素会被覆盖。
 *   复杂度：O(n) */
bool DeleteByIndex(SqList* L, int index, int* e) {
    if (index < 0 || index >= L->length)return false; //下标合法范围0~length-1

    *e = L->data[index]; //先备份被删元素

    //从前往后搬：data[index+1]->data[index]，依次往前补齐
    for (int j = index;j < L->length - 1; j++)
        L->data[j] = L->data[j + 1];

    L->length--; //元素个数-1
    return true;
}

/*   按值查找
 *   参数：x —— 目标值
 *   返回：第一个等于 x 的元素【下标】（从 0 开始）；找不到返回 -1
 *   提示：若题目要求返回「位序」，把返回值 +1 即可。
 *   复杂度：O(n) */
int FindByValue(SqList* L, int x) {
    for (int i = 0;i < L->length;i++)//i本身就是下标,0->length-1
        if (L->data[i] == x)
            return i;//命中，返回下标
    return -1;//查无此值
}


/* ------------------------------------------------------------
* 打印整表
*   上下两行对齐输出：第一行是下标，第二行是对应元素值。
*   遍历的规范写法：i 从 0 到 length-1。
* ------------------------------------------------------------ */
void Print(SqList* L) {
    printf("下标:  ");
    for (int i = 0; i < L->length; i++)
        printf("%2d ", i);                  // 打印下标
    printf("\n元素:  ");
    for (int i = 0; i < L->length; i++)
        printf("%2d ", L->data[i]);         // 打印下标对应的元素
    printf("  (length=%d)\n\n", L->length);
}

/* ------------------------------------------------------------
 * 演示：位序 与 下标 的对应关系
 *   逐行展示： 位序 = i+1  <-->  下标 = i  <-->  值 = data[i]
 * ------------------------------------------------------------ */
void ShowIndexRule(SqList* L) {
    printf("===== 下标 vs 位序 对照表 =====\n");
    for (int i = 0; i < L->length; i++)
        printf("位序 = %d (第 %d 个)  <-->  下标 = %d  <-->  值 = %d\n",
            i + 1, i + 1, i, L->data[i]);
    printf("================================\n\n");
}

int main(void) {
    SqList L;
    InitList(&L);

    // —— 依次按下标 0、1、2、3 插入，等价于顺序追加 ——
    printf(">> 按下标插入 10、20、30、40\n");
    InsertByIndex(&L, 0, 10);   // 插到下标 0
    InsertByIndex(&L, 1, 20);   // 插到下标 1
    InsertByIndex(&L, 2, 30);   // 插到下标 2
    InsertByIndex(&L, 3, 40);   // 插到下标 3
    Print(&L);
    ShowIndexRule(&L);

    // —— 在下标 1 处插入，观察后续元素整体后移 ——
    printf(">> 按下标 1 插入 15（把原来的 20、30、40 往后挤）\n");
    InsertByIndex(&L, 1, 15);
    Print(&L);
    ShowIndexRule(&L);

    // —— 两种访问方式对比 ——
    printf(">> 随机访问：按下标 2 取值\n");
    printf("data[2] = %d\n\n", GetByIndex(&L, 2));

    printf(">> 按位序访问：取第 3 个元素\n");
    printf("第3个元素 = %d\n\n", GetByPos(&L, 3));

    // —— 按值查找 ——
    printf(">> 按值查找：找 30 的下标\n");
    int idx = FindByValue(&L, 30);
    printf("30 的下标 = %d（对应位序 = %d）\n\n", idx, idx + 1);

    // —— 删除并回收被删元素 ——
    printf(">> 按下标 1 删除（删掉 15）\n");
    int e;
    DeleteByIndex(&L, 1, &e);
    printf("删掉的元素 = %d\n", e);
    Print(&L);

    // —— 越界保护测试 ——
    printf(">> 测试越界访问\n");
    GetByIndex(&L, 100);   // 下标 100 越界
    GetByPos(&L, 99);      // 位序 99 越界

    return 0;
}
