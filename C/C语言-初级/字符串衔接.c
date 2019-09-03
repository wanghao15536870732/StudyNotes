/*
编程实现字符串的处理。程序运行时从键盘输入一个字符串（字符个数小于20）
和一个指定字符，要求将字符串中该指定字符移动字符串的末尾，最后输出处理后的字符串。
要求：程序由两个函数构成，main函数的作用是输入字符串和指定字符，
子函数的作用是实现指定字符的移动操作。
*/ 
#include"stdio.h"
#include"string.h"
void fun(char s[],char c)
{
	int count = 0;
	int i = 0,j = 0;
	int l;
	l = strlen(s);
	while (s[i])
	{
		if (s[i++] == c)
			count++;
	}
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			s[j++] = s[i];
		i++;
	}
	for (i = 0; i < count;i++)
		s[j ++] = c;
	s[j] = '\0';
}

int main()
{
	char s[80], c;
	gets(s);
	c = getchar();
	fun(s, c);
	puts(s);
}



