/*
有两个字符串，分别为母串和子串，利用指针编程实现在母串中查找子串出现的次数。
要求：程序运行时，母串和子串由键盘输入。
*/ 

#include <stdio.h>
#include <string.h>
int main()
{	
	char s1[80],s2[80];
	char ss1[80],ss2[80];
	puts("请输入一个字符母串：");
	gets(s1);
	puts("请输入一个字符子串：");
	gets(ss1);
	int i,j,k,count = 0;
	int m,n;
	i = 0;
	m = 0;
	while(s1[i])
	{
		j = 0;
		k = i;
		while(ss1[j])
		{
			if(ss1[j] != s1[k])
			{
				break;
			}
			else
			{
				k ++;
				j ++;
			}
		}
		if(ss1[j] == 0)
		{
			n = 0;
			count ++;
			i = i + strlen(ss1);
		}
		else
		{
			s2[m ++] = s1[i];
			i ++;
		}
	}
	printf("子字符串出现了%d次\n",count);
	return 0;
}

