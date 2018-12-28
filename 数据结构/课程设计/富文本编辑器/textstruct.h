#define M 200 /*预定最大的行号*/
//每个字的结构体
#define MAXSIZE 2000
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
typedef struct {
	char str[MAXSIZWE];
	int length;
}seqstring;

typedef struct {
	int a[MAXSIZE];
	int top;
}seqstack;
