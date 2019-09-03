# 贪吃的小Q

## 【题目描述】

小Q的父母要出差N天，走之前给小Q留下了M块巧克力。小Q决定每天吃的巧克力数量不少于前一天吃的一半，但是他又不想在父母回来之前的某一天没有巧克力吃，请问他第一天最多能吃多少块巧克力

## 【输入描述】

每个输入包含一个测试用例

每个测试用例的第一行包含两个正整数，表示父母的出差天数N(N <= 50000) 和巧克力的数量M(N=<M<=100000>)

## 【输出描述】

输出一个数表示小Q第一天最多能吃多少块巧克力

`输入示例`
3 7

`输出示例`
4

### 【答案及解析】

```c++
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
using namespace std;

int main()
{
    int N = 0, M = 0; //天数 以及 巧克力数 初始化
    bool ok;
    int temp, now, mid;
    scanf("%d%d", &N, &M);
    int left = 1, right = M; //设置左值以及右值
    while (left != right)  //
    {
        ok = 1;
        mid = (right + left + 1) / 2; //二分法，先求中间值
        temp = M;  //储存总值
        now = mid;  //保存中间值
        for (int i = 0; i < N; i++)  //循环N次（天数）
        {
            if (temp < now)
            {
                ok = 0;
                break;
            }
            temp -= now;
            now + (now + 1) / 2;
        }
        if (ok)
            left = mid;  //左值等于中间值
        else
            right = mid - 1; //右值等于中间值 - 1
    }
    printf("小Q第一天最多能吃%d块巧克力\n", left);
    system("pause");
    return 0;
}
```