/*
编写程序，统计素数的个数。程序运行时输入一个自然数n（n在100到10000之间），
输出100到n之间（包括n）素数的个数。（提示：只能被1和它本身整除的数为素数。）
*/ 

#include <stdio.h>
#include <math.h>
int main()
{	
	int n,i,j,s;
	puts("请输入一个自然数 ：");
	scanf("%d",&n);
	if(n < 100 || n > 10000) return 0;
	s = 0;
	for(i = 100;i <= n;i ++)
	{
		for(j = 2;j <= (int) sqrt( (double) i );j ++)
			if(i % j == 0)
				break;
			if(j == (int) sqrt( (double) i ) + 1)
				s ++;
	}
	printf("100到该自然数之间素数的个数为 ：%d",s);
	return 0;
}

