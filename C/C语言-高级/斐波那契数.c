/*
输出100以内的斐波那契数
*/ 

#include <stdio.h>
int main()
{
	int a[3];
	a[0] = 1;
	a[1] = 1;
	a[2] = 0;
	printf("输出100以内的斐波那契数 : \n%d\t%d\t%d\t",a[2],a[1],a[0]);
	for(;a[2] <= 100;)
	{
		a[2] = a[1] + a[0]; 
		a[0] = a[1];
		a[1] = a[2];
		if( a[2] <= 100 )
		{
			printf("%d\t",a[2]);
		}
    }
	return 0;
}

