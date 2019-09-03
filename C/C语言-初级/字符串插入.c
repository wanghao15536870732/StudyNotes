/*
编程实现字符串的处理。程序运行时从键盘输入一个字符串（字符个数小于20）和一个指定字符，
要求在字符串中每两个字符之间插入该指定字符，最后输出处理后的字符串。
要求：程序由两个函数构成，main函数的作用是输入字符串和指定字符，
子函数的作用是实现指定字符的插入操作
*/ 

#include <stdio.h>
void insert_main(char s[],char n);
int main()
{	
	char c;	
	char str[100];
	puts("请输入一个字符串(字符个数小于20):");
	gets(str);
	puts("请输入想要插入的字符:");
	scanf("%c",&c);	
	insert_main(str,c);
	return 0;
} 
void insert_main(char s[],char n)
{
	
	int i,j = 0;
	while(s[j] != '\0')
		j ++;
	for(i = j - 1;i > 0;i --)
	{
		s[2 * i] = s[i];
		s[2 * i - 1] = n;
	}
	for(i = 0;i < 2 * j;i ++)
		printf("%c",s[i]);
	printf("\n");
}

