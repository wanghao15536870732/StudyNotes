/*
编写程序，有一包含10个整数的数列（数据由键盘输入，保证至少有一个正数），
计算并输出数列中所有正数的平均值（结果保留两位小数）。
*/

#include <stdio.h>
#include <math.h>
int main()
{ 
	int num[10];
	int i;
	double n,c,s;
	puts("请输入十个整数 ：\n");
	for(i = 0;i < 10;i ++)
		scanf("%d",&num[i]);
	c = 0;
	s = 0;
	for(i = 0;i < 10;i ++)
	{
		if(num[i] > 0)
		{
			s += num[i];
			c ++;
		}
	}
	n = s / c;
	printf("数列中所有正数的平均值 ：%.2lf\n",n);
	return 0;
}

