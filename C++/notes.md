## 类与对象

- 类也可以由struct关键字声明，`strust`与`class`的区别是：如果不指定访问权限，前者缺省的访问权限是`公有`的，而后者是`私有`的。
- 将成员函数的定义直接写在类中即成为`内联成员函数`，或者在类外定义时用`inline`指出
- 默认参数只能在声明或定义中的一处给出
- 拷贝构造函数的参数为`该类对象的引用`
  - 每个类都必须有一个拷贝构造函数；
  - 如果类中没有说明拷贝构造函数，则编译系统自动生成一个具有上述形式的默认拷贝构造函数，依次完成类中对应数据成员的拷贝。

- 使用拷`贝构造函数`的三种情况
  - 明确表示由一个对象初始化另一个对象时；例如：TPoint N(M);
  - 当对象作为函数实参传递给函数形参时（传数据值调用）；例如：P=fun(N);
  - 当对象作为函数返回值时（数据值）；例如：return R;

- 在C++中是通过`构造函数的初始化表`为`子对象`初始化的。

```c
类名::构造函数(参数表)：子对象1(参数表1)，子对象2(参数表2)，…
```

- `构造函数的初始化列表`中未给出对`子对象的初始化`，则表示使用子对象的`缺省构造函数`初始化`子对象`；
- `静态数据成员`不属于任何一个对象，可以通过`类名`直接对它进行访问，一般的用法是：`类名::静态数据成员名`。
- `静态成员函数`可以直接访问该类的静态数据成员和静态函数成员，不能直接访问非静态数据成员和非静态成员函数。
- `组合类`构造函数的执行顺序
  - 按`子对象`的`声明顺序`依次调用子对象的`构造函数`
  - 然后执行组合类`本身的构造函数`体
- 在静态成员函数中访问非静态数据成员，或非静态成员函数，都会产生语法错误。

- 使用const关键字进行声明的数据成员
- 常数据成员必须被初始化，并且不能被更新；
- 一般情况下，常数据成员只能通过初始化表的方法进行初始化；

- 指针常量 `指针是个常量，即 指针的地址值不能改变。`

```c
char * const ps1 = s1;
```

- 常量指针`指向常量的指针，即所指向的值不能改变。`

```c
const char  *ps2 = s2;
```

```c
#include <iostream>
using namespace std;
const int N=6;
void print(const int *p,int n){
    cout<<"{"<<*p;
    for(int i=1;i<N;i++) cout<<","<<*(p+i);
    cout<<"}"<<endl;
} 
int main(){
    int array[N];
    for(int i=0;i<N;i++) cin>>array[i];
    print(array,N); return 0;
}
/*
输入：1 2 3 4 5 6
输出：{1,2,3,4,5,6}
*/
```

- 常对象
  - 类名 const 对象名(初值);或 const 类名 对象名(初值);
  - 定义常对象a1、a2:  const A a1(3,4);    A const a2(3,4);
  - `常对象`不能调用`非常成员函数`，而只能调用`常成员函数`。

```c
#include <iostream>
using namespace std;
class B{
public:
    B(int i,int j) {b1=i;b2=j;}
    void Print() {cout<<b1<<";"<<b2<<endl;}
    void Print() const {cout<<b1<<":"<<b2<<endl;}
private:
    int b1,b2;
};
int main(){
    B bb1(12,5);
    bb1.Print();
    const B bb2(10,9);
    bb2.Print();
    return 0;
}

/*
12 ; 5
10: 9
*/
```

- 对重载条件的补充：

```c
void Print();
void Print() const;  //可重载；
```

- 对象数组

