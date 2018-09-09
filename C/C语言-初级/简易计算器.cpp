/*
编程程序实现一个复杂算术运算的计算器，即：可实现形如"a op1 b op2 c"的混合算术运算，
其中a、b、c分别是操作数，op1、op2分别是运算符。设计要求：

（1）操作数类型是浮点型，运算符可以是加（+）、减（-）、乘（*）、除（/）、,
优先级与结合性说明：先乘除后加减，左结合性；

（2）程序由多个函数构成，其中main函数用于实现算术表达式的输入，
和运算结果的输出，子函数用于实现算术表达式的计算，
子函数可以是一个，也可以是多个，由用户自行设计；

（3）运算结果保留两位小数；

（4）程序运行时，由键盘输入数据。

示例1： 
输入数据为：1+2+3<回车>
输出结果：6

示例1： 
输入数据为：1+2/3<回车>
输出结果：1.67


*/ 

#include<stdio.h>
double fun(double i,double j,char str1);
int main()
{
	double a,b,c;
	char s1,s2;
	double e = 0;
	scanf("%lf%c%lf%c%lf",&a,&s1,&b,&s2,&c);
	if(s2 == '*' || s2 == '/')
		e = fun(a,fun(b,c,s2),s1); 
	else 
		e = fun(fun(a,b,s1),c,s2);
	printf("%.2lf",e);
	return 0;
} 
double fun(double i,double j,char str)
{
	double n = 0;
	int t = (int)str;
	switch(t)
	{
	case 43:
		n = i + j;break;
	case 45:
		n = i - j;break;
	case 42:
		n = i * j;break;
	case 47:
		n = i / j;break;
	}
	return n;
}

