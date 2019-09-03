/*
有三个字符串，分别为母串、子串1和子串2，利用指针编程实现将母串中所有的子串1用子串2替换。
要求：程序运行时，母串、子串1和子串2由键盘输入。
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
	puts("请输入你想要替换成的字符串：");
	gets(ss2);
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
			for(int ii = 0;ii < strlen(ss2);ii ++)
			{
				s2[m ++] = ss2[n ++];
			}
			count ++;
			i = i + strlen(ss1);
		}
		else
		{
			s2[m ++] = s1[i];
			i ++;
		}
	}
	printf("子字符串出现了%d回\n",count);
	puts("替换后的字符串为：");
	puts(s2);
	return 0;
}



