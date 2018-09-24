/*
编写程序判断两个数是否为自然数对。要求程序运行时，从键盘输入两个自然数，
输出是否为自然数对。自然数对：若两个自然数分别为A和B，其中A>B，
如果A+B和A-B都是平方数，那么A、B就是自然数对。要求若A和B是自然数对，输出：1；
若A和B不是自然数对，输出：0；若A<B，则输出：error!。
*/ 
#include <stdio.h> 
#include <math.h> 
int main()
{
	int i,j,temp1,temp2;
	printf("输入两个自然数 ：");
	scanf("%d%d",&i,&j);
	temp1 = (int)sqrt(i + j);
	temp2 = (int)sqrt(i - j);
	if(i < j)
        printf("error!");
	else if(temp1 * temp1 == i + j && temp2 * temp2 == i - j)
	    printf("1");
	else
	    printf("0");
	return 0;
}

