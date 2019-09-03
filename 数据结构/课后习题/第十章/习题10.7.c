/*设计一个算法，重新排列一组整数位置，使所有负值的整数位于正值的整数之前（不


*/

#include <stdlib.h>
#include <stdio.h>
/*本函数的功能是将数组a在O（n）的时间内将所有的负数调整到正数的左边*/
void change(int a[], int len)
{
    int i, j, t;
    i = 0;
    j = len - 1;
    while (i < j)
    {
        while ((i < j) && (a[i] < 0))
            i++; /*从左向右找第一个正数*/
        while ((i < j) && (a[j] > 0))
            j--; /*从右向左找第一个负数*/
        if (i != j)
        {
            t = a[i];
            a[i++] = a[j];
            a[j--] = t;
        }

    }
    



int main()
{
    int a[10], i;
    for (i = 0; i < 10; i++)

        111
        {
            printf("a[%d]=", i);
            scanf("%d", &a[i]);
        }
    change(a, 10);
    printf("\n\n");
    for (i = 0; i < 10; i++)
        printf("%4d", a[i]);
    return 0;
}