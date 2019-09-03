/*
编写程序，要求程序运行时接收从键盘输入的两个字符串（长度均不超过80），
并将第二个字符串中奇数位置上的字符顺序连接到第一个字符串的末尾（
说明：字符串中的首字符位置为1），最后输出第一个字符串。
*/
#include <stdio.h>
int main()
{
	char num1[80],num2[80];
	int i,j;
	gets(num1);
	gets(num2);
	i = 0;	while(num1[i] != '\0')
		i ++;
	j = 0;
	while(num2[j] != '\0')	{
		num1[i + j / 2] = num2[j]; 
		j ++;
		if(num2[j] == '\0')
			break;
		j ++;
	}
	num1[i + j / 2 + 1] = '\0';
	puts(num1);
	return 0;
} 

