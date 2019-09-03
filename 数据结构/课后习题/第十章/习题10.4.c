/*修改冒泡排序算法，使第一趟把排序序码最大的记录放到最末尾，第二趟把排序码
最小的记录在最前面，如此反复进行，达到排序的目的*/

#define MAXSIZE 100
typedef int keytype;
typedef struct{
    keytype key;
    int other;
}recordtype;
typedef struct 
{
    recordtype r[MAXSIZE + 1];
    int length;
}table;
/*冒泡排序*/
void bubblesort(table *L)
{
    int i, j, k, done;
    i = 1;
    j = L->length;
    done = 1;
    while (done)
    {
        done = 0;
        for (k = i; k <= j; k++)
            if (L->r[k + 1].key < L->r[k].key)
            {
                L->r[0] = L->r[k];
                L->r[k] = L->r[k + 1];
                L->r[k + 1] = L->r[0];
                done = 1;
            }
        j--;
        done = 0;
        for (k = j; k >= i; k--)
            if (L->r[k].key < L->r[k - 1].key)
            {
                L->r[0] = L->r[k];
                L->r[k] = L->r[k - 1];
                L->r[k - 1] = L->r[0];
                done = 1;
            }
        i++;
    }
}

int main()
{
    table L;             /*定义表L*/
    input(&L, "in.txt"); /*从文件in.txt中读入排序数据*/
    print(L);            /*输出原表*/
    bubblesort(&L);
    print(L); /*输出排序后的表*/
    return 0;
}