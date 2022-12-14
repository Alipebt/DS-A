#include <iostream>
#include <stdlib.h>

using namespace std;

#define MAXSIZE 10

// 顺序栈
/*
typedef struct
{
    int stack[MAXSIZE];
    int top;
} Stack;

int InitStack(Stack &s)
{
    s.top = -1;
    return 1;
}
int EmptyStack(Stack s)
{
    return s.top == -1 ? 1 : 0;
}

int Push(Stack &s, int x)
{
    if (s.top == MAXSIZE - 1)
    {
        return -1;
    }

    s.stack[++s.top] = x;
    return 1;
}

int Pop(Stack &s, int *x)
{
    if (!EmptyStack(s))
    {
        return -1;
    }

    *x = s.stack[s.top--];
    return 1;
}

int getTop(Stack s, int *x)
{
    if (!EmptyStack(s))
    {
        return -1;
    }

    *x = s.stack[s.top];
    return 1;
}

int printfStack(Stack s)
{
    while (s.top >= 0)
    {
        printf("%d\n", s.stack[s.top--]);
    }
    return 1;
}
*/
// 链栈
/*
typedef struct StackNode
{
    int data;
    struct StackNode *next;
} * Stack;

int InitStack(Stack &s)
{
    s = NULL;
    return 1;
}

int EmptyStack(Stack s)
{
    return s == NULL ? 1 : 0;
}
int Push(Stack &s, int data)
{
    Stack news = (Stack)malloc(sizeof(Stack));
    news->data = data;
    news->next = s;
    s = news;
    return 1;
}

int Pop(Stack &s, int *x)
{
    if (!s)
    {
        return 0;
    }
    Stack p = s;
    *x = p->data;
    s = p->next;
    free(p);
    return 1;
}
int getTop(Stack s, int *x)
{
    if (!s->next)
    {
        return 0;
    }
    *x = s->data;
    return 1;
}

void printfStack(Stack &s)
{
    Stack p = s;
    while (p)
    {
        printf("%d\n", p->data);
        p = p->next;
    }
    return;
}
*/
// 顺序队列
/*
typedef struct
{
    int queue[MAXSIZE];
    int front, rear;
} Queue;

int InitQueue(Queue &q)
{
    q.front = q.rear = 0;
    return 1;
}

int EmptyQueue(Queue q)
{
    return q.front == q.rear ? 1 : 0;
}

int EnQueue(Queue &q, int *x)
{
    if (q.rear + 1 % MAXSIZE == q.front)
    {
        return -1;
    }
    q.queue[q.rear++ % MAXSIZE] = *x;
    return 1;
}

int DeQueue(Queue &q, int *x)
{
    if (q.front == q.rear)
    {
        return -1;
    }
    *x = q.queue[q.front++ % MAXSIZE];

    return 1;
}

int GetHead(Queue q, int *x)
{
    if (!EmptyQueue(q))
    {
        return -1;
    }
    *x = q.queue[q.front];

    return 1;
}
*/
// 链队
typedef struct Node
{
    int data;
    struct Node *next;
} QueueNode;
typedef struct
{
    struct Node *front, *rear;
} Queue;

int InitQueue(Queue &q)
{
    q.front = q.rear = NULL;
}
int EmptyQueue(Queue q)
{
    return q.front == NULL ? 1 : 0;
}
int EnQueue(Queue &q, int *x)
{
    QueueNode *qn = (QueueNode *)malloc(sizeof(QueueNode));
    qn->data = *x;
    qn->next = NULL;
    if (!q.front)
    {
        q.front = qn;
        q.rear = qn;
    }
    else
    {
        q.rear->next = qn;
        q.rear = qn;
    }
}
int DeQueue(Queue &q, int *x)
{
    if (!q.front)
    {
        return -1;
    }
    QueueNode *d = q.front;

    *x = q.front->data;
    q.front = q.front->next;

    if (q.rear == d)
    {
        q.rear = NULL;
    }
    free(d);
}
int GetHead(Queue &q, int *x)
{
    if (!EmptyQueue(q))
    {
        return -1;
    }
    *x = q.front->data;
    return 1;
}
int main()
{
    /*
        Stack s;
        int x, n;
        InitStack(s);

        while (1)
        {
            printf("1.入栈\t2.出栈\t3.判空\t4.取栈顶\t5.遍历\n");
            scanf("%d", &n);
            if (n == 1)
            {
                printf("入栈数据:");
                scanf("%d", &x);
                Push(s, x);
                printf("入栈: %d\n", x);
            }
            else if (n == 2)
            {
                if (!EmptyStack(s))
                {
                    Pop(s, &x);
                    printf("出栈：%d\n", x);
                }
                else
                {
                    printf("无数据\n");
                }
            }
            else if (n == 3)
            {
                printf("判空: %s\n", EmptyStack(s) ? "空" : "非空");
            }
            else if (n == 4)
            {
                getTop(s, &x);
                printf("取栈顶: %d\n", x);
            }
            else if (n == 5)
            {
                printf("遍历：\n");
                printfStack(s);
            }
        }*/

    Queue q;

    int x, n;
    InitQueue(q);

    while (1)
    {
        printf("1.入队\t2.出队\t3.判空\t4.取队头\t");
        scanf("%d", &n);
        if (n == 1)
        {
            printf("入队数据:");
            scanf("%d", &x);
            EnQueue(q, &x);
            printf("入队: %d\n", x);
        }
        else if (n == 2)
        {
            if (!EmptyQueue(q))
            {
                DeQueue(q, &x);
                printf("出队：%d\n", x);
            }
            else
            {
                printf("无数据\n");
            }
        }
        else if (n == 3)
        {
            printf("判空: %s\n", EmptyQueue(q) ? "空" : "非空");
        }
        else if (n == 4)
        {
            GetHead(q, &x);
            printf("取队头: %d\n", x);
        }
    }
}