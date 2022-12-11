
#include <fstream>
#include <stdio.h>
#include <iostream>

typedef struct char_count *count_node;
struct char_count
{
    char ch;
    long count;
    short bit;
};
count_node weight[126];

typedef struct HNodeType *HNode;
struct HNodeType
{
    count_node node;
    HNode parent;
    HNode lchild;
    HNode rchild;
};
HNode p;

typedef struct charCode *code;
struct charCode
{
    char ch;
    short codeNum[1000];
    int codeLen;
};
code char_code[125];

int n, num;
int sumStrLen = 0;
char str[100000];
short codeStr[100000000];

using namespace std;

/**
 * 译码
 */
void tranCode(int len)
{
    HNode q;
    q = p;
    ofstream fout("Haffman.decode");
    cout << "\n译码结果:" << endl;
    for (int i = 0; i < len; i++)
    {
        if (codeStr[i] == 0)
        {
            q = q->lchild;
            if (q->node->ch)
            {
                cout << q->node->ch;
                fout << q->node->ch;
                q = p;
            }
        }
        if (codeStr[i] == 1)
        {
            q = q->rchild;
            if (q->node->ch)
            {
                cout << q->node->ch;
                fout << q->node->ch;
                q = p;
            }
        }
    }
    cout << "\n结果写入Huffman.decode" << endl;
}

/**
 * 计算压缩效率
 */
void efficiency(int len)
{
    int sumCodeLen = 0;
    for (int i = 0; i <= len; i++)
    {
        sumCodeLen += char_code[i]->codeLen;
    }
    cout << "\n压缩效率:" << sumCodeLen << "/" << sumStrLen << "=" << sumCodeLen * 1.0 / sumStrLen << endl;
}

/**
 * 把字符串编码，返回编码后数组的长度
 */
int finishCode()
{
    int m = 0;
    ofstream fout("Haffman.code");
    cout << "\n编码结果:" << endl;
    for (int i = 0; i < sumStrLen; i++)
    {
        for (int j = 0; j < sumStrLen; j++)
        {
            if (char_code[j]->ch == str[i])
            {
                for (int k = 0; k < char_code[j]->codeLen; k++)
                {
                    codeStr[m] = char_code[j]->codeNum[k];
                    cout << codeStr[m];
                    fout << codeStr[m];
                    m++;
                }
                break;
            }
        }
    }
    cout << "\n结果写入Huffman.code" << endl;
    return m;
}

/**
 * 获取各个字符的编码
 */
void getCode()
{

    for (int i = 0; i < 125; i++)
    {
        char_code[i] = new charCode();
        for (int j = 0; j < 1000; j++)
        {
            char_code[i]->codeNum[j] = -1;
        }
    }

    int cache[1000] = {0}, i = 0, j = 0;
    HNode q1, q2;
    q1 = p;

    while (q1->lchild)
    {
        char_code[i]->ch = q1->lchild->node->ch;
        j = 0;
        cache[j] = q1->lchild->node->bit;
        j++;
        q2 = q1;
        while (q2->node->bit)
        {
            cache[j] = q2->node->bit;
            j++;
            q2 = q2->parent;
        }
        int m = 0;
        for (int k = j - 1; k >= 0; k--)
        {
            char_code[i]->codeNum[m] = cache[k];
            m++;
        }
        char_code[i]->codeLen = m;
        i++;
        if (q1->rchild)
        {
            q1 = q1->rchild;
        }
        else
        {
            break;
        }
    }

    q1 = p;
    if (q1->rchild)
    {
        j = 0;
        int cache2[1000] = {0};
        while (q1->rchild)
        {
            cache[j] = q1->rchild->node->bit;
            j++;
            if (q1->rchild->node->ch)
            {
                char_code[i]->ch = q1->rchild->node->ch;
            }
            q1 = q1->rchild;
        }
        int m = 0;
        for (int k = j - 1; k >= 0; k--)
        {
            char_code[i]->codeNum[m] = cache[k];
            m++;
        }
        char_code[i]->codeLen = m;
    }

    cout << "\n编码:" << endl;
    for (int k = 0; k <= i; k++)
    {
        if (char_code[k]->ch)
        {
            cout << char_code[k]->ch << " : ";
            int k2 = 0;
            while (char_code[k]->codeNum[k2] != -1)
            {
                cout << char_code[k]->codeNum[k2];
                k2++;
            }
        }
        cout << endl;
    }

    // 把字符串进行编码
    int codeLen = finishCode();

    // 统计压缩效率
    efficiency(i);

    // 译码
    tranCode(codeLen);
}

