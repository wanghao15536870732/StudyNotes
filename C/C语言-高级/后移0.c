/*
一个一维n*sizeof(int)数组(有0和非0数)，将非0数放到数组前面，0往后移。
（要求循环执行次数越少越好,n是自己输入的，里面的数也自己输入） 
*/

#include <stdio.h>
int main()
{
    int a[10000],n;
    int i,j,temp = 0;
	printf("输入数组中数的个数 ：");
	scanf("%d",&n);
	for(i = 0;i < n;i ++)
	{ 
		scanf("%d",&a[i]);
	}
	for(i = 1;i <= n - 1;i ++)
	{
		for(j = 1;j <= n - 1;j ++)
		{
			if(a[j - 1] < a[j])
			{
				temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
			}
		}
	} 
	for(i = 0;i < n;i ++)
	{
        puts("输出");
		printf("%d\t",a[i]);
	}
	printf("\n");
	return 0;
}

