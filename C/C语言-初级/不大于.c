/*
编写程序，它的功能是：输入正整数m（m的值在100~10000之间），
使得等差数列1、2、3、4、5、6…n前n项和小于m，前n+1项和大于m，输出n的值。
如m的值为155，1+2+……+17>155,且1+2+……+17+18<155，输出17。
*/ 

#include <stdio.h>
#include <stdlib.h>
int main()
{	
	int m,n,i,s;
	printf("请输入一个正整数m ：");
	scanf("%d",&m);
	if(m < 100 || m > 1000) return 0;
	s = 0;
	for(i = 1;i <= m;i ++)
	{
		s += i;
		if(s > m) break; 
	}
	printf("%d",i - 1);
	system("pause");
	return 0;
} 
