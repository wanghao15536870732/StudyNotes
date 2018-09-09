/*
写程序，进行整除判断。程序运行时输入一个整数n（n在10到1000之间），
输出10到n之间所有能同时被5和7整除的整数个数。
*/ 

#include <stdio.h>
int main()
{
	int n,i,s;
	printf("请输入一个整数n ：");
	scanf("%d",&n);	
	if(n < 10 || n > 1000) return 0;
	s = 0; 
	for(i = 10;i <= n;i ++)
	{
		if(i % 7 == 0 && i % 5 == 0)
			s ++; 
	}
	printf("10到n之间同时被5和7整除的整数个数 ：",s);
	return 0;
}

