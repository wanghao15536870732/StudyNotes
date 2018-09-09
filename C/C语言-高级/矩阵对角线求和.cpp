/*
数组两个对角线求和.（n维数组如果觉得一个一个输入赋值的太麻烦的话可以考虑活用i和j）
*/ 
#include <stdio.h>
int main()
{
	int i,n,j;
	int c1 = 0,c2 = 0,c = 0,k = 0;
	int a[100][100];
	printf("请输入矩阵的阶数 n ：");
	scanf("%d",&n); 
	for( i = 0;i < n;i ++ )
	{
		for(j = 0;j < n;j ++ )
		{
			scanf("%d",&a[i][j]);
	    }
	    k = a[i][i];
	    c1 = c1 + k;
	    c = a[i][n - i - 1];
	    c2 = c2 + c;
    }
	printf("该n阶矩阵的对角线之和为 ：%d",c1 + c2);
	return 0;
}

