/*
三天打鱼两天晒网
*/ 
#include<stdio.h>
int leapYear(int year)
{
     if((year%4==0&&year%100!=0)||(year%400==0))
     {
         return 1 ;
     }
     else
     {
         return 0 ;
     }
}
int theDayOfMonth(int month,int isLeap)
{
    if((month>=1) && (month <=7) && (month % 2 == 1))
    {
        return 31 ;
    }
    else if((month>7) && (month <=12) && (month % 2 == 0))
    {
        return 31 ;
    }
    else if((month == 2) && isLeap)
    {
        return 29 ;
    }
    else if((month == 2) && !isLeap)
    {
        return 28 ;
    }
    else
    {
        return 30;
    }

}
int main()
{
    int theSumOfDay = 0 ;
    int month , year , remainder;

    for( year = 1990 ; year < 2017 ; year ++ )
    {
        if(leapYear(year))
        {
            theSumOfDay = theSumOfDay + 366 ;
        }
        else
        {
            theSumOfDay = theSumOfDay + 365 ;
        }
    }
    /*
    for(i = 1 ; i <= 12 ; i ++)
    {
        printf("%d,%d\n",theDayOfMonth(i,1),theDayOfMonth(i,0));
    }
    */
    for( month = 1 ; month < 10 ; month ++)
    {
        theSumOfDay = theSumOfDay + theDayOfMonth(month,leapYear(2017)) ;
    }
    theSumOfDay = theSumOfDay + 15 ;
    remainder = theSumOfDay % 5 ;
    if( remainder <= 3 )
    {
        printf("打渔");
    }
    else
    {
        printf("晒网");
    }
    return 0 ;
}


