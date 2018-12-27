#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define M 20 /*预定最大的行号*/
//每个字的结构体
typedef struct node
{
    char data[1000]; //一行字的数据域
    int length;      // 一行字的数据域
} Word;

typedef struct vnode
{
    int row;         //储存行号
    Word *FirstWord; //邻接表表头指针,指向每一行的第一个字
} Vertexnode;

typedef struct
{                         //邻接表类型
    Vertexnode column[M]; //存放每一行头节点的顺序表
    int count;            //记录总行数
} TextCompiler;           //整个文本编译器结构体



//邻接表转换成数组
void TableToArray(TextCompiler *text, char route[])
{
    int count = 0; //数组下标
    for (int i = 0; i < text->count; i++)
    {
        int mn = 0; //邻接表的每一行数组的下标
        while (text->column[i].FirstWord->data[mn] != '\0')
        {
            char letter = text->column[i].FirstWord->data[mn];
            route[count] = letter;
            count++; //导出数组的下标加1
            mn++;    //邻接表的数组下标加1
        }
    }
    route[count] = '\0'; //数组最后一位赋值'\0'
}

//数组Z转换成邻接表
void ArrayToTable(char route, TextCompiler *text)
{

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
                j++;                                 //行数加1再赋值
                text->column[j].FirstWord = word;    //将读取的这一行链接到表结点的后面
                word = (Word *)malloc(sizeof(Word)); //再次开辟一个新的word
                word->length = 0;                    //开始赋值长度为0
                i = 0;                               //再次从i=0开始循环
                text->count++;                       //整体行数加1
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
}

//整体输出
void EsayOutput(TextCompiler *text)
{
    for (int i = 0; i < text->count; i++)
        printf("%s\n", text->column[i].FirstWord->data);
}

//统计整个文本中所有字母的个数
int TheLetterNumberOfText(TextCompiler *text)
{
    int count = 0; //计数器
    int j;         //数组下标记录
    for (int i = 0; i < text->count; i++)
    {
        j = 0;
        while (text->column[i].FirstWord->data[j] != '\0')
        {
            j++;     //数组下标移动
            count++; //添加数据
        }
    }
    return count;
}
//统计整个文本中所有单词的个数
int TheWordNumberOfText(TextCompiler *text)
{
    int count = 0; //计数器
    int m;         //数组下标记录
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
        int i = 0;     //标记下表
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
        int i = 0;     //标记下表
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
        int i = 0;     //标记下表
        while (text->column[row - 1].FirstWord->data[i] != '\0')
        {
            char data = text->column[row - 1].FirstWord->data[i];
            if (data == ',' || data == '.' || data == '?' || data == '"' || data == '\'')
                count++;
            i++;
        }
        printf("第%d行文本中有%d个标点符号\n", row, count);
        break;
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

//获得每一行文本的next[]数组
void getnext(Word *word, int next[])
{
    int index, jndex;                 //两个下表，用于前后比较
    next[0] = -1;                     //第一个是-1
    index = 0, jndex = -1;            //先赋值
    while (word->data[index] != '\0') //还没有读取到每行的最后一个数据
    {
        if (jndex == -1 || word->data[index] == word->data[jndex])
        {
            ++index; //向后比较
            ++jndex;
            next[index] = jndex;
        }
        else
            jndex = next[jndex]; //next数组再次嵌套查找
    }
    /*
	index = 0;
	while (word->data[index] != '\0')
	{
		printf("%d ", next[index]);
		index++;
	}
	*/
    printf("\n");
}

//kmp字符串匹配
int Kmp(Word *wordT, Word *wordP, int next[])
{
    int index = 0;
    int jndex = 0;
    while (index < wordT->length && jndex < wordP->length)
    {
        if (jndex == -1 || wordT->data[index] == wordP->data[jndex]) //如果在该位置相等
        {
            index++; //两个下标一起向后走
            jndex++;
        }
        else
            jndex = next[jndex]; //否则匹配串相对于模式串向后
    }
    if (jndex == wordP->length)
        return index - wordP->length;
    else
        return -1;
}

//朴素模式匹配
void nativematch(TextCompiler *text)
{
    int i = 0, j, k, m = 0, succ = 0, q, plength = 0;
    char p[20] = {0};
    printf("请输入需要查找的单词:\n");
    scanf("%s", p);
    while (p[i])
    {
        plength++; //获取输入字符串的长度
        i++;       //字符串下标向下移动
    }
    p[plength] = '\0';                //最后一位设置为'\0'
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
            if (text->column[k].FirstWord->data[i + j] == ' ' && text->column[k].FirstWord->data[i - 1] == ' ') //添加单词模式匹配
                i++;
            else
            {
                succ = 0; //标记为设置为0
                i++;
            }
            if (succ)
            {
                printf("匹配成功的位置在第%d行第%d列\n", k + 1, i - 1); //输出匹配成功的行列
                succ = 0;                                               //标志位重新设定为0
            }
        }
    }
}

