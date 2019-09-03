/*
编写程序，有一包含10个整数的数列（数据由键盘输入），计算并输出数列中非负数的个数。
*/ 
#include <stdio.h>
int main()	
{
	int num[10];
	int i,j,s;
	puts("请输入十个整数 ："); 
	for(i = 0;i < 10;i ++)
		scanf("%d",&num[i]);
	s = 0;
	for(j = 0;j < 10;j ++)
	{
		if(num[j] >= 0)
			s ++;
	}
	printf("该数组中非负数的个数为 ：%d\n",s);
	return 0;
}