/**
 * 分配比特
 */
void coder(HNode p)
{
    if (p)
    {
        if (p->lchild)
        {
            p->lchild->node->bit = 0;
        }
        if (p->rchild)
        {
            p->rchild->node->bit = 1;
        }
        if (p->lchild)
        {
            coder(p->lchild);
        }
        if (p->rchild)
        {
            coder(p->rchild);
        }
    }
}

/**
 * 构建哈夫曼树
 */
void HaffmanTree()
{
    HNode hNl, hNr;
    hNl = new HNodeType();
    hNr = new HNodeType();
    hNl->lchild = hNl->rchild = NULL;
    hNl->node = weight[1];

    hNr->lchild = hNr->rchild = NULL;

    if (n == 1)
    {
        hNr->node = NULL;

        p = hNl->parent = new HNodeType();

        p->lchild = hNl;
        p->rchild = NULL;
        p->node = new char_count();
        p->node->ch = 0;
        p->node->count = p->lchild->node->count;
        p->parent = NULL;
    }
    else
    {
        hNr->node = weight[2];

        for (int i = 3; i <= n; i++)
        {
            p = hNl->parent = hNr->parent = new HNodeType();

            p->lchild = hNl;
            p->rchild = hNr;
            p->node = new char_count();
            p->node->ch = 0;
            p->node->count = p->lchild->node->count + p->rchild->node->count;

            hNl = new HNodeType();
            hNl->node = weight[i];
            hNl->lchild = hNl->rchild = NULL;

            hNr = p;
        }

        p = hNl->parent = hNr->parent = new HNodeType();

        p->lchild = hNl;
        p->rchild = hNr;
        p->node = new char_count();
        p->node->ch = 0;
        p->node->count = p->lchild->node->count + p->rchild->node->count;
        p->parent = NULL;
    }
    // 打印

    // 分配比特
    coder(p);
}

/**
 * 交换堆中两个元素
 *
 */
void swap(int x, int y)
{
    count_node t;
    t = weight[x];
    weight[x] = weight[y];
    weight[y] = t;
}

/**
 * 向下调整
 */
void siftdown(int i)
{
    int t, flag = 0;
    while (i * 2 <= num && flag == 0)
    {
        if (weight[i]->count < weight[i * 2]->count)
            t = i * 2;
        else
            t = i;
        if (i * 2 + 1 <= num)
            if (weight[t]->count < weight[i * 2 + 1]->count)
                t = i * 2 + 1;
        if (t != i)
        {
            swap(t, i);
            i = t;
        }
        else
            flag = 1;
    }
}

/**
 * 建立堆
 */
void creat()
{
    for (int i = num / 2; i >= 1; i--)
        siftdown(i);
}

/**
 * 堆排序
 */
void heapsort()
{
    while (num > 1)
    {
        swap(1, num);
        num--;
        siftdown(1);
    }
}

/**
 * 构造权重低的先出的优先队列（最小堆）
 */
void priority_queue()
{
    creat();
    heapsort();
    cout << "\n最小堆:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << weight[i]->ch << " 权重：" << weight[i]->count << endl;
    }
}

/**
 * 统计从文件当中获取的字符串中每个字符出现的次数
 */
void get_str_weight2()
{
    int i = 0;
    long count[126] = {0};
    while (str[i] != '\0')
    {

        count[str[i] - 32]++;
        sumStrLen++;
        i++;
    }

    sumStrLen *= 8;
    int j = 1;
    cout << "出现次数:" << endl;
    for (int i = 1; i < 126; i++)
    {
        if (count[i] > 0)
        {
            weight[j]->ch = i + 32;
            weight[j]->count = count[i];
            cout << weight[j]->ch << " :  " << weight[j]->count << endl;
            j++;
            num++;
        }
    }

    n = num;
}

/**
 * 获取文件中的所有字符
 */
void get_file()
{

    // 以读模式打开文件
    ifstream fin("Haffman.souce");
    fin >> str;
}

/**
 * 执行任务
 */
void task()
{
    get_file();
    get_str_weight2();
    priority_queue();
    HaffmanTree();
    getCode();
}

int main()
{
    // 初始化
    for (int i = 0; i < 126; i++)
    {
        weight[i] = new char_count();
    }

    task();

    return 0;
}