/*
编写程序，求一数列的值。数列如下所示，程序运行时输入正整数n，输出y的值。
（计算结果的小数部分保留两位小数） 
 y = 1 - 1 / 2 - 1 / 3 - ... - 1 / n
*/ 

#include <stdio.h>
int main()
{	
	int n,m,k;
	double s;
	printf("请输入两个正整数 ：");
	scanf("%d%d",&n,&m);
	if(n <= 0 || m <= 0) return 0;
	s = 0;
	for(k = 1;k <= m;k ++)
	s += k;
	for(k = 1;k <= m;k ++)
	s += k * k;
	for(k = 1;k <= m;k ++)
	s += 1.0 / k;
	for(k = 1;k <= m;k ++)
	s += 1.0 / k * k; 
	printf("%.2lf\n",s);
	return 0;
}

