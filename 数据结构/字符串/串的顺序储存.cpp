#include "stdio.h"
#include "stdlib.h"
# define MAXSIZE 100

//顺序串的头文件
typedef struct{
	char str[MAXSIZE];
	int length;
}seqstring;

//顺序串的插入
void strinsert(seqstring *S,int i,seqstring T)
{
	int k;
	if(i < 1 || i > S->length + 1 || S->length + T.length > MAXSIZE -1)/*非法判断*/
		printf("字符串过长，无法插入！\n");
	else
	{
		//从第i个元素开始后移
		for(k = S->length; k >= i - 1;k --)
			S->str[T.length + k] = S->str[k];
		//将T写入S中的第i个字符串开始的位置
		for(k = 0;k < T.length; k ++)
			S->str[i + k - 1] = T.str[k];
		S->length = S->length + T.length;
		S->str[S->length] = '\0';

	}
}

//字符串的删除
void strdelete(seqstring *S,int i,int len)
{
	int k;
	if(i < 1 || i > S->length || i + len - 1 > S->length) /*非法情况的处理*/
		printf("无法插入字符串！");
	else
	{
		for(k = i + len - 1; k < S->length; k ++)
			//s中从下标为i + len - 1开始的元素前移
			S->str[k - len] = S->str[k];
		S->length = S->length - len;
		S->str[S->length] = '\0';
	}
}

//字符串的连接
seqstring *strconcat(seqstring S1,seqstring S2)
{
	int i;
	seqstring *r;
	//处理字符串数组空间不够使用的情况
	if(S1.length + S2.length > MAXSIZE - 1)
	{
		printf("无法插入字符串！\n");
		return (NULL);
	}
	else
	{
		r = (seqstring *) malloc(sizeof(seqstring));
		//将s1复制到r字符串的前端
		for(i = 0;i < S1.length;i ++)
			r->str[i] = S1.str[i];
		//将s2复制到r字符串的后端
		for(i = 0;i < S2.length;i ++)
			r->str[S1.length  + i] = S2.str[i];
		r->length = S1.length + S2.length;
		r->str[r->length] = '\0';
	}
	return (r);
}

//求给定字符串的子串
seqstring *substring(seqstring S,int i,int len)
{
	int k;
	seqstring *r;
	//处理非法情况
	if(i < 1 || i > S.length || i + len - 1 > S.length)
	{
		printf("错误！\n");
		return (NULL);
	}
	else
	{
		r = (seqstring *) malloc(sizeof(seqstring));
		for(k = 0;k < len;k ++)
			r->str[k] = S.str[i + k - 1];
		r->length =len;
		r->str[r->length] = '\0';
	}
	return (r);
}


int main()
{

	return 0;
}
