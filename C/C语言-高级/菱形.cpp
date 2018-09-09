/*
输出n边菱形
*/ 

#include <stdio.h>
int main()
{
	int n;
	printf("请输入菱形边长数 ：");
	scanf("%d",&n);
	for( int i = 1;i <= n ;i ++ )
	{
		for(int a = 1;a <= n - i + 1;a ++)
		{
			printf(" ");
		}
		for( int b = 1;b <= 2 * i - 1;b ++)
		{
		    printf("*");
	    }
	    printf("\n");
	}
	for( int i = 1;i <= n - 1;i ++ )
	{ 
	    for(int a = 1;a <= i + 1;a ++)
	    { 
	    	printf(" ");
		}
		for( int b = 1;b <= 2 * ( n - i) -1;b ++ )
		{
		    printf("*");
		}
		printf("\n");
	} 
	return 0;
}

