#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  HEAD printf("\t|%-21s %-10s %-10s %-8s %-8s %-5s %-5s %-5s %-8s %-9s %-5s|\n","学号","姓名","专业","班级","公寓名","宿舍","床位","性别","年龄","手机号","级别")

//密码登录 
//管理登录信息 

typedef struct EN{ //存用户和密码 
	char userName1[10];
	char passWorld1[10];
}EN;

void enter();

//密码加密
void encryption(char passWorld[])
{
	int i; 
	//将每一位密码的Ascall码值改变 
	for(i = 0;i < strlen(passWorld);i ++)
	{
		passWorld[i] += 20;
	} 
} 

//注册
void  sign_in(char userName[],char passWorld[])
{
	FILE *fp;
	int flag = 0;
	char userName1[10];
	char passWorld1[10];
	printf("\t注册\n");
	printf("\t用户名:");
	fflush(stdin);
	gets(userName);
	printf("\t密码:");
	gets(passWorld);
	//判断文件是否存在 
	if((fp = fopen("enter.txt","rt")) == NULL)
	{
		//如果不存在就直接退出 
		exit(0);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",userName1,passWorld1);
		
		//判断userName跟userName1是否相同 
		if(!strcmp(userName,userName1))
		{
			printf("用户名重复\n");
			flag = 1;
			break;
		}
	}
	//关闭文件流 
	fclose(fp);
	if(flag == 1)
	{
		enter(); 
	} 
	else
	{ 
		if((fp = fopen("enter.txt","at")) == NULL)
			exit(0);
		encryption(passWorld); //加密
		
		//将userName跟passWorld写入enter.txt文件当中 
		fprintf(fp,"%s %s\n",userName,passWorld);
	}
	
	//关闭文件流 
	
	fclose(fp);
	enter(); 
}

//删除不合法用户
void alter()
{
	FILE *fp;
	int n = 0;
	
	//开辟 
	EN en[1000];
	//打开enter.txt文件 
	fp = fopen("enter.txt","rt");
	if(fp == NULL)
	{
		printf("\t打开文件失败\n");
		exit(0);
	}
	//判断读取是否到文件的结尾 
	while(!feof(fp))
	{
		//读取enter.txt文件当中的userName跟passWorld 
		fscanf(fp,"%s %s",en[n].userName1,en[n].passWorld1);
		n ++;
	}
	
	printf("\t%-8s\t%-8s\n","用户名","密码");
	int i;
	for(i = 0;i < n;i ++)
	{
		printf("\t%-8s\t%-8s\n",en[i].userName1,en[i].passWorld1);
	}
	fclose(fp);
	printf("\t输入你要删除的用户名\n");
	printf("\t用户名:");
	char ch[10];
	printf("\t");
	scanf("%s",ch);
	for(i = 0;strcmp(ch,en[i].userName1);i ++)
	{
		
	}
	int k = i;
	for(i = k;i < n - 1;i ++)
	{
		en[i] = en[i + 1];
	}
	n --;
	fp = fopen("enter.txt","wt");
	if(fp == NULL)
	{
		printf("\t打开文件失败\n");
		exit(0);
	}
	//把不合法的用户删除并写入文件 
	for(i = 0;i < n;i ++)
	{
		fprintf(fp,"%s %s\n",en[i].userName1,en[i].passWorld1);
	}
	fclose(fp);	
}

//登录入口 

