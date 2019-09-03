/*
编写程序，求自然数的阶乘之和。程序运行时输入一个自然数n（n在1到20之间），
输出"1！+2！+…+n！"的值。（要求：计算结果的小数部分保留两位小数）。
*/ 
#include <stdio.h>
int main()
{	
	int n,i,j,s,d;
	printf("请输入一个自然数 ：");
	scanf("%d",&n);
	if(n < 1 || n > 20) return 0;
	s = 1;
	for(i = 2;i <= n;i ++)
	{
		d = 1;
		for(j = 2;j <= i;j ++)
			d = d * j;
		s += d;
	}
	printf("阶乘合为 ：%d",s);
	return 0;
}

