#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode
{
    int data;
    struct StackNode *next;
} Stack;

int InitStack(Stack **s)
{
    *s = (Stack *)malloc(sizeof(Stack));
    (*s)->data = 0;
    (*s)->next = NULL;
    return 1;
}

int EmptyStack(Stack *s)
{
    return s->next == NULL ? 1 : 0;
}
int Push(Stack *s, int data)
{
    Stack *new = (Stack *)malloc(sizeof(Stack));
    new->data = data;
    new->next = s->next;
    s->next = new;
    return 1;
}

int Pop(Stack *s, int *x)
{
    if (!s->next)
    {
        return 0;
    }
    Stack *p = s->next;
    *x = p->data;
    s->next = p->next;
    free(p);
    return 1;
}
int getTop(Stack *s, int *x)
{
    if (!s->next)
    {
        return 0;
    }
    *x = s->next->data;
    return 1;
}

void printfStack(Stack *s)
{
    Stack *p = s;
    while (p->next)
    {
        p = p->next;
        printf("%d\n", p->data);
    }
    return;
}

int main()
{
    Stack *s;
    int x, n;
    InitStack(&s);

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
    }
}