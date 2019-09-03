/*
输出杨辉三角
*/ 

#include <stdio.h>
int main()
{
	int i,j,k,n;
	int a[100][100];
	printf("请输入此杨辉三角的行数 ：");
	scanf("%d",&n);
	for(i = 0;i <= n ;i ++)
	{
		a[i][0] = 1;
		a[i][i] = 1;
    }
    for(i = 1;i <= n ;i ++)
    {
	    for(j = 1;j < i ;j ++)
	    {
	    	a[i][j] = a[i - 1][j - 1] + a[i -1][j];
		}
    }
   
    for(i = 0;i < n ;i ++)
    {
	    for(k = 0;k < n - i;k ++)
            printf(" ");
	    for(j = 0;j <= i;j ++)
	    {
	    	printf("%2d",a[i][j]);
	    }
       printf("\n");
	}
    return 0;
}		

