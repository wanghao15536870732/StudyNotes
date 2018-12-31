#define _CRT_SECURE_NO_WARNINGS

#include "stdlib.h"
#include "string.h"
#include "ArrayText.c"

void init(seqstack *st)
{
	st->top = 0;
}
void push(seqstack *st, int x)
{
	if (st->top == MAXSIZE)
	{
		printf("\n栈是满的!");
		exit(1);
	}
	st->a[st->top] = x;
	st->top++;
}

int pop(seqstack *st)
{
	if (st->top == 0)
	{
		printf("\n栈是空的!");
		exit(1);
	}
	st->top--;
	return st->a[st->top];
}

void ReadFromFile(TextCompiler *text, char *filename)
{
	Word *word; //新的结点
	FILE *file;
	Word *p = NULL;
	file = fopen(filename, "r");
	int i = 0;
	int j = -1;
	if (file)
	{
		word = (Word *)malloc(sizeof(Word));
		word->length = 0; //开始赋值长度为0
		while ((word->data[i] = fgetc(file)) != EOF)
		{
			if (word->data[i] == '\n') //如果读取的这个
			{
				word->data[i] = '\0';
				j++;								 //行数加1再赋值
				text->column[j].FirstWord = word;	//将读取的这一行链接到表结点的后面
				word = (Word *)malloc(sizeof(Word)); //再次开辟一个新的word
				word->length = 0;					 //开始赋值长度为0
				i = 0;								 //再次从i=0开始循环
				text->count++;						 //整体行数加1
			}
			else
			{
				i++;
				word->length++;
			}
		}
		printf("文件数据读取成功!!!\n");
	}
	else
		printf("文件打开失败！\n");
	fclose(file); //关闭文件
}

//整体输出
void EasyOutput(TextCompiler *text)
{
	if (text == NULL)
	{
		printf("数据文本为空！请重试！\n");
		exit(0);
	}
	for (int i = 0; i < text->count; i++)
		printf("%s\n", text->column[i].FirstWord->data);
}

//统计整个文本中所有字母的个数
int TheLetterNumberOfText(TextCompiler *text)
{
	int count = 0; //计数器
	int j;		   //数组下标记录
	for (int i = 0; i < text->count; i++)
	{
		j = 0;
		while (text->column[i].FirstWord->data[j] != '\0')
		{
			j++;	 //数组下标移动
			count++; //添加数据
		}
	}
	return count;
}
//统计整个文本中所有单词的个数
int TheWordNumberOfText(TextCompiler *text)
{
	int count = 0; //计数器
	int m;		   //数组下标记录
	int n;
	for (int i = 0; i < text->count; i++)
	{
		m = 0;
		n = 1;
		while (text->column[i].FirstWord->data[n] != '\0')
		{
			if (text->column[i].FirstWord->data[m] != ' ' &&
				(text->column[i].FirstWord->data[n] == ' ' ||
				 text->column[i].FirstWord->data[n] == '.' ||
				 text->column[i].FirstWord->data[n] == '!' ||
				 text->column[i].FirstWord->data[n] == '?' ||
				 text->column[i].FirstWord->data[n] == '"'))
				count++;
			n++; //数组下标移动
			m++;
		}
	}
	return count;
}
//检索每一行的特殊字符
void RowNumber(TextCompiler *text)
{
	int row = 0;
	int input = 0;
	printf("\t1.统计指定行的空格的个数\n");
	printf("\t2.统计指定行的字母的个数\n");
	printf("\t3.统计指定行的标点符号的个数\n");
	printf("\t4.统计整篇文章的字符个数\n");
	printf("\t5.统计整篇文章的单词个数\n");
	printf("请输入功能编号：\n");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
	{
		printf("请输入行号：\n");
		scanf("%d", &row);
		int count = 0; //计数器
		int i = 0;	 //标记下表
		while (text->column[row - 1].FirstWord->data[i] != '\0')
		{
			if (text->column[row - 1].FirstWord->data[i] == ' ')
				count++;
			i++;
		}
		printf("第%d行文本中有%d个空格\n", row, count);
		break;
	}
	case 2:
	{
		printf("请输入行号：\n");
		scanf("%d", &row);
		int count = 0; //计数器
		int i = 0;	 //标记下表
		char letter;
		while ((letter = text->column[row - 1].FirstWord->data[i]) != '\0')
		{
			if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
				count++;
			i++;
		}
		printf("第%d行文本中有%d个字母\n", row, count);
		break;
	}
	case 3:
	{
		printf("请输入行号：\n");
		scanf("%d", &row);
		int count = 0; //计数器
		int i = 0;	 //标记下表
		while (text->column[row - 1].FirstWord->data[i] != '\0')
		{
			char data = text->column[row - 1].FirstWord->data[i];
			if (data == ',' || data == '.' || data == '?' || data == '"' || data == '\'')
				count++;
			i++;
		}
		printf("第%d行文本中有%d个标点符号\n", row, count);
		break;
	}
	case 4:
	{
		printf("整篇文本中有%d个字符\n", TheLetterNumberOfText(text));
		break;
	}
	case 5:
	{
		printf("整篇文本中有%d个单词\n", TheWordNumberOfText(text));
		break;
	}
	default:
		printf("输入有误！！！\n");
		exit(0);
		break;
	}
}

