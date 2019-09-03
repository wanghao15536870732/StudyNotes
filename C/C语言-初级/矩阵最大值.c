/*编
写程序，有一3行4列矩阵，矩阵中各元素均为浮点数（数据由键盘输入，所有数据值各不相同），
输出其中最大元素值（结果保留两位小数）。
*/ 

#include <stdio.h>
int main()	
{	
	int i,j;
	double num[3][4];
	puts("输入一个3行4列的矩阵 ：");
	for(i = 0;i < 3;i ++)
	{	
		for(j = 0;j < 4;j ++)
		{	
			scanf("%lf",&num[i][j]);
		}
	}
	for(i = 1;i < 3;i ++)
	{	
		for(j = 1;j < 4;j ++)
		{
			if(num[0][0] < num[i][j])
				num[0][0] = num[i][j];
		}
	}
	printf("数组中最大的元素为 ：%.2lf\n",num[0][0]);
	return 0;
}