//查找、替换和删除
void SearchReplaceDelete(TextCompiler *text)
{
    int input = 0;
    printf("\t1.查找\n");
    printf("\t2.替换\n");
    printf("\t3.删除\n");
    printf("\t4.朴素查找\n");
    printf("请输入功能编号：\n");
    scanf("%d", &input);
    int i;
    int next[50];
    switch (input)
    {
    case 1:
    {
        int temp = 0; //储存查询成功的列下标
        Word rd;
        printf("请输入想要查询的子串：\n");
        scanf("%s", rd.data);
        int j = 0;

        for (i = 0; i < text->count; i++)
        {
            //获取每一行字符的next值
            getnext(text->column[i].FirstWord, next);
            if (temp = Kmp(text->column[i].FirstWord, &rd, next) != -1)
            {
                printf("匹配成功！！\n");
                printf("匹配位置为文本第%d行第%d列：\n", i + 1, temp);
                break;
            }
        }
        if (i == text->count)
            printf("匹配失败！！\n");
        break;
    }
    case 2:
    {

        break;
    }
    case 3:
    {

        break;
    }
    case 4:
    {
        nativematch(text);
        break;
    }
    default:
        printf("输入有误！\n");
        exit(0);
        break;
    }
}

void menu()
{
    printf("\t*******简易文本编辑器*******\n");
    printf("\t\t1.输入文本数据\n");
    printf("\t\t2.从文件读取数据\n");
    printf("\t\t3.整体输出文本\n");
    printf("\t\t4.统计文本中的字符个数\n");
    printf("\t\t5.删除子串\n");
    printf("\t\t6.查找、替换、插入字符串\n");
    printf("\t\t7.检索某个单词的行号和在该行出现的次数以及位置\n");
    printf("\t\t8.输出总行数\n");
    printf("\t\t9.退出\n");
}

//用户从界面输入文本
void InputFromScreen()
{
    int row; //每一行所包含的列数
    char input[] = "";
    printf("请输入一行所占的列数：\n");
    scanf("%d", &row);
    printf("请输入你想要录入的文本：\n");
    scanf("%s", &input);
    for (int i = 0; i < row; i++)
    {
        while (fputc())
    }
}

int main()
{
    int input = 0;
    menu();
    char filename[] = "D:\\Desktop\\test.txt";
    printf("请输出功能编号：\n");
    scanf("%d", &input);
    TextCompiler text; //定义的结构体
    text.count = 0;    //一开始的行数为0
    while (input > 0 && input < 11)
    {
        switch (input)
        {
        case 1:
        {

            break;
        }
        case 2:
        {
            //printf("请输入文件路径：\n");  //D:\\Desktop\\test.txt
            //scanf("%s", filename);
            ReadFromFile(&text, filename);
            break;
        }
        case 3:
        {
            EsayOutput(&text);
            break;
        }
        case 4:
        {
            RowNumber(&text);
            break;
        }
        case 5:
        {

            break;
        }
        case 6:
        {
            SearchReplaceDelete(&text);
            break;
        }
        case 7:
        {
            nativematch(&text);
            break;
        }
        case 8:
        {
            printf("总行数为:%d\n", text.count);
            break;
        }
        case 9:
        {
            exit(0);
            break;
        }
        case 10:
        {
            char letter[1000] = "";
            TableToArray(&text, letter);
            printf("%s\n", letter);
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