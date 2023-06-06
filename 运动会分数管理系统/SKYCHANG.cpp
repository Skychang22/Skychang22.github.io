/********************************************************************************\
������Ϣ��
	���������Ӳ�   ѧ�ţ�21251106224  �༶��21��ʵ2��  ѧԺ����ϢѧԺ
	Email:2010435481@qq.com    Tel:13071656746
��Ȩ������
	��Ȩ�����Ӳ����У�����ʦ�⣬δ�������ÿ���������ҵ
ժҪ��
����˵����
	��
ģ�飺
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
{//ѧԺ�ڵ�
	int  collegeID;        //ѧԺ���
	char collegeName[100]; //ѧԺ����
	int  collegeGrade;     //ѧԺ�ܷ�
	int  manGrade;         //�������ܷ�
	int  womGrade;         //Ů�����ܷ�
	struct college* next;  //ָ��
} collegeNode;
typedef struct event
{//��Ŀ�ڵ�
	int    eventID;        //��Ŀ���
	char    eventName[100];//��Ŀ����
	int    sex;            //�Ա�1����/0.Ů��
	int    gradeWeight;    //ѡ��ǰ����(5)����ǰ����(3)
	int    awardCollege[25];//�񽱵�ѧԺ 
	int    competeCollege;//�μӸ���Ŀ��ѧԺ��
	struct event* next;    //ָ��
} eventNode;
//��ӡ�˵�
void PrintMenu();
//���ÿһ����������Ƿ���Ϸ�Χ  
int  NumCheck(int* num, int max, int min);

//��ʼ����Ϣ
void InitImfomation(collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend);
//��ʼ��ѧԺ��Ϣ(β�巨����������)
void GetCollegeNode(collegeNode** Chead, collegeNode** Cend);
//��ʼ����Ŀ��Ϣ
void GetEventNode(eventNode** Ehead, eventNode** Eend);
//��ʼ����Ŀ�ɼ���Ϣ
void InitGrade(eventNode* Ehead, collegeNode* Ehaed, int lacation);
//��ӳɼ�
void AddCollegeGrade(eventNode* ENode, collegeNode* Chead, int intID, int ranking);

//����ѡ�񣬵�����Ŀ����ѧԺɾ������
void Delete(collegeNode** Chead, eventNode** Ehead);
//ɾ��ѧԺ�ڵ�
void  DeleteCollege(collegeNode** Chead, eventNode** Ehead);
//ɾ����Ŀ�ڵ�
void  DeleteEvent(collegeNode** Chead, eventNode** Ehead);
//�޸Ļ����μ�¼
void ModifyGrade(eventNode* Ehead, collegeNode* Chead);

//�� ��� ���� ���� ��ѯ ѧԺ�����
void Search(collegeNode* Chead, eventNode* ENode);
//��ʾ������Ŀ��ѧԺ�������
void PrintEvent(collegeNode* Chead, eventNode* Ehead);
//�� ��� ���� ���� ��ѯ ��Ŀ����� 
void FindTop(collegeNode* Chead, eventNode* Ehead);


//���򣬵�����������������
void Sort(collegeNode** Chead);
//��ѧԺID�����������
void CollegeIDQuickSort(collegeNode** head, collegeNode** tail);
//����Ů���ֽܷ����������
void WomQuickSort(collegeNode** head, collegeNode** tail);
//���������ֽܷ����������
void ManQuickSort(collegeNode** head, collegeNode** tail);
//����ѧԺ�ֽܷ����������
void CollegeGradeQuickSort(collegeNode** head, collegeNode** tail);
//���������ڵ������ֵ
void SwapNodeValue(collegeNode** a, collegeNode** b);
//��ӡ�����Ľ��
void GradePrint(collegeNode* Chead);

//����CFileRead��EFileRead��������ȡ�Ѵ��ڵ���Ϣ
void Load(collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend);
//ͨ������CFileWrite��EFileWrite������������Ϣ���˳�
void Save(collegeNode* Chead, eventNode* Ehead);
//��ȡ�ļ���ѧԺ����Ϣ
void CFileRead(collegeNode** Chead, collegeNode** Cend);
//��ȡ�ļ�����Ŀ����Ϣ
void EFileRead(eventNode** Ehead, eventNode** Eend);
//��ȡ�ļ���ѧԺ����Ϣ
void CFileWrite(collegeNode* Chead);
//��ȡ�ļ�����Ŀ����Ϣ
void EFileWrite(eventNode* Chead);



//todo**********************ȫ�ֱ���****************************/
int id_event = 0;                //��ѧԺ��Ÿ�ֵ
int id_college = 0;              //����Ŀ��Ÿ�ֵ   
int grade_3[100] = { 5,3,2 };    //��ȡǰ����������ֵ
int grade_5[100] = { 7,5,3,2,1 };//��ȡǰ����������ֵ
int location = 0;                //��λ����Ҫ��ʼ������Ŀ�ڵ�
int collegeCount=0;              //�ۼ�ѧԺ���� 
int print_choose;                //ѡ���ӡ��һ�������Ľ��
bool fileFlag = true;            //�Ƿ��Ѿ���ȡ�ļ�
//todo*********************************************************/