//kmp模式匹配
void kmpmatch(TextCompiler *text)
{
	int i = 0, plength = 0;
	char p[20] = {0};
	printf("请输入需要查找的单词:\n");
	scanf("%s", p);
	while (p[i])
	{
		plength++; //获取输入字符串的长度
		i++;	   //字符串下标向下移动
	}
	p[plength] = '\0'; //最后一位设置为'\0'
}

void chinesematch(TextCompiler *text, seqstack *st) //中文查找
{
	int i = 0, j, k, m = 0, succ, q, plength = 0;
	char p[20] = {0};
	printf("请输入需要查找的汉字:\n");
	scanf("%s", p);
	while (p[i])
	{
		plength++;
		i++;
	}
	p[plength] = '\0';
	for (k = 0; k < text->count; k++)
	{
		i = 0;
		q = text->column[k].FirstWord->length;
		while (i <= q - plength)
		{
			j = 0;
			succ = 1;
			while ((j <= plength - 1) && succ)
			{
				if (p[j] == text->column[k].FirstWord->data[i + j])
					j++;
				else
					succ = 0;
			}
			i++;
			if (succ)
			{
				printf("匹配成功的位置在第%d行第%d列\n", k + 1, i - 1);
				push(st, i - 1);
				push(st, k + 1);
				succ = 0;
			}
		}
	}
}
void englishmatch(TextCompiler *text, seqstack *st) //英文查找
{
	int i = 0, j, k, m = 0, succ, q, plength = 0;
	char p[20] = {0};
	printf("请输入需要查找的单词:\n");
	scanf("%s", p);
	while (p[i])
	{
		plength++;
		i++;
	}
	p[plength] = '\0';
	for (k = 0; k < text->count; k++)
	{
		i = 0;
		q = text->column[k].FirstWord->length;
		while (i <= q - plength)
		{
			j = 0;
			succ = 1;
			while ((j <= plength - 1) && succ)
			{
				if (p[j] == text->column[k].FirstWord->data[i + j])
					j++;
				else
					succ = 0;
			}
			if (text->column[k].FirstWord->data[i + j] == ' ' && text->column[k].FirstWord->data[i - 1] == ' ')
				i++;
			else
			{
				succ = 0;
				i++;
			}
			if (succ)
			{
				printf("匹配成功的位置在第%d行第%d列\n", k + 1, i - 1);
				push(st, i - 1); //写入栈，方便下一次调用
				push(st, k + 1);
				succ = 0;
			}
		}
	}
}

//朴素模式匹配
void nativematch(TextCompiler *text, seqstack *st)
{
	int input = 0;
	printf("请选择需要查找的语言类型:1.中文 2.英文\n");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
		chinesematch(text, st);
		break;
	case 2:
		englishmatch(text, st);
		break;
	default:
	{
		printf("输入有误！！\n");
		exit(0);
		break;
	}
	}
}

//将数组写入文件
void PutInFile(char *filename, seqstring *array)
{
	int row; //每一行所包含的列数
	printf("请输入一行所占的列数：\n");
	scanf("%d", &row);
	FILE *fp;
	int save = 0; //保存写入文件的返回值
	int count = 0;
	fp = fopen(filename, "w"); //以写入的方式打开文件
	if (fp)
	{
		while (array->str[count] != '\0')
		{
			save = fputc(array->str[count], fp);
			if (save == -1) //如果返回-1,代表文件写入失败
			{
				printf("写入文件失败！！！\n");
				exit(0); //退出
			}
			count++; //写入字符加1
			if (count % row == 0)
				fputc('\n', fp); //写入回车已达到按照用户的方式存储文本
		}
		fputc('\n', fp);
	}
	else
		printf("文件打开失败！！\n");
	fclose(fp);
}

