/*
编写程序，要求程序运行时接收从键盘输入的字符串（长度均不超过80），
请统计并输出字符串中英文字母（大小写一起统计）的个数。
*/
#include <stdio.h>
int main()	
{	
	int i,j;
	char num[80];
	puts("输入一个字符串 ："); 
	scanf("%s",&num);
	j = 0; 
	for(i = 0;num[i] != '0';i ++) 
	{
		if( (65 <= num[i] && num[i] <=90) || (97 <= num[i] && num[i] <= 122) )
			j ++;
	}
	printf("字符串中英文字母的个数 ：%d\n",j);
	return 0;
}