```c
#include <iostream>
using namespace std;
class Date {
public:
    Date() {
        month=day=year=0;
        cout<<"Default constructor called."<<endl;
    }
    Date(int m,int d,int y) {
        month=m;
        day=d;
        year=y;
        cout<<"Constructor called."<<day<<endl;
    }
    ~ Date (){
        cout<<"Destructor called."<<day<<endl;
    }
    void Print(){
        cout<<"Month="<<month<<",Day="<<day
               <<",Year="<<year<<endl;
    }
private:
    int month, day ,year;
};
int main()
{
    Date dates[5]={
        Date(7,22,1998),
        Date(7,23,1998),
        Date(7,24,1998)};
    dates[3]= Date(7,25,1998);
    dates[4]= Date(7,26,1998);
    for(int i=0;i<5;i++)  
        dates[i].Print();
    return 0;
}
/*
Constructor called.22
Constructor called.23
Constructor called.24
Default constructor called.
Default constructor called.
Constructor called.25 //匿名对象 赋值
Destructor called.25  //匿名对象 赋值
Constructor called.26  //匿名对象 赋值
Destructor called.26  //匿名对象 赋值
Month=7,Day=22,Year=1998
Month=7,Day=23,Year=1998
Month=7,Day=24,Year=1998
Month=7,Day=25,Year=1998
Month=7,Day=26,Year=1998
Destructor called.26  //析构函数的执行顺序与构造函数相反。
Destructor called.25
Destructor called.24
Destructor called.23
Destructor called.22
*/
```

- 对象数组与对象指针

```c
//类名   *对象指针名；
Date *pDate;
Date d1(7,22,1998);
pDate = &d1;
```

```c
#include <iostream>
using namespace std;
class Date {
public:
    Date() {
        month = day = year = 0;
        cout<<"Default constructor called."<<endl;
    }
    Date( int m, int d, int y) {
        month=m;
        day=d;
        year=y;
        cout<<"Constructor called."<<day<<endl;
    }
    ~ Date(){
        cout<<"Destructor called."<<day<<endl;
    }
    void Print(){
        cout<<"Month="<<month<<",Day="<<day 
               <<",Year="<<year<<endl; 
    }
private:
    int month, day ,year;
};
int main(){
    Date d1(7,25,1998);
    Date d2(7,26,1998);
    Date *p1;
    p1 = &d1;
    p1->Print();
    p1 = &d2;
    p1->Print();
    return 0;
}
/*
Constructor called.25
Constructor called.26
Month=7,Day=25,Year=1998
Month=7,Day=26,Year=1998
Destructor called.26
Destructor called.25
*/
```

```c
class TPoint{
public:
    TPoint(int x,int y) {X=x;Y=y;}
    TPoint(TPoint &p);
    ~TPoint() {cout<<"Destructor called."<<endl;}
    int Xcoord() {return X;}
    int Ycoord() {return Y;}
private:
    int X,Y;
};

TPoint::TPoint(TPoint &p){
    X=p.X; Y=p.Y;
    cout<<"Copy_initialization Constructor called.\n";
}
TPoint fun(TPoint Q){
    cout<<"OK! "<<endl;
    int x,y;
    x=Q.Xcoord()+10;  y=Q.Ycoord()+15;
    TPoint R(x,y);
    return R;
}

int  main(){
    TPoint M(12,20),P(0,0),S(0,0);
    TPoint N(M); P=fun(N);
    S=M;
    cout<<"P="<<P.Xcoord()<<", " <<P.Ycoord()<<endl;
    cout<<"S="<<S.Xcoord()<<", " <<S.Ycoord()<<endl;
    return 0;
}

/*
Copy_initialization Constructor called.
Copy_initialization Constructor called.
OK!
Copy_initialization Constructor called.
Destructor called.
Destructor called.
Destructor called.
P=22,35
S=12,20
Destructor called.
Destructor called.
Destructor called.
Destructor called.

*/

```

### 构造函数的特点

- 构造函数的函数名与类名相同
- 不能定义构造函数的类型（即不能指明构造函数返回值的类型）。
- 构造函数应声明为公有函数。
- 构造函数不能在程序中调用，在对象创建时，构造函数被系统自动调用。

### 析构函数的特点

- 析构函数名字为符号“~”加类名。
- 析构函数没有参数，不能指定返回值类型。
- 一个类中只能定义一个析构函数，所以析构函数不能重载。
- 当一个对象作用域结束时或者使用delete运算符释放new运算符创建的对象时，系统自动调用析构函数。

