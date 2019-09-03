/*
编写程序判断字符类型，要求程序运行时，从键盘输入一个字符，输出该字符的类型。
若输入的字符是字母则输出：It is an alphabetic character.，
若输入的字符是数字则输出：It is a digit.，
若输入的字符是其他字符则输出：It is other character.。
*/
#include <stdio.h>
int main()
{
	int c;
	printf("请输入一个字符 ：");
	c = getchar();
	if(c >= 48 && c <= 57)
		printf("It is a digit.\n");
	else if( (c >= 65 && c <= 90) || (c >= 97 && c <= 122) )
		printf("It is an alphabetic character.\n");
	else 

		printf("It is other character.");
	return 0;
}