void IntoFile(TextCompiler *text, char *filename)
{
	printf("删除后的字符串:\n");
	EasyOutput(text);
	printf("转换成数组后的文档：\n");
	seqstring strtr;
	strtr.length = 0;
	TableToArray(text, &strtr);
	printf("%s\n", strtr.str);
	PutInFile(filename, &strtr);
}

//横向删除单词
void StrDelete(TextCompiler *text, char *filename)
{
	seqstring str;
	str.length = 0;
	int i = 0, j, k, m = 0, succ = 0, q, plength = 0;
	char p[20] = {0};
	printf("请输入想要删除的单词:\n");
	scanf("%s", p);
	while (p[i])
	{
		plength++; //获取输入字符串的长度
		i++;	   //字符串下标向下移动
	}
	p[plength] = '\0';				  //最后一位设置为'\0'
	for (k = 0; k < text->count; k++) //循环遍历每一行
	{
		i = 0;
		q = text->column[k].FirstWord->length; //保存一下长度
		while (i <= q - plength)
		{
			j = 0;
			succ = 1;
			while ((j <= plength - 1) && succ) //没有匹配结束且标志位是1
			{
				if (p[j] == text->column[k].FirstWord->data[i + j])
					j++;
				else
					succ = 0;
			}
			i++;
			if (succ)
			{
				strdelete(text->column[k].FirstWord, i, plength); //删除该字符串
				succ = 0;										  //标志位重新设定为0
			}
		}
	}
	//TableToArray(text, &str);  //先将邻接表转换成一维数组
	IntoFile(text, filename); //转换成数组写入文件
}

//行字符串替换
void StrReplace(TextCompiler *text)
{
	Word word;
	seqstring str;
	str.length = 0;
	int i = 0, j, k, m = 0, succ = 0, q, plength = 0;
	char p[20] = {0};
	printf("请输入想要被替换的字符串:\n");
	scanf("%s", p);
	printf("请输入想要替换的字符串：\n");
	scanf("%s", word.data);
	while (p[i])
	{
		plength++; //获取输入字符串的长度
		i++;	   //字符串下标向下移动
	}
	p[plength] = '\0'; //最后一位设置为'\0'
	word.length = plength;
	for (k = 0; k < text->count; k++) //循环遍历每一行
	{
		i = 0;
		q = text->column[k].FirstWord->length; //保存一下长度
		while (i <= q - plength)
		{
			j = 0;
			succ = 1;
			while ((j <= plength - 1) && succ) //没有匹配结束且标志位是1
			{
				if (p[j] == text->column[k].FirstWord->data[i + j])
					j++;
				else
					succ = 0;
			}
			i++;
			if (succ)
			{
				strreplace(text->column[k].FirstWord, i - 1, &word); //替换该字符串
				succ = 0;											 //标志位重新设定为0
			}
		}
	}
	printf("替换后的字符串:\n");
	EasyOutput(text);
}