void enter()		
{
	printf("\t=================================\n");
	printf("\t|\t登录:\t\t\t|\n");
	printf("\t=================================\n");
	FILE *fp;
	int i;
	printf("\t1.宿舍管理员\t2.登录\n");
	char userName[10];
	char passWorld[10];
	char userName1[10];
	char passWorld1[10];
	int choice;
	printf("\t");
	scanf("%d",&choice);
	int flag = 0;
	switch(choice)
	{
		case 1:{        //管理员，注册用户和删除 
			char adm[10]; 
			printf("\t输入宿舍管理员密码\n");
			printf("\t");
			scanf("%s",adm);
			//将管理员密码跟1进行对比，意味着管理员密码就是1 
			if(strcmp(adm,"1"))
			{
				printf("\t宿舍管理员密码错误\n");
				enter();
			}
			printf("\t");
			printf("1.注册\t2.修改\n");
			int j;
			printf("\t");
			scanf("%d",&j);
			switch(j)
			{
				case 1:{
					//注册 
					sign_in(userName,passWorld);
					break;
				}
				case 2:{
					//修改 
					int flag1 = 0;
					do
					{
						alter();
						flag1 = 0;
						printf("\t是否继续删除：1.是  2.否\n");
						printf("\t");
						scanf("%d",&flag1);
					}
					while(flag1 == 1);
					//进入主界面 
					enter();
					break;
				}
				default:{
					break;
				}
			}			
			break;
		}
		
		//用户登录 
		case 2:{     
			printf("\t登录\n");
			printf("\t用户名:");
			//函数fflush用于将缓冲区的内容输出到文件中去
			//如果成功刷新，fflush返回0。指定的流没有缓冲区或者只读打开时也返回0值
			fflush(stdin);
			printf("\t");
			gets(userName);
			printf("\t密码:");
			printf("\t");
			gets(passWorld);
			if((fp = fopen("enter.txt","rt")) == NULL)
			{
				exit(0);
			}
			//feof(FILE *stream) 测试给定流 stream 的文件结束标识符。
			//如果没有到达文件结尾 
			while(!feof(fp))
			{
				fscanf(fp,"%s %s",userName1,passWorld1);
				
				//加密
				encryption(passWorld);
				
				//如果账号跟密码是已经注册过的
				if(!strcmp(userName,userName1) && !strcmp(passWorld,passWorld1))
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				printf("\t输入用户名密码不匹配或者错误\n");
				enter();
			}
			printf("\t成功\n");
			break;
		}
		default:{
			printf("输入选择不符合格式\n");
			break;
		}
	}
}

//储存数据 操作数据 

//宿舍信息结构体 
typedef struct stu{ 

	int enUniversity;  //大学编号 
	char major[20];		//专业 
	int banji;  		// 班级  	
	char id[10];   		//学号 
	char name[10];  	 //姓名 
	char sex[3]; 		//性别 
	int age; 			//年龄 
	char number[12];   //手机号
	char dorm[50]; 		//宿舍楼名
	int dorm_num;  		//宿舍编号 
	int dorm_num_id;  	//床号 
	struct stu *next; 	//尾节点 
	
}stu;

void print(stu *head);

void interface()//主界面 
{
	printf("\n\n");
	printf("\t---------------------------------------------------------\n"); 
	printf("\t|\t\t欢迎使用宿舍信息管理系统\t\t|\n");
	printf("\t---------------------------------------------------------\n");
	
	// 数据录入 
	
	printf("\t|\t\t\t1-录入数据\t\t\t|\n"); 
	
	//数据增删改查
	
	printf("\t|\t\t\t2-数据增加\t\t\t|\n");  
	printf("\t|\t\t\t3-数据删除\t\t\t|\n");
	printf("\t|\t\t\t4-数据修改\t\t\t|\n");
	printf("\t|\t\t\t5-数据查询\t\t\t|\n");
	
	//数据统计 
 
	printf("\t|\t\t\t6-数据统计\t\t\t|\n");
	
	//报表 
	
	printf("\t|\t\t\t7-数据报表\t\t\t|\n");
	printf("\t---------------------------------------------------------\n");
}

//学号查重,重复返回0，否则1
int find_id(char id[],stu *head)
{
	stu *i;
	//链表查找 
	for(i = head->next;i != NULL;i = i->next)
	{
		//判断学号是否相等 
		if(strcmp(id,i->id) == 0)
		{
			printf("\t学号重复\n");
			return 0;
		}
	}
	return 1;
}

//检查宿舍是否有重复的,符合返回1，不符合返回0 
int find_check(stu *head,stu *p) 
{
	stu *i;
	for(i = head->next;i != NULL;i = i->next)
	{
		if(! strcmp(p->dorm,i->dorm) && (p->dorm_num_id == i->dorm_num_id) && (p->dorm_num == i->dorm_num))
		{
			printf("\t宿舍信息重复!!!\n");
			printf("\t请重新输入:\n");
			
			return 0;
		}
	}
	return 1;
}


