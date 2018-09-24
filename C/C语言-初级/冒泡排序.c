/*
编写程序，有一包含10个数的整数数列（程序运行时，数据由键盘输入），
完成对该数列从小到大排序，输出排序后的结果。
*/
 #include <stdio.h>
int main()	
{
	int num[10];
	int n,i,j;
	puts("请输入十个整数 ："); 
	for(n = 0;n < 10;n ++)
		scanf("%d",&num[n]);
	int temp;
	for(i = 1;i <= 10 - 1;i ++)
	{
		for(j = 1;j <= 10 - i;j ++)
		{
			if(num[j - 1] > num[j])
			{	
				temp = num[j - 1];
				num[j - 1] = num[j];
				num[j] = temp;
			}
		}
	}
	puts("该数组从小到大排序后 ");
	for(j = 0;j < 10;j ++)
		printf("%d ",num[j]);
	printf("\n\n");
	return 0;
}

