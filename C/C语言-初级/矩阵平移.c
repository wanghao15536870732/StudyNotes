/*
编写程序，有一3行3列的整数矩阵（数据由键盘输入），
进行如下操作：矩阵第一行移至最后，矩阵其它行均上移一行。输出处理后的矩阵。
*/

#include <stdio.h>
int main()
{ 
	int num1[3][3],num2[3][3];
	int i,j;
	puts("请输入一个三阶矩阵 ：\n");
	for(i = 0;i < 3;i ++)
	{
		for(j = 0;j < 3;j ++)
			scanf("%d",&num1[i][j]);
	}
	for(i = 1;i < 3;i ++)
	{
		for(j = 0;j < 3;j ++)
			num2[i - 1][j] = num1[i][j];
	}
	for(j = 0;j < 3;j ++)
		num2[2][j] = num1[0][j];
	puts("转换之后的矩阵为 ：");
	for(i = 0;i < 3;i ++)
	{
		for(j = 0;j < 3;j ++)
		{
			printf("%d ",num2[i][j]);
			if(j == 2)
				printf("\n");
		}
	}
	printf("\n");	
	return 0;
}	


