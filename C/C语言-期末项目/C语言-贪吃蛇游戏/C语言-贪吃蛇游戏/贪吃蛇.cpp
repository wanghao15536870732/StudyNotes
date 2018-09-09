/*
1707004716--王浩
开发环境: vs2010 + Easy-X
*/

/*
1.按下Ctrl  + 鼠标左键  彩色字符阵
2.按下Shift + 鼠标左键   彩色圆球阵
3.按下Ctrl  + 鼠标右键   简单的贪吃蛇游戏
*/
#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <dos.h>
#define N 30  //蛇的最大长度为30

//设置蛇的属性
struct Snack
{
	int X[N];
	int Y[N];
	int node;   //蛇的节数
	int dir;   //蛇的方向
	int life;   //蛇的死活
}snack;

//设置事物的属性
struct Food
{
	int x1;      //食物的横坐标
	int y1;      //食物的纵坐标
	int temp;  //判断是否要出现下一个食物 
}food;

//自定义函数wall()，用来画组成墙的砖


void wall(int x,int y)
{
	int sizx = 9;
	int sizy = 9;
	//定义砖的颜色为蓝色
	setcolor(BLUE);  
	//下面画的四条线组成一个方块
	//画上面
	line(x,y,x + sizx,y);
	line(x + 1,y + 1,x + sizx - 1,y + 1);
	//画左面
	line(x,y,x,y + sizy);
	line(x + 1,y + 1,x + 1,y + sizy - 1);
	setcolor(YELLOW);
	//画右面
	line(x + sizx,y,x + sizx,y + sizy);
	line(x + sizx - 1,y + 1,x + sizx - 1,y + sizy - 1);
	//画下面
	line(x,y + sizy,x + sizx,y + sizy);
	line(x + 1,y + sizy - 1,x + sizx - 1,y + sizy - 1);
	setfillstyle(1,12);    //填充砖的中间部分,用固实填充
	setcolor(GREEN);
	bar(x + 2,y + 2,x + sizx - 2,y + sizy - 2);  //画条形图
}

//定义函数dowall(),来进行画墙

void dowall()
{
	int j;
	for(j = 40;j <= 600;j += 10)
	{
		wall(j,40);  //画上面墙
		wall(j,441);  //画下面墙
	}
	for(j = 40;j <= 440;j += 10)
	{
		wall(40,j);  //画左面墙
		wall(601,j);  //画右面墙
	}
}

//定义两个函数来提示游戏结束

void Gameover1(int score)
{
	TCHAR c1[] = _T("很遗憾！撞到墙了！GAME  OVER!!!");
	cleardevice();  //清屏
	setcolor(YELLOW);  //设置前景色为黄色
	settextstyle(50, 0, _T("宋体"));  //设置字体为50号宋体
	outtextxy(50,200,c1);              //在指定位置输出
	settextcolor(RGB(155, 51, 68));
	TCHAR b[10];
	//将分数转变成字符写进数组
	_stprintf(b, _T("%d"), score);
	//在窗口上输出分数
	outtextxy(540, 300, _T("你的分数:"));
	//设置字体的颜色为红色
	settextcolor(RED);
	outtextxy(790, 300, b);
	Sleep(3);
}
void Gameover2()
{
	TCHAR c2[] = _T("很遗憾！吃到自己了！GAME  OVER!!!");
	setbkcolor(BLACK);
	cleardevice();  //清屏
	setcolor(RED);  //设置前景色为红色
	settextstyle(50, 0, _T("宋体"));  //设置字体为50号宋体
	outtextxy(50,200,c2);              //在指定位置输出
	Sleep(3);
}

//游戏的实现过程

