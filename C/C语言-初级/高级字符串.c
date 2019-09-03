/*
编写程序，要求程序运行时接收从键盘输入的两个字符串（长度均不超过80），
请分别对两个字符串中奇数位置上的字符形成的两个子串比较大小，若第一个子串大于第二个子串，输出1，
若第一个子串等于第二个子串，输出0，否则输出-1。如两个字符串分别为"123abcdefg"和"12345678"，
奇数位置上的字符形成的子串分别为"13bdf"和"1357"，输出结果为1。
*/ 

#include <stdio.h>
int main()
{
	char num1[80],num2[80];
	char num3[40],num4[40];  
	int i,j;
	int m,n,pos;
	gets(num1);
	gets(num2);
	i = 0;
	m = 0;
	while(num1[i] != '\0')
	{
		num3[m] = num1[i];
		m ++;
		i ++;
		if(num1[i] == '\0')
			break;
		i ++;
		
	}
	num3[m + 1] = '\0';
	j = 0;n = 0;
	while(num2[j] != '\0')
	{
		num4[n] = num2[j];
		j ++;
		if(num2[j] == '\0')
			break;
		j ++;
		n ++;
	}
	num4[n + 1] = '\0';
	m = 0;n = 0;
	while(num3[m] != '\0' && num4[n] != '\0')
	{
		if(num3[m] > num4[n])
		{
			pos = 1;
			break;
		}
		else if(num3[m] < num4[n])
		{
			pos = -1;
			break;
		}
	}
	if(pos == 0)
	{
		if(num3[m + 1] != '\0')
			pos = 1;
		else if(num4[n + 1] != '\0')
			pos = -1;
		else
			pos = 0;
	}
	printf("%d\n",pos);
	return 0;
}

