/*
编写程序，要求程序运行时，从键盘输入x的值，
根据分段函数计算并输出y的值（结果保留两位小数）。
分段函数如下。（提示：可使用求平方根函数：sqrt()）
*/ 

#include <stdio.h>
#include <math.h> 
int main()
{                        
	int x;
	double y;
	printf("输出x的值 ：");
	scanf("%d",&x);
	if(x < 1)
	{
		y = x * x + 2 * x + sin(x);
		printf("输出y的值 ：%.2lf\n",y); 
	}
	else if(x >= 1 && x <= 10)
	{
		y = 2 * x - 1;
		printf("输出y的值 ：%.2lf\n",y);
	}
	else
	{
		y = sqrt(2 * x * x * x - 11);
		printf("输出y的值 ：%.2lf\n",y);
	}
	return 0;
}



