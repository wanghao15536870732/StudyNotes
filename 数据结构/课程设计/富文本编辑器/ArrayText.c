#define _CRT_SECURE_NO_WARNINGS

#include "textstruct.h"
#include "stdio.h"

//将邻接表转换成数组
void TableToArray(TextCompiler *text, seqstring *str)
{
	int count = 0; //数组下标
	for (int i = 0; i < text->count; i++)
	{
		int mn = 0; //邻接表的每一行数组的下标
		while (text->column[i].FirstWord->data[mn] != '\0')
		{
			char letter = text->column[i].FirstWord->data[mn];
			str->str[count] = letter;
			count++; //导出数组的下标加1
			mn++;	//邻接表的数组下标加1
			str->length++;
		}
	}
	str->str[count] = '\0'; //数组最后一位赋值'\0'
}

//邻接表写入文件
void TableToFile(TextCompiler *text, char *filename)
{
	FILE *fp;
	int save = 0;			   //保存写入文件的返回值
	fp = fopen(filename, "w"); //以写入的方式打开文件
	if (fp)
	{
		for (int i = 0; i < text->count; i++)
		{
			save = fprintf(fp, "%s", text->column[i].FirstWord->data);
			if (save == -1) //如果返回-1,代表文件写入失败
			{
				printf("写入文件失败！！！\n");
				exit(0); //退出
			}
			fputc('\n', fp); //写入回车已达到按照用户的方式存储文本
		}
		fputc('\n', fp);
	}
	else
		printf("文件打开失败！！\n");
	fclose(fp); //关闭文件
}

/*
字符串的插入
@ Str 母串
@ Ttr 想要匹配的子串
*/

void strinsert(Word *Str, int i, Word *Ttr)
{
	int k;
	if (i < 1 || i > Str->length + 1 || Str->length + Ttr->length > MAXSIZWE - 1) //非法情况的处理
		printf("字符串过长，无法进行插入操作！！\n");
	else
	{
		for (k = Str->length - 1; k >= i - 1; k--) //Str中从第i个元素来世后移
			Str->data[Ttr->length + k] = Str->data[k];
		for (k = 0; k < Ttr->length; k++) //将写入S中的第i个字符开始的位置
			Str->data[i + k - 1] = Ttr->data[k];
		Str->length = Str->length + Ttr->length;
		Str->data[Str->length] = '\0'; //设置字符串S新的结束符
	}
}

/*
字符串的删除
@ Str 母串
@ i 想要删除的位置
@ len 想要删除的长度
*/

void strdelete(Word *Str, int i, int len)
{
	int k;
	if (i < 1 || i > Str->length || i + len - 1 > Str->length) //非法情况的处理
	{
		printf("无法进行删除操作！！\n");
		exit(0);
	}
	else
	{
		for (k = i + len - 1; k < Str->length; k++)
			Str->data[k - len] = Str->data[k]; //Str中下标为i + len -1开始的元素前移
		Str->length = Str->length - len;
		Str->data[Str->length] = '\0'; //置字符串Str新的结束符
	}
}

/*
字符串的连接
@ S1 第一个字符串
@ S2 第二个字符串
*/

Word *strconcat(Word *S1, Word *S2)
{
	int i;
	Word *r;
	if (S1->length + S2->length > MAXSIZWE - 1) //处理字符串空间不足的情况
	{
		printf("无法进行连接！\n");
		return NULL;
	}
	else
	{
		r = (Word *)malloc(sizeof(Word));
		for (i = 0; i < S1->length; i++)
			r->data[i] = S1->data[i]; //将S1复制到字符数组r的前端
		for (i = 0; i < S2->length; i++)
			r->data[S1->length + i] = S2->data[i]; //将S2复制到字符数组r的后端
		r->data[r->length] = '\0';
	}
	return r;
}

//用S2替换S1中的i位置的字符串
void strreplace(Word *S1, int i, Word *S2, int length)
{
	if (S2->length == length) //如果替换的字符串与元字符串长度相等
	{
		for (int j = 0; j < S2->length; j++)
			S1->data[i + j] = S2->data[j]; //直接赋值替换
	}
	else if (S2->length > length) //替换字符串比原字符串要长
	{

		for (int k = S1->length - 1; k >= i - 1; k--) //Str中从第i个元素开始后移
			S1->data[S2->length - length + k] = S1->data[k];
		for (int j = 0; j < S2->length; j++) //赋值替换
			S1->data[i + j] = S2->data[j];
		S1->length += S2->length - length; //最后处理一下长度
		S1->data[S1->length] = '\0';
	}
	else
	{ //替换字符串比元字符串要短
		for (int k = i + length - 1; k < S1->length; k++)
			S1->data[k - (length - S2->length)] = S1->data[k]; //Str中下标为i + len -1开始的元素前移
		for (int j = 0; j < S2->length; j++)
			S1->data[i + j] = S2->data[j];   //进行字符串的替换
		S1->length -= (length - S2->length); //最后处理一下长度
		S1->data[S1->length] = '\0';		 //最后赋值'\0'
	}
}

//获得每一行文本的next[]数组
void get_next(int *n, char *b, int next[])
{
	int i, j;
	i = 0;
	n[0] = j = -1; //指针j在最左边无法移动时让指针i后移
	while (i < strlen(b))
	{
		while (j != -1 && b[i] != b[j]) //当发生不匹配时,j的下一步移动位置next【j】=j
		{
			j = next[j];
		}
		next[++i] = ++j; //当匹配成功时b[0 ~ i]=b[j-i ~ j]即next[ ++i ] = ++ j。
	}
}

//kmp字符串匹配
int kmp(char *vis1, char *vis2, int next[], int length)
{
	int i, j;
	int ans = 0;
	i = j = 0;			  //主串和模式串的位置
	int n = strlen(vis1); //主串长度
	int m = strlen(vis2); //模式串长度
	while (i < n)
	{
		while (j != -1 && vis1[i] != vis2[j]) //主串与模式串发现不匹配
			j = next[j];					  //指针j进行行回溯
		if (j == m - 1)						  //如果匹配成功
		{
			printf("匹配成功的位置为：第%d行,第%d列\n", (i - m) / length + 1, (i - m) % length + 2);
			ans++;
			j = next[j]; //j指针返回到正确位置
		}
		i++; //i，j指针后移寻找下一模式串
		j++;
	}
	return ans; //返回匹配的次数
}
