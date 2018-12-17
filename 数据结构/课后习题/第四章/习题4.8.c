/*试编写一个函数，实现在顺序存储方式下字符串的strcompare（S1，S2）运算。*/

#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
typedef struct
{
    char str[MAXSIZE];
    int length;
} seqstring;
/* 函数strcompare()的功能是：当s1>s2时返回1，当s1==s2时返回0，当s1<s2时返回-1*/
int strcompare(seqstring s1, seqstring s2)
{
    int i, m = 0, len;
    len = s1.length < s2.length ? s1.length : s2.length;
    for (i = 0; i <= len; i++)
        if (s1.str[i] > s2.str[i])
        {
            m = 1;
            break;
        }
        else if (s1.str[i] < s2.str[i])
        {
            m = -1;
            break;
        }
    return m;
}
int main()
{
    seqstring s1, s2;
    int i, m;
    printf("input  char to s1:\n");
    gets_s(s1.str);
    s1.length = strlen(s1.str);
    printf("input  char to s2:\n");
    gets_s(s2.str);
    s2.length = strlen(s2.str);
    m = strcompare(s1, s2);
    if (m == 1)
        printf("s1>s2\n");
    else if (m == -1)
        printf("s2>s1\n");
    else if (m == 0)
        printf("s1=s2\n");
}