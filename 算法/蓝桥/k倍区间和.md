# 标题： k倍区间和

> 给定一个长度为N的数列，A1, A2, ... AN，如果其中一段连续的子序列Ai, Ai+1, ... Aj(i <= j)之和是K的倍数，我们就称这个区间[i, j]是K倍区间。

你能求出数列中总共有多少个K倍区间吗？

输入

-----
第一行包含两个整数N和K。(1 <= N, K <= 100000)
以下N行每行包含一个整数Ai。(1 <= Ai <= 100000)

输出

-----
输出一个整数，代表K倍区间的数目。

例如，
输入：

```c
5 2
1
2
3
4
5
```

程序应该输出：

```c
6
```

资源约定：
峰值内存消耗（含虚拟机） < 256M
CPU消耗  < 2000ms

请严格按要求输出，不要画蛇添足地打印类似：“请您输入...” 的多余内容。

注意：
> main函数需要返回0;只使用ANSI C/ANSI C++ 标准;
不要调用依赖于编译环境或操作系统的特殊函数。
所有依赖的函数必须明确地在源文件中 #include <xxx>
不能通过工程设置而省略常用头文件。

提交程序时，注意选择所期望的语言类型和编译器类型。

```c
//答案
#include<iostream>
using namespace std;
int n, k;
int a[100010];
int s[100010];//前缀和
int main()
{
    cin >> n >> k;
    s[0] = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i-1] + a[i];
    }

    long long ans = 0;
//    枚举i,j
    for(int i = 1; i <= n; i++) {
        for (int j = i; j <=n ; ++j) {
//            ij之间的区间和=s[j]-s[i-1]
            if((s[j]-s[i-1])%k==0)
                ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
```

```c
//自己见解
#include <stdio.h>
int main()
{
    int sum = 0;
    int num[100000];
    int m,n,k;
    scanf("%d%d",&n,&k);
    for(m = 0;m < n;m ++)
        scanf("%d",&num[m]);
    for(int i = 0;i < n;i ++)
    {
        int count = 0;
        for(int j = i;j < n;j ++)
        {
            count += num[j];
            if(count % k == 0)
                sum ++;
        }
    }
    printf("%d",sum);
    return 0;
}
```