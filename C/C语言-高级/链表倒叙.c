#include<stdio.h>
#include<stdlib.h> 
typedef struct listTest
{
    int num ;
    struct listTest *next ;
}mList;

mList * init()
{
    int i ;
    mList *head , *p , *temp;
    temp = (mList *)malloc(sizeof(mList));
    temp->num = 0 ;
    head = temp ;
    for(i = 1 ; i < 5 ; i++)
    {
        p = (mList *)malloc(sizeof(mList));
        p->num = i ;
        temp->next = p ;
        temp = p ;
    }
    temp->next = NULL ;
    return head ;
}

int showListMember(mList *head , int num)
{
    do
    {
        printf("%d\t",head->num);
        num = num + 1 ;
    }while(head = head->next);
    return num ;
}

void resersal(mList *head,int numOfList)
{
    mList *next , *prev = NULL ;
    int i ;
    for(i = 0 ; i < numOfList  ; i ++)
    {

      //printf("test:%d\t",head->num);
        next = head->next;
        //printf("test in:%d\t",head->num);
        head->next = prev;
        prev = head ;
        if(next == NULL)
        {

        }
        else
        {
             head = next ;
        }

    }
    printf("\n");
    do
    {
        printf("%d\t",head->num);

    }while(head = head->next);
}

int main()
{
    mList *head ;
    head = init();
    int numOfList = 0 , i ;
    numOfList = showListMember(head ,numOfList);
    resersal(head,numOfList);
    return 0 ;
}

