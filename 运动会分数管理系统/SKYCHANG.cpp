/********************************************************************************\
作者信息：
	姓名：梁子昌   学号：21251106224  班级：21计实2班  学院：信息学院
	Email:2010435481@qq.com    Tel:13071656746
版权声明：
	版权归梁子昌所有，除老师外，未经允许不得拷贝本人作业
摘要：
其他说明：
	无
模块：
	Created  on          2023/3/10 by author
	The latest update on 2023/4/28 by author
\********************************************************************************/
/************************SportsMeetingScoreStatisticsSystem****************/
//x***********************@SKYCHANG******************************************/
/***********************2023/05/28*****************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#pragma warning(disable:4996)

using namespace std;
typedef struct college
{//学院节点
	int  collegeID;        //学院编号
	char collegeName[100]; //学院名称
	int  collegeGrade;     //学院总分
	int  manGrade;         //男团体总分
	int  womGrade;         //女团体总分
	struct college* next;  //指针
} collegeNode;
typedef struct event
{//项目节点
	int    eventID;        //项目编号
	char    eventName[100];//项目名称
	int    sex;            //性别（1，男/0.女）
	int    gradeWeight;    //选择前五名(5)还是前三名(3)
	int    awardCollege[25];//获奖的学院 
	int    competeCollege;//参加该项目的学院数
	struct event* next;    //指针
} eventNode;
//打印菜单
void PrintMenu();
//检查每一次输入的数是否符合范围  
int  NumCheck(int* num, int max, int min);

//初始化信息
void InitImfomation(collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend);
//初始化学院信息(尾插法建立单链表)
void GetCollegeNode(collegeNode** Chead, collegeNode** Cend);
//初始化项目信息
void GetEventNode(eventNode** Ehead, eventNode** Eend);
//初始化项目成绩信息
void InitGrade(eventNode* Ehead, collegeNode* Ehaed, int lacation);
//添加成绩
void AddCollegeGrade(eventNode* ENode, collegeNode* Chead, int intID, int ranking);

//根据选择，调用项目或者学院删除函数
void Delete(collegeNode** Chead, eventNode** Ehead);
//删除学院节点
void  DeleteCollege(collegeNode** Chead, eventNode** Ehead);
//删除项目节点
void  DeleteEvent(collegeNode** Chead, eventNode** Ehead);
//修改获奖名次记录
void ModifyGrade(eventNode* Ehead, collegeNode* Chead);

//按 编号 或者 名称 查询 学院的情况
void Search(collegeNode* Chead, eventNode* ENode);
//显示比赛项目各学院名次情况
void PrintEvent(collegeNode* Chead, eventNode* Ehead);
//按 编号 或者 名称 查询 项目获奖情况 
void FindTop(collegeNode* Chead, eventNode* Ehead);


//排序，调用三个快速排序函数
void Sort(collegeNode** Chead);
//根学院ID升序快速排序
void CollegeIDQuickSort(collegeNode** head, collegeNode** tail);
//根据女团总分降序快速排序
void WomQuickSort(collegeNode** head, collegeNode** tail);
//根据男团总分降序快速排序
void ManQuickSort(collegeNode** head, collegeNode** tail);
//根据学院总分降序快速排序
void CollegeGradeQuickSort(collegeNode** head, collegeNode** tail);
//交换两个节点的所有值
void SwapNodeValue(collegeNode** a, collegeNode** b);
//打印排序后的结果
void GradePrint(collegeNode* Chead);

//调用CFileRead、EFileRead函数，读取已存在的信息
void Load(collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend);
//通过调用CFileWrite、EFileWrite函数，保存信息并退出
void Save(collegeNode* Chead, eventNode* Ehead);
//读取文件中学院的信息
void CFileRead(collegeNode** Chead, collegeNode** Cend);
//读取文件中项目的信息
void EFileRead(eventNode** Ehead, eventNode** Eend);
//读取文件中学院的信息
void CFileWrite(collegeNode* Chead);
//读取文件中项目的信息
void EFileWrite(eventNode* Chead);



//todo**********************全局变量****************************/
int id_event = 0;                //给学院编号赋值
int id_college = 0;              //给项目编号赋值   
int grade_3[100] = { 5,3,2 };    //给取前三名分数赋值
int grade_5[100] = { 7,5,3,2,1 };//给取前五名分数赋值
int location = 0;                //定位到需要初始化的项目节点
int collegeCount=0;              //累计学院数量 
int print_choose;                //选择打印哪一个排序后的结果
bool fileFlag = true;            //是否已经读取文件
//todo*********************************************************/


