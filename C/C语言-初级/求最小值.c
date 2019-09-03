/*
 编写程序，要求程序运行时，从键盘输入三个整数，输出其中最小的一个数。
*/
#include <stdio.h>
#include <math.h>
int main()
{
	int a,b,c,temp = 0;
	printf("输入三个整数 ：");
	scanf("%d%d%d",&a,&b,&c);
	if(a > b)
	{
		temp = a;
		a = b;
		b = temp;
    }
	if(a > c)
	{
		temp = a;
		c = a;
		a = temp;
	}
    printf("其中最小的一个数为 : %d",a);
    return 0; 
}

