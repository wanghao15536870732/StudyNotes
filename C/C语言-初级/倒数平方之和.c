/*
编写程序，求一数列的值。数列描述如下所示，输入整数m和整数n的值，输出数列的值。
（计算结果的小数部分保留两位小数。）
∑(k=1,m) k + ∑(k=1,m) k^2 +∑(k=1,n) 1/k + ∑(k=1,n) 1/k^2 
*/ 
#include <stdio.h>
int main()
{	
	int n,i;
	double s;
	printf("请输入一个正整数 ：");
	scanf("%d",&n);
	if(n <= 0) return 0;
	s = 1;
	for(i = 2; i <= n;i ++)
		s = s - 1.0 / i;
	printf("%.2lf\n",s);
	return 0;
}


