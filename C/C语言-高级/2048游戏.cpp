#include<iostream>  
#include<stdlib.h>  
#include<time.h>  
using namespace std;  
#define NO 0  
int s = 1,i,j,n = 4,t = 0;  
int num[4][4];  
char fx;  
void randij(int *i1,int *j1)  
{  
	srand((int)time(0));  
	*i1 = rand()%4;  
	*j1 = rand()%4;  
	while(num[*i1][*j1]!=NO){  
	*i1 = rand()%4;  
	*j1 = rand()%4;  
}  
}  
void startGameinit()//初始化游戏  
{  
	for(int k = 1;k <= 2;k ++)  
	{
		randij(&i,&j);  
		num[i][j] = 2;  
	}  
}  
void up()  
{  
	int k,p;  
	for(k = 0;k < n;k ++)  
	{  
	    for(p = 0;p < n - 1;p ++)  
	    {  
	        if(num[p][k] == NO)
			{  
	        	for(int d = p;d <n - 1;d ++)  
	    		{  
	            	num[d][k] = num[d + 1][k];  
	            }  
	        	num[n - 1][k] = NO;  
	        }  
	        else if(num[p + 1][k] == NO)
			{  
	        	for(int d = p+1;d < n - 1;d ++)  
	            {  
	            	num[d][k] = num[d + 1][k];  	
	            }  
	        	num[n - 1][k] = NO;  
	        }  
	        else p++;  
	    }  
	}  
	for(k = 0;k < n;k ++)  
    {  
        for(p = 0;p < n - 1;p++)  
    	{  
	        if(num[p][k] == num[p + 1][k])
			{  
	        	num[p][k] += num[p + 1][k];  
	        for(int z = p + 1;z < n - 1;z ++)  
            	num[z][k]=num[z+1][k];  
         	num[n-1][k]=0;  
        	}  
    	}  
    }  
}  
void down()  
{  
    int k,p;  
	for(k = n - 1;k >= 0;k --)  
	{  
    	for(p=n-1;p>0;p--)  
    	{  
        	if(num[p][k]==NO)
			{  
        		for(int d=p;d>=0;d--)  
            	{  
            		num[d][k]=num[d-1][k];  
            	}  
        	num[0][k]=NO;  
        	}  
        	else if(num[p-1][k]==NO)
			{  
        		for(int d=p-1;d>=0;d--)  
            	{  
            		num[d][k]=num[d-1][k];  
            	}  
        		num[0][k]=NO;  
       		}	  
        	else p--;  
    	}  
	}  
	for(k =n-1;k>=0;k--)  
	{  
	    for(p=n-1;p>0;p--)  
	    {  
	        if(num[p][k]==num[p-1][k])
			{  
	        	num[p][k]+=num[p-1][k];  
	        	for(int z=p-1;z>0;z--)  
	            	num[z][k]=num[z-1][k];  
	        	num[0][k]=NO;  
	        }  
	    }  
	}  
}  
void left()  
{
	int p,k;  
	for(k=0;k<n;k++)  
	{	
		t=0;  
    	for(p=0;p<n-1;p++)  
    	{  
        	if(num[k][p]==NO)
			{  
        		for(int d=p;d<n-1;d++)  
            	{  
            		num[k][d]=num[k][d+1];  
            	}	  
        		num[k][n-1]=NO;  
        		p--;  
        		t++;  
        		if(t>4)break;  
        	}  
        else if(num[k][p+1]==NO)
		{  
	        for(int d=p+1;d<n-1;d++)  
	        {  
	            num[k][d]=num[k][d+1];  
	        }  
	        num[k][n-1]=NO;  
	        p--;  
	        t++;  
	        if(t>4)break;  
        }  
        else p++;  
    }  
}  
for(k=0;k<n;k++)  
{  
    for(p=0;p<n-1;p++)  
    {  
        if(num[k][p]==num[k][p+1])
		{  
            num[k][p]+=num[k][p+1];  
            for(int z=p+1;z<n-1;z++)  
            num[k][z]=num[k][z+1];  
            num[k][n-1]=NO;  
        }  
    }  
}  
}  
void right()  
{  
    int p,k;  
    for(k=n-1;k>=0;k--)  
	{
		t=0;  
	    for(p=n-1;p>0;p--)  
	    {  
	        if(num[k][p]==NO)
			{  
		        for(int d=p;d>=0;d--)  
		        {  
		            num[k][d]=num[k][d-1];  
		        }  
		        num[k][0]=NO;  
		        p++;  
		        t++;  
		        if(t>4)break;  
	        }  
	        else if(num[k][p-1]==NO)
			{  
		        for(int d=p-1;d>0;d--)  
		        {  
		        	num[k][d]=num[k][d-1];  
		        }  
		        num[k][0]=NO;  
		        p++;  
		        t++;  
		        if(t>4)break;  
	        }  
	        else p--;  
	    }  
    }  
	for(k=n-1;k>=0;k--)  
	{  
	    for(p=n-1;p>0;p--)  
	    {  
	        if(num[k][p]==num[k][p-1])
			{  
		        num[k][p]+=num[k][p-1];  
		        for(int z=p-1;z>0;z--)  
		        num[k][z]=num[k][z-1];  
		        num[k][0]=NO;  
	        }  
	    }  
	}  
}  
  