void Play()
{
	int i;
	int score = 0;  //定义游戏分数
	int speed = 300;
	char key;  //定义键盘信息
	srand((unsigned long)time(0));   //为食物的出现提供随机数
	food.temp = 1;   //出现食物,为了在蛇吃掉食物后，再次出现食物
	//定义一开始蛇的方向向右
	snack.dir = 1;
	//蛇头的位置
	snack.X[0] = 300;   //定义蛇的第一节的位置
	snack.Y[0] = 240;

	snack.X[1] = 290;   //定义蛇的第二节的位置
	snack.Y[1] = 240;
	snack.life = 0;   //蛇活着
	//定义蛇的节数
	snack.node = 2;  
	do
	{	
		while(!kbhit())    //在没有按键信息的情况下，蛇自己移动
		{
			//随机出现第一种食物

			if(food.temp == 1)     //判断是否需要新食物的出现
			do
			{
				food.x1 = (rand() % 520) + 60;  //定义事物的横坐标
				food.y1 = (rand() % 270) + 60;  //定义食物的纵坐标
				food.temp = 0;               //食物的产生	
			}while(food.x1 % 10 != 0 || food.y1 % 10 != 0 ||
				food.x1 > 600 || food.x1 < 40 || food.y1 < 40 || food.y1 > 440);
			//蛇的一节长为边长为10的正方形，所以只能吃到坐标为10的倍数并且在四面墙之内的食物
			if(food.temp == 0)    //判断是否要画食物
			{
				setcolor(LIGHTBLUE);  //设置第一种食物的颜色为亮蓝色
				setlinestyle(PS_DASH,PS_ENDCAP_ROUND); //设置为虚线，连接处为圆形
				rectangle(food.x1,food.y1,food.x1 + 10,food.y1 + 10);   //画出食物 
			}
			for(i = snack.node;i > 0;i --)  //实现蛇向前移动
			{
				//横纵坐标均向前移
				snack.X[i] = snack.X[i - 1];         
				snack.Y[i] = snack.Y[i - 1];  
			}
			//蛇的方向
			switch(snack.dir)
			{
			case 1:
				snack.X[0] += 10;   //蛇头向右移
				break;
			case 2:
				snack.X[0] -= 10;   //蛇头向左移
				break;
			case 3:
				snack.Y[0] -= 10;   //蛇头向上移
				break;
			case 4:
				snack.Y[0] += 10;   //蛇头向下移
				break;
			}
			
			//如果蛇吃到自己，则游戏结束
			for(i = 3;i < snack.node;i ++)
			{
				//蛇最多吃到自己的第四段，i从3开始
				if((snack.X[0] == snack.X[i]) && (snack.Y[0] == snack.Y[i]))  
				//如果蛇头与身体的某一节坐标相同
				{
					Gameover2();
					snack.life = 1;  //蛇吃到自己死了
					break;
				}
			}
			if(snack.X[0] == food.x1 && snack.Y[0] == food.y1)  //判断是否吃掉了食物
			{
				//用背景色画矩形遮盖掉食物
				setcolor(BLACK);
				//rectangle(food.x1,food.y1,food.x1 + 10,food.y1 + 10);
				snack.node ++;   //蛇增加一节
				food.temp = 1;     //再出现食物
				speed = speed - 10;  //蛇的速度提升
				score ++; //分数加一
			}
			//显示游戏分数
			//设置文字颜色
			settextcolor(LIGHTRED);
			TCHAR b[10];

			//将分数写进数组,即将int型转变成char类型
			_stprintf(b, _T("%d"), score);
			outtextxy(660, 300, _T("你的分数:"));
			//在指定位置输出分数score
			settextcolor(LIGHTRED);
			outtextxy(780, 300, b);

			//如果蛇撞到墙壁，则游戏结束
			if(snack.X[0] < 50 || snack.X[0] > 590 || snack.Y[0] < 50 || snack.Y[0] > 430)
			{
				Gameover1(score);
				snack.life = 1;  //蛇撞墙死了
					break;      
			}

			//画出蛇的方块图案

			setcolor(YELLOW);
			for(i = 0;i < snack.node;i ++)
			{
				//定义线的格式为实线，端点为圆形
				setlinestyle(PS_SOLID,PS_ENDCAP_ROUND);

				//通过循环来画不同节数的蛇
				rectangle(snack.X[i],snack.Y[i],snack.X[i] + 10,snack.Y[i] + 10);
			}
			Sleep(speed);   //延迟时间，而在人们看来是蛇的移动速度

			//从新设置颜色为背景色黑色
			setcolor(BLACK);
			//用背景色覆盖掉蛇的最后一节
			rectangle(snack.X[snack.node - 1],snack.Y[snack.node - 1],snack.X[snack.node - 1] + 10,snack.Y[snack.node - 1] + 10);
		}
		if(snack.life == 1)  //如果蛇死
		{ 
			break;			//则跳出循环
		}
		key = _getch();      //接受键盘按键信息

		//接下来就是通过按键传递信息并改变蛇的方向

		if(key == 'p')  //如果按下p键，就暂停
		{
			system("pause");   //整个停止
		}
		if(key == 'w' && snack.dir != 4)   //按下w键并且此时不向下走
		{
			snack.dir = 3;                //向上走
		}
		else                              
		{
			if(key == 's' && snack.dir != 3)		//按下s键并且此时不向上走
			{										
				snack.dir = 4;            //向上走
			}
			else
			{
				if(key == 'd' && snack.dir != 2)    //按下d键并且此时不向左走
				{
					snack.dir = 1;			//向右走
				}
				else
				{
					if(key = 'a' && snack.dir != 1)  //按下a键并且此时不向右走
					{
						snack.dir = 2;	     //向左走
					}
				}
			}
		}
	}
	while (key != 'o');   //按下o键结束游戏
}

