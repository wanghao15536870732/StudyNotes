/*
编写程序，要求程序运行时，从键盘输入一个年份（整数），判断并输出该年份是否为闰年。
如果是闰年，输出1，否则输出0。

闰年的判断条件是：能被4整除且不能被100整除，或者能被400整除。
*/ 

#include <stdio.h>
#include <stdlib.h>
int main()
{
	int year;
	printf("请输入一个年份 ："); 
	scanf("%d",&year);
	if(( year % 4 == 0 && year % 100 != 0 ) || year % 400 == 0 )
	{
		printf("1");
	} 
	else
	{
		printf("0");
	}
	system("pause");
	return 0;
}