//创建链表
stu *creat() 
{
	int i = 1;
	stu *head,*end,*p;
	char id[10];
	head = NULL;
	head = (stu*)malloc(sizeof(stu));
	head->next = NULL;
	end = head;
	printf("录入第%d个学生的信息:",i);
	printf("\t输入学号:");
	
	// fflush(stdin)刷新标准输入缓冲区，把输入缓冲区里的东西丢弃 
	//fflush(stdout)刷新标注输出缓冲区，把输出缓冲区里的东西打印到标准输出设备上 
	
	fflush(stdin);
	gets(id);
	//如果get到的id是大于0的 
	while(strlen(id) > 0)
	{
		//学号查重,重复返回0，否则1
		if(find_id(id,head)) 
		{
			p = (stu*)malloc(sizeof(stu));
			strcpy(p->id,id);
			printf("\t输入姓名:");	
			gets(p->name);
			printf("\t输入公寓名称:");		
			scanf("%s",p->dorm);
			printf("\t输入宿舍名称:");
			scanf("%d",&p->dorm_num);
			printf("\t输入床位号:");
			scanf("%d",&p->dorm_num_id);
			
			/*
				int enUniversity;  //大学名称	
				char major[20];	//专业 
				int banji;  // 班级  	
				char id[10];   //学号 
				char name[10];   //姓名 
				char sex[3]; 	//性别 
				int age;        //年龄 
				char number[12];   //手机号 
				char dorm[50]; //宿舍楼名
				int dorm_num;  //宿舍编号 
				int dorm_num_id;  //床号 
				struct stu *next; //尾节点 
			*/
			
			//检查宿舍是否满员,符合返回1，不符合返回0 
			if(find_check(head,p)) 
			{		
				printf("\t手机号:");
				fflush(stdin);
				gets(p->number); 
				printf("\t年龄:");
				scanf("%d",&p->age); 
				printf("\t性别:");
				scanf("%s",p->sex); 
				printf("\t专业:");
				scanf("%s",p->major);
				printf("\t班级:");
				scanf("%d",&p->banji);
				printf("\t输入入学年份:");
				scanf("%d",&p->enUniversity);
				end->next = p;
				end = p;
				p->next = NULL;
			} 	
		}
		printf("\n\n");
		i ++; 
		printf("录入第%d个学生的信息:\n",i);
		printf("\t输入学号:");
		//函数fflush用于将缓冲区的内容输出到文件中去
		//如果成功刷新，fflush返回0。指定的流没有缓冲区或者只读打开时也返回0值
		fflush(stdin);
		gets(id);
	}
	return head;
}

