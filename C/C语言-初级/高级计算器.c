/*
编程实现一个复杂算术运算的计算器，即：可实现形如"a op1 b op2 c"的混合算术运算，
其中a、b、c分别是操作数，op1、op2分别是运算符。设计要求：
（1）操作数类型是基本整型，运算符可以是加（+）、减（-）、取余（%）、求幂（^）,
优先级与结合性说明：取余和求幂优先相同，先取余、求幂，后加、减，左结合性；
（2）程序由多个函数构成，其中main函数用于实现算术表达式的输入，和运算结果的输出，
子函数用于实现算术表达式的计算，子函数可以是一个，也可以是多个，由用户自行设计；
（3）程序运行时，由键盘输入数据。
*/ 

#include"stdio.h"
int fun(int x, char op, int y)
{
	switch (op)
	{
	case '+':return x + y;
	case '-':return x - y;
	case '%':return x % y;
	case '^':
		{
				int re=1;
				for (int i = 1; i <= y; i++)
					re *= x;
				return re;
		}
	}
}
int computer(int a, char op1, int b, char op2, int c)
{
	int op1sort=1, op2sort=1;
	if ((op1 == '+' || op1 == '-') && (op2 == '%' || op2 == '^'))
		op2sort = 2;
	if (op1sort == op2sort)
		return fun(fun(a, op1, b), op2, c);
	else
		return fun(a,op1,fun(b,op2,c));
}
int main()
{
	int a, b, c;
	int result;
	char op1, op2;
	scanf("%d",&a);
	op1 = getchar();
	scanf("%d", &b);
	op2 = getchar();
	scanf("%d", &c);
	result = computer(a, op1, b, op2, c);
	printf("%d\n",result);
}


