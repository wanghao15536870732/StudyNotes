/*
编写程序，求一个包含10个元素的整型数组中的最大元素值（数据由键盘输入）。
*/

#include <stdio.h>
int main()	
{
	int num[10];
	int i,j;
	puts("请输入十个整数 ："); 
	for(i = 0;i < 10;i ++)
		scanf("%d",&num[i]);
	for(j = 0;j < 10;j ++)
	{
		if(num[0] < num[j])
			num[0] = num[j];
	}
	printf("该数组中最大的元素为 ：%d\n",num[0]);
	return 0;
} 