//链表打印输出 
void print(stu *head)
{
	
	stu *i;
	for(i = head->next;i != NULL;i = i->next)
	{
		printf("\t|%-20s %-10s %-9s %-5d %-10s %-5d %-5d %-5s %-5d %-12s %-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
	}
}

//文件生成链表 
stu *write_linked()  
{
	
	FILE *fp;
	fp = fopen("student.txt","rt");
	stu *i;
	stu *head;
	head = NULL;
	head = (stu*)malloc(sizeof(stu));
	stu *end,*p;
	end = head;
	
	//feof用检测流上的文件结束符，其返回值有两种情况：
	//如果遇到文件结束，函数值为非零值，否则函数值为0
	//如果没有到文件结尾 
	while(!feof(fp))
	{
		p = (stu*)malloc(sizeof(stu));
		//向下读取的数据存放的内存 ，一个一个的读取 
		fread(p,sizeof(stu),1,fp);
		fgetc(fp);
		end->next = p;
		end = p;
		p->next = NULL;
	}
	//关闭读写自流 
	fclose(fp);
	//返回头节点 
	return head; 
}

//用链表，生成文件 储存 
void write_file(stu *head)  
{
	FILE *fp;
	
	//打开student.txt,必须提前在项目文件夹下新建student.txt文件 
	fp = fopen("student.txt","wt");
	stu *i;
	
	for(i = head->next;i != NULL;i = i->next)
	{
		fwrite(i,sizeof(stu),1,fp);
		if(i->next != NULL)
		fputc('\n',fp);
	}
	fclose(fp);
}

//数据表头
void header()
{
	printf("\t-------------------------------------------------------------------------------------------------------\n");
	
	HEAD;//"学号","姓名","专业","班级","公寓名","宿舍","床位","性别","年纪","手机号","级别"
	
	printf("\t-------------------------------------------------------------------------------------------------------\n");
}

//交换int
void exchange_num(int *x,int *y) 
{
	int t = *x;
	*x = *y;
	*y = t;
}

//交换字符串 
void exchange_string(char a[],char b[])
{
	char t[20];
	strcpy(t,a);
	strcpy(a,b);
	strcpy(b,t);
}

//交换stu结构体类型 
void exchange(stu *ec1,stu *ec2) 
{
	exchange_num(&ec1->age,&ec2->age);
	exchange_num(&ec1->banji,&ec2->banji);
	exchange_string(ec1->dorm,ec2->dorm);
	exchange_num(&ec1->dorm_num,&ec2->dorm_num);
	exchange_num(&ec1->dorm_num_id,&ec2->dorm_num_id);
	exchange_string(ec1->id,ec2->id);
	exchange_num(&ec1->enUniversity,&ec2->enUniversity);
	exchange_string(ec1->major,ec2->major);
	exchange_string(ec1->name,ec2->name);
	exchange_string(ec1->number,ec2->number);
	exchange_string(ec1->sex,ec2->sex);
}

//根据公寓 宿舍 床位 排序 
void sort(stu *head) 
{
	//根据公寓 排序
	stu *i,*j;
	for(i = head->next;i != NULL;i = i->next)
	{
		for(j = i->next;j != NULL;j = j->next)
		{
			// i->dorm > j->dorm
			if(strcmp(i->dorm,j->dorm) > 0)
			{
				exchange(i,j);
			}
		}
	}
	
	//根据宿舍 排序
	for(i = head->next;i != NULL;i = i->next)
	{
		for(j = i->next;j != NULL;j = j->next)
		{
			//在宿舍楼相等的情况下，比肩宿舍的编号 
			if(!strcmp(i->dorm,j->dorm) && i->dorm_num > j->dorm_num)
			{
				exchange(i,j);
			}
		}
	}
	
	//根据床位 排序
	for(i = head->next;i != NULL;i = i->next)
	{
		for(j = i->next;j != NULL;j = j->next)
		{
			//在宿舍楼号跟宿舍号相等的情况下，在比较宿舍里面床号的顺序 
			if(strcmp(i->dorm,j->dorm) == 0 && i->dorm_num == j->dorm_num && i->dorm_num_id > j->dorm_num_id)
			{
				exchange(i,j);
			}
		}
	}
	
}

//添加数据 
void add(stu *head)
{
	stu *end;
	for(end = head->next;end->next != NULL;end = end->next)
	{
		
	}
	int i = 0;
	stu *p;
	char id[20];
	printf("\t输入学号:");
	//fflush(stdin)刷新标准输入缓冲区，把输入缓冲区里的东西丢弃
	fflush(stdin);
	gets(id);
	while(strlen(id) > 0)
	{
		
		if(find_id(id,head))//学号查重,重复返回0，否则1 
		{
			p=(stu*)malloc(sizeof(stu));
			p->next = NULL;
			strcpy(p->id,id);
			printf("\t输入姓名:");	
			gets(p->name);
			printf("\t输入公寓名称:");			
			scanf("%s",p->dorm);
			printf("\t输入宿舍名称:");
			scanf("%d",&p->dorm_num);
			printf("\t输入床位号:");
			scanf("%d",&p->dorm_num_id);
			
			//检查宿舍是否满员,符合返回1，不符合返回0
			if(find_check(head,p))   
			{		
				printf("\t手机号:");
				fflush(stdin);
				gets(p->number); 
				printf("\t年龄:");
				scanf("%d",&p->age); 
				printf("\t性别:");
				scanf("%s",p->sex); 
				printf("\t专业:");
				scanf("%s",p->major);
				printf("\t班级:");
				scanf("%d",&p->banji);
				printf("\t输入入学年份:");
				scanf("%d",&p->enUniversity);	
				end->next = p;
				end = p;	
			} 	
		}
		printf("\n\n");
		printf("\t输入学号:");
	
		//fflush(stdin)刷新标准输入缓冲区，把输入缓冲区里的东西丢弃
		fflush(stdin);
		gets(id);
	}
	printf("\t结束\n");
}

//按学号删除数据
void dele(stu *head) 
{
	printf("\t输入你要删除的学号:");
	char id[20];
	fflush(stdin);
	gets(id);
	//倒数第二个 	
	stu *end1;
	stu *i;
	while(strlen(id) > 0)
	{
		//找到最后的一个节点 
		for(end1 = head->next;end1->next->next != NULL;end1 = end1->next)
		{
			
		}
		i = head;
		while((i=i->next) != NULL)
		{
			if(strcmp(id,i->id) == 0)
			{
				exchange(i,end1->next);
				free(end1->next);
				end1->next = NULL;
				sort(head);
				printf("\t成功\n");
				break;
			}
			else if(i->next == NULL)
			{
				printf("\t->未找到相匹配的学号<-\n");
			}
		}
		printf("\t输入你要删除的学号:");
		gets(id);
	}	
}

//按学号修改数据
void modify(stu *head) 
{
	char flag[5];
	printf("\t输入你要修改的学号:");
	char id[20];
	char new_id[20];
	fflush(stdin);
	gets(id);
	stu *i;
	stu *k;
	k = (stu*)malloc(sizeof(stu));
	k->next = NULL;
	while(strlen(id) > 0)
	{	
		i = head;
		while((i = i->next) != NULL)
		{
			if(strcmp(id,i->id) == 0)
			{
				printf("\t是否修改学号(yes/no?):") ;
				gets(flag);
				if(strcmp(flag,"yes") == 0)
				{
					printf("\t输入修改的学号:");
					gets(new_id);
					//判断新的学号跟之前的学号是否相同 
					if(find_id(new_id,head) || strcmp(id,new_id) == 0)
					{
						//保存新的new_id 
						strcpy(k->id,new_id);
					}
					else
					{
						printf("\t新学号重复");
						break;
					}
				}
				else
				{
					strcpy(k->id,i->id);
				} 
				printf("\t输入姓名:");	
				gets(k->name);
				printf("\t输入公寓名称:");	
				scanf("%s",k->dorm);
				printf("\t输入宿舍名称:");
				scanf("%d",&k->dorm_num);
				printf("\t输入床位号:");
				scanf("%d",&k->dorm_num_id);
				//检查宿舍是否满员,符合返回1，不符合返回0 
				//即判断 
				if(find_check(head,k) || (!strcmp(k->dorm,i->dorm) && 
					i->dorm_num == k->dorm_num && 
					i->dorm_num_id == k->dorm_num_id))  
				{		
					printf("\t手机号:");
					fflush(stdin);
					gets(k->number); 
					printf("\t年龄:");
					scanf("%d",&k->age); 
					printf("\t性别:");
					scanf("%s",k->sex); 
					printf("\t专业班级:");
					scanf("%s",k->major);
					printf("\t班级:");
					scanf("%d",&k->banji);
					printf("\t输入入学年份:");
					scanf("%d",&k->enUniversity);
					//将之前保存的查找到的数据用k节点的数据替换 
					exchange(i,k);
				} 				
			}
			else if(i->next ==  NULL)
			{
				printf("\t->未找到相匹配的学号<-\n");
			}
		}
		printf("\t输入你要修改的学号:");
		fflush(stdin);
		gets(id);
	}	
	free(k);
}

//数据查询子界面 
void interface1()
{
	printf("\t\t------------------\n");
	printf("\t\t|1.按学号查询    |\n");
	printf("\t\t|2.按姓名查询    |\n");
	printf("\t\t|3.按公寓宿舍查询|\n");
	printf("\t\t------------------\n");
}

//按学号查找 
void lookup_id(stu *head)
{
	char id[20];
	printf("\t输入学号:");
	fflush(stdin);
	gets(id);
	stu *i;
	while(strlen(id) > 0)
	{	
		i = head;
		while((i = i->next) != NULL)
		{
			if(strcmp(id,i->id) == 0)
			{
				header();
				printf("\t|%-10s%-8s%-9s%-5d%-10s%-5d%-5d%-5s%-5d%-12s%-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
				printf("\t---------------------------------------------------------------------------------\n");
				break;
			}
			else if(i->next == NULL)
			{
				printf("\t未找到相应学号\n");
			}
		}
		printf("\t输入学号:");
		fflush(stdin);
		gets(id);
	}
}

//按姓名查找 
void lookup_name(stu *head)
{
	char name[20];
	printf("\t输入姓名:");
	fflush(stdin);
	gets(name);
	stu *i;
	int flag;//判断是否找到数据，1找到，0枚找到 
	int flag1;//判断是否输出表头 ，1输出，0不输出
	flag1 = 1; 
	while(strlen(name) > 0)
	{	
		flag = 0;
		i = head;
		while((i = i->next) != NULL)
		{
			if(strcmp(name,i->name) == 0)
			{
				if(flag1 == 1)
				{
					header();
					flag1 = 0;
				}				
				printf("\t|%-10s%-8s%-9s%-5d%-10s%-5d%-5d%-5s%-5d%-12s%-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
				flag = 1;
			}
			else if(i->next == NULL && flag == 0)
			{
				printf("\t未找到相应姓名\n");
			}
		}
		printf("\t---------------------------------------------------------------------------------\n");
		printf("\n");
		printf("\t输入姓名:");
		fflush(stdin);
		gets(name);
	}
}

//按公寓宿舍查找 
void lookup_dorm_num(stu *head)
{
	int  num = 0;
	char dorm[20];
	printf("\t输入公寓和宿舍号:");
	scanf("%s %d",dorm,&num);
	stu *i;
	int flag;//判断是否找到数据，1找到，0枚找到 
	int flag1;//判断是否输出表头 ，1输出，0不输出
	flag1 = 1; 
	while(strlen(dorm) > 0 && num != 0)
	{	flag = 0;
		i = head;
		while((i = i->next) != NULL)
		{
			if(num == i->dorm_num && strcmp(dorm,i->dorm) == 0)
			{
				if(flag1 == 1)
				{
					header();
					flag1 = 0;
				}				
				printf("\t|%-10s%-8s%-9s%-5d%-10s%-5d%-5d%-5s%-5d%-12s%-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
				flag = 1;
			}
			else if(i->next == NULL&&flag == 0)
			{
				printf("\t未找到相应宿舍号\n");
			}
		}
		printf("\t---------------------------------------------------------------------------------\n");
		printf("\n");
		num = 0;
		printf("\t输入公寓和宿舍号:");
		scanf("%s %d",dorm,&num);
	}
}

//按需求查询人数 
void son_operation(stu *head)
{
	
	printf("\t输入选项(0退出):");
	int choice;
	scanf("%d",&choice);
	//输入0就直接退出 
	if(choice == 0)
	{
		return;
	}
	switch(choice)
	{
		case 1:{
			//按id查询 
			lookup_id(head);
			break;
		}
		case 2:{
			//按姓名查询 
			lookup_name(head);
			break;
		}
		case 3:{
			//按公寓宿舍查询 
			lookup_dorm_num(head);
			break;
		}
		default :{
			printf("\t->输入格式有误<-\n");
			break;
		} 
	}
}

//统计操作表子目录 
void son_statistical()
{
	printf("\t\t----------------\n");
	printf("\t\t|1.统计总人数  |\n");
	printf("\t\t|2.统计单个公寓|\n");
	printf("\t\t|3.统计公寓宿舍|\n");
	printf("\t\t----------------\n");
}

//统计总人数
void  statistical_total(stu *head)
{
	stu *i;
	int n = 0;
	for(i = head->next;i != NULL;i = i->next)
	{
		n ++;
	}
	printf("\t->共%d人<-\n",n); 
}

//统计单个公寓
void statistical_dorm(stu *head)
{
	int n=0;
	char dorm[20];
	printf("\t输入公寓:");
	fflush(stdin);
	gets(dorm);
	stu *i;
	while(strlen(dorm) > 0)
	{	
		i=head;
		n=0;
		while((i = i->next) != NULL)
		{
			if(strcmp(dorm,i->dorm) == 0)
				n++;	
		}
		printf("\t->该公寓共%d人<-\n",n);
		printf("\t输入公寓:");
		fflush(stdin);
		gets(dorm);
	}
}

//统计公寓宿舍
void statistical_dorm_num(stu *head)
{
	int  num=0;
	int n;
	char dorm[20];
	printf("\t输入公寓和宿舍号:");
	scanf("%s %d",dorm,&num);
	stu *i;
	while(strlen(dorm) > 0 && num != 0)
	{	
		n = 0;
		i = head;
		while((i = i->next) != NULL)
		{
			if(num == i->dorm_num && strcmp(dorm,i->dorm) == 0)			
				n++;
			
		}		
		printf("\t->该宿舍共%d人<-\n",n);
		num = 0;
		printf("\t输入公寓和宿舍号:");
		scanf("%s %d",dorm,&num);
	}
}


//按各种方式统计人数 
void statistical_operation(stu *head) 
{
	printf("\t输入选项(0退出):");
	int choice;
	scanf("%d",&choice);
	if(choice == 0)
	{
		return;
	}
	switch(choice)
	{
		case 1:{
			statistical_total(head);//统计总人数 
			break;
		}
		case 2:{
			statistical_dorm(head);//统计单个公寓
			break;
		}
		case 3:{
			statistical_dorm_num(head);//统计公寓宿舍
			break;
		}
		default :{
			printf("\t->输入格式有误<-\n");
			break;
		} 
	}
} 

//主程序 
int main() 
{	
	//登录 
	enter();
	system("cls");
	printf("\t登陆成功\n");
	int choice;
	while(1)
	{
		//界面 
		interface();
		stu *head;
		printf("\t输入1~7：");
		scanf("%d",&choice);
		switch(choice)
		{
			//录入学生信息 
			case 1:{
				head = creat();//创建链表
				write_file(head);//写入文件 
				break;
			}
			
			//增加学生信息 
			case 2:{
				head = write_linked();
				//添加信息 
				add(head);
				//对数据进行排序 
				sort(head);
				//将修改好的数据写入文件 
				write_file(head);
				break;
			}
			
			//按学生的学号进行删除 
			case 3:{ 
				//根据文件提取学生信息 
				head = write_linked();
				//删除查找的学号的学生 
				dele(head);
				//将修改过的数据写入文件 
				write_file(head);
				break;
			}
			
			//按学生的学号进行修改 
			case 4:{
				head = write_linked();
				//按学号修改数据 
				modify(head);
				//修改后的数据写入文件 
				write_file(head);
				break;
			}
			
			//按学生的姓名，宿舍，学号查找 
			case 5:{
				interface1();//子目录 
				 //生成链表
				head = write_linked();
				//按需求查询人数的方法 
				son_operation(head);
				break;
			}
			
			//统计，总人数，每个宿舍人数，一栋楼的人数
			case 6:{  
			   //文件生成链表 ，从文件中取出学生数据 
				head = write_linked();
				son_statistical();
				//统计人数的方法 
				statistical_operation(head); 
				break;
			}
			
			//报表 
			case 7:{
				//文件生成链表 ，从文件中取出学生数据 
				head = write_linked();
				//打印的数据表头 
				header(); 
				//排序 
				sort(head);
				//链表打印输出 
				print(head);
				printf("\t-------------------------------------------------------------------------------------------------------\n");
				break;
			}
			default :{
				printf("\t->输入有误,重新输入<-\n");
				break;
			}
		}
		printf("\t按任意键继续");
		//刷新标准输入缓冲区，把输入缓冲区里的东西丢弃
		fflush(stdin);
		getchar();
		//每次输入后清除所有显示的信息
		system("cls");
	}
}
