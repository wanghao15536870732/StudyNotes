/*
编写程序，要求程序运行时，从键盘输入一个三位正整数，
将它反向输出。（提示：若输入的不是正整数，输出error!3若输入三位正整数的个位数为0，
十位数不为0，则输出十位数和百位数；若输入三位正整数的个位数和十位数均为0，
则输出百位数。）
*/ 
#include <stdio.h>
int main()
{
	int i,a,b,c;
	printf("请输入一个三位整数 ：");
	scanf("%d",&i);
	a = i / 100 % 10;
	b = i / 10 % 10;
	c = i % 10; 
	if(i < 0)
		printf("error!\n");
	else if(b != 0 && c == 0)
	    printf("%d\t%d\n",b,a);
	else if(b == 0 && c == 0)
	    printf("%d\n",a);
	else
	    return 0;
}