```c
#include <iostream>
using namespace std;
class A{
public:
    A(int i){a=i;}
    int fun(int b) {return a*c+b;}
    int c;
private:
    int a;
};
int main(){
   A x(18);
   int A::*pc;
   pc=&A::c;
   x.*pc=5;
   int (A::*pfun)(int);
   pfun=A::fun;
   A  *p=&x;
   cout<<(p->*pfun)(10);
   return 0;
}
```

- 使用new创建对象数组时，不能为该数组指定初始值，其初始值为缺省值。所以，使用new创建对象数组时，类中必须说明缺省构造函数.

## 类的继承与派生

- `私有成员(private)`：可以被类自身的成员和友元访问，但不能被包括派生类在内的其他任何类和任何普通函数访问。
- `公有成员(public)`：可以被任何普通函数和任何类的成员函数访问。
- `保护成员(protected)`：可以被类自身的成员和友元访问外，还可以被派生类的成员函数访问。

- 派生类构造函数的执行顺序
  - 先调用基类的构造函数;
  - 然后对派生类的成员初始化列表中数据成员（包括子对象、常量、引用等必须初始化的成员）按照声明顺序，依次初始化;
  - 最后执行派生类构造函数的函数体;
- 构造函数的执行顺序只与成员声明的顺序有关，而与初始化表中各项的排列顺序无关。
- 常数据成员、引用成员、子对象，只能在成员初始化列表中进行初始化.

```c
#include <iostream>
using namespace std;
class A
{
private:
    int a;
public:
    A(int x):a(x)
    {
        cout << "construct A " << a << endl;
    }
};

class B : public A{
private:
    int   b,c;
    const int d;
    A   x,y;
public:
   B(int v) : b(v), y(b+2), x(b+1), d(b), A(v){
      c = v; 
       cout << "construct B " << b <<" "  << c << " " << d << endl;
   }
};

int main()
{
    B  b1(10);
    return 0;
}
/*
construct A 10
construct A 11
construct A 12
construct B 10 10 10
*/
```

```c
#include <iostream>
using namespace std;
class CBase1 {
protected:
    int b;
public:
    CBase1(int x=0){
        b=x;  cout << "Construct CBase1!  " << b <<endl;
    }
    ~CBase1(){cout << "Destruct CBase1!  " << b <<endl;}
};

class CBase2 {
protected:
    int b;
public:
    CBase2(int x=0){
        b=x;   cout << "Construct CBase2!  " << b <<endl;
    }
    ~CBase2(){cout << "Destruct CBase2!  " << b <<endl;}
};

class CDerived : public CBase1,private CBase2 {
protected:
    CBase1 b1;  CBase2 b2;  int d;
public:
    CDerived(int x,int y, int z): b1(y),CBase2(y),b2(z),CBase1(x){
        d=z;  cout << "Construct CDerived!  " << d <<endl;
    }
    ~CDerived(){
        cout << "Destruct CDerived!  " << d <<endl;
    }
};

int main(){
    CDerived d1(1,2,3);
    return 0;
}
```

- 在一个成员初始化列表中出现对`虚基类`和对`非虚基类`构造函数的调用时，虚基类的构造函数`先于`非虚基类的构造函数的执行；
- 最远派生类的构造函数的成员初始化列表中必须给出对虚基类的构造函数的调用；如果未列出，则相应的虚基类必须有缺省构造函数。

```c
#include <iostream>
using namespace std;
class A{
public:
    A() {}
    virtual void fun() { cout<<"In A::fun().\n";}
};
class B:public A{
public:
    B() { fun(); }
    void g() { fun(); }
};
class C:public B{
public:
    C() {}
    virtual void g() { cout<<"In C::fun().\n"; }
};
int main(){
    C c;
    c.g();
    return 0;
}
/*
In A::f() called.
In C::f() called.
*/
```

- 构造函数中调用虚函数时，采用静态联编，即构造函数调用的虚函数是自己类中定义的虚函数，如果自己类中没有实现这个虚函数，则调用基类中的虚函数，而不是任何派生类中实现的虚函数。
- 构造函数不能被声明为虚函数
- 如果基类的指针指向派生类对象，当用delete删除这个对象时，若析构函数不是虚函数，就要调用基类的析构函数，而不会调用派生类的析构函数。如果为基类和派生类的对象分配了动态内存，或者为派生类的对象成员分配了动态内存，这时释放的只是基类中动态分配的内存，而派生类中动态分配的内存未被释放。

