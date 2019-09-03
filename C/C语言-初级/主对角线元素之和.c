/*
编写程序，有一3行3列的整数矩阵（数据由键盘输入），计算并输出矩阵中主对角线元素之和。
*/

#include <stdio.h>
int main()
{ 
	int num[3][3];
	int i,j,sum;
	puts("请输入一个三阶矩阵 ：\n");
	for(i = 0;i < 3;i ++)
	{
		for(j = 0;j < 3;j ++)
			scanf("%d",&num[i][j]);
	}
	sum = 0;
	for(i = 0;i < 3;i ++)
		sum += num[i][i];
	printf("该数组主对角线之和为 ：%d",sum);
	return 0;
}

