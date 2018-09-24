/*
编写程序，要求程序运行时，从键盘求一元二次方程ax2+bx+c=0的系数a、b和c，
计算并输出该方程实根的个数。要求：若a =0，输出error!。
*/ 

#include <stdio.h>
int main()
{
	int a,b,c;
	int temp = 0;
	printf("请输入一元二次方程a*x*x + b*x + c = 0的系数a,b,c : ");
	scanf("%d%d%d",&a,&b,&c);
	temp = b * b - 4 * a * c; 
	if(a == 0)
	    printf("error!");
	else if(temp > 0)
		printf("该方程有两个实根\n");
	else if(temp = 0)
	    printf("该方程有一个实根\n");
	else
	    printf("该方程没有实根\n");
	return 0;
}

