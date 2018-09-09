/*
编写程序，要求程序运行时，从键盘输入一个月份，输出2017年该月有多少天。
若输入的月份不是1到12，输出error!。
*/

#include <stdio.h>
int main()
{
	int i;
	printf("请输入2017年的一个月份 ：");
	scanf("%d",&i);
	if(i >= 1 && i <= 12) 
	{
		switch(i)
		{
        case 1:case 3:case 5:case 7:case 8:case 10:case 12: 
        	printf("该月有31天\n");break;
        case 4:case 6:case 9:case 11: 
        	printf("该月有30天\n");break;
        case 2:
        	printf("该月有28天\n");break;
		}
	}
	else
	{
		printf("error!");
	}
	return 0;
}

