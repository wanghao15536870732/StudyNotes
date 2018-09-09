/*
编写程序，有一3行3列的整数矩阵(数据由键盘输入)，输出该矩阵的转置矩阵
(提示：转置矩阵的行是原矩阵的列)。
*/ 
#include <stdio.h>
int main()	
{	
	int i,j;
	int num1[3][3],num2[3][3];
	puts("输入一个3行3列的矩阵 ：");
	for(i = 0;i < 3;i ++)
	{	
		for(j = 0;j < 3;j ++)
		{	
			scanf("%d",&num1[i][j]);
		}
	}
	for(i = 0;i < 3;i ++)
	{	
		for(j = 0;j < 3;j ++)
		{
			num2[i][j] = num1[j][i];
		}
	}
	puts("转置后的矩阵为 ：\n"); 
	for(i = 0;i < 3;i ++)
	{	
		for(j = 0;j < 3;j ++)
		{		
			printf("%d ",num2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}