```c
#include <iostream>
using namespace std;

class A
{
public:
    virtual ~A() {cout<<"A::~A() called. "<<endl;}
};

class B:public A{
public:
    B(int i) {buf=new char[i];}
    virtual ~B(){
        delete [] buf;
        cout<<"B::~B() called. "<<endl;
    }
private:
    char *buf;
};

int main(){
    A *a=new B(15);
    delete a;
    return 0;
}
/*
B::~B() called.
A::~A() called.
*/
```

- 不能定义CShape抽象类的对象，但可以定义CShape类的指针

```c
#include <iostream>
using namespace std;
class complex{
public:
    complex(double r=0,double i=0);
    complex operator +(const complex& c);
    complex operator -(const complex& c);
    complex operator -();
    void print() const;
private:
    double real, imag;
};

complex::complex(double r,double i){
    real=r;
    imag=i;
}

complex complex::operator +(const complex& c){
    double r=real+c.real;
    double i=imag+c.imag;
    return complex(r,i);
}

complex complex::operator -(const complex& c){
    double r=real-c.real;
    double i=imag-c.imag;
    return complex(r,i);
}
complex complex::operator -(){
    return complex(-real,-imag);
}
void complex::print() const{
    cout<<'('<<real<<','<<imag<<')'<<endl;
}

int main(){
    complex c1(2.5,3.7), c2(4.2,6.5), c;
    c=c1-c2;
    c.print();
    c=c1+c2;
    c.print();
    c=-c1;
    c.print();
    return 0;
}
/*
(-1.7,-2.8)
(6.7,10.2)
(-2.5,-3.7)
*/
```

```c
#include <iostream>
#include <string>
using namespace std;
class CPoint{
private:
    int X, Y;
public:
    CPoint(int x=0, int y=0){X=x; Y=y;} 
    CPoint(CPoint &p){ X=p.X; Y=p.Y; }
    int GetX(){ return X; }
    int GetY() {return Y;}
};

class CShape{
private:
    string Color;
public:
    CShape(string c){Color = c;}
    virtual void Draw(){
        cout << "Draw a shape. The color is " << Color << endl;
    }
    void PrintColor(){ cout << Color << endl;}
};


class CLine:public CShape{
private:
    CPoint Start;  //线段的起点
    CPoint End;   //线段的终点
public:
    CLine(CPoint s, CPoint e, string c):CShape(c),Start(s),End(e){}
    virtual void Draw(){
        cout << "Draw a Line from (" << Start.GetX() << "," << Start.GetY();
        cout<<") to ("<<End.GetX()<<","<<End.GetY() << "), with color ";
         PrintColor();
    }
};

class CCircle:public CShape{
private:
    CPoint Center;
    int Radius;
public:
    CCircle(CPoint ctr, int r, string c):CShape(c),Center(ctr){
        Radius = r;
    }
   virtual void Draw(){
        cout << "Draw a circle at center (" << Center.GetX() << "," ;
        cout << Center.GetY()<< ") with radius " << Radius << " and color ";
        PrintColor();
    }
};

int main(){
    CShape *ps[3];
    CShape s("Red");
    CPoint p1(10,10), p2(100,100),p3(50,50);
    CLine  l(p1,p2,"Green");
    CCircle c(p3, 20, "Black");
    ps[0] = &s;   ps[1] = &l;  ps[2] = &c;
    for(int i=0; i<3; i++) ps[i]->Draw();
    return 0;
}

/*
Draw a Shape. The color is Red
Draw a Line from (10, 10) to (100, 100) , with color Green
Draw a Circle at center (50, 50) with radius 20 and color Black
*/
```

- C++中的变量名，名称中只能使用字母、数字和下划线
- 变量名的第一个字符不能是数字
- 取名时变量名不能是C++的关键字，即不能使用C++中已定义好的有特殊含义的单词
- C++中的变量名，区分大小写，即同一字母大小写是不同的变量名