//*******************************************基本*******************************************************************/
/**********************************************************************\
函数名称:
	main
功能描述:
	定义结构题指针，调用各函数
函数参数:
	无
返回值:
	无
模块  :
	梁子昌于2023年3月10日创建本模块，
\*********************************************************************/
void main() 
{
	collegeNode* Chead = NULL;
	collegeNode* Cend = NULL; //结构体指针,头尾
	eventNode* Ehead = NULL;
	eventNode* Eend = NULL;
	int MAX = 9;
	int MIN = 1;
	while (1)
	{
		PrintMenu();
		int chooseNum = NumCheck(&chooseNum, MAX, MIN);

		switch (chooseNum)
		{
		case 1://添加学院项目
			InitImfomation(&Chead, &Cend, &Ehead, &Eend);
			// CheckIFin(Chead, Ehead);
			break;
		case 2://排序输出		
			Sort(&Chead);
			break;		
		case 3://按 编号 或者 名称 查询 学院的情况
			Search(Chead,Ehead);
			break;
		case 4:
			FindTop(Chead, Ehead);
			break;
		case 5://显示比赛项目各学院名次情况           
			PrintEvent(Chead, Ehead);
			break;
		case 6://修改获奖名次记录
			ModifyGrade(Ehead, Chead);
			break;
		case 7://删除某个学院或者项目       
			Delete(&Chead, &Ehead);
			break;
		case 8://读取存在的数据
			Load(&Chead, &Cend, &Ehead, &Eend);
			break;
		case 9://保存并退出
			Save(Chead, Ehead);
			break;

		}//switch
	}//while
}
/**********************************************************************\
函数名称:
	PrintMenu
功能描述:
   打印菜单
函数参数:
   无
返回值:
	 无
模块  :
	梁子昌于2023年3月11日创建本模块，
\*********************************************************************/
void PrintMenu()
{//打印菜单
	SetConsoleTitle("运动会分数统计系统 @SKYCHANG");
	system("mode con cols=150 lines=30");//控制台 宽度150 高度30
	cout << "\t\t===============运动会分数管理系统=============================" << endl;
	cout << "\t\t |   1.添加学院和项目                           |   三名制(1,2,3) " << endl;
	cout << "\t\t |   2.按男团体/女团体/学院总分/学院ID排序输出  |  分数--5,3,2" << endl;
	cout << "\t\t |   3.按 编号 或者 名称 查询 学院的情况        |  " << endl;
	cout << "\t\t |   4.按 编号 或者 名称 查询 项目获奖情况      |  " << endl;
	cout << "\t\t |   5.显示比赛项目各学院名次情况               |  五名制(1,2,3,4,5)" << endl;
	cout << "\t\t |   6.修改获奖名次记录                         |  分数--7,5,3,2,1 " << endl;
	cout << "\t\t |   7.删除某学院或者项目                       |  " << endl;
	cout << "\t\t |   8.读取已存在的信息                         |  " << endl;
	cout << "\t\t |   9.保存信息并退出                           |  " << endl;
	cout << "\t\t==============================================================" << endl;
	cout << "\t\t请输入你的选择（1~9）：";
}//PrintMenu
/**********************************************************************\
函数名称:
	NumCheck
功能描述:
	数字输入兼数字范围检测函数
函数参数:
   int* num, int MAX, int MIN
返回值:
	 *num
模块  :
	梁子昌于2023年3月15日创建本模块，
\*********************************************************************/
int NumCheck(int* num, int MAX, int MIN)
{/*数字输入兼数字范围检测函数*/
	while (1)
	{
		if (scanf("%d", num) != 1)
		{//使用 scanf 函数的返回值来检查输入是否成功。如果返回值不为1，则表示输入的不是整数，输入失败。
			printf("\t输入错误，请重新输入[%d~~%d]:", MIN, MAX);
			scanf("%*s");//清除错误输入
		}
		else if (*num > MAX || *num < MIN) {
			printf("\t你输入的数字不符合范围，请输入[%d~~%d]:", MIN, MAX);
		}
		else
			break;

	}
	return *num;
}
/****************************************信息输入*******************************************************************/
/**********************************************************************\
函数名称:
	InitImfomation
功能描述:
   初始化信息
函数参数:
   collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend
返回值:
	无
模块  :
	梁子昌于2023年3月16日创建本模块，
\*********************************************************************/
void InitImfomation(collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend)//指针的指针
//初始化信息
{
	int college_num;//录入学院的个数
	int event_num;  //录入项目的个数

	if (*Chead == NULL) {//第一次录入最低需要3个学院
		cout << "\t录入学院的个数（3~25）:";
		college_num = NumCheck(&college_num, 25, 3);
		collegeCount += college_num;
	}
	else {
		cout << "\t录入学院的个数（0~20）:";
		college_num = NumCheck(&college_num, 20, 0);
		collegeCount += college_num;
	}

	cout << "\t录入项目的个数（0~20）:";
	event_num = NumCheck(&event_num, 20, 0);
	system("cls");

	for (int i = 1; i <= college_num; i++)
	{//增加学院节点
		GetCollegeNode(Chead, Cend);
	}
	system("cls");
	for (int i = 1; i <= event_num; i++)
	{//增加项目节点并初始化项目的成绩
		GetEventNode(Ehead, Eend);
		InitGrade(*Ehead, *Chead, location++);
	}
}
/**********************************************************************\
函数名称:
	InitGrade
功能描述:
   初始化成绩信息
函数参数:
  eventNode* ENode, collegeNode* Chead,int location
返回值:
	无
模块  :
	梁子昌于2023年3月16日创建本模块，
\*********************************************************************/
void  InitGrade(eventNode* ENode, collegeNode* Chead, int location)
{//初始化成绩信息

	for (int j = 0; j < location; j++)
	{
		ENode = ENode->next;
	}//定位到当前输入项目节点

	collegeNode* temp = Chead;
	
	int count = 0;
	while (temp)
	{//统计学校个数
		count++;
		temp = temp->next;
	}temp = Chead;

	if (ENode->sex == 1)
		printf("\t男子%s项目参赛学院数为：", ENode->eventName);
	else
		printf("\t女子%s项目产赛学院数为：", ENode->eventName);
	NumCheck(&(ENode->competeCollege), collegeCount, 1);
	system("cls");

	while (temp)
	{
		printf("\t%d.%s\n", temp->collegeID, temp->collegeName);
		temp = temp->next;//打印出学院和对应编号方便录入
	}printf("\n");

	if (ENode->sex == 1)
		printf("\t男子%s %d个学院参赛 取前%d名计分\n\n", ENode->eventName, ENode->competeCollege, ENode->gradeWeight);
	else
		printf("\t女子%s %d个学院参赛 取前%d名计分\n\n", ENode->eventName, ENode->competeCollege, ENode->gradeWeight);

	int choice = 0;//选择的名次

	for (int i = 1; i <= ENode->competeCollege; i++)
	{//通过录入学院的名次来统计分数
		printf("\t获得第%d名的学院是<输入1-%d的编号>：", i, count);
		choice = NumCheck(&choice, count, 1);
		ENode->awardCollege[i] = choice;//录入名次
		AddCollegeGrade(ENode, Chead, choice, i);
	}
	system("pause");
}
/**********************************************************************\
函数名称:
	GetEventNode
功能描述:
   初始化项目信息(尾插法建立单链表)
函数参数:
   eventNode** Ehead, eventNode** Eend
返回值:
	无
模块  :
	梁子昌于2023年3月21日创建本模块，
\*********************************************************************/
void GetEventNode(eventNode** Ehead, eventNode** Eend)
{//初始化项目信息
	int gradeWeigth = 0;
	eventNode* ENODE = (eventNode*)malloc(sizeof(eventNode));//申请内存

	printf("\t请输入第%d个项目的名称：", ++id_event);
	ENODE->eventID = id_event;
	scanf("%s", &ENODE->eventName);
	fflush(stdin);

	while (1)
	{
		printf("\t输入的是男子项目(1)还是女子项目(0):");
		NumCheck(&(ENODE->sex), 1, 0);

		while (2)
		{
			if (ENODE->sex == 1)
				printf("\t男子%s项目", ENODE->eventName);
			else
				printf("\t女子%s项目录入", ENODE->eventName);
			cout << "前三名(3)/前五名(5)获得分数：";
			scanf("%d", &gradeWeigth);
			fflush(stdin);

			if (gradeWeigth == 5)
			{
				ENODE->gradeWeight = 5;
				break;
			}
			else if (gradeWeigth == 3)
			{
				ENODE->gradeWeight = 3;
				break;
			}
			else
				cout << "\t请输入[3,5]!" << endl;
		}//while2
		break;
	}//while1

	ENODE->next = NULL;
	if (*Ehead == NULL)
		*Ehead = ENODE;
	else
		(*Eend)->next = ENODE;//尾插法插入新节点

	*Eend = ENODE;
}
/**********************************************************************\
函数名称:
	GetCollegeNode
功能描述:
   初始化学院信息(尾插法建立单链表)
函数参数:
   collegeNode** Chead, collegeNode** Cend
返回值:
	无
模块  :
	梁子昌于2023年3月19日创建本模块，
\*********************************************************************/
void GetCollegeNode(collegeNode** Chead, collegeNode** Cend)//指针的指针
{//初始化学院信息(尾插法建立单链表)
	collegeNode* CNODE = (collegeNode*)malloc(sizeof(collegeNode));//为新节点申请空间

	printf("\t请输入第%d个学院的名称：", ++id_college);
	CNODE->collegeID = id_college;
	scanf("%s", &CNODE->collegeName);
	fflush(stdin);
	CNODE->next = NULL;
	CNODE->collegeGrade = 0;
	CNODE->manGrade = 0;
	CNODE->womGrade = 0;

	if (*Chead == NULL)
		*Chead = CNODE;//把新节点的地址给头指针，就是让头指针指向新节点（就一次，指向头节点）
	else
		(*Cend)->next = CNODE;//把新节点的地址赋值给上一个节点的指针域,是上一个节点的指针指向新节点   

	*Cend = CNODE;//把新节点的地址赋值给尾指针，使尾指针指向新的尾节点，尾插完成

}//GetCollegeNode
/**********************************************************************\
函数名称:
	AddCollegeGrade
功能描述:
   添加成绩
函数参数:
  eventNode* ENode, collegeNode* Chead,int intID,int ranking
返回值:
	无
模块  :
	梁子昌于2023年3月18日创建本模块，
\*********************************************************************/
void AddCollegeGrade(eventNode* ENode, collegeNode* Chead, int intID, int ranking)
{//添加成绩
	collegeNode* temp = Chead;
	while (temp)
	{
		if (temp->collegeID == intID)
		{//找到对应学校         
			if (ENode->sex == 1)
			{//男子
				if (ENode->gradeWeight == 3) {
					temp->manGrade += grade_3[ranking - 1];
					temp->collegeGrade += grade_3[ranking - 1];
				}
				else {
					temp->manGrade += grade_5[ranking - 1];
					temp->collegeGrade += grade_5[ranking - 1];
				}
			}

			else {//女子
				if (ENode->gradeWeight == 3)
				{
					temp->womGrade += grade_3[ranking - 1];
					temp->collegeGrade += grade_3[ranking - 1];
				}
				else
				{
					temp->womGrade += grade_5[ranking - 1];
					temp->collegeGrade += grade_5[ranking - 1];
				}
			}
		}
		temp = temp->next;
	}//while
}
/******************************************查找*********************************************************************/
/**********************************************************************\
函数名称:
	Search
功能描述:
	按 编号 或者 名称 查询 学院的情况
函数参数:
   collegeNode* Chead
返回值:
	无
模块  :
	梁子昌于2023年4月5日创建本模块，
\*********************************************************************/
void Search(collegeNode* Chead, eventNode* ENode)
{//按 编号 或者 名称 查询 学院的情况
	if (!Chead || !ENode) {
		printf("====================\n");
		printf("当前没有任何数据\n");
		printf("====================\n");
		system("pause");
		return;
	}

	int searchType = 0; // 查询类型
	int searchKey = 0;  // 查询关键字
	char name[50];
	printf("\t1.按学院编号查询\n\t2.按学院名称查询\n");
	printf("\t请选择查询方式：");
	searchType = NumCheck(&searchType, 2, 1);
	if (searchType == 1) {
		printf("\t请输入学院编号：");
		searchKey = NumCheck(&searchKey, 100, 1);
	}
	else {
		printf("\t请输入学院名称：");
		scanf("%s", name);
	}

	int eventId = 0;
	eventNode* tempE = ENode;
	printf("\t请输入要查询的比赛项目ID：");
	eventId = NumCheck(&eventId, 100, 1);

	printf("——————————————————————————————————————————————————————————————\n");
	while (tempE) 
	{
		if (tempE->eventID == eventId)//若找到了要查询的比赛项目
		{
			collegeNode* tempC = Chead;
			while (tempC)//遍历学院节点
			{
				if (searchType == 1 && tempC->collegeID == searchKey)//通过学院ID查询的方法而且找到了对应的学院
				{
					if (tempE->competeCollege > 0)//该项目有参赛项目
					{
						int i;
						for (i = 1; i <= tempE->competeCollege; i++) //遍历参赛的学院
						{
							if (tempC->collegeID == tempE->awardCollege[i])//如该学院在此项目参加了比赛
							{//输出学院的总体情况和该学院在这个项目的排名
								printf("\t学院编号(名称)\t\t团体总分\t男团总分\t女团总分\t在%s项目中排名\n",tempE->eventName);
								printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\t\t%d\n", tempC->collegeID, tempC->collegeName, tempC->collegeGrade, tempC->manGrade, tempC->womGrade, i);
								printf("——————————————————————————————————————————————————————————————\n");
								system("pause");
								return;
							}
						}
					}//如该学院没有在此项目参加了比赛，输入总体情况提示无排名
					printf("\t学院编号(名称)\t\t团体总分\t男团总分\t女团总分\t在%s项目中排名\n", tempE->eventName);
					printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\t\t无\n", tempC->collegeID, tempC->collegeName, tempC->collegeGrade, tempC->manGrade, tempC->womGrade);
					printf("——————————————————————————————————————————————————————————————\n");
					system("pause");
					return;
				}
				else if (searchType == 2 && strcmp(tempC->collegeName, name) == 0) //通过学院名称查询的方法而且找到了对应的学院
				{
					if (tempE->competeCollege > 0)//该项目有参赛项目
					{
						int i;
						for (i = 1; i <= tempE->competeCollege; i++) //遍历参赛的学院
						{//输出学院的总体情况和该学院在这个项目的排名
							if (tempC->collegeID == tempE->awardCollege[i])//如该学院在此项目参加了比赛
							{
								printf("\t学院编号(名称)\t\t团体总分\t男团总分\t女团总分\t在%s项目中排名\n", tempE->eventName);
								printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\t\t%d\n", tempC->collegeID, tempC->collegeName, tempC->collegeGrade, tempC->manGrade, tempC->womGrade, i);
								printf("——————————————————————————————————————————————————————————————\n");
								system("pause");
								return;
							}
						}
					}//如该学院没有在此项目参加了比赛，输入总体情况提示无排
					printf("\t学院编号(名称)\t\t团体总分\t男团总分\t女团总分\t在%s项目中排名\n", tempE->eventName);
					printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\t\t无\n", tempC->collegeID, tempC->collegeName, tempC->collegeGrade, tempC->manGrade, tempC->womGrade);
					printf("——————————————————————————————————————————————————————————————\n"); 
					system("pause"); 
					return;
				}
				tempC = tempC->next;
			} //while (tempC)
			printf("====================\n"); printf("未找到相关学院信息\n"); printf("====================\n");
			system("pause");
			return;
		}
		tempE = tempE->next;
	} //while(tempE)
	printf("====================\n"); printf("未找到相关比赛项目\n"); printf("====================\n"); 
	system("pause"); 
	return;
}
/**********************************************************************\
函数名称:
	PrintEvent
功能描述:
   显示比赛项目各学院名次情况
函数参数:
   collegeNode* Chead, eventNode* ENode
返回值:
	 无
模块  :
	梁子昌于2023年4月20日创建本模块，
\*********************************************************************/
void PrintEvent(collegeNode* Chead, eventNode* ENode)
{// 显示比赛项目各学院名次情况
	if (!ENode)
	{
		printf("====================\n");
		printf("当前没有任何数据\n");
		printf("====================\n");
		system("pause");
		return;
	}
	while (ENode)
	{
		printf("——————————————————————————————————————————————————————————————\n");
		printf("\t\t第%d个比赛项目：%s", ENode->eventID, ENode->eventName);

		if (ENode->sex == 1)
			printf("\t<男子>前%d名获奖\n\n", ENode->gradeWeight);
		else
			printf("\t<女子>前%d名获奖\n\n", ENode->gradeWeight);

		for (int i = 1; i <= ENode->competeCollege; i++)
		{
			collegeNode* temp = Chead;
			while (temp)
			{
				if (ENode->awardCollege[i] == temp->collegeID)
					printf("\t第%d名：%-15s", i, temp->collegeName);
				temp = temp->next;
			}	
		}	
		printf("\n");
		ENode = ENode->next;
	}
	printf("——————————————————————————————————————————————————————————————\n");
	system("pause");
}
/**********************************************************************\
函数名称:
	FindTop
功能描述:
   按项目编号或者名称查询取得前三名或者前五名的学校
函数参数:
   collegeNode* Chead, eventNode* Ehead
返回值:
	 无
模块  :
	梁子昌于2023年6月1日创建本模块，
\*********************************************************************/
void FindTop(collegeNode* Chead, eventNode* Ehead)
{//按项目编号或者名称查询取得前三名或者前五名的学校
	if (!Ehead)
	{
		printf("====================\n");
		printf("当前没有任何数据\n");
		printf("====================\n");
		system("pause");
		return;
	}
	collegeNode* tempC = Chead;
	eventNode* tempE = Ehead;

	int searchType = 0; // 查询类型
	int searchKey = 0;  // 查询关键字
	char name[50];
	printf("\t1.按项目编号查询\n\t2.按项目名称查询\n");
	printf("\t请选择查询方式：");
	searchType = NumCheck(&searchType, 2, 1);
	if (searchType == 1) {
		printf("\t请输入项目编号：");
		searchKey = NumCheck(&searchKey, 100, 1);
	}else {
		printf("\t请输入项目名称：");
		scanf("%s", name);
	}
	printf("——————————————————————————————————————————————————————————————\n");
	while (tempE)//遍历项目节点
	{
		if (searchType == 1 && tempE->eventID == searchKey)//通过Id查找而且找到指定项目
		{
			if(tempE->sex==1)
			printf("\t男子%s前%d名获奖学院：\n", tempE->eventName, tempE->gradeWeight);
			else
			printf("\t女子%s前%d名获奖学院：\n", tempE->eventName, tempE->gradeWeight);
			for (int i = 1; i <= tempE->gradeWeight; i++)//输出前五名或者前三名
			{
				tempC = Chead;//重置
				while (tempC) //遍历学院节点
				{
					if (tempC->collegeID == tempE->awardCollege[i])//ID匹配
					{
						printf("\t第%d名：%-15s", i, tempC->collegeName);
						break;
					}
					tempC = tempC->next;
				}

			}
			printf("\n——————————————————————————————————————————————————————————————\n");
			system("pause");
			return;

		}
		else if (searchType == 2 && strcmp(tempE->eventName, name) == 0)//通过name查找而且找到指定项目
		{
			if (tempE->sex == 1)
				printf("\t男子%s前%d名获奖学院：\n", tempE->eventName, tempE->gradeWeight);
			else
				printf("\t女子%s前%d名获奖学院：\n", tempE->eventName, tempE->gradeWeight);
			for (int i = 1; i <= tempE->gradeWeight; i++)//输出前五名或者前三名
			{
				tempC = Chead;//重置
				while (tempC)//遍历学院节点
				{
					if (tempC->collegeID == tempE->awardCollege[i])//ID匹配
					{
						printf("\t第%d名：%-15s", i, tempC->collegeName);
						break;
					}
					tempC = tempC->next;
				}

			}
			printf("\n——————————————————————————————————————————————————————————————\n");
			system("pause");
			return;
		}
		tempE = tempE->next;
	}
	printf("====================\n");
	printf("未找到相关比赛项目\n");
	printf("====================\n");
	system("pause");
	return;

}
/******************************************修改/删除****************************************************************/
/**********************************************************************\
函数名称:
	Delete
功能描述:
   根据选择，调用项目或者学院删除函数
函数参数:
   collegeNode** Chead, eventNode** Ehead
返回值:
	 无
模块  :
	梁子昌于2023年4月20日创建本模块，
\*********************************************************************/
void Delete(collegeNode** Chead, eventNode** Ehead)
{//根据选择，调用项目或者学院删除函数
	int deleteChoose = 0;
	printf("\t1.删除一个学院\n\t2.删除一个项目\n\t请选择：");
	deleteChoose = NumCheck(&deleteChoose, 2, 1);
	if (deleteChoose == 1)
		DeleteCollege(Chead, Ehead);//学院删除
	else 
		DeleteEvent(Chead, Ehead);//项目删除
}
/**********************************************************************\
函数名称:
	ModifyGrade
功能描述:
   修改获奖名次记录
函数参数:
   eventNode * Ehead, collegeNode * Chead
返回值:
	 无
模块  :
	梁子昌于2023年4月20日创建本模块，
\*********************************************************************/
void ModifyGrade(eventNode* Ehead, collegeNode* Chead)
{//修改获奖名次记录

	if (Chead == NULL || Ehead == NULL)
	{
		printf("====================\n");
		printf("当前没有任何数据\n");
		printf("====================\n");
		system("pause");
		return;
	}

	int eventID;   //要修改的项目编号
	int collegeID; //要修改的学院编号
	int newRanking;//新名次
	eventNode* eTemp = Ehead;
	collegeNode* cTemp = Chead;

	printf("请输入要修改的项目编号：");
	//scanf("%d", &eventID);
	NumCheck(&eventID, id_event, 1);
	printf("请输入要修改的学院编号：");
	//scanf("%d", &collegeID);
	NumCheck(&collegeID, collegeCount, 1);
	printf("请输入新的排名：");
	//scanf("%d", &newRanking);
	NumCheck(&newRanking, id_college, 1);

	while (eTemp) {//定位到指定项目节点
		if (eTemp->eventID == eventID) {
			break;
		}
		eTemp = eTemp->next;
	}

	while (cTemp) {//定位到指定学院节点
		if (cTemp->collegeID == collegeID) {
			break;
		}
		cTemp = cTemp->next;
	}

	if (eTemp && cTemp) {//获得旧的名次
		int oldRanking = 0;
		for (int i = 1; i <= eTemp->gradeWeight; i++) {
			if (eTemp->awardCollege[i] == collegeID) {
				oldRanking = i;
				break;
			}
		}

		if (oldRanking > 0)//大于零即使是取了旧的名次，所以确定该院在指定项目中获奖
		{                  //随即将旧名次的获奖记录，包括分数清零
			eTemp->awardCollege[oldRanking] = 0;

			if (eTemp->sex == 1) {
				if (eTemp->gradeWeight == 3) {
					cTemp->manGrade -= grade_3[oldRanking - 1];
					cTemp->collegeGrade -= grade_3[oldRanking - 1];
				}
				else {
					cTemp->manGrade -= grade_5[oldRanking - 1];
					cTemp->collegeGrade -= grade_5[oldRanking - 1];
				}
			}

			else {
				if (eTemp->gradeWeight == 3) {
					cTemp->womGrade -= grade_3[oldRanking - 1];
					cTemp->collegeGrade -= grade_3[oldRanking - 1];
				}
				else {
					cTemp->womGrade -= grade_5[oldRanking - 1];
					cTemp->collegeGrade -= grade_5[oldRanking - 1];
				}
			}
		}

		eTemp->awardCollege[newRanking] = collegeID;//将新的名次的位置赋值为新的学院
		//并重新计算分数
		if (eTemp->sex == 1) {
			if (eTemp->gradeWeight == 3) {
				cTemp->manGrade += grade_3[newRanking - 1];
				cTemp->collegeGrade += grade_3[newRanking - 1];
			}
			else {
				cTemp->manGrade += grade_5[newRanking - 1];
				cTemp->collegeGrade += grade_5[newRanking - 1];
			}
		}

		else {
			if (eTemp->gradeWeight == 3) {
				cTemp->womGrade += grade_3[newRanking - 1];
				cTemp->collegeGrade += grade_3[newRanking - 1];
			}
			else {
				cTemp->womGrade += grade_5[newRanking - 1];
				cTemp->collegeGrade += grade_5[newRanking - 1];
			}
		}
	}
	else {
		printf("未找到指定的项目或学院\n");
	}
}
/**********************************************************************\
函数名称:
	DeleteCollege
功能描述:
   删除学院
函数参数:
   collegeNode** Chead, eventNode** Ehead
返回值:
	 无
模块  :
	梁子昌于2023年4月19日创建本模块，
\*********************************************************************/
void  DeleteCollege(collegeNode** Chead, eventNode** Ehead)
{//删除学院
	if (*Chead == NULL || *Ehead == NULL)
	{
		printf("====================\n");
		printf("当前没有任何数据\n");
		printf("====================\n");
		system("pause");
		return;
	}
	int collegeID;
	char confirm;
	printf("请输入你要删除学院的编号：");
	scanf("%d", &collegeID);
	printf("\t\t你真的想要删除编号为%d的学院吗，注意！删除操作不可撤销！\n\t\t\t删除（y/Y）取消（n/N）:", collegeID);
	cin >> confirm;
	if (confirm == 'n' || confirm == 'N')
		return;//二次删除确定

	collegeNode* temp1 = *Chead;
	collegeNode* temp2 = NULL;

	while (temp1 != NULL && temp1->collegeID != collegeID)
	{//找到要删除的节点
		temp2 = temp1;
		temp1 = temp1->next;
	}
	if (temp1 == NULL)
	{//没有该节点，将返回
		printf("\t\t未找到编号为%d的学院\n", collegeID);
		system("pause");
		return;
	}
	if (temp2 == NULL) *Chead = temp1->next;//若要删除的是第一个节点
	else temp2->next = temp1->next;
	free(temp1);//释放节点
	collegeCount--;//x学院累计数量-1

	eventNode* etemp = *Ehead;
	collegeNode* ctemp = *Chead;

	while (etemp)
	{
		int j = 1;
		for (int i = 1; i <=25; i++)
		{//将该学院的获奖记录删除,后边排名的向前进
			if (etemp->awardCollege[i] != collegeID)
			{
				etemp->awardCollege[j] = etemp->awardCollege[i];
				j++;
			}
		}
		etemp = etemp->next;
	}

	etemp = *Ehead;

	while (ctemp) {//首先清零所有学院的得分
		ctemp->collegeGrade = 0;
		ctemp->manGrade = 0;
		ctemp->womGrade = 0;
		ctemp = ctemp->next;
	}

	while (etemp) {//然后遍历所有项目，根据修改后的获奖记录重新计算得分
		for (int i = 1; i <= etemp->gradeWeight; i++) {
			ctemp = *Chead;
			while (ctemp)
			{
				if (ctemp->collegeID == etemp->awardCollege[i])
				{

					if (etemp->sex == 1)
					{//男子项目
						if (etemp->gradeWeight == 3)
						{
							ctemp->manGrade += grade_3[i - 1];
							ctemp->collegeGrade += grade_3[i - 1];
						}

						else
						{
							ctemp->manGrade += grade_5[i - 1];
							ctemp->collegeGrade += grade_5[i - 1];
						}
					}

					else
					{//女子项目
						if (etemp->gradeWeight == 3)
						{
							ctemp->womGrade += grade_3[i - 1];
							ctemp->collegeGrade += grade_3[i - 1];
						}
						else
						{
							ctemp->womGrade += grade_5[i - 1];
							ctemp->collegeGrade += grade_5[i - 1];
						}
					}
				}
				ctemp = ctemp->next;
			}
		}
		etemp = etemp->next;
	}
}
/**********************************************************************\
函数名称:
	DeleteEvent
功能描述:
   删除项目
函数参数:
   collegeNode** Chead, eventNode** Ehead
返回值:
	 无
模块  :
	梁子昌于2023年4月18日创建本模块，
\*********************************************************************/
void  DeleteEvent(collegeNode** Chead, eventNode** Ehead)
{//删除项目
	if (*Chead == NULL || *Ehead == NULL)
	{
		printf("====================\n");
		printf("当前没有任何数据\n");
		printf("====================\n");
		system("pause");
		return;
	}
	int eventID;
	char confirm;
	printf("请输入你要删除项目的编号：");
	scanf("%d", &eventID);
	printf("\t\t你真的想要删除编号为%d的项目吗，注意！删除操作不可撤销！\n\t\t\t删除（y/Y）取消（n/N）:", eventID);
	cin >> confirm;
	if (confirm == 'n' || confirm == 'N')
		return;//二次删除确定

	eventNode* temp1 = *Ehead;
	eventNode* temp2 = NULL;
	collegeNode* temp3 = *Chead;

	while (temp1 != NULL && temp1->eventID != eventID)
	{//找到要删除的节点
		temp2 = temp1;
		temp1 = temp1->next;
	}

	if (temp1 == NULL)
	{//没有该节点，将返回
		printf("未找到编号为%d的项目\n", eventID);
		system("pause");
		return;
	}

	for (int i = 1; i <= temp1->gradeWeight; i++)
	{//清除所有学院从该项目获得的分数
		temp3 = *Chead;
		if (temp1->sex == 1)//男子项目
		{
			while (temp3)
			{
				if (temp3->collegeID == temp1->awardCollege[i])
				{
					if (temp1->gradeWeight == 3)
					{
						temp3->collegeGrade -= grade_3[i - 1];
						temp3->manGrade -= grade_3[i - 1];
					}
					else
					{
						temp3->collegeGrade -= grade_5[i - 1];
						temp3->manGrade -= grade_5[i - 1];
					}
				}
				temp3 = temp3->next;
			}
		}

		else//女子项目
		{

			while (temp3)
			{
				if (temp3->collegeID == temp1->awardCollege[i])
				{
					if (temp1->gradeWeight == 3)
					{
						temp3->collegeGrade -= grade_3[i - 1];
						temp3->womGrade -= grade_3[i - 1];
					}
					else
					{
						temp3->collegeGrade -= grade_5[i - 1];
						temp3->womGrade -= grade_5[i - 1];
					}
				}
				temp3 = temp3->next;
			}
		}
	}

	if (temp2 == NULL) *Ehead = temp1->next;//若要删除的是第一个节点
	else temp2->next = temp1->next;
	free(temp1);//释放节点 
}
/******************************************排序*******************************************************************/
/**********************************************************************\
函数名称:
	Sort
功能描述:排序函数，调用三个快速排序函数
   打印菜单
函数参数:
   collegeNode** Chead
返回值:
	 无
模块  :
	梁子昌于2023年5月11日创建本模块，
\*********************************************************************/
void Sort(collegeNode** Chead)
{//排序函数，调用三个快速排序函数
	if (*Chead == NULL) {
		printf("====================\n");
		printf("当前没有任何数据\n");
		printf("====================\n");
		system("pause");
		return;
	}
	while (1)
	{
		int choose;
	system("cls");
	cout << "\n\n\t\t 1.按 男团体总分 降序输出 " << endl;
	cout << "\t\t 2.按 女团体总分 降序输出 " << endl;
	cout << "\t\t 3.按 学院总分   降序输出 " << endl;
	cout << "\t\t 4.按 学院ID     升序输出 " << endl;
	cout << "\t\t 5.返回主菜单 " << endl;
	cout << "\t\t   请选择 ：";
	NumCheck(&choose, 5, 1);

	collegeNode* tail = *Chead; // 定义一个指针，用来找到尾节点的地址
	while (tail->next != NULL) {
		tail = tail->next;
	}

	if (choose == 1) ManQuickSort(Chead, &tail);
	if (choose == 2) WomQuickSort(Chead, &tail); // 调用WomQuickSort函数对单链表进行快速排序，并传递尾节点的地址 
	if (choose == 3) CollegeGradeQuickSort(Chead, &tail);
	if (choose == 4) CollegeIDQuickSort(Chead, &tail);
	if (choose == 5) return;
	GradePrint(*Chead); // 打印排序结果
 }

}
/**********************************************************************\
函数名称:
	WomQuickSort
功能描述:
    根据女团总分降序快速排序
函数参数:
    collegeNode** head,collegeNode** tail
返回值:
	 无
模块  :
	梁子昌于2023年5月11日创建本模块，
\*********************************************************************/
void WomQuickSort(collegeNode** head, collegeNode** tail)
{
	if (*head == *tail || *head == NULL || head == &(*tail)->next) return;//出口
	//*head == *tail，表示链表只有一个节点，不需要排序。
	//* head == NULL，表示链表为空，没有节点，不需要排序。
	//head == &(*tail)->next，表示链表已经被分割到最小的子链表，每个子链表只有一个节点或者没有节点，不需要排序。
	collegeNode* q = *head;
	collegeNode* p = *head;
	collegeNode* pre = *head;
	collegeNode* temp = *head;

	while (q != *tail) {
		q = q->next;// 对于一个链表只遍历一遍
		if (q->womGrade > (*head)->womGrade) {// 如果q的值大于基点则放在p左边
			pre = p;
			p = p->next;
			SwapNodeValue(&p, &q);
		}
	}
	SwapNodeValue(head, &p);// 将基点放在最终位置
	WomQuickSort(head, &pre);
	WomQuickSort(&p->next, tail);
}
/**********************************************************************\
函数名称:
	CollegeIDQuickSort
功能描述:
	根据学院ID升序序快速排序
函数参数:
	collegeNode** head,collegeNode** tail
返回值:
	 无
模块  :
	梁子昌于2023年5月28日创建本模块，
\*********************************************************************/
void CollegeIDQuickSort(collegeNode** head, collegeNode** tail)
{
	if (*head == *tail || *head == NULL || head == &(*tail)->next) return;//出口
	//*head == *tail，表示链表只有一个节点，不需要排序。
	//* head == NULL，表示链表为空，没有节点，不需要排序。
	//head == &(*tail)->next，表示链表已经被分割到最小的子链表，每个子链表只有一个节点或者没有节点，不需要排序。
	collegeNode* q = *head;
	collegeNode* p = *head;
	collegeNode* pre = *head;
	collegeNode* temp = *head;

	while (q != *tail) {
		q = q->next;// 对于一个链表只遍历一遍
		if (q->collegeID < (*head)->collegeID) {// 如果q的值大于基点则放在p左边
			pre = p;
			p = p->next;
			SwapNodeValue(&p, &q);
		}
	}
	SwapNodeValue(head, &p);// 将基点放在最终位置
	CollegeIDQuickSort(head, &pre);
	CollegeIDQuickSort(&p->next, tail);
}
/**********************************************************************\
函数名称:
	ManQuickSort
功能描述:
     根据男团总分降序快速排序 
函数参数:
     collegeNode** head,collegeNode** tail
返回值:
	 无
模块  :
	梁子昌于2023年5月11日创建本模块，
\*********************************************************************/
void ManQuickSort(collegeNode** head, collegeNode** tail)
{//按女团体总分快速排序
	if (*head == *tail || *head == NULL || head == &(*tail)->next) return;//出口

	collegeNode* q = *head;
	collegeNode* p = *head;
	collegeNode* pre = *head;

	while (q != *tail) {
		q = q->next;// 对于一个链表只遍历一遍
		if (q->manGrade > (*head)->manGrade) {// 如果q的值大于基点则放在p左边
			pre = p;
			p = p->next;
			SwapNodeValue(&p, &q);
		}
	}
	SwapNodeValue(head, &p);// 将基点放在最终位置
	ManQuickSort(head, &pre);
	ManQuickSort(&p->next, tail);
}
/**********************************************************************\
函数名称:
	CollegeGradeQuickSort
功能描述:
     根据学院总分降序快速排序 
函数参数:
     collegeNode** head,collegeNode** tail
返回值:
	 无
模块  :
	梁子昌于2023年5月11日创建本模块，
\*********************************************************************/
void CollegeGradeQuickSort(collegeNode** head, collegeNode** tail)
{//按学院总分快速排序
	if (*head == *tail || *head == NULL || head == &(*tail)->next) return;//出口

	collegeNode* q = *head;
	collegeNode* p = *head;
	collegeNode* pre = *head;

	while (q != *tail) {
		q = q->next;// 对于一个链表只遍历一遍
		if (q->collegeGrade > (*head)->collegeGrade) {// 如果q的值大于基点则放在p左边
			pre = p;
			p = p->next;
			SwapNodeValue(&p, &q);
		}
	}

	SwapNodeValue(head, &p);// 将基点放在最终位置
	CollegeGradeQuickSort(head, &pre);
	CollegeGradeQuickSort(&p->next, tail);
}
/**********************************************************************\
函数名称:
	SwapNodeValue
功能描述:
    交换值,不更改链表指针
函数参数:
    collegeNode** a, collegeNode** b
返回值:
	 无
模块  :
	梁子昌于2023年5月11日创建本模块，
\*********************************************************************/
void SwapNodeValue(collegeNode** a, collegeNode** b)
{//交换值,不更改链表指针

	  //暂时存放a的值
	collegeNode* temp = (collegeNode*)malloc(sizeof(collegeNode));
	temp->collegeID = (*a)->collegeID;
	strcpy(temp->collegeName, (*a)->collegeName);
	temp->collegeGrade = (*a)->collegeGrade;
	temp->manGrade = (*a)->manGrade;
	temp->womGrade = (*a)->womGrade;

	// 将节点b的数据复制到节点a
	(*a)->collegeID = (*b)->collegeID;
	strcpy((*a)->collegeName, (*b)->collegeName);
	(*a)->collegeGrade = (*b)->collegeGrade;
	(*a)->manGrade = (*b)->manGrade;
	(*a)->womGrade = (*b)->womGrade;

	// 将临时节点的数据复制到节点b
	(*b)->collegeID = temp->collegeID;
	strcpy((*b)->collegeName, temp->collegeName);
	(*b)->collegeGrade = temp->collegeGrade;
	(*b)->manGrade = temp->manGrade;
	(*b)->womGrade = temp->womGrade;

	// 释放临时节点
	free(temp);
}
/**********************************************************************\
函数名称:
	GradePrint
功能描述:
	输出排序后的结果
函数参数:
   collegeNode* Chead
返回值:
	 无
模块  :
	梁子昌于2023年4月5日创建本模块，
\*********************************************************************/
void GradePrint(collegeNode* Chead)
{//输出排序后的结果
	if (Chead == NULL)
	{
		printf("====================\n");
		printf("当前没有任何数据\n");
		printf("====================\n");
		system("pause");
		return;
	}
	system("cls");
	switch (print_choose)//print_choose已经在main中选择
	{
	case 1:
		printf("按男团体总分降序输出:\n");
		break;
	case 2:
		printf("按女团体总分降序输出：\n");
		break;
	case 3:
		printf("按学院总分降序输出：\n");
		break;
	case 4:
		printf("按学院ID升序序输出：\n");
		break;
	}

	printf("——————————————————————————————————————————————————————————————\n");
	printf("\t学校编号(名称)\t\t团体总分\t男团总分\t女团总分\n");

	while (Chead) {
		printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\n", Chead->collegeID, Chead->collegeName, Chead->collegeGrade, Chead->manGrade, Chead->womGrade);
		Chead = Chead->next;
	}
	printf("——————————————————————————————————————————————————————————————\n");
	system("pause");
}
/******************************************文件读写*****************************************************************/
/**********************************************************************\
函数名称:
	Load
功能描述:
   调用CFileRead、EFileRead函数，读取已存在的信息
函数参数:
   collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend
返回值:
	 无
模块  :
	梁子昌于2023年5月21日创建本模块，
\*********************************************************************/
void Load(collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend)
{//读取已存在的信息
	if (fileFlag) {
		CFileRead(Chead, Cend);//学院读取
		EFileRead(Ehead, Eend);//项目读取
		fileFlag = false;//读取后不能再次读取
		printf("\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t\t丨               数据已读入             丨\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");		
		system("pause");
	}
	else {
		printf("\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t\t丨               请勿重复读写             丨\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
		system("pause");
	}

}
/**********************************************************************\
函数名称:
	Save
功能描述:
   通过调用CFileWrite、EFileWrite函数，保存信息并退出
函数参数:
   collegeNode* Chead, eventNode* Ehead
返回值:
	 无
模块  :
	梁子昌于2023年5月21日创建本模块，
\*********************************************************************/
void Save(collegeNode* Chead, eventNode* Ehead)
{//保存信息并退出
	printf("\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t\t丨           确定覆盖？<Y/N>           丨\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n\t\t\t\t");
	char ch;
	cin >> ch;
	if (ch == 'Y' || ch == 'y') {
		printf("\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t\t丨           文件覆盖成功           丨\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
		CFileWrite(Chead);
		EFileWrite(Ehead);
		exit(0);
	}
	else return;
}
/**********************************************************************\
函数名称:
	CFileRead
功能描述:
   读取文件中学院的信息
函数参数:
   collegeNode** Chead, collegeNode** Cend
返回值:
	 无
模块  :
	梁子昌于2023年5月24日创建本模块，
\*********************************************************************/
void CFileRead(collegeNode** Chead, collegeNode** Cend)
{//读取文件中学院的信息
	FILE* file = NULL;
	file = fopen("Cdata.txt", "r+");

	if (!file) {
		printf("\n\tERROR:打开文件失败\n");
		exit(0);
	}
	char buf[1024];
	fgets(buf, sizeof(buf), file);//读取第一行标题，不做处理
	while (1)
	{
		char collegeName[100];
		int  collegeID;
		int  collegeGrade;
		int  manGrade;
		int  womGrade;

		if (fscanf(file, "%d %s %d %d %d", &collegeID, collegeName, &collegeGrade, &manGrade, &womGrade) != EOF)//逐行读取
		{
			collegeNode* temp = (collegeNode*)malloc(sizeof(collegeNode));//为节点申请空间

			id_college = temp->collegeID = collegeID;
			strcpy(temp->collegeName, collegeName);
			temp->collegeGrade = collegeGrade;           //为节点各项信息赋值
			temp->manGrade = manGrade;
			temp->womGrade = womGrade;
			temp->next = NULL;          
	        collegeCount++;
           
			//尾插法建立单链表
			if (*Chead == NULL) {
				*Chead = temp;
			}
			else {
				(*Cend)->next = temp;
			}
			*Cend = temp;
		}
		else break;
	}
	// id_college++;
	fclose(file);
}
/**********************************************************************\
函数名称:
	CFileWrite
功能描述:
   将学院链表打印到文件，保存信息
函数参数:
   collegeNode* Chead
返回值:
	 无
模块  :
	梁子昌于2023年5月21日创建本模块，
\*********************************************************************/
void CFileWrite(collegeNode* Chead)
{//将学院链表打印到文件，保存信息

	FILE* file = NULL;
	file = fopen("Cdata.txt", "w+");
	fprintf(file, "学院编号 学院名称        学院成绩 男团成绩 女团成绩\n");
	while (Chead)
	{
		fprintf(file, "%-8d %-15s   %-8d %-8d %-8d\n", Chead->collegeID, Chead->collegeName, Chead->collegeGrade, Chead->manGrade, Chead->womGrade);
		Chead = Chead->next;
	}
	fclose(file);
}
/**********************************************************************\
函数名称:
	EFileRead
功能描述:
   读取文件中项目的信息
函数参数:
   eventNode** Ehead, eventNode** Eend
返回值:
	 无
模块  :
	梁子昌于2023年5月28日创建本模块，
\*********************************************************************/
void EFileRead(eventNode** Ehead, eventNode** Eend)
{//读取文件中项目的信息

	ifstream file("Edata.txt");//打开文件

	if (!file.is_open()) {
		cout << "Failed to open file: Edata.txt" << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	getline(file, line); // 读取第一行标题，不做处理

	while (getline(file, line))//逐行读取文件内容
	{
		int eventID;
		int sex;
		int gradeWeight;
		int* awardCollege;
		int competeCollege;
		string eventName;

		istringstream iss(line); // 使用istringstream将一行内容转化为各个值
		iss >> eventName >> eventID >> sex >> gradeWeight >> competeCollege;

		awardCollege = new int[competeCollege];
		for (int i = 1; i <= competeCollege; i++)
			iss >> awardCollege[i];//循环读取接下来的内容

		//给节点的各项值赋值
		eventNode* temp = (eventNode*)malloc(sizeof(eventNode));
		strcpy(temp->eventName, eventName.c_str());//将String转化为char[]
		memcpy(temp->awardCollege, awardCollege, sizeof(awardCollege) * competeCollege);
		temp->gradeWeight = gradeWeight;
		id_event = temp->eventID = eventID;
		temp->competeCollege = competeCollege;
		temp->sex = sex;
		temp->next = NULL;
		//id_event++;

		//尾插法建立单链表
		if (*Ehead == NULL)
			*Ehead = temp;
		else
			(*Eend)->next = temp;
		*Eend = temp;
	}
	file.close();
}
/**********************************************************************\
函数名称:
	EFileWrite
功能描述:
	将项目链表打印到文件，保存信息
函数参数:
   无
返回值:
	 无
模块  :
	梁子昌于2023年5月21日创建本模块，
\*********************************************************************/
void EFileWrite(eventNode* Ehead)
{//将项目链表打印到文件，保存信息

	FILE* file = NULL;
	file = fopen("Edata.txt", "w+");
	fprintf(file, "项目名称       项目编号 性别 前几名   参赛学院数量  参赛学院编号(名次)\n");//第一行打印标题

	while (Ehead)//先写单独数据，再写数组数据
	{
		fprintf(file, "%-12s   %-8d %-4d %-4d    %-4d          ", Ehead->eventName, Ehead->eventID, Ehead->sex, Ehead->gradeWeight, Ehead->competeCollege);
		for (int i = 1; i <= Ehead->competeCollege; i++)
			fprintf(file, " %d", Ehead->awardCollege[i]);
		fprintf(file, "\n");//输入完一个项目的信息就换行
		Ehead = Ehead->next;
	}
	fclose(file);
}
