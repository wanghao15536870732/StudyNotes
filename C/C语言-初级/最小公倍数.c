/*
编写程序，求两个正整数的最大公约数和最小公倍数。
程序运行时输入两个正整数，输出最大公约数和最小公倍数。
*/

#include <stdio.h>
int main()
{
	int i,j,x,y;
	printf("请输入两个正整数 ：");
	scanf("%d %d",&i,&j);
	x = i;
	y = j;
	int temp1,temp2;
	if(i > j)
	{
		temp1 = i;
		i = j;
		j = temp1;
	}
	temp2 = j % i;
	while(temp2 != 0)
	{
		j = i;
		i = temp2;
		temp2 = j % i;
	}
	printf("最大公约数是 ：%d\n",i);
	printf("最小公倍数是 ：%d\n\n",x*y/i);
	return 0;
}