int checkGameOver()  
{  
    int k,p,count=0;  
    for(k=1;k<=n-2;k++)  
    {  
	    for(p=1;p<=n-2;p++)  
	    {  
	        if(num[k][p]!=num[k-1][p] && num[k][p]!=num[k][p-1] &&
				num[k][p]!=num[k+1][p] && num[k][p]!=num[k][p+1])
				count++;  
	    }  
    }  
      
      
    for(p=0;p<n-1;p++)  
    {  
	    if(num[0][p]!=num[0][p+1])count++;  
	    if(num[p][0]!=num[p+1][0])count++;  
	    if(num[n-1][p]!=num[n-1][p+1])count++;  
	    if(num[p][n-1]!=num[p+1][n-1])count++;  
    }  
    if(count==13)return 1;  
    else  return 0;  
}  
void clear()  
{  	
	system("CLS");  
}  
int getNum()  
{  
    int temp=0;  
	for(int k=0;k<n;k++)  
	{  
	    for(int p=0;p<n;p++)  
	    {  
	    	if(num[k][p]!=NO)temp++;  
	    }  
	}  
	return temp;  
}  
void showGame()  
{  
    int sum=0,k,d;  
      
    for(k=0;k<n;k++)  
    {  
        for(d=0;d<n;d++)  
        sum+=num[k][d];  
    }  
	cout<<"\t\t2048 C++版"<<endl<<endl<<"\t总分："<<sum<<"   "<<"数字个数："<<getNum()<<endl<<endl<<"\t请输入W A S D控制方向"<<endl;  
	for(k=0;k<40;k++)  
	cout<<"-";  
	cout<<endl;  
	for(k=0;k<n;k++)  
	{  
	    for(d=0;d<n;d++)  
	    {  
	    if(num[k][d]==NO)cout<<"\t ";  
	    else cout<<"\t"<<num[k][d];  
	    }  
	    cout<<endl<<endl<<endl;  
	}  
	for(k=0;k<40;k++)  
	cout<<"-";  
	cout<<endl;  
}  
int getMax()  
{  
	int max=0;  
	for(int k=0;k<n;k++)  
	{  
	    for(int p=0;p<n;p++)  
	    {  
	    	if(max<num[k][p])max=num[k][p];  
	    }  
	}  
	return max;  
}  
int main()  
{  
	for(i=0;i<n;i++)  
	{  
	    for(j=0;j<n;j++)  
	    {  
	  	  num[i][j]=NO;  
	    }  
	}  
	startGameinit();  
	showGame();  
	while(s)  
	{  
		cin>>fx;  
		switch(fx)  
	    {  
			case 'W':case 'w':up();clear();showGame();break;  
			case 'A':case 'a':left();clear();showGame();break;  
			case 'D':case 'd':right();clear();showGame();break;  
			case 'S':case 's':down();clear();showGame();break;  
   		}  
		if(getMax()==2048)
		{
			cout<<"\t\t\tYOU WIN!"<<endl;break;
		}  
		if(getNum()==n*n)
		{  
		    if(checkGameOver()){s=0;cout<<endl<<endl<<"\t\t\tGAME OVER!"<<endl;}  
		}  
		else
		{  
			randij(&i,&j);  
			num[i][j]=2;  
		}  
	}  
return 0;  
}  




