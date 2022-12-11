#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char char_wight[256] = {0};

void readin()
{
    char c;
    int fp = open("Haffman.souce", 'r');
    while (fp)
    {
        if (read(fp, &c, 1) <= 0)
        {
            break;
        }
        char_wight[c]++;
    }
}
int main()
{
    readin();
}
