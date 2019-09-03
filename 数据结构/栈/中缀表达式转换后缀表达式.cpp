#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int is_operation(char op);
int priority(char op);
void postfix(char e[], char f[]);

int main()
{

	char a[20] = "";
	char b[20] = { 0 };
	printf("请输入以\"#\"结尾的中缀表达式：\n");
	scanf("%s",a);
	postfix(a, b);
	printf("对应的后缀表达式为：\n");
	for (int i = 0; i < 10; i++)
		printf("%c", b[i]);
	printf("\n");
	system("pause");
	return 0;
}

/****************************************/
/****** 判断一个字符串是否为运算符 ******/
/****************************************/
int is_operation(char op)
{
	switch (op)
	{
	case '+':
	case '-':
	case '*':
	case '/': return 1;
	default:return 0;
	}
}

/****************************************/
/*********** 求运算符的优先级 ***********/
/****************************************/
int priority(char op)
{
	switch (op)
	{
	case '#': return -1;
	case '(': return 0;
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	default: return -1;
	}
}


/***************************************************/
/* 将一个中缀表达式 e 转换成与它等价的后缀表达式 f */
/***************************************************/

void postfix(char e[], char f[])
{
	int i = 0, j = 0;
	char opst[100] = { 0 };
	int top, t;
	top = 0;
	opst[top] = ' ';
	top++;
	while (e[i] != '#')
	{
		if ((e[i] >= '0' && e[i] <= '9') || e[i] == '.')
			f[j++] = e[i];  // 遇到数字或者小鼠点直接写入后缀表达式
		else if (e[i] == '(')  // 遇到左括号进入操作符栈
		{
			opst[top] = e[i];
			top++;
		}
		else if (e[i] == ')')
			//遇到右括号将其对应的左括号后的操作符全部写入后缀表达式 
		{
			t = top - 1;
			while (opst[t] != '(')
			{
				f[j++] = opst[--top];
				t = top - 1;
			}
			top--; // '( ' 出栈
		}
		else if (is_operation(e[i])) // '+ 、-、*、/ '
		{
			f[j++] = ' '; // 用空格分开两个操作符
			while (priority(opst[top - 1]) >= priority(e[i]))
				f[j++] = opst[--top];
			opst[top] = e[i];
			top++;// 当前元素入栈
		}
		i++;// 处理下一个元素	
	}
	while (top)
		f[j++] = opst[--top];
}