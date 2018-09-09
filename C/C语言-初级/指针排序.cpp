/*
利用指针实现多个字符串的排序。要求：程序运行时，各字符串由键盘输入，并输出排序的结果。
*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
int main()
{
	char s1[10][80];
	char * p[10], * t;
	int i,j,k,count;
	scanf("%d", &count);
	if (count<1 || count>10)
		return 0;
	for (i = 0; i <= count; i++)
		gets_s(s1[i],80);
	for (i = 0; i <= count; i++)
		p[i] = s1[i];
	for (i = 0; i <= count - 2;i++)
		for (j = i; j < count;j++)
			if (strcmp(p[i], p[j])==1)
			{
				t = p[i];
				p[i] = p[j];
				p[j] = t;
			}
	for (i = 0; i <= count; i++)
		puts(p[i]);
	return 0;
}