//*******************************************����*******************************************************************/
/**********************************************************************\
��������:
	main
��������:
	����ṹ��ָ�룬���ø�����
��������:
	��
����ֵ:
	��
ģ��  :
	���Ӳ���2023��3��10�մ�����ģ�飬
\*********************************************************************/
void main() 
{
	collegeNode* Chead = NULL;
	collegeNode* Cend = NULL; //�ṹ��ָ��,ͷβ
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
		case 1://���ѧԺ��Ŀ
			InitImfomation(&Chead, &Cend, &Ehead, &Eend);
			// CheckIFin(Chead, Ehead);
			break;
		case 2://�������		
			Sort(&Chead);
			break;		
		case 3://�� ��� ���� ���� ��ѯ ѧԺ�����
			Search(Chead,Ehead);
			break;
		case 4:
			FindTop(Chead, Ehead);
			break;
		case 5://��ʾ������Ŀ��ѧԺ�������           
			PrintEvent(Chead, Ehead);
			break;
		case 6://�޸Ļ����μ�¼
			ModifyGrade(Ehead, Chead);
			break;
		case 7://ɾ��ĳ��ѧԺ������Ŀ       
			Delete(&Chead, &Ehead);
			break;
		case 8://��ȡ���ڵ�����
			Load(&Chead, &Cend, &Ehead, &Eend);
			break;
		case 9://���沢�˳�
			Save(Chead, Ehead);
			break;

		}//switch
	}//while
}
/**********************************************************************\
��������:
	PrintMenu
��������:
   ��ӡ�˵�
��������:
   ��
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��3��11�մ�����ģ�飬
\*********************************************************************/
void PrintMenu()
{//��ӡ�˵�
	SetConsoleTitle("�˶������ͳ��ϵͳ @SKYCHANG");
	system("mode con cols=150 lines=30");//����̨ ���150 �߶�30
	cout << "\t\t===============�˶����������ϵͳ=============================" << endl;
	cout << "\t\t |   1.���ѧԺ����Ŀ                           |   ������(1,2,3) " << endl;
	cout << "\t\t |   2.��������/Ů����/ѧԺ�ܷ�/ѧԺID�������  |  ����--5,3,2" << endl;
	cout << "\t\t |   3.�� ��� ���� ���� ��ѯ ѧԺ�����        |  " << endl;
	cout << "\t\t |   4.�� ��� ���� ���� ��ѯ ��Ŀ�����      |  " << endl;
	cout << "\t\t |   5.��ʾ������Ŀ��ѧԺ�������               |  ������(1,2,3,4,5)" << endl;
	cout << "\t\t |   6.�޸Ļ����μ�¼                         |  ����--7,5,3,2,1 " << endl;
	cout << "\t\t |   7.ɾ��ĳѧԺ������Ŀ                       |  " << endl;
	cout << "\t\t |   8.��ȡ�Ѵ��ڵ���Ϣ                         |  " << endl;
	cout << "\t\t |   9.������Ϣ���˳�                           |  " << endl;
	cout << "\t\t==============================================================" << endl;
	cout << "\t\t���������ѡ��1~9����";
}//PrintMenu
/**********************************************************************\
��������:
	NumCheck
��������:
	������������ַ�Χ��⺯��
��������:
   int* num, int MAX, int MIN
����ֵ:
	 *num
ģ��  :
	���Ӳ���2023��3��15�մ�����ģ�飬
\*********************************************************************/
int NumCheck(int* num, int MAX, int MIN)
{/*������������ַ�Χ��⺯��*/
	while (1)
	{
		if (scanf("%d", num) != 1)
		{//ʹ�� scanf �����ķ���ֵ����������Ƿ�ɹ����������ֵ��Ϊ1�����ʾ����Ĳ�������������ʧ�ܡ�
			printf("\t�����������������[%d~~%d]:", MIN, MAX);
			scanf("%*s");//�����������
		}
		else if (*num > MAX || *num < MIN) {
			printf("\t����������ֲ����Ϸ�Χ��������[%d~~%d]:", MIN, MAX);
		}
		else
			break;

	}
	return *num;
}
/****************************************��Ϣ����*******************************************************************/
/**********************************************************************\
��������:
	InitImfomation
��������:
   ��ʼ����Ϣ
��������:
   collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend
����ֵ:
	��
ģ��  :
	���Ӳ���2023��3��16�մ�����ģ�飬
\*********************************************************************/
void InitImfomation(collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend)//ָ���ָ��
//��ʼ����Ϣ
{
	int college_num;//¼��ѧԺ�ĸ���
	int event_num;  //¼����Ŀ�ĸ���

	if (*Chead == NULL) {//��һ��¼�������Ҫ3��ѧԺ
		cout << "\t¼��ѧԺ�ĸ�����3~25��:";
		college_num = NumCheck(&college_num, 25, 3);
		collegeCount += college_num;
	}
	else {
		cout << "\t¼��ѧԺ�ĸ�����0~20��:";
		college_num = NumCheck(&college_num, 20, 0);
		collegeCount += college_num;
	}

	cout << "\t¼����Ŀ�ĸ�����0~20��:";
	event_num = NumCheck(&event_num, 20, 0);
	system("cls");

	for (int i = 1; i <= college_num; i++)
	{//����ѧԺ�ڵ�
		GetCollegeNode(Chead, Cend);
	}
	system("cls");
	for (int i = 1; i <= event_num; i++)
	{//������Ŀ�ڵ㲢��ʼ����Ŀ�ĳɼ�
		GetEventNode(Ehead, Eend);
		InitGrade(*Ehead, *Chead, location++);
	}
}
/**********************************************************************\
��������:
	InitGrade
��������:
   ��ʼ���ɼ���Ϣ
��������:
  eventNode* ENode, collegeNode* Chead,int location
����ֵ:
	��
ģ��  :
	���Ӳ���2023��3��16�մ�����ģ�飬
\*********************************************************************/
void  InitGrade(eventNode* ENode, collegeNode* Chead, int location)
{//��ʼ���ɼ���Ϣ

	for (int j = 0; j < location; j++)
	{
		ENode = ENode->next;
	}//��λ����ǰ������Ŀ�ڵ�

	collegeNode* temp = Chead;
	
	int count = 0;
	while (temp)
	{//ͳ��ѧУ����
		count++;
		temp = temp->next;
	}temp = Chead;

	if (ENode->sex == 1)
		printf("\t����%s��Ŀ����ѧԺ��Ϊ��", ENode->eventName);
	else
		printf("\tŮ��%s��Ŀ����ѧԺ��Ϊ��", ENode->eventName);
	NumCheck(&(ENode->competeCollege), collegeCount, 1);
	system("cls");

	while (temp)
	{
		printf("\t%d.%s\n", temp->collegeID, temp->collegeName);
		temp = temp->next;//��ӡ��ѧԺ�Ͷ�Ӧ��ŷ���¼��
	}printf("\n");

	if (ENode->sex == 1)
		printf("\t����%s %d��ѧԺ���� ȡǰ%d���Ʒ�\n\n", ENode->eventName, ENode->competeCollege, ENode->gradeWeight);
	else
		printf("\tŮ��%s %d��ѧԺ���� ȡǰ%d���Ʒ�\n\n", ENode->eventName, ENode->competeCollege, ENode->gradeWeight);

	int choice = 0;//ѡ�������

	for (int i = 1; i <= ENode->competeCollege; i++)
	{//ͨ��¼��ѧԺ��������ͳ�Ʒ���
		printf("\t��õ�%d����ѧԺ��<����1-%d�ı��>��", i, count);
		choice = NumCheck(&choice, count, 1);
		ENode->awardCollege[i] = choice;//¼������
		AddCollegeGrade(ENode, Chead, choice, i);
	}
	system("pause");
}
/**********************************************************************\
��������:
	GetEventNode
��������:
   ��ʼ����Ŀ��Ϣ(β�巨����������)
��������:
   eventNode** Ehead, eventNode** Eend
����ֵ:
	��
ģ��  :
	���Ӳ���2023��3��21�մ�����ģ�飬
\*********************************************************************/
void GetEventNode(eventNode** Ehead, eventNode** Eend)
{//��ʼ����Ŀ��Ϣ
	int gradeWeigth = 0;
	eventNode* ENODE = (eventNode*)malloc(sizeof(eventNode));//�����ڴ�

	printf("\t�������%d����Ŀ�����ƣ�", ++id_event);
	ENODE->eventID = id_event;
	scanf("%s", &ENODE->eventName);
	fflush(stdin);

	while (1)
	{
		printf("\t�������������Ŀ(1)����Ů����Ŀ(0):");
		NumCheck(&(ENODE->sex), 1, 0);

		while (2)
		{
			if (ENODE->sex == 1)
				printf("\t����%s��Ŀ", ENODE->eventName);
			else
				printf("\tŮ��%s��Ŀ¼��", ENODE->eventName);
			cout << "ǰ����(3)/ǰ����(5)��÷�����";
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
				cout << "\t������[3,5]!" << endl;
		}//while2
		break;
	}//while1

	ENODE->next = NULL;
	if (*Ehead == NULL)
		*Ehead = ENODE;
	else
		(*Eend)->next = ENODE;//β�巨�����½ڵ�

	*Eend = ENODE;
}
/**********************************************************************\
��������:
	GetCollegeNode
��������:
   ��ʼ��ѧԺ��Ϣ(β�巨����������)
��������:
   collegeNode** Chead, collegeNode** Cend
����ֵ:
	��
ģ��  :
	���Ӳ���2023��3��19�մ�����ģ�飬
\*********************************************************************/
void GetCollegeNode(collegeNode** Chead, collegeNode** Cend)//ָ���ָ��
{//��ʼ��ѧԺ��Ϣ(β�巨����������)
	collegeNode* CNODE = (collegeNode*)malloc(sizeof(collegeNode));//Ϊ�½ڵ�����ռ�

	printf("\t�������%d��ѧԺ�����ƣ�", ++id_college);
	CNODE->collegeID = id_college;
	scanf("%s", &CNODE->collegeName);
	fflush(stdin);
	CNODE->next = NULL;
	CNODE->collegeGrade = 0;
	CNODE->manGrade = 0;
	CNODE->womGrade = 0;

	if (*Chead == NULL)
		*Chead = CNODE;//���½ڵ�ĵ�ַ��ͷָ�룬������ͷָ��ָ���½ڵ㣨��һ�Σ�ָ��ͷ�ڵ㣩
	else
		(*Cend)->next = CNODE;//���½ڵ�ĵ�ַ��ֵ����һ���ڵ��ָ����,����һ���ڵ��ָ��ָ���½ڵ�   

	*Cend = CNODE;//���½ڵ�ĵ�ַ��ֵ��βָ�룬ʹβָ��ָ���µ�β�ڵ㣬β�����

}//GetCollegeNode
/**********************************************************************\
��������:
	AddCollegeGrade
��������:
   ��ӳɼ�
��������:
  eventNode* ENode, collegeNode* Chead,int intID,int ranking
����ֵ:
	��
ģ��  :
	���Ӳ���2023��3��18�մ�����ģ�飬
\*********************************************************************/
void AddCollegeGrade(eventNode* ENode, collegeNode* Chead, int intID, int ranking)
{//��ӳɼ�
	collegeNode* temp = Chead;
	while (temp)
	{
		if (temp->collegeID == intID)
		{//�ҵ���ӦѧУ         
			if (ENode->sex == 1)
			{//����
				if (ENode->gradeWeight == 3) {
					temp->manGrade += grade_3[ranking - 1];
					temp->collegeGrade += grade_3[ranking - 1];
				}
				else {
					temp->manGrade += grade_5[ranking - 1];
					temp->collegeGrade += grade_5[ranking - 1];
				}
			}

			else {//Ů��
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
/******************************************����*********************************************************************/
/**********************************************************************\
��������:
	Search
��������:
	�� ��� ���� ���� ��ѯ ѧԺ�����
��������:
   collegeNode* Chead
����ֵ:
	��
ģ��  :
	���Ӳ���2023��4��5�մ�����ģ�飬
\*********************************************************************/
void Search(collegeNode* Chead, eventNode* ENode)
{//�� ��� ���� ���� ��ѯ ѧԺ�����
	if (!Chead || !ENode) {
		printf("====================\n");
		printf("��ǰû���κ�����\n");
		printf("====================\n");
		system("pause");
		return;
	}

	int searchType = 0; // ��ѯ����
	int searchKey = 0;  // ��ѯ�ؼ���
	char name[50];
	printf("\t1.��ѧԺ��Ų�ѯ\n\t2.��ѧԺ���Ʋ�ѯ\n");
	printf("\t��ѡ���ѯ��ʽ��");
	searchType = NumCheck(&searchType, 2, 1);
	if (searchType == 1) {
		printf("\t������ѧԺ��ţ�");
		searchKey = NumCheck(&searchKey, 100, 1);
	}
	else {
		printf("\t������ѧԺ���ƣ�");
		scanf("%s", name);
	}

	int eventId = 0;
	eventNode* tempE = ENode;
	printf("\t������Ҫ��ѯ�ı�����ĿID��");
	eventId = NumCheck(&eventId, 100, 1);

	printf("����������������������������������������������������������������������������������������������������������������������������\n");
	while (tempE) 
	{
		if (tempE->eventID == eventId)//���ҵ���Ҫ��ѯ�ı�����Ŀ
		{
			collegeNode* tempC = Chead;
			while (tempC)//����ѧԺ�ڵ�
			{
				if (searchType == 1 && tempC->collegeID == searchKey)//ͨ��ѧԺID��ѯ�ķ��������ҵ��˶�Ӧ��ѧԺ
				{
					if (tempE->competeCollege > 0)//����Ŀ�в�����Ŀ
					{
						int i;
						for (i = 1; i <= tempE->competeCollege; i++) //����������ѧԺ
						{
							if (tempC->collegeID == tempE->awardCollege[i])//���ѧԺ�ڴ���Ŀ�μ��˱���
							{//���ѧԺ����������͸�ѧԺ�������Ŀ������
								printf("\tѧԺ���(����)\t\t�����ܷ�\t�����ܷ�\tŮ���ܷ�\t��%s��Ŀ������\n",tempE->eventName);
								printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\t\t%d\n", tempC->collegeID, tempC->collegeName, tempC->collegeGrade, tempC->manGrade, tempC->womGrade, i);
								printf("����������������������������������������������������������������������������������������������������������������������������\n");
								system("pause");
								return;
							}
						}
					}//���ѧԺû���ڴ���Ŀ�μ��˱������������������ʾ������
					printf("\tѧԺ���(����)\t\t�����ܷ�\t�����ܷ�\tŮ���ܷ�\t��%s��Ŀ������\n", tempE->eventName);
					printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\t\t��\n", tempC->collegeID, tempC->collegeName, tempC->collegeGrade, tempC->manGrade, tempC->womGrade);
					printf("����������������������������������������������������������������������������������������������������������������������������\n");
					system("pause");
					return;
				}
				else if (searchType == 2 && strcmp(tempC->collegeName, name) == 0) //ͨ��ѧԺ���Ʋ�ѯ�ķ��������ҵ��˶�Ӧ��ѧԺ
				{
					if (tempE->competeCollege > 0)//����Ŀ�в�����Ŀ
					{
						int i;
						for (i = 1; i <= tempE->competeCollege; i++) //����������ѧԺ
						{//���ѧԺ����������͸�ѧԺ�������Ŀ������
							if (tempC->collegeID == tempE->awardCollege[i])//���ѧԺ�ڴ���Ŀ�μ��˱���
							{
								printf("\tѧԺ���(����)\t\t�����ܷ�\t�����ܷ�\tŮ���ܷ�\t��%s��Ŀ������\n", tempE->eventName);
								printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\t\t%d\n", tempC->collegeID, tempC->collegeName, tempC->collegeGrade, tempC->manGrade, tempC->womGrade, i);
								printf("����������������������������������������������������������������������������������������������������������������������������\n");
								system("pause");
								return;
							}
						}
					}//���ѧԺû���ڴ���Ŀ�μ��˱������������������ʾ����
					printf("\tѧԺ���(����)\t\t�����ܷ�\t�����ܷ�\tŮ���ܷ�\t��%s��Ŀ������\n", tempE->eventName);
					printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\t\t��\n", tempC->collegeID, tempC->collegeName, tempC->collegeGrade, tempC->manGrade, tempC->womGrade);
					printf("����������������������������������������������������������������������������������������������������������������������������\n"); 
					system("pause"); 
					return;
				}
				tempC = tempC->next;
			} //while (tempC)
			printf("====================\n"); printf("δ�ҵ����ѧԺ��Ϣ\n"); printf("====================\n");
			system("pause");
			return;
		}
		tempE = tempE->next;
	} //while(tempE)
	printf("====================\n"); printf("δ�ҵ���ر�����Ŀ\n"); printf("====================\n"); 
	system("pause"); 
	return;
}
/**********************************************************************\
��������:
	PrintEvent
��������:
   ��ʾ������Ŀ��ѧԺ�������
��������:
   collegeNode* Chead, eventNode* ENode
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��4��20�մ�����ģ�飬
\*********************************************************************/
void PrintEvent(collegeNode* Chead, eventNode* ENode)
{// ��ʾ������Ŀ��ѧԺ�������
	if (!ENode)
	{
		printf("====================\n");
		printf("��ǰû���κ�����\n");
		printf("====================\n");
		system("pause");
		return;
	}
	while (ENode)
	{
		printf("����������������������������������������������������������������������������������������������������������������������������\n");
		printf("\t\t��%d��������Ŀ��%s", ENode->eventID, ENode->eventName);

		if (ENode->sex == 1)
			printf("\t<����>ǰ%d����\n\n", ENode->gradeWeight);
		else
			printf("\t<Ů��>ǰ%d����\n\n", ENode->gradeWeight);

		for (int i = 1; i <= ENode->competeCollege; i++)
		{
			collegeNode* temp = Chead;
			while (temp)
			{
				if (ENode->awardCollege[i] == temp->collegeID)
					printf("\t��%d����%-15s", i, temp->collegeName);
				temp = temp->next;
			}	
		}	
		printf("\n");
		ENode = ENode->next;
	}
	printf("����������������������������������������������������������������������������������������������������������������������������\n");
	system("pause");
}
/**********************************************************************\
��������:
	FindTop
��������:
   ����Ŀ��Ż������Ʋ�ѯȡ��ǰ��������ǰ������ѧУ
��������:
   collegeNode* Chead, eventNode* Ehead
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��6��1�մ�����ģ�飬
\*********************************************************************/
void FindTop(collegeNode* Chead, eventNode* Ehead)
{//����Ŀ��Ż������Ʋ�ѯȡ��ǰ��������ǰ������ѧУ
	if (!Ehead)
	{
		printf("====================\n");
		printf("��ǰû���κ�����\n");
		printf("====================\n");
		system("pause");
		return;
	}
	collegeNode* tempC = Chead;
	eventNode* tempE = Ehead;

	int searchType = 0; // ��ѯ����
	int searchKey = 0;  // ��ѯ�ؼ���
	char name[50];
	printf("\t1.����Ŀ��Ų�ѯ\n\t2.����Ŀ���Ʋ�ѯ\n");
	printf("\t��ѡ���ѯ��ʽ��");
	searchType = NumCheck(&searchType, 2, 1);
	if (searchType == 1) {
		printf("\t��������Ŀ��ţ�");
		searchKey = NumCheck(&searchKey, 100, 1);
	}else {
		printf("\t��������Ŀ���ƣ�");
		scanf("%s", name);
	}
	printf("����������������������������������������������������������������������������������������������������������������������������\n");
	while (tempE)//������Ŀ�ڵ�
	{
		if (searchType == 1 && tempE->eventID == searchKey)//ͨ��Id���Ҷ����ҵ�ָ����Ŀ
		{
			if(tempE->sex==1)
			printf("\t����%sǰ%d����ѧԺ��\n", tempE->eventName, tempE->gradeWeight);
			else
			printf("\tŮ��%sǰ%d����ѧԺ��\n", tempE->eventName, tempE->gradeWeight);
			for (int i = 1; i <= tempE->gradeWeight; i++)//���ǰ��������ǰ����
			{
				tempC = Chead;//����
				while (tempC) //����ѧԺ�ڵ�
				{
					if (tempC->collegeID == tempE->awardCollege[i])//IDƥ��
					{
						printf("\t��%d����%-15s", i, tempC->collegeName);
						break;
					}
					tempC = tempC->next;
				}

			}
			printf("\n����������������������������������������������������������������������������������������������������������������������������\n");
			system("pause");
			return;

		}
		else if (searchType == 2 && strcmp(tempE->eventName, name) == 0)//ͨ��name���Ҷ����ҵ�ָ����Ŀ
		{
			if (tempE->sex == 1)
				printf("\t����%sǰ%d����ѧԺ��\n", tempE->eventName, tempE->gradeWeight);
			else
				printf("\tŮ��%sǰ%d����ѧԺ��\n", tempE->eventName, tempE->gradeWeight);
			for (int i = 1; i <= tempE->gradeWeight; i++)//���ǰ��������ǰ����
			{
				tempC = Chead;//����
				while (tempC)//����ѧԺ�ڵ�
				{
					if (tempC->collegeID == tempE->awardCollege[i])//IDƥ��
					{
						printf("\t��%d����%-15s", i, tempC->collegeName);
						break;
					}
					tempC = tempC->next;
				}

			}
			printf("\n����������������������������������������������������������������������������������������������������������������������������\n");
			system("pause");
			return;
		}
		tempE = tempE->next;
	}
	printf("====================\n");
	printf("δ�ҵ���ر�����Ŀ\n");
	printf("====================\n");
	system("pause");
	return;

}
/******************************************�޸�/ɾ��****************************************************************/
/**********************************************************************\
��������:
	Delete
��������:
   ����ѡ�񣬵�����Ŀ����ѧԺɾ������
��������:
   collegeNode** Chead, eventNode** Ehead
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��4��20�մ�����ģ�飬
\*********************************************************************/
void Delete(collegeNode** Chead, eventNode** Ehead)
{//����ѡ�񣬵�����Ŀ����ѧԺɾ������
	int deleteChoose = 0;
	printf("\t1.ɾ��һ��ѧԺ\n\t2.ɾ��һ����Ŀ\n\t��ѡ��");
	deleteChoose = NumCheck(&deleteChoose, 2, 1);
	if (deleteChoose == 1)
		DeleteCollege(Chead, Ehead);//ѧԺɾ��
	else 
		DeleteEvent(Chead, Ehead);//��Ŀɾ��
}
/**********************************************************************\
��������:
	ModifyGrade
��������:
   �޸Ļ����μ�¼
��������:
   eventNode * Ehead, collegeNode * Chead
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��4��20�մ�����ģ�飬
\*********************************************************************/
void ModifyGrade(eventNode* Ehead, collegeNode* Chead)
{//�޸Ļ����μ�¼

	if (Chead == NULL || Ehead == NULL)
	{
		printf("====================\n");
		printf("��ǰû���κ�����\n");
		printf("====================\n");
		system("pause");
		return;
	}

	int eventID;   //Ҫ�޸ĵ���Ŀ���
	int collegeID; //Ҫ�޸ĵ�ѧԺ���
	int newRanking;//������
	eventNode* eTemp = Ehead;
	collegeNode* cTemp = Chead;

	printf("������Ҫ�޸ĵ���Ŀ��ţ�");
	//scanf("%d", &eventID);
	NumCheck(&eventID, id_event, 1);
	printf("������Ҫ�޸ĵ�ѧԺ��ţ�");
	//scanf("%d", &collegeID);
	NumCheck(&collegeID, collegeCount, 1);
	printf("�������µ�������");
	//scanf("%d", &newRanking);
	NumCheck(&newRanking, id_college, 1);

	while (eTemp) {//��λ��ָ����Ŀ�ڵ�
		if (eTemp->eventID == eventID) {
			break;
		}
		eTemp = eTemp->next;
	}

	while (cTemp) {//��λ��ָ��ѧԺ�ڵ�
		if (cTemp->collegeID == collegeID) {
			break;
		}
		cTemp = cTemp->next;
	}

	if (eTemp && cTemp) {//��þɵ�����
		int oldRanking = 0;
		for (int i = 1; i <= eTemp->gradeWeight; i++) {
			if (eTemp->awardCollege[i] == collegeID) {
				oldRanking = i;
				break;
			}
		}

		if (oldRanking > 0)//�����㼴ʹ��ȡ�˾ɵ����Σ�����ȷ����Ժ��ָ����Ŀ�л�
		{                  //�漴�������εĻ񽱼�¼��������������
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

		eTemp->awardCollege[newRanking] = collegeID;//���µ����ε�λ�ø�ֵΪ�µ�ѧԺ
		//�����¼������
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
		printf("δ�ҵ�ָ������Ŀ��ѧԺ\n");
	}
}
/**********************************************************************\
��������:
	DeleteCollege
��������:
   ɾ��ѧԺ
��������:
   collegeNode** Chead, eventNode** Ehead
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��4��19�մ�����ģ�飬
\*********************************************************************/
void  DeleteCollege(collegeNode** Chead, eventNode** Ehead)
{//ɾ��ѧԺ
	if (*Chead == NULL || *Ehead == NULL)
	{
		printf("====================\n");
		printf("��ǰû���κ�����\n");
		printf("====================\n");
		system("pause");
		return;
	}
	int collegeID;
	char confirm;
	printf("��������Ҫɾ��ѧԺ�ı�ţ�");
	scanf("%d", &collegeID);
	printf("\t\t�������Ҫɾ�����Ϊ%d��ѧԺ��ע�⣡ɾ���������ɳ�����\n\t\t\tɾ����y/Y��ȡ����n/N��:", collegeID);
	cin >> confirm;
	if (confirm == 'n' || confirm == 'N')
		return;//����ɾ��ȷ��

	collegeNode* temp1 = *Chead;
	collegeNode* temp2 = NULL;

	while (temp1 != NULL && temp1->collegeID != collegeID)
	{//�ҵ�Ҫɾ���Ľڵ�
		temp2 = temp1;
		temp1 = temp1->next;
	}
	if (temp1 == NULL)
	{//û�иýڵ㣬������
		printf("\t\tδ�ҵ����Ϊ%d��ѧԺ\n", collegeID);
		system("pause");
		return;
	}
	if (temp2 == NULL) *Chead = temp1->next;//��Ҫɾ�����ǵ�һ���ڵ�
	else temp2->next = temp1->next;
	free(temp1);//�ͷŽڵ�
	collegeCount--;//xѧԺ�ۼ�����-1

	eventNode* etemp = *Ehead;
	collegeNode* ctemp = *Chead;

	while (etemp)
	{
		int j = 1;
		for (int i = 1; i <=25; i++)
		{//����ѧԺ�Ļ񽱼�¼ɾ��,�����������ǰ��
			if (etemp->awardCollege[i] != collegeID)
			{
				etemp->awardCollege[j] = etemp->awardCollege[i];
				j++;
			}
		}
		etemp = etemp->next;
	}

	etemp = *Ehead;

	while (ctemp) {//������������ѧԺ�ĵ÷�
		ctemp->collegeGrade = 0;
		ctemp->manGrade = 0;
		ctemp->womGrade = 0;
		ctemp = ctemp->next;
	}

	while (etemp) {//Ȼ�����������Ŀ�������޸ĺ�Ļ񽱼�¼���¼���÷�
		for (int i = 1; i <= etemp->gradeWeight; i++) {
			ctemp = *Chead;
			while (ctemp)
			{
				if (ctemp->collegeID == etemp->awardCollege[i])
				{

					if (etemp->sex == 1)
					{//������Ŀ
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
					{//Ů����Ŀ
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
��������:
	DeleteEvent
��������:
   ɾ����Ŀ
��������:
   collegeNode** Chead, eventNode** Ehead
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��4��18�մ�����ģ�飬
\*********************************************************************/
void  DeleteEvent(collegeNode** Chead, eventNode** Ehead)
{//ɾ����Ŀ
	if (*Chead == NULL || *Ehead == NULL)
	{
		printf("====================\n");
		printf("��ǰû���κ�����\n");
		printf("====================\n");
		system("pause");
		return;
	}
	int eventID;
	char confirm;
	printf("��������Ҫɾ����Ŀ�ı�ţ�");
	scanf("%d", &eventID);
	printf("\t\t�������Ҫɾ�����Ϊ%d����Ŀ��ע�⣡ɾ���������ɳ�����\n\t\t\tɾ����y/Y��ȡ����n/N��:", eventID);
	cin >> confirm;
	if (confirm == 'n' || confirm == 'N')
		return;//����ɾ��ȷ��

	eventNode* temp1 = *Ehead;
	eventNode* temp2 = NULL;
	collegeNode* temp3 = *Chead;

	while (temp1 != NULL && temp1->eventID != eventID)
	{//�ҵ�Ҫɾ���Ľڵ�
		temp2 = temp1;
		temp1 = temp1->next;
	}

	if (temp1 == NULL)
	{//û�иýڵ㣬������
		printf("δ�ҵ����Ϊ%d����Ŀ\n", eventID);
		system("pause");
		return;
	}

	for (int i = 1; i <= temp1->gradeWeight; i++)
	{//�������ѧԺ�Ӹ���Ŀ��õķ���
		temp3 = *Chead;
		if (temp1->sex == 1)//������Ŀ
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

		else//Ů����Ŀ
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

	if (temp2 == NULL) *Ehead = temp1->next;//��Ҫɾ�����ǵ�һ���ڵ�
	else temp2->next = temp1->next;
	free(temp1);//�ͷŽڵ� 
}
/******************************************����*******************************************************************/
/**********************************************************************\
��������:
	Sort
��������:��������������������������
   ��ӡ�˵�
��������:
   collegeNode** Chead
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��11�մ�����ģ�飬
\*********************************************************************/
void Sort(collegeNode** Chead)
{//��������������������������
	if (*Chead == NULL) {
		printf("====================\n");
		printf("��ǰû���κ�����\n");
		printf("====================\n");
		system("pause");
		return;
	}
	while (1)
	{
		int choose;
	system("cls");
	cout << "\n\n\t\t 1.�� �������ܷ� ������� " << endl;
	cout << "\t\t 2.�� Ů�����ܷ� ������� " << endl;
	cout << "\t\t 3.�� ѧԺ�ܷ�   ������� " << endl;
	cout << "\t\t 4.�� ѧԺID     ������� " << endl;
	cout << "\t\t 5.�������˵� " << endl;
	cout << "\t\t   ��ѡ�� ��";
	NumCheck(&choose, 5, 1);

	collegeNode* tail = *Chead; // ����һ��ָ�룬�����ҵ�β�ڵ�ĵ�ַ
	while (tail->next != NULL) {
		tail = tail->next;
	}

	if (choose == 1) ManQuickSort(Chead, &tail);
	if (choose == 2) WomQuickSort(Chead, &tail); // ����WomQuickSort�����Ե�������п������򣬲�����β�ڵ�ĵ�ַ 
	if (choose == 3) CollegeGradeQuickSort(Chead, &tail);
	if (choose == 4) CollegeIDQuickSort(Chead, &tail);
	if (choose == 5) return;
	GradePrint(*Chead); // ��ӡ������
 }

}
/**********************************************************************\
��������:
	WomQuickSort
��������:
    ����Ů���ֽܷ����������
��������:
    collegeNode** head,collegeNode** tail
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��11�մ�����ģ�飬
\*********************************************************************/
void WomQuickSort(collegeNode** head, collegeNode** tail)
{
	if (*head == *tail || *head == NULL || head == &(*tail)->next) return;//����
	//*head == *tail����ʾ����ֻ��һ���ڵ㣬����Ҫ����
	//* head == NULL����ʾ����Ϊ�գ�û�нڵ㣬����Ҫ����
	//head == &(*tail)->next����ʾ�����Ѿ����ָ��С��������ÿ��������ֻ��һ���ڵ����û�нڵ㣬����Ҫ����
	collegeNode* q = *head;
	collegeNode* p = *head;
	collegeNode* pre = *head;
	collegeNode* temp = *head;

	while (q != *tail) {
		q = q->next;// ����һ������ֻ����һ��
		if (q->womGrade > (*head)->womGrade) {// ���q��ֵ���ڻ��������p���
			pre = p;
			p = p->next;
			SwapNodeValue(&p, &q);
		}
	}
	SwapNodeValue(head, &p);// �������������λ��
	WomQuickSort(head, &pre);
	WomQuickSort(&p->next, tail);
}
/**********************************************************************\
��������:
	CollegeIDQuickSort
��������:
	����ѧԺID�������������
��������:
	collegeNode** head,collegeNode** tail
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��28�մ�����ģ�飬
\*********************************************************************/
void CollegeIDQuickSort(collegeNode** head, collegeNode** tail)
{
	if (*head == *tail || *head == NULL || head == &(*tail)->next) return;//����
	//*head == *tail����ʾ����ֻ��һ���ڵ㣬����Ҫ����
	//* head == NULL����ʾ����Ϊ�գ�û�нڵ㣬����Ҫ����
	//head == &(*tail)->next����ʾ�����Ѿ����ָ��С��������ÿ��������ֻ��һ���ڵ����û�нڵ㣬����Ҫ����
	collegeNode* q = *head;
	collegeNode* p = *head;
	collegeNode* pre = *head;
	collegeNode* temp = *head;

	while (q != *tail) {
		q = q->next;// ����һ������ֻ����һ��
		if (q->collegeID < (*head)->collegeID) {// ���q��ֵ���ڻ��������p���
			pre = p;
			p = p->next;
			SwapNodeValue(&p, &q);
		}
	}
	SwapNodeValue(head, &p);// �������������λ��
	CollegeIDQuickSort(head, &pre);
	CollegeIDQuickSort(&p->next, tail);
}
/**********************************************************************\
��������:
	ManQuickSort
��������:
     ���������ֽܷ���������� 
��������:
     collegeNode** head,collegeNode** tail
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��11�մ�����ģ�飬
\*********************************************************************/
void ManQuickSort(collegeNode** head, collegeNode** tail)
{//��Ů�����ֿܷ�������
	if (*head == *tail || *head == NULL || head == &(*tail)->next) return;//����

	collegeNode* q = *head;
	collegeNode* p = *head;
	collegeNode* pre = *head;

	while (q != *tail) {
		q = q->next;// ����һ������ֻ����һ��
		if (q->manGrade > (*head)->manGrade) {// ���q��ֵ���ڻ��������p���
			pre = p;
			p = p->next;
			SwapNodeValue(&p, &q);
		}
	}
	SwapNodeValue(head, &p);// �������������λ��
	ManQuickSort(head, &pre);
	ManQuickSort(&p->next, tail);
}
/**********************************************************************\
��������:
	CollegeGradeQuickSort
��������:
     ����ѧԺ�ֽܷ���������� 
��������:
     collegeNode** head,collegeNode** tail
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��11�մ�����ģ�飬
\*********************************************************************/
void CollegeGradeQuickSort(collegeNode** head, collegeNode** tail)
{//��ѧԺ�ֿܷ�������
	if (*head == *tail || *head == NULL || head == &(*tail)->next) return;//����

	collegeNode* q = *head;
	collegeNode* p = *head;
	collegeNode* pre = *head;

	while (q != *tail) {
		q = q->next;// ����һ������ֻ����һ��
		if (q->collegeGrade > (*head)->collegeGrade) {// ���q��ֵ���ڻ��������p���
			pre = p;
			p = p->next;
			SwapNodeValue(&p, &q);
		}
	}

	SwapNodeValue(head, &p);// �������������λ��
	CollegeGradeQuickSort(head, &pre);
	CollegeGradeQuickSort(&p->next, tail);
}
/**********************************************************************\
��������:
	SwapNodeValue
��������:
    ����ֵ,����������ָ��
��������:
    collegeNode** a, collegeNode** b
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��11�մ�����ģ�飬
\*********************************************************************/
void SwapNodeValue(collegeNode** a, collegeNode** b)
{//����ֵ,����������ָ��

	  //��ʱ���a��ֵ
	collegeNode* temp = (collegeNode*)malloc(sizeof(collegeNode));
	temp->collegeID = (*a)->collegeID;
	strcpy(temp->collegeName, (*a)->collegeName);
	temp->collegeGrade = (*a)->collegeGrade;
	temp->manGrade = (*a)->manGrade;
	temp->womGrade = (*a)->womGrade;

	// ���ڵ�b�����ݸ��Ƶ��ڵ�a
	(*a)->collegeID = (*b)->collegeID;
	strcpy((*a)->collegeName, (*b)->collegeName);
	(*a)->collegeGrade = (*b)->collegeGrade;
	(*a)->manGrade = (*b)->manGrade;
	(*a)->womGrade = (*b)->womGrade;

	// ����ʱ�ڵ�����ݸ��Ƶ��ڵ�b
	(*b)->collegeID = temp->collegeID;
	strcpy((*b)->collegeName, temp->collegeName);
	(*b)->collegeGrade = temp->collegeGrade;
	(*b)->manGrade = temp->manGrade;
	(*b)->womGrade = temp->womGrade;

	// �ͷ���ʱ�ڵ�
	free(temp);
}
/**********************************************************************\
��������:
	GradePrint
��������:
	��������Ľ��
��������:
   collegeNode* Chead
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��4��5�մ�����ģ�飬
\*********************************************************************/
void GradePrint(collegeNode* Chead)
{//��������Ľ��
	if (Chead == NULL)
	{
		printf("====================\n");
		printf("��ǰû���κ�����\n");
		printf("====================\n");
		system("pause");
		return;
	}
	system("cls");
	switch (print_choose)//print_choose�Ѿ���main��ѡ��
	{
	case 1:
		printf("���������ֽܷ������:\n");
		break;
	case 2:
		printf("��Ů�����ֽܷ��������\n");
		break;
	case 3:
		printf("��ѧԺ�ֽܷ��������\n");
		break;
	case 4:
		printf("��ѧԺID�����������\n");
		break;
	}

	printf("����������������������������������������������������������������������������������������������������������������������������\n");
	printf("\tѧУ���(����)\t\t�����ܷ�\t�����ܷ�\tŮ���ܷ�\n");

	while (Chead) {
		printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\n", Chead->collegeID, Chead->collegeName, Chead->collegeGrade, Chead->manGrade, Chead->womGrade);
		Chead = Chead->next;
	}
	printf("����������������������������������������������������������������������������������������������������������������������������\n");
	system("pause");
}
/******************************************�ļ���д*****************************************************************/
/**********************************************************************\
��������:
	Load
��������:
   ����CFileRead��EFileRead��������ȡ�Ѵ��ڵ���Ϣ
��������:
   collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��21�մ�����ģ�飬
\*********************************************************************/
void Load(collegeNode** Chead, collegeNode** Cend, eventNode** Ehead, eventNode** Eend)
{//��ȡ�Ѵ��ڵ���Ϣ
	if (fileFlag) {
		CFileRead(Chead, Cend);//ѧԺ��ȡ
		EFileRead(Ehead, Eend);//��Ŀ��ȡ
		fileFlag = false;//��ȡ�����ٴζ�ȡ
		printf("\n\t\t������������������������������������������\n\t\tح               �����Ѷ���             ح\n\t\t������������������������������������������\n\n");		
		system("pause");
	}
	else {
		printf("\n\t\t��������������������������������������������\n\t\tح               �����ظ���д             ح\n\t\t��������������������������������������������\n\n");
		system("pause");
	}

}
/**********************************************************************\
��������:
	Save
��������:
   ͨ������CFileWrite��EFileWrite������������Ϣ���˳�
��������:
   collegeNode* Chead, eventNode* Ehead
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��21�մ�����ģ�飬
\*********************************************************************/
void Save(collegeNode* Chead, eventNode* Ehead)
{//������Ϣ���˳�
	printf("\n\t\t������������������������������������������\n\t\tح           ȷ�����ǣ�<Y/N>           ح\n\t\t������������������������������������������\n\n\t\t\t\t");
	char ch;
	cin >> ch;
	if (ch == 'Y' || ch == 'y') {
		printf("\n\t\t������������������������������������������\n\t\tح           �ļ����ǳɹ�           ح\n\t\t������������������������������������������\n\n");
		CFileWrite(Chead);
		EFileWrite(Ehead);
		exit(0);
	}
	else return;
}
/**********************************************************************\
��������:
	CFileRead
��������:
   ��ȡ�ļ���ѧԺ����Ϣ
��������:
   collegeNode** Chead, collegeNode** Cend
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��24�մ�����ģ�飬
\*********************************************************************/
void CFileRead(collegeNode** Chead, collegeNode** Cend)
{//��ȡ�ļ���ѧԺ����Ϣ
	FILE* file = NULL;
	file = fopen("Cdata.txt", "r+");

	if (!file) {
		printf("\n\tERROR:���ļ�ʧ��\n");
		exit(0);
	}
	char buf[1024];
	fgets(buf, sizeof(buf), file);//��ȡ��һ�б��⣬��������
	while (1)
	{
		char collegeName[100];
		int  collegeID;
		int  collegeGrade;
		int  manGrade;
		int  womGrade;

		if (fscanf(file, "%d %s %d %d %d", &collegeID, collegeName, &collegeGrade, &manGrade, &womGrade) != EOF)//���ж�ȡ
		{
			collegeNode* temp = (collegeNode*)malloc(sizeof(collegeNode));//Ϊ�ڵ�����ռ�

			id_college = temp->collegeID = collegeID;
			strcpy(temp->collegeName, collegeName);
			temp->collegeGrade = collegeGrade;           //Ϊ�ڵ������Ϣ��ֵ
			temp->manGrade = manGrade;
			temp->womGrade = womGrade;
			temp->next = NULL;          
	        collegeCount++;
           
			//β�巨����������
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
��������:
	CFileWrite
��������:
   ��ѧԺ�����ӡ���ļ���������Ϣ
��������:
   collegeNode* Chead
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��21�մ�����ģ�飬
\*********************************************************************/
void CFileWrite(collegeNode* Chead)
{//��ѧԺ�����ӡ���ļ���������Ϣ

	FILE* file = NULL;
	file = fopen("Cdata.txt", "w+");
	fprintf(file, "ѧԺ��� ѧԺ����        ѧԺ�ɼ� ���ųɼ� Ů�ųɼ�\n");
	while (Chead)
	{
		fprintf(file, "%-8d %-15s   %-8d %-8d %-8d\n", Chead->collegeID, Chead->collegeName, Chead->collegeGrade, Chead->manGrade, Chead->womGrade);
		Chead = Chead->next;
	}
	fclose(file);
}
/**********************************************************************\
��������:
	EFileRead
��������:
   ��ȡ�ļ�����Ŀ����Ϣ
��������:
   eventNode** Ehead, eventNode** Eend
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��28�մ�����ģ�飬
\*********************************************************************/
void EFileRead(eventNode** Ehead, eventNode** Eend)
{//��ȡ�ļ�����Ŀ����Ϣ

	ifstream file("Edata.txt");//���ļ�

	if (!file.is_open()) {
		cout << "Failed to open file: Edata.txt" << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	getline(file, line); // ��ȡ��һ�б��⣬��������

	while (getline(file, line))//���ж�ȡ�ļ�����
	{
		int eventID;
		int sex;
		int gradeWeight;
		int* awardCollege;
		int competeCollege;
		string eventName;

		istringstream iss(line); // ʹ��istringstream��һ������ת��Ϊ����ֵ
		iss >> eventName >> eventID >> sex >> gradeWeight >> competeCollege;

		awardCollege = new int[competeCollege];
		for (int i = 1; i <= competeCollege; i++)
			iss >> awardCollege[i];//ѭ����ȡ������������

		//���ڵ�ĸ���ֵ��ֵ
		eventNode* temp = (eventNode*)malloc(sizeof(eventNode));
		strcpy(temp->eventName, eventName.c_str());//��Stringת��Ϊchar[]
		memcpy(temp->awardCollege, awardCollege, sizeof(awardCollege) * competeCollege);
		temp->gradeWeight = gradeWeight;
		id_event = temp->eventID = eventID;
		temp->competeCollege = competeCollege;
		temp->sex = sex;
		temp->next = NULL;
		//id_event++;

		//β�巨����������
		if (*Ehead == NULL)
			*Ehead = temp;
		else
			(*Eend)->next = temp;
		*Eend = temp;
	}
	file.close();
}
/**********************************************************************\
��������:
	EFileWrite
��������:
	����Ŀ�����ӡ���ļ���������Ϣ
��������:
   ��
����ֵ:
	 ��
ģ��  :
	���Ӳ���2023��5��21�մ�����ģ�飬
\*********************************************************************/
void EFileWrite(eventNode* Ehead)
{//����Ŀ�����ӡ���ļ���������Ϣ

	FILE* file = NULL;
	file = fopen("Edata.txt", "w+");
	fprintf(file, "��Ŀ����       ��Ŀ��� �Ա� ǰ����   ����ѧԺ����  ����ѧԺ���(����)\n");//��һ�д�ӡ����

	while (Ehead)//��д�������ݣ���д��������
	{
		fprintf(file, "%-12s   %-8d %-4d %-4d    %-4d          ", Ehead->eventName, Ehead->eventID, Ehead->sex, Ehead->gradeWeight, Ehead->competeCollege);
		for (int i = 1; i <= Ehead->competeCollege; i++)
			fprintf(file, " %d", Ehead->awardCollege[i]);
		fprintf(file, "\n");//������һ����Ŀ����Ϣ�ͻ���
		Ehead = Ehead->next;
	}
	fclose(file);
}
