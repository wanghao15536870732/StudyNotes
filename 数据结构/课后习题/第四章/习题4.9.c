/*试编写一个函数，实现在顺序存储方式下字符串的replace（S，T1，T2）运算。
本程序用来在顺序存储下用快速匹配模式实现在字符串S中用T2替换所有T1出现的可能*/

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#define maxsize 100
typedef struct
{
    char str[maxsize];
    int length;
} seqstring;
//求next[]函数
void getnext(seqstring *p, int next[])
{
    int i, j;
    next[0] = -1;
    i = 0;
    j = -1;
    while (i < p->length)
    {
        if (j == -1 || p->str[i] == p->str[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

//快速模式匹配算法
int kmp(seqstring *t, seqstring *p, int next[], int temppos)
{
    int i, j;
    i = temppos, j = 0;
    while (i < t->length && j < p->length)
    {
        if (j == -1 || t->str[i] == p->str[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j == p->length)
        return (i - p->length);
    else
        return (-1);
}
//替换函数
void takeplace(seqstring *S, seqstring *T1, seqstring *T2)
{
    int next[maxsize], temppos = 0, pos, i;
    int lent1, lent2;
    lent1 = strlen(T1->str); //求T1串长度
    lent2 = strlen(T2->str); //求T2串长度
    getnext(T1, next);       //求T1串的next[]向量
    do
    {
        pos = kmp(S, T1, next, temppos); //快速模式匹配
        temppos = pos + T1->length;
        if (pos != -1) //匹配成功
        {
            if (lent1 > lent2) //T1串长度大于T2串长度
            {
                for (i = temppos; i < S->length; i++) //前移
                    S->str[i - lent1 + lent2] = S->str[i];
                for (i = 0; i < T2->length; i++) //替换
                    S->str[pos + i] = T2->str[i];
                S->length -= lent1 - lent2; //修改长度
            }
            else if (lent2 > lent1) //T2串长度大于T1串长度
            {
                for (i = S->length - 1; i >= temppos; i--) //后移留空
                    S->str[i + lent2 - lent1] = S->str[i];
                for (i = 0; i < T2->length; i++) //替换
                    S->str[pos + i] = T2->str[i];
                S->length += lent2 - lent1; //修改长度
            }
            else //T1长度与T2长度相等
            {
                for (i = 0; i < T2->length; i++)
                    S->str[pos + i] = T2->str[i];
            }
            temppos = pos + T2->length; //修改下一次模式匹配的起点位置
        }
    } while (pos != -1);
    S->str[S->length] = '\0';
}
int main()
{
    seqstring *S, *T1, *T2;
    printf("\n\n本程序用来实现字符串替换，将S中用T2替换T1所有出现\n:");
    printf("请输入S中的字符\n");
    S = (seqstring *)malloc(sizeof(seqstring));
    T1 = (seqstring *)malloc(sizeof(seqstring));
    T2 = (seqstring *)malloc(sizeof(seqstring));
    scanf("%s", S->str);
    S->length = strlen(S->str);
    printf("输入要被替换的串(input T1):\n");
    scanf("%s", T1->str);
    T1->length = strlen(T1->str);
    printf("输入替换串(input T2):\n");
    scanf("%s", T2->str);
    T2->length = strlen(T2->str);
    takeplace(S, T1, T2);
    printf("替换后的字符串为：\n");
    printf("%s\n", S->str);
    free(S);
    free(T1);
    free(T2);
}