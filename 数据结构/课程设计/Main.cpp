#define M 200 /*预定最大的行号*/
//每个字的结构体
#define MAXSIZE 2000
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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

#define MAXSIZWE 2000
typedef struct
{
    char str[MAXSIZWE];
    int length;
} seqstring;

typedef struct
{
    int a[MAXSIZE];
    int top;
} seqstack;

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
            mn++;    //邻接表的数组下标加1
            str->length++;
        }
    }
    str->str[count] = '\0'; //数组最后一位赋值'\0'
}

//邻接表写入文件
void TableToFile(TextCompiler *text, char *filename)
{
    FILE *fp;
    int save = 0;              //保存写入文件的返回值
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
        S1->data[S1->length] = '\0';         //最后赋值'\0'
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
    i = j = 0;            //主串和模式串的位置
    int n = strlen(vis1); //主串长度
    int m = strlen(vis2); //模式串长度
    while (i < n)
    {
        while (j != -1 && vis1[i] != vis2[j]) //主串与模式串发现不匹配
            j = next[j];                      //指针j进行行回溯
        if (j == m - 1)                       //如果匹配成功
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
//从文本当中提取数据，利用邻接表存储
void ReadFromFile(TextCompiler *text, char *filename)
{
    text->count = 0; //每次行号赋0
    Word *word;      //新的结点
    FILE *file;
    Word *p = NULL;
    file = fopen(filename, "r"); //打开文件
    int i = 0;                   //列下标
    int j = -1;                  //行下标
    if (file)
    {
        word = (Word *)malloc(sizeof(Word)); //开辟一个新的空间
        word->length = 0;                    //开始赋值每一行长度为0
        while ((word->data[i] = fgetc(file)) != EOF)
        {
            if (word->data[i] == '\n') //如果读取的这个字符是'\n'
            {
                word->data[i] = '\0';                //这句话读取结束，补上'\0'
                j++;                                 //行数加一再赋值
                text->column[j].FirstWord = word;    //将读取的这一行链接到表结点的后面
                word = (Word *)malloc(sizeof(Word)); //再次开辟一个新的word
                word->length = 0;                    //开始赋值长度为0
                i = 0;                               //再次从i=0开始循环
                text->count++;                       //整体行数加1
            }
            else
            {
                i++;            //这一行还没有读取结束，下标向后继续读取
                word->length++; //每一行的字符个数加一
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

//统计整个文本中所有字符的个数
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
                 text->column[i].FirstWord->data[n] == '\"'))
                count++;
            n++; //数组下标移动
            m++;
        }
    }
    return count;
}
//kmp算法匹配字符串
void StringNumber(TextCompiler *text)
{
    int length = text->column[0].FirstWord->length; //保存第一行的列数
    char vis2[MAXSIZE] = {0}, vis1[1000] = {0};
    int next[1000] = {0};
    int count = 0;
    seqstring str;
    str.length = 0;
    TableToArray(text, &str);
    strcpy(vis1, str.str);
    count = 0;
    printf("请输入想要查询的子串：\n");
    getchar();
    gets_s(vis2);
    get_next(next, vis2, next);
    count = kmp(vis1, vis2, next, length);
    printf("\n字符串 %s 在文章中出现次数为：%d\n\n", vis2, count);
}

//检索每一行的特殊字符
void RowNumber(TextCompiler *text)
{
    int row = 0;
    int input = 0;
    printf("\t1.统计整篇文章的空格的个数\n");
    printf("\t2.统计整篇文章的字母的个数\n");
    printf("\t3.统计某一字符串在文章中出现的次数\n");
    printf("\t4.统计整篇文章的字符个数\n");
    printf("\t5.统计整篇文章的单词个数\n");
    printf("请输入功能编号：\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
    {
        int count = 0; //计数器
        int i = 0;     //标记下表
        for (int row = 0; row < text->count; row++)
        {
            i = 0;
            while (text->column[row].FirstWord->data[i] != '\0')
            {
                if (text->column[row].FirstWord->data[i] == ' ') //判断是否为空格
                    count++;                                     //计数器
                i++;                                             //下标加1
            }
        }
        printf("整篇文本中有%d个空格\n", count);
        break;
    }
    case 2:
    {
        int count = 0; //计数器
        int i = 0;     //标记下表
        char letter;
        for (int row = 0; row < text->count; row++)
        {
            i = 0;
            while ((letter = text->column[row].FirstWord->data[i]) != '\0')
            {
                if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) //判断该字符是否在这个范围之内
                    count++;                                                              //计数器
                i++;                                                                      //下标向后走，继续遍历
            }
        }
        printf("整篇文本中有%d个字母\n", count);
        break;
    }
    case 3:
    {
        StringNumber(text);
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
        i++;       //字符串下标向下移动
    }
    p[plength] = '\0'; //最后一位设置为'\0'
}

void chinesematch(TextCompiler *text, seqstack *st) //中文查找
{
    int i = 0, j, k, m = 0, succ, q, plength = 0;
    char p[20] = {0};
    printf("请输入需要查找的汉字:\n");
    scanf("%s", p);
    while (p[i]) //统计
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
    if (st->top == 0)
        printf("匹配失败！！\n");
}
void englishmatch(TextCompiler *text, seqstack *st) //英文查找
{
    int i = 0, j, k, m = 0, succ, q, plength = 0;
    char p[20] = {0};
    printf("请输入需要查找的单词:\n");
    //scanf("%s", p);
    getchar();
    gets_s(p);
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
            if (text->column[k].FirstWord->data[i + j] == ' ' &&
                text->column[k].FirstWord->data[i - 1] == ' ') //判断字符串两边是否为' '
                i++;
            else if (text->column[k].FirstWord->data[i + j] == ' ' &&
                     k == 0) //判断整篇文章的第一个单词
                i++;
            else if (text->column[k].FirstWord->data[i + j] == ' ' &&
                     text->column[k - 1].FirstWord->data[m] == '\0') //判断每行的第一个单词是否为
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
    if (st->top == 0)
        printf("匹配失败！！\n");
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
void PutInFile(char *filename, seqstring *array, int roww)
{
    int row; //每一行所包含的列数
    row = roww;
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

void IntoFile(TextCompiler *text, char *filename, int length)
{
    seqstring strtr;
    strtr.length = 0;
    TableToArray(text, &strtr);
    PutInFile(filename, &strtr, length);
}

//删除指定子串
void StrDelete(TextCompiler *text, char *filename)
{
    if (text->count == 0)
        printf("文本数据为空！！\n");
    else
    {
        int length = text->column[0].FirstWord->length; //先保存第一行的长度
        seqstring str;
        str.length = 0;
        int i = 0, j, k, m = 0, succ = 0, q, plength = 0;
        char p[20] = {0};
        printf("请输入想要删除的子字符串:\n");
        getchar();
        gets_s(p);
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
                i++;
                if (succ)
                {
                    strdelete(text->column[k].FirstWord, i, plength); //删除该字符串
                    succ = 0;                                         //标志位重新设定为0
                }
            }
        }
        IntoFile(text, filename, length); //转换成数组写入文件
        ReadFromFile(text, filename);
        printf("删除后的字符串:\n");
        EasyOutput(text);
    }
}

void strdelete2(TextCompiler *text, seqstack *st, char *filename)
{
    int length = text->column[0].FirstWord->length;
    char route[MAXSIZE] = {0};
    int k, h = 0, l = 0, r = 0, z, d, i, q = 0, c = 0;
    printf("请输入要查找并删除的单词：\n");
    nativematch(text, st);
    printf("请输入要删除的单词所在的位置：\n");
    printf("行号：");
    scanf("%d", &h);
    printf("列号：");
    scanf("%d", &l);
    int count = 0; //数组下标
    for (i = 0; i < h - 1; i++)
    {
        int k = 0; //邻接表的每一行数组的下标
        while (text->column[i].FirstWord->data[k] != '\0')
        {
            char letter = text->column[i].FirstWord->data[k];
            route[count] = letter;
            count++; //导出数组的下标加1
            k++;     //邻接表的数组下标加1
        }
        r = r + k;
        //printf("第%d行有%d个元素:",i+1,r);
    }
    z = r + l; //z为删除的起始位置
    count = 0;
    for (i = 0; i < text->count; i++)
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
    if (z < 1)
        printf("cannot delete\n");
    else
    {
        for (d = r + q + l; d < c; d++)
            route[d - q] = route[d]; //q为删除的单词的长度
        count = count - q;
        route[count] = '\0';
    }
    printf("删除后的字符串为：\n");
    for (int j = 0; j < count / length; j++)
    {
        for (int i = j * length; i < j * length + length; i++)
            printf("%c", route[i]);
        printf("\n");
    }
}

//行字符串替换
void StrReplace(TextCompiler *text, char *filename)
{
    int length = text->column[0].FirstWord->length;
    Word word;
    word.length = 0;
    seqstring str;
    str.length = 0;
    int i = 0, j, k, m = 0, succ = 0, q, plength = 0;
    char p[20] = {0};
    printf("请输入想要被替换的字符串:\n");
    getchar();
    gets_s(p);
    printf("请输入想要替换的字符串：\n");
    //getchar();
    gets_s(word.data);
    //scanf("%s", word.data);
    while (p[i])
    {
        plength++; //获取输入字符串的长度
        i++;       //字符串下标向下移动
    }
    p[plength] = '\0'; //最后一位设置为'\0'
    while (word.data[word.length])
        word.length++;
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
                strreplace(text->column[k].FirstWord, i - 1, &word, plength); //替换该字符串
                succ = 0;                                                     //标志位重新设定为0
            }
        }
    }
    printf("替换后的文本：\n");
    IntoFile(text, filename, length);
    ReadFromFile(text, filename);
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
    printf("请输入功能编号：\n");
    scanf("%d", &input);
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
        StrReplace(text, filename);
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
            int length = text->column[0].FirstWord->length;
            printf("请输出想要插入的位置：(行跟列)\n");
            printf("行号：");
            scanf("%d", &row);
            printf("列号：");
            scanf("%d", &column);
            printf("请输入想要插入的字符串：\n");
            getchar();
            gets_s(word.data);
            while (word.data[word.length])
                word.length++;
            strinsert(text->column[row - 1].FirstWord, column, &word);
            IntoFile(text, filename, length);
            ReadFromFile(text, filename);
            printf("\n\n在第%d行%d列 横向 添加%s的字符串后的文本为：\n\n", row, column, word.data);
            EasyOutput(text);
            break;
        }
        case 2:
        { //列的插入
            int dlength = 0;
            int col = 0;
            char data[100] = {0};
            int length = text->column[0].FirstWord->length;
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
            printf("\n\n在第%d行%d列 列向 添加%s的字符串后的文本为：\n\n", row, column, data);
            EasyOutput(text);
            IntoFile(text, filename, length);
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
                    count = 0;                               //下标标记
                    Word wordT;                              //用于插入的wordT
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
                    lastword.data[lastword.length++] = word.data[j++];                  //处理最后一行
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
        { //字符串列删除
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
            int lengthh = text->column[0].FirstWord->length; //保存文本第一行的长度
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
            IntoFile(text, filename, length);
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
    default:
        printf("输入有误！\n");
        exit(0);
        break;
    }
}

