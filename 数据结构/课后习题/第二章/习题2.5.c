/*2.5已知一个顺序表中的各结点值是从小到大有序的，设计一个算法，插入一个值为x的结点，
 使顺序表中的结点仍然是从小到大有序。 */
 
void insertx(seqlist *L, datatype x)
{
    int j;
    if (L->length < N)
    {
        j = L->length - 1;
        while (j >= 0 && L->data[j] > x)
        {
            L->data[j + 1] = L->data[j];
            j--;
        }
        L->data[j + 1] = x;
        L->length++;
    }
}