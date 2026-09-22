# 数据结构基础：顺序队列、循环队列与链式队列完整实现

本项目使用 C 语言实现了**队列（Queue）**的三种基本存储结构：**顺序队列（Sequential Queue）**、**循环队列（Circular Queue）** 和 **链式队列（Linked Queue）**。代码包含详细的中文注释，涵盖初始化、判空、判满、入队、出队、读取队头及内存释放等核心操作，非常适合数据结构初学者复习与参考。

## 文件结构

| 文件名 | 说明 |
| :--- | :--- |
| `Queue.c` | 顺序队列、循环队列与链式队列的完整实现及测试代码 |

---

## 详细功能说明

队列是一种**先进先出（FIFO, First In First Out）**的线性表，只允许在队尾进行插入操作，在队头进行删除操作。本项目分别用“数组”和“链表”实现了这三种队列。

### 1. 顺序队列（SeqQueue）
顺序队列本质是一段连续的内存空间加上队头指针和队尾指针。

**核心特性：**
- **存储方式**：静态数组 `data[MaxSize]`。
- **队头指针**：`front` 指向队头元素。
- **队尾指针**：`rear` 指向队尾元素的下一个位置。
- **初始状态**：`front = rear = 0`。
- **判空**：`front == rear`。
- **判满**：`rear == MaxSize`。
- **缺点**：出队后前面空出的位置无法复用，会产生“假溢出”。

**提供的操作：**
- `Seq_InitQueue`：初始化空队列，令 `front = rear = 0`。
- `Seq_QueueEmpty`：判断队列是否为空。
- `Seq_QueueFull`：判断队列是否已满。
- `Seq_QueueLength`：返回队列元素个数（`rear - front`）。
- `Seq_EnQueue`：入队，先判断是否队满，再执行 `data[rear++] = e`。
- `Seq_DeQueue`：出队，先判断是否队空，再执行 `e = data[front++]`。
- `DemoSeqOverflow`：演示顺序队列的假溢出现象。

### 2. 循环队列（CircQueue）
循环队列通过取模运算让队头、队尾指针在数组末尾绕回开头，解决假溢出。

**核心特性：**
- **存储方式**：静态数组 `data[MaxSize]`。
- **队头指针**：`front` 指向队头元素。
- **队尾指针**：`rear` 指向队尾元素的下一个位置。
- **判空**：`front == rear`。
- **判满**：`(rear + 1) % MaxSize == front`（牺牲一个存储单元）。
- **实际容量**：`MaxSize - 1`。
- **长度**：`(rear - front + MaxSize) % MaxSize`。

**提供的操作：**
- `Circ_InitQueue`：初始化空队列，令 `front = rear = 0`。
- `Circ_QueueEmpty`：判断队列是否为空。
- `Circ_QueueFull`：判断队列是否已满。
- `Circ_QueueLength`：返回队列元素个数。
- `Circ_EnQueue`：入队，先判满，再执行 `data[rear] = e; rear = (rear + 1) % MaxSize;`。
- `Circ_DeQueue`：出队，先判空，再执行 `e = data[front]; front = (front + 1) % MaxSize;`。
- `DemoCircLoop`：演示循环队列的绕回复用。

### 3. 链式队列（LiQueue）
链式队列采用带头结点的单链表实现，队头指针指向头结点，队尾指针指向最后一个数据结点。

**核心特性：**
- **存储方式**：动态申请结点，内存不连续。
- **头结点**：`front` 指向头结点，不存放有效数据。
- **队尾指针**：`rear` 指向最后一个数据结点。
- **空队列**：`front == rear`。
- **动态扩展**：只要内存足够，不会出现队满。
- **入队**：尾插法，在 `rear` 后插入新结点，并更新 `rear`。
- **出队**：头删法，删除 `front->next` 结点，并 `free` 释放内存。

**提供的操作：**
- `LiInit`：初始化链式队列，创建头结点，`front = rear = 头结点`。
- `LiEmpty`：判断队列是否为空（`front == rear`）。
- `LiLength`：遍历链表统计元素个数。
- `LiEnQueue`：入队，在队尾插入新结点。
- `LiDeQueue`：出队，删除队头结点并释放。
- `LiGetHead`：读取队头元素，只读不删。
- `LiClear`：清空队列，保留头结点。
- `LiDestroy`：销毁队列，释放头结点。

---

## 编译与运行

本项目使用标准 C 语言编写（C99 及以上），已在 Visual Studio 和 GCC 环境下测试通过。

**使用 GCC 编译（Linux / macOS / MinGW）：**
```bash
gcc Queue.c -o Queue -std=c99 -Wall
./Queue