void strRemove(TextCompiler *text, char *filename)
{
    if (text->count == 0)
        printf("文档为空，请重试！\n");
    else
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
        {                 //字符串的行移动
            int row1 = 0; //移动前的列位置
            int row2 = 0; //移动前的
            printf("请输入想要移动行的位置：\n");
            scanf("%d", &row1);
            printf("请输入想要移动到的位置：\n");
            scanf("%d", &row2);
            Word *word = text->column[row1 - 1].FirstWord; //保存最后想要交换的那一行
            for (int i = row1; i < row2; i++)
                text->column[i - 1].FirstWord = text->column[i].FirstWord;
            text->column[row2 - 1].FirstWord = word;
            printf("行移动后的文本:\n");
            EasyOutput(text);            //简单输出
            TableToFile(text, filename); //写入文件
            break;
        }
        case 2:
        {                    //字符串的列移动
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
            EasyOutput(text);            //简单输出
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
}

void menu()
{
    puts("\n");
    printf("\t                        简易文本编辑器                    \n");
    printf("\t*\t                                                      *\n");
    printf("\t*\t 1.输入文本数据                                       *\n");
    printf("\t*\t 2.从文件读取数据                                     *\n");
    printf("\t*\t 3.整体输出文本                                       *\n");
    printf("\t*\t 4.统计文章中英文字母、空格、总字数                   *\n");
    printf("\t*\t 5.删除某一子串                                       *\n");
    printf("\t*\t 6.查找、替换、插入字符串                             *\n");
    printf("\t*\t 7.字符串的移动                                       *\n");
    printf("\t*\t 8.检索某个单词的行号和在该行出现的次数以及位置       *\n");
    printf("\t*\t 9.输出总行数                                         *\n");
    printf("\t*\t 10.退出                                              *\n");
}

//用户从界面输入文本写入到文件
void InputFromScreen(char *filename)
{
    int column; //每一行所包含的列数
    printf("请输入一行所占的列数：\n");
    scanf("%d", &column);
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
            count++;        //写入字符加1
            if (save == -1) //如果返回-1,代表文件写入失败
            {
                printf("写入文件失败！！！\n");
                exit(0); //退出
            }
            ch = getchar(); //继续向后读取数据
            if (count % column == 0)
                fputc('\n', fp); //写入回车已达到按照用户的方式存储文本
        }
        printf("数据录入成功！！\n");
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
    //char filename[] = "D:\\Desktop\\Test.txt";
    char filename1[] = "D:\\Desktop\\Test2.txt";
    printf("请输出功能编号：\n");
    scanf("%d", &input);
    TextCompiler text; //定义一个text
    text.count = 0;    //一开始的行数为0
    while (input >= 1 && input <= 10)
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
            printf("整个文本为：\n");
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
            //strdelete2(&text, &st, filename1);
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
        {                        //输出整个文本的行数
            if (text.count == 0) //行数为0
            {
                printf("读取文本为空！请重试！\n");
                exit(0); //退出
            }
            else
                printf("总行数为:%d\n", text.count);
            break;
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