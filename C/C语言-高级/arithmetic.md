# 一个输入输出的实践

## 一个输入输出的实践一

## 问题描述

你的任务是计算A + B。
太容易了？！
你一定发现了一些问题有相同的标题，这一次，是的，所有这些问题都为同一目的而设计的。
 
### 输入

将包括由空格分隔的一对整数a和b系列，一对整数，每行输入。  

### 产量

对于每个对输入整数a和b你应该输出a和b在同一行，并在输入的每一行与行输出的总和。

### 样例输入

```c
1 5
10 20
```

输出范例

```c
6
30
```

```c
#include<iostream>  
using namespace std;  
  
int main()  
{  
  int a,b;  
  while(cin>>a>>b)  
  {  
    cout << a + b << endl;  
  }  
  return 0;  
}  
```

## 一个输入输出的实践二

### 问题描述

你的任务是计算A + B

### 输入
输入包含一个整数N在第一线，然后按照N行。由一对整数a和b，由空格分隔的，一对整数，每行每行。

### 产量
对于每个对输入整数a和b你应该输出a和b在同一行，并在输入的每一行与行输出的总和。  

### 样例输入
2
1 5
10 20 
### 输出范例

6
30

```c++
#include<iostream>  
using namespace std;  
int main()  
{  
    int n;  
    double a,b;  
    cin>>n;  
    while(n--)  
    {  
        cin>>a>>b;  
        cout<<a+b<<endl;  
    }  
    return 0;  
}  

```

## 一个输入输出的实践三

时限：2000/1000 MS（Java /其他的）记忆体限制：65536/32768度（Java /其他的）
总的意见书（S）：40724接受的意见书（S）：20776


### 问题描述

你的任务是计算A + B。 

### 输入
输入包含多个测试案例。每个测试用例包含一对整数a和b，一对每行的整数。测试用例包含0终止输入，这个测试用例是不是要处理。
 
### 产量
对于每个对输入整数a和b你应该输出a和b在同一行，并在输入的每一行与行输出的总和。  

### 样例输入
1 5
10 20
0 
### 输出范例
6
30
 

```c++
#include<iostream>  
using namespace std;  
int main()  
{  
    double a,b;  
    while(cin>>a>>b&&(a!=0||b!=0))  
    {  
        cout<<a+b<<endl;  
    }  
    return 0;  
}  
```

## 一个输入输出的实践四


### 问题描述
你的任务是计算一些整数的总和。 

### 输入
输入包含多个测试案例。每个测试案例包含一个整数N，然后在同一行的N个整数遵循。0开始测试的情况下终止的输入，这个测试用例是不是要处理。 

### 产量
对于每一组输入整数，你应该在同一行输出它们的总和，并与在输入的每一行输出一行。  

### 样例输入
4 1 2 3 4
5 1 2 3 4 5
0  
### 输出范例
10
15
 

```c++
#include<iostream>  
using namespace std;  
  
int main()  
{  
    int n,x,sum;  
    while(cin>>n&&n!=0)  
    {  
        sum = 0;  
        while(n--)  
        {  
            cin>>x;  
            sum+=x;  
        }  
        cout<<sum<<endl;  
    }  
    return 0;  
}  
```


## 一个输入输出的实践五


### 问题描述
你的任务是计算一些整数的总和。
 
### 输入
输入包含一个整数N在第一线，然后按照N行。每一行开始一个整数M，则M在同一行的整数遵循。
 
### 产量
对于每一组输入整数，你应该在同一行输出它们的总和，并与在输入的每一行输出一行。 
 
### 样例输入
2
4 1 2 3 4
5 1 2 3 4 5
 
### 输出范例
10
15
 

```c++
#include<iostream>  
using namespace std;  
  
int main()  
{  
    int t,n,x,sum;  
    cin>>t;  
    while(t--)  
    {  
        cin>>n;  
        sum = 0;  
        while(n--)  
        {  
            cin>>x;  
            sum+=x;  
        }  
        cout<<sum<<endl;  
    }  
    return 0;  
}  
```

## 一个输入输出的实践六
### 问题描述
你的任务是计算一些整数的总和。
 
### 输入
输入包含多个测试例，1例一行。每一种情况下开始与一个整数N，然后在同一行的N个整数遵循。
 
### 产量
对于每个测试用例，你应该在同一行输出N个整数的总和，并与一个在输入的每一行输出线。 
 
### 样例输入

4 1 2 3 4
5 1 2 3 4 5 

### 输出范例
10
15


```c++
#include<iostream>  
using namespace std;  
  
int main()  
{  
    int n,x,sum;      
    while(cin>>n)  
    {  
        sum = 0;  
        while(n--)  
        {  
            cin>>x;  
            sum+=x;  
        }  
        cout<<sum<<endl;  
    }  
    return 0;  
}  
```
 
## 一个输入输出的实践七
 
### 问题描述
你的任务是计算A + B。
 
 
### 输入
将包括由空格分隔的一对整数a和b系列，一对整数，每行输入。 
 
 
### 产量
对于每个对输入整数A和B你应该输出A和B的总和，其次是一个空白行。 
 
 
### 样例输入
1 5
10 20
 
 
### 输出范例
6
30

```c++
#include<iostream>  
using namespace std;  
int main()  
{  
    double a,b;  
    while(cin>>a>>b)  
    {  
        cout<<a+b<<endl<<endl;  
    }  
    return 0;  
}  
```
 
## 一个输入输出的实践八
时限：2000/1000 MS（Java /其他的）记忆体限制：65536/32768度（Java /其他的）
总的意见书（S）：53965接受的意见书（S）：16352


 
### 问题描述
你的任务是计算一些整数的总和。
 

 
### 输入
输入包含一个整数N在第一线，然后按照N行。每一行开始一个整数M，则M在同一行的整数遵循。
 

 
### 产量
对于每一组输入整数，你应该在同一行输出的总和，你必须注意输出之间有一个空白行。
 

 
### 样例输入
3
4 1 2 3 4
5 1 2 3 4 5
3 1 2 3
 

 
### 输出范例
10
15
6

```c
#include<iostream>  
using namespace std;  
  
int main()  
{  
    int n,m,x,sum;    
    while(cin>>n)  
    {  
        while(n--)  
        {  
            cin>>m;  
            sum = 0;  
            while(m--)  
            {  
                cin>>x;  
                sum+=x;  
            }  
            cout<<sum<<endl;  
            if(n!=0)  //注意n=0的时候  
                cout<<"\n";  
        }  
    }  
    return 0;  
}  
```