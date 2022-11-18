#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node *lchild;
    struct Node *rchild;
} BTNode, *BiTree;

typedef struct SNode
{
    BiTree StatckTree[1000];
    int top;
} SepStack;

typedef struct QNode
{
    BiTree QueueTree[1000];
    int front;
    int rear;
} SepQueue;

BiTree CreateBiTree(); //创建二叉树
void PostOrder(BiTree root);
void PreOrder(BiTree root);
SepStack *InitStack();
int ISEmpty(SepStack *S);
void Push(SepStack *S, BiTree P);
BiTree pop(SepStack *S);
void TreeLevelOrder(BiTree root);
SepQueue *InitQueue();
int ISEmptyQ(SepQueue *Q);
void AddQ(SepQueue *Q, BiTree P);
BiTree DeleteQ(SepQueue *Q);

int main()
{
    printf("创造二叉树\n");
    BiTree T = CreateBiTree();
    printf("后序遍历结果为:\n");
    PostOrder(T);
    printf("\n");
    printf("非递归的先序遍历结果为\n");
    PreOrder(T);
    printf("层序遍历结果为:\n");
    TreeLevelOrder(T);
}

SepStack *InitStack()
{
    SepStack *S = (SepStack *)malloc(sizeof(struct SNode));
    S->top = -1;
    return S;
}

int ISEmpty(SepStack *S)
{
    if (S->top == -1)
        return 1;
    return 0;
}
void Push(SepStack *S, BiTree P)
{

    S->StatckTree[++(S->top)] = P;
}
BiTree pop(SepStack *S)
{

    return S->StatckTree[(S->top)--];
}

BiTree CreateBiTree()
{
    char ch;
    ch = getchar();
    getchar();
    if (ch == '#')
        return NULL; //#代表返回空
    else
    {
        BiTree T = (BiTree)malloc(sizeof(BTNode));
        T->data = ch;
        T->lchild = CreateBiTree();
        T->rchild = CreateBiTree();
        return T;
    }
}

void PostOrder(BiTree root)
{
    if (root)
    {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        printf("%c ", root->data);
    }
}

void PreOrder(BiTree root)
{
    SepStack *S = InitStack();
    BiTree P;
    P = root;
    while (P != NULL || !ISEmpty(S))
    {
        while (P != NULL)
        {
            printf("%c ", P->data);
            Push(S, P);
            P = P->lchild;
        }
        if (!ISEmpty(S))
        {
            P = pop(S);
            P = P->rchild;
        }
    }
    printf("\n");
}

SepQueue *InitQueue()
{
    SepQueue *Q = (SepQueue *)malloc(sizeof(struct QNode));
    Q->rear = 0;
    Q->front = 0;
    return Q;
}

int ISEmptyQ(SepQueue *Q)
{
    if (Q->front == Q->rear)
    {
        return 1;
    }
    return 0;
}

void AddQ(SepQueue *Q, BiTree P)
{
    Q->rear = (Q->rear + 1) % 1000;
    Q->QueueTree[Q->rear] = P;
}

BiTree DeleteQ(SepQueue *Q)
{

    Q->front = (Q->front + 1) % 1000;
    return Q->QueueTree[Q->front];
}

void TreeLevelOrder(BiTree root)
{
    SepQueue *Q = InitQueue();
    BiTree P;
    InitQueue(Q);
    AddQ(Q, root);
    while (!ISEmptyQ(Q))
    {
        P = DeleteQ(Q);
        printf("%c ", P->data);
        if (P->lchild != NULL)
        {
            AddQ(Q, P->lchild);
        }
        if (P->rchild != NULL)
        {
            AddQ(Q, P->rchild);
        }
    }
}