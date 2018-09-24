/*
编写程序输出图案。程序运行时，从键盘输入图案代号，输出指定图案（
共12种，图案代号与图案请参考如下示例说明。）。
要求：程序由13个函数构成，其中main()函数的功能是输入一个图案代号，
其它12个函数的功能分别是输出一种指定图案。图在这里就省略了，可以自己运行下看看 
*/ 

#include <stdio.h>
void pattern1()
{
	printf("#####\n");
	printf("## ##\n");
	printf("#   #\n");
	printf("## ##\n");
	printf("#####\n");
}
void pattern2()
{
	int i,j;
	printf("*********\n");
 
	for(i = 1;i < 10;i ++)
 
	{
		for(j = i;j < 10;j ++)
			printf("%d",j);
		printf("\n");
	}
	printf("*********\n");
}
void pattern3()
{
	printf("***********\n");
	printf("*1+'1'='2'*\n");
	printf("***********\n");
}
void pattern4()
{
	int i,a,b;
	printf("*123456789*123456789\n");
	for(i = 1;i <= 10;i ++)
	{
		for(a = 1;a < i;a ++)
			printf(" ");
		for(b = 1;b <= 21 - 2 * i;b ++)
			printf("@");
		printf("\n");
	}
	printf("*123456789*123456789\n");
}
void pattern5()
{
	int i;
	int num[1000];
	printf("*123456789*123456789*1234\n");
	num[0] = 0;
	num[1] = 1;
	for(i = 1;i <= 19;i ++)
		num[i + 1] = num[i] + num[i - 1];
	for(i = 0;i < 20;i ++)
	{
		printf("%5d",num[i]);
		if((i + 1) % 5 == 0)
			printf("\n"); 
	}
	printf("*123456789*123456789*1234\n"); 
}
void pattern6()
{
	printf("*****\n");
	printf("*   *\n");
	printf("*   *\n");
	printf("*   *\n");
	printf("*****\n");
}
void pattern7()
{
	int i,a,b;
	printf("*********\n");
	for(i = 1;i <= 9;i ++)
	{
		for(a = 1;a < i;a ++)
			printf(" ");
		for(b = i;b <= 9;b ++)
			printf("%d",b);
		printf("\n");
	}
	printf("*********\n");
}
void pattern8()
{
	printf("**********\n");
	printf("*\"Hello!\"*\n");
	printf("**********\n");
}
void pattern9()
{
	int i,a,b;
	printf("*123456789*123456789\n");
	for(i = 1;i <= 10;i ++)
	{
		for(a = 1;a <= 10 - i;a ++)
			printf(" ");
		for(b = 1;b <= 2 * i - 1; b ++)
			printf("@");
		printf("\n");
	}
	printf("*123456789*123456789\n");
}
void pattern10()
{
	int i,j;
	int a[100][100];
	
	for(i = 0;i <= 16;i ++)
	{
		a[i][0] = 1;
		a[i][i] = 1;
	}
	for(i = 1;i <= 16;i ++)
		for(j = 1;j < i; j ++)
			a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
	for(i = 0;i < 16;i ++)
	{
		for(j = 0;j <= i; j ++)
			printf("%5d",a[i][j]);
		printf("\n");
	}
	printf("*123456789*123456789*123456789*123456789*");
	printf("123456789*123456789*123456789*123456789\n");
} 
void pattern11()
{
	int i,j;
	printf("*123456789*123456789*123456789*123456789*");
	printf("123456789*123456789*123456789*123456789\n");
	for(i = 1;i <= 20;i ++)
	{
		for(j = i;j <= i * i;j += i)
			printf("%4d",j);
		printf("\n");
	}
	printf("*123456789*123456789*123456789*123456789*");
	printf("123456789*123456789*123456789*123456789\n");
}
void pattern12()
{
	int i,j;
	printf("*123456789*123456789*123456789*123456789*");
	printf("123456789*123456789*123456789*123456789\n");
	for(i = 1;i <= 20;i ++)
	{
		for(j = i;j <= 20 * i;j += i)
			printf("%4d",j);
		printf("\n");
	}
	printf("*123456789*123456789*123456789*123456789*");
	printf("123456789*123456789*123456789*123456789\n");
}
int main()
{
	int i;
	puts("输入你想要的图案代号(1~12)："); 
	scanf("%d",&i);
	puts("图案如下：\n");
	switch(i)
	{
	case 1:
		pattern1();
		break;
	case 2:
		pattern2();
		break;
	case 3:
		pattern3();
		break;
	case 4:
		pattern4();
		break;
	case 5:
		pattern5();
		break;
	case 6:
		pattern6();
		break;
	case 7:
		pattern7();
		break;
	case 8:
		pattern8();
		break;
	case 9:
		pattern9();
		break;
	case 10:
		pattern10();
		break;
	case 11:
		pattern11();
		break;
	case 12:
		pattern12();
		break;
	}
	return 0;	
}