//查找、替换和删除
void SearchReplaceDelete(TextCompiler *text, seqstack *st, char *filename)
{
	if (text == NULL)
	{
		printf("数据文本为空！请检查文件路径是否有误！\n");
		exit(0);
	}
	int input = 0;
	printf("\t1.字符串查找\n");
	printf("\t2.字符串替换\n");
	printf("\t3.字符串插入\n");
	printf("\t4.字符串删除\n");
	printf("\t5.朴素查找\n");
	printf("请输入功能编号：\n");
	scanf("%d", &input);
	int i;
	int next[50];
	switch (input)
	{
	case 1:
	{
		seqstack st;
		init(&st);
		nativematch(text, &st);
		break;
	}
	case 2:
	{
		StrReplace(text);
		break;
	}
	case 3:
	{
		int input = 0;
		printf("请问想要行插入还是列插入？\n");
		printf("\t1.字符串的行插入\n");
		printf("\t2.字符串的列插入\n");
		printf("\t3.字符串的块插入\n");
		printf("请输入操作编号：\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		{
			Word word;
			word.length = 0;
			int row = 0, column = 0; //定义行跟列
			printf("请输出想要插入的位置：(行跟列)\n");
			printf("行号：");
			scanf("%d", &row);
			printf("列号：");
			scanf("%d", &column);
			printf("请输入想要插入的字符串：\n");
			scanf("%s", word.data);
			while (word.data[word.length])
				word.length++;
			strinsert(text->column[row - 1].FirstWord, column, &word);
			EasyOutput(text);
			break;
		}
		case 2:
		{ //列的插入
			int dlength = 0;
			int col = 0;
			char data[100] = {0};
			int row = 0, column = 0; //定义行跟列
			printf("请输出想要插入的位置：(行跟列)\n");
			printf("行号：");
			scanf("%d", &row);
			printf("列号：");
			scanf("%d", &column);
			printf("请输入想要插入的字符串：\n");
			scanf("%s", data);
			while (data[dlength]) //统计输入字符串的长度
				dlength++;
			for (int i = row - 1; i < row + dlength; i++) //循环遍历行数到行数加输入字符串的长度
			{
				Word *word = text->column[i].FirstWord;
				for (int j = word->length - 1; j >= column; j--) //循环到指定长度
					word->data[j + 1] = word->data[j];
				if (data[col] != '\0')
					word->data[column] = data[col++];
				word->length++;
				word->data[word->length] = '\0';
			}
			EasyOutput(text);
			break;
		}
		case 3:
		{ //块的插入
			int row = 0, column = 0;
			int width = 0, length = 0;
			Word word;
			word.length = 0;
			printf("请输入想要插入块的行号、列号、块的宽度、块的长度：\n");
			printf("行号：");
			scanf("%d", &row);
			printf("列号：");
			scanf("%d", &column);
			printf("长度：");
			scanf("%d", &width);
			printf("宽度：");
			scanf("%d", &length);
			if (row + length > text->count || column + width > text->column[0].FirstWord->length)
			{
				printf("块插入的位置有误，请重试！！\n");
				exit(0);
			}
			else
			{
				printf("请输入想要插入的字符串：\n");
				scanf("%s", word.data);
				while (word.data[word.length]) //统计字符串的长度
					word.length++;
				int count; //下标标记
				int j = 0;
				for (int i = row; i < row + length - 1; i++)
				{
					count = 0;								 //下标标记
					Word wordT;								 //用于插入的wordT
					Word *wordP = text->column[i].FirstWord; //定义word指向当前行数
					for (j = i * width; j < i * width + width; j++)
					{
						wordT.data[count++] = word.data[j];
						wordT.length = width; //长度赋值
					}
					strinsert(wordP, column, &wordT); //将分好组的
				}
				Word lastword;
				lastword.length = 0;
				while (word.data[j] != '\0')
					lastword.data[lastword.length++] = word.data[j++];					//处理最后一行
				strinsert(text->column[row + length - 1].FirstWord, column, &lastword); //插入
			}
			EasyOutput(text);
			break;
		}
		default:
			break;
		}
		break;
	}
	case 4:
	{
		int input = 0;
		printf("请问想要行删除还是列删除？\n");
		printf("\t1.行删除\n");
		printf("\t2.列删除\n");
		printf("\t3.块的删除\n");
		printf("请输入操作编号：\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		{ //字符串行删除
			StrDelete(text, filename);
			break;
		}
		case 2:
		{
			int column = 0;
			printf("请输入想要删除的列号：\n");
			scanf("%d", &column);
			for (int i = 0; i < text->count; i++)
				strdelete(text->column[i].FirstWord, column, 1);
			break;
		}
		case 3:
		{
			int row = 0, column = 0;
			int width = 0, length = 0;
			printf("请输入想要删除块的行号、列号、宽度、长度：\n");
			printf("行号：");
			scanf("%d", &row);
			printf("列号：");
			scanf("%d", &column);
			printf("长度：");
			scanf("%d", &width);
			printf("宽度：");
			scanf("%d", &length);
			if (row + length > text->count || column + width > text->column[0].FirstWord->length)
			{
				printf("块的面积过大,请重新输出！！\n");
				exit(0);
			}
			for (int i = row - 1; i < row + length; i++)
				strdelete(text->column[i].FirstWord, column, length);
			IntoFile(text, filename);
			break;
		}
		default:
		{
			printf("输入有误！！\n");
			exit(0);
			break;
		}
		}
		EasyOutput(text); //简单输出
		break;
	}
	case 5:
	{
		nativematch(text, st);
		break;
	}
	default:
		printf("输入有误！\n");
		exit(0);
		break;
	}
}

