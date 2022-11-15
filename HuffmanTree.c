#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define N 30
#define M 2 * N - 1
#define MAX 99999

typedef struct
{
    char name;
    int weight;
    int parent;
    int left;
    int right;
    char mi[N];
} HTNode, HuffmanTree[M + 1];
HuffmanTree ht;
void Select(HuffmanTree ht, int n, int *s1, int *s2);
void Huffman(HuffmanTree ht, int w[], int n);
void HuffmanCode(int n, HuffmanTree ht);
void CodeHuffman(HuffmanTree ht, char k[], int g);
void write(HuffmanTree ht, const char *filename, int n);
void write1(HuffmanTree ht, const char *filename, int n);
void read(HuffmanTree ht, const char *filename);
void read1(HuffmanTree ht, const char *filename);

void Select(HuffmanTree ht, int n, int *s1, int *s2)
{
    int i, min1 = MAX, min2 = MAX;
    *s1 = 0;
    *s2 = 0;
    for (i = 1; i <= n; i++)
    {
        if (ht[i].parent == 0)
        {
            if (ht[i].weight < min1)
            {
                min2 = min1;
                *s2 = *s1;
                min1 = ht[i].weight;
                *s1 = i;
            }
            else if (ht[i].weight < min2)
            {
                min2 = ht[i].weight;
                *s2 = i;
            }
        }
    }
}

void Huffman(HuffmanTree ht, int w[], int n)
{

    int i;
    for (i = 1; i <= n; i++)
    {

        ht[i].parent = 0;
        ht[i].left = 0;
        ht[i].right = 0;
    }
    int m = 2 * n - 1;
    for (i = n + 1; i <= m; i++)
    {
        ht[i].weight = 0;
        ht[i].parent = 0;
        ht[i].left = 0;
        ht[i].right = 0;
    }

    int s1, s2;
    for (i = n + 1; i <= m; i++)
    {
        Select(ht, i - 1, &s1, &s2);
        ht[i].weight = ht[s1].weight + ht[s2].weight;
        ht[s1].parent = i;
        ht[s2].parent = i;
        ht[i].left = s1;
        ht[i].right = s2;
    }
}

void HuffmanCode(int n, HuffmanTree ht)
{
    int k = 0;
    char *ma;
    ma = (char *)malloc(n * sizeof(char));
    memset(ma, '#', sizeof(ma));
    for (int i = 1; i <= n; i++)
    {
        k = 0;
        int start = n - 1, c = i, p = ht[i].parent;
        int o = 0;
        while (p != 0)
        {
            --start;
            if (ht[p].left == c)
                ma[start] = '0';
            else
                ma[start] = '1';
            c = p;
            p = ht[p].parent;
        }
        printf("%c的编码:\n", ht[i].name);

        for (int j = 0; j < n; j++)
        {
            if (ma[j] == '0' || ma[j] == '1')
            {
                printf("%c", ma[j]);
                ht[i].mi[o++] = ma[j];
            }
        }

        printf("\n");
        memset(ma, '#', sizeof(ma));
    }
}

void CodeHuffman(HuffmanTree ht, char k[], int g)
{
    int s = 0;
    int j = strlen(k);
    int q = 2 * g - 1;

    while (s <= j)
    {
        if (ht[q].left == 0 && ht[q].right == 0)
        {
            printf("%c", ht[q].name);
            q = g * 2 - 1;
        }
        if (k[s] == '0')
        {
            q = ht[q].left;
        }
        if (k[s] == '1')
        {
            q = ht[q].right;
        }
        s++;
    }
}

void write(HuffmanTree ht, const char *filename, int n)
{
    FILE *fp;

    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fp = fopen(filename, "w+");
    }

    int y = 1;
    while (n--)
    {
        fprintf(fp, "%s\n", ht[y++].mi);
    }
    y = 1;

    fclose(fp);
}

void write1(HuffmanTree ht, const char *filename, int n)
{
    FILE *fp;
    int o = 2 * n - 1;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fp = fopen(filename, "w+");
    }
    int y = 1;
    while (o--)
    {
        fprintf(fp, "%c\t%d\t%d\t%d\n", ht[y].name, ht[y].parent, ht[y].left, ht[y].right);
        y++;
    }
    fclose(fp);
}
int y;

void tongji(char t[], HuffmanTree ht)
{
    int i, j, d = 1;
    int p[MAX] = {0};
    int k = strlen(t);
    for (i = 0; i < k; i++)
    {
        if (p[t[i] - '0'] == 0)
        {
            p[t[i] - '0'] = 1;
            ht[d].name = t[i];
            ht[d++].weight++;
        }
        else
        {
            for (j = 1; j <= d; j++)
            {
                if (ht[j].name == t[i])
                {
                    ht[j].weight++;
                    break;
                }
            }
        }
    }
    y = d - 1;
}
int f;

void read(HuffmanTree ht, const char *filename)
{
    int u = 1;
    int d = 1;

    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fopen(filename, "w+");
    }

    while (fscanf(fp, "%s\n", ht[u++].mi) != EOF)
    {
    }

    fclose(fp);
    f = u - 2;
}

void read1(HuffmanTree ht, const char *filename)
{
    int d = 1;

    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fopen(filename, "w+");
    }
    while (fscanf(fp, "%c\t%d\t%d\t%d\n", &ht[d].name, &ht[d].parent, &ht[d].left, &ht[d].right) != EOF)
    {
        d++;
    }
    fclose(fp);
}

void read2(const char *filename, char k[])
{

    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fopen(filename, "w+");
    }

    fscanf(fp, "%s", k);

    fclose(fp);
}

int main()
{
    int i, j;
    int w[N];
    char str[N];
    int z;
    scanf("%d", &z);
    if (z == 1)
    {
        scanf("%s", str);
        int r = strlen(str);
        tongji(str, ht);

        char e[MAX];
        Huffman(ht, w, y);
        HuffmanCode(y, ht);
        printf("这段话的编码是：");
        for (i = 0; i < r; i++)
        {
            for (j = 1; j <= y; j++)
            {
                if (str[i] == ht[j].name)
                {
                    printf("%s", ht[j].mi);
                    strcat(e, ht[j].mi);
                    break;
                }
            }
        }
        printf("\n");

        write(ht, "huffman.txt", y);
        write1(ht, "huffman1.txt", y);
        write2(ht, "huffman2.txt", r, y, str);
    }
    if (z == 2)
    {
        char t[MAX];
        read(ht, "huffman.txt");
        read1(ht, "huffman1.txt");
        read2("huffman2.txt", t);
        CodeHuffman(ht, t, f);
    }
    return 0;
}