int main()
{
	//设置随机函数种子
	srand((unsigned) time(NULL));
	initgraph(640,480);
	//先设置页面介绍
	settextstyle(25, 0, _T("宋体"));  //设置字体为30号宋体
	TCHAR s0[] = _T("1 .按下Ctrl  + 鼠标左键  彩色字符阵");
	outtextxy(80,100,s0);
	TCHAR s1[] = _T("2 .按下Shift + 鼠标左键   彩色圆球阵");
	outtextxy(80,130,s1);
	TCHAR s2[] = _T("3 .按下Ctrl  + 鼠标右键   简单的贪吃蛇游戏");
	outtextxy(80,160,s2);
	TCHAR s3[] = _T("贪吃蛇游戏：");
	outtextxy(130,190,s3);
	TCHAR s4[] = _T("游戏规则：");
	outtextxy(130,220,s4);
	TCHAR s5[] = _T("'w'---控制蛇向上走");
	outtextxy(160,250,s5);
	TCHAR s6[] = _T("'a'---控制蛇向左走");
	outtextxy(160,280,s6);
	TCHAR s7[] = _T("'s'---控制蛇向下走");
	outtextxy(160,310,s7);
	TCHAR s8[] = _T("'d'---控制蛇向右走");
	outtextxy(160,340,s8);
	TCHAR s9[] = _T("'p'---暂停(再按其他键继续)");
	outtextxy(160,370,s9);
	TCHAR s10[] = _T("请准备好！！游戏即将开始！！");
	outtextxy(140,410,s10);
	//定义字符的坐标x,y
	int x,y;
	//设置字符
	char c;
	//定义小圆球的半径
	int f = 10;
	//设置颜色
	float T = 190;  //设置色相
	float H = 190;  //设置色相
	float S = 1;	//设置饱和度
	float L = 0.7f;   //设置亮度
	//设置字体
	settextstyle(16,8,_T("宋体"));
	MOUSEMSG m;		// 定义鼠标消息
	while(true)
	{
		// 获取一条鼠标的信息
		m = GetMouseMsg();
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				// 如果点左键的同时按下了 Ctrl 键
				if (m.mkCtrl)
				{
					//把刚才的页面介绍清除掉
					setbkcolor(BLACK);
					cleardevice();
					int i;
					for(i = 0;i <= 240;i ++)
					{
						//颜色随机变化的字符
						//由色相，亮度，和饱和度组成的颜色
						settextcolor( HSLtoRGB(H,S,L));
						//随机位置显示三个随机字母
						for(int j = 0;j < 3;j ++)
						{
							//定义文字的位置
							x = (rand() % 80) * 10;  //随机横坐标
							y = (rand() % 20) * 25;  //随机纵坐标
							c = (rand() % 20) + 65;   //定义字符
							//在窗口上输出这三个字符
							outtextxy(x,y,c);
						}
						//画黄色的线从上往下擦除
						setlinecolor(YELLOW);
				    //  setlinestyle(PS_DOT | PS_ENDCAP_ROUND,5);
						line(0,i,640,i);  //line(起始坐标x,y,结束坐标x,y)
						Sleep(3);    
						//画变色的线从下往上擦除
						setlinecolor( HSLtoRGB(H,S,L));
						H += 5;
						if(H == 790)
							H = 190;
				    //  setlinestyle(PS_DASHDOT | PS_ENDCAP_SQUARE,3);
						line(0,480 - i,640,480 - i);
						Sleep(3);
						if(i >= 240)    //重复进行擦除
							i = -1;
						if(kbhit())  //如果键盘按下任意键，则退出
							break;
					}
				}
				//如果点左键的同时按下了 Shift 键
				if(m.mkShift)
				{ 
					//把刚才的页面介绍清除掉
					setbkcolor(BLACK);
					cleardevice();
					int i,j;
					for(i = 0;i <= 320;i ++)
					{
						//随机位置显示圆
						for(j = 0;j < 3;j ++)
						{
							x = (rand() % 70) * 15; 
							y = (rand() % 20) * 35; 
							//填充实的圆
							fillcircle(x,y,10);	
							/*
							//定义的一种大小可变的圆，得到不一样的效果
							fillcircle(x,y,f);
							f += 5;
							if(f == 80)
								f = 10;
							*/
							//定义填充的颜色
							setfillcolor(HSLtoRGB(T,S,L));
							T += 5;  //颜色逐渐增加
							if(T == 790)
								T = 190;
							setfillstyle(BS_HATCHED,HS_DIAGCROSS);  //设置圆形为固实填充 
							//条格 HS_CROSS, 右斜 HS_FDIAGONAL, 斜条格 HS_DIAGCROSS

						}
						//画黄色的线从左往右擦除	
						setlinecolor(YELLOW);
				//      setlinestyle(PS_DOT | PS_ENDCAP_ROUND,5);
						line(i,0,i,480);
						Sleep(3);//睡眠3毫秒
						//画变色的线从右往左擦除
						setlinecolor( HSLtoRGB(H,S,L));
						H += 5;
						if(H == 790)
							H = 190;
				    //  setlinestyle(PS_DASHDOT | PS_ENDCAP_SQUARE,3);
						line(640 - i,0,640 - i,480);
						Sleep(3);
						if(i >= 320)    //重复进行擦除
							i = -1;
						if(kbhit())  //如果键盘按下任意键，则退出
							break;
					}
				}
			case WM_RBUTTONUP:
				if(m.mkCtrl)  //按鼠标右键 + Ctrl
				{	
					//定义幕布大小
					initgraph(940,480);
					
					//定义前景色为黄色
					setcolor(YELLOW);
					/*
					//背景色设置为绿色，以便可以观察到它的原理
					setbkcolor(GREEN);
					cleardevice();
					*/
					//输处游戏的玩法
					settextstyle(20, 0, _T("宋体"));  //设置字体为20号宋体
					TCHAR c3[] = _T("贪吃蛇游戏");
					outtextxy(730,40,c3);
					TCHAR c4[] = _T("游戏规则：");
					outtextxy(630,60,c4);
					TCHAR c5[] = _T("'w'---控制蛇向上走");
					outtextxy(660,100,c5);
					TCHAR c6[] = _T("'a'---控制蛇向左走");
					outtextxy(660,140,c6);
					TCHAR c7[] = _T("'s'---控制蛇向下走");
					outtextxy(660,180,c7);
					TCHAR c8[] = _T("'d'---控制蛇向右走");
					outtextxy(660,220,c8);
					TCHAR c9[] = _T("'p'---暂停(再按其他键继续)");
					outtextxy(660,260,c9);
					settextstyle(25, 10, _T("Verdana"));
					dowall();			//开始画墙
					Play();				//开始玩游戏
					getch();            //退出游戏界面
					closegraph();		
				}
				if(m.mkShift)
					return 0;	// 按鼠标右键 + Shift 退出程序
		}
	}
	closegraph();
	return 0;
}