void strRemove(TextCompiler *text, char *filename)
{
	int input = 0;
	printf("\t1.字符串的行移动\n");
	printf("\t2.字符串的列移动\n");
	printf("\t3.字符串的块移动\n");
	printf("请输入操作编号：\n");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
	{
		int row1 = 0; //移动前的列位置
		int row2 = 0; //移动前的
		printf("请输入想要移动行的位置：\n");
		scanf("%d", &row1);
		printf("请输入想要移动到的位置：\n");
		scanf("%d", &row2);
		Word *word = text->column[row1 - 1].FirstWord; //保存一下
		text->column[row1 - 1].FirstWord = text->column[row2 - 1].FirstWord;
		text->column[row2 - 1].FirstWord = word;
		printf("行移动后的文本:\n");
		EasyOutput(text);			 //简单输出
		TableToFile(text, filename); //写入文件
		break;
	}
	case 2:
	{
		int column1 = 0; //移动前的列位置
		int column2 = 0; //移动前的
		printf("请输入想要移动列的位置：\n");
		scanf("%d", &column1);
		printf("请输入想要移动列的位置：\n");
		scanf("%d", &column2);
		for (int i = 0; i < text->count; i++)
		{
			char temp; //中间交换物
			temp = text->column[i].FirstWord->data[column1 - 1];
			text->column[i].FirstWord->data[column1 - 1] = text->column[i].FirstWord->data[column2 - 1];
			text->column[i].FirstWord->data[column2 - 1] = temp;
		}
		printf("列移动后的文本:\n");
		EasyOutput(text);			 //简单输出
		TableToFile(text, filename); //写入文件
		break;
	}
	case 3:
	{

		break;
	}
	default:
		break;
	}
}

void menu()
{
	puts("\n");
	printf("\t                        简易文本编辑器                 \n");
	printf("\t*\t                                                      *\n");
	printf("\t*\t 1.输入文本数据                                       *\n");
	printf("\t*\t 2.从文件读取数据                                     *\n");
	printf("\t*\t 3.整体输出文本                                       *\n");
	printf("\t*\t 4.统计文本中的字符个数                               *\n");
	printf("\t*\t 5.删除子串                                           *\n");
	printf("\t*\t 6.查找、替换、插入字符串                             *\n");
	printf("\t*\t 7.字符串的移动                                       *\n");
	printf("\t*\t 8.检索某个单词的行号和在该行出现的次数以及位置       *\n");
	printf("\t*\t 9.输出总行数                                         *\n");
	printf("\t*\t 10.退出                                              *\n");
}

//用户从界面输入文本
void InputFromScreen(char *filename) //abcdefghiklmnopqrst
{
	int row; //每一行所包含的列数
	printf("请输入一行所占的列数：\n");
	scanf("%d", &row);
	printf("请输入你想要录入的文本：\n");
	char ch; //读取的字符
	FILE *fp;
	int save = 0; //保存写入文件的返回值
	int count = 0;
	fp = fopen(filename, "w"); //以写入的方式打开文件
	if (fp)
	{
		getchar();
		ch = getchar();
		while (ch != '\n')
		{
			save = fputc(ch, fp);
			count++;		//写入字符加1
			if (save == -1) //如果返回-1,代表文件写入失败
			{
				printf("写入文件失败！！！\n");
				exit(0); //退出
			}
			ch = getchar();
			if (count % row == 0)
				fputc('\n', fp); //写入回车已达到按照用户的方式存储文本
		}
	}
	else
		printf("文件打开失败！！\n");
	fclose(fp); //关闭文件
}

int main()
{
	int input = 0;
	seqstack st;
	init(&st);
	menu();
	char filename[] = "D:\\Desktop\\Test.txt";
	char filename1[] = "D:\\Desktop\\Test2.txt";
	printf("请输出功能编号：\n");
	scanf("%d", &input);
	TextCompiler text; //定义的结构体
	text.count = 0;	//一开始的行数为0
	while (input >= 0 && input <= 10)
	{
		switch (input)
		{
		case 1:
		{
			//将从屏幕录入的数据写入文件
			InputFromScreen(filename1);
			break;
		}
		case 2:
		{
			//printf("请输入文件路径：\n");  //D:\\Desktop\\test.txt
			//scanf("%s", filename);
			ReadFromFile(&text, filename1);
			break;
		}
		case 3:
		{
			EasyOutput(&text);
			break;
		}
		case 4:
		{
			RowNumber(&text);
			break;
		}
		case 5:
		{
			StrDelete(&text, filename1);
			break;
		}
		case 6:
		{
			SearchReplaceDelete(&text, &st, filename1);
			break;
		}
		case 7:
		{
			strRemove(&text, filename1);
			break;
		}
		case 8:
		{
			nativematch(&text, &st);
			break;
		}
		case 9:
		{
			printf("总行数为:%d\n", text.count);
		}
		case 10:
		{
			exit(0);
			break;
		}
		default:
			printf("输入有误！！！\n");
			exit(0);
			break;
		}
		//menu();
		printf("请输出功能编号：\n");
		scanf("%d", &input);
	}
	system("pause");
	return 0;
}