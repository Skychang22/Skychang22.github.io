
//! ， 红色注释
//? , 蓝色注释
////, 灰色删除线注释
// todo橘红色注释
// *, 浅绿色注释




#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
/*
　　参加运动会有n个学校，学校编号为1⋯⋯n。比赛分成m个男子项目，和w个女子项目。项目编号为男子1⋯⋯m，女子m+1⋯⋯m+w。不同的项目取前五名或前三名积分；取前五名的积分分别为：7、5、3、2、1，前三名的积分分别为：5、3、2；哪些取前五名或前三名由学生自己设定。（m<=20,n<=20）
　　【基本要求】
　　（1）可以输入各个项目的前三名或前五名的成绩；
　　（2）能统计各学校总分，
　　（3）可以按学校编号或名称、学校总分、男女团体总分排序输出；
　　（4）可以按学校编号查询学校某个项目的情况；可以按项目编号查询取得前三或前五名的学校。
　　（5）存储结构自选，但要求运动会的相关数据存入并能随时查询
　　（6）规定：输入数据形式和范围：可以输入学校的名称，运动项目的名称
　　（7）输出形式：有中文提示，各学校分数为整形
    （8）界面要求：有合理的提示，每个功能可以设立菜单，根据提示，可以完成相关的功能要求。
*/

typedef struct school {
    int schoolId;            //学校编号
    char* schoolName;       //学校名称
    int schoolGrade;         //学校总分
    int manGrade;            //男团分数
    int womanGrade;          //女团分数
    struct school* next;
}Node;

typedef struct program {
    int programId;           //项目编号
    char* programName;      //项目名称
    int sex;                //性别
    int power;               //积分方式
    int school[100];                //获奖学校
    struct program* next;
}PNode;
/*
功能函数
*/
char* GetString();      //读入变长字符串
char Getchar();         //清空stdin
/*
链表操作
*/
void GetSchoolNode(Node** pHead, Node** pEnd);
void GetProgramNode(PNode** pHead, PNode** pEnd);

void PrintMenu1();       //主菜单
/*
学校 项目 信息初始化
*/
void IntiInfo(Node** pHead, Node** pEnd, PNode** ppHead, PNode** ppEnd);
/*
数字范围检验
*/
int CheckNum(int* num, int max, int min);
/*
初始化项目成绩信息
*/
void InitGrade1(PNode* pnode, Node* pHead, int i);
/*
修改学校结点
*/
void AddSchoolGrade1(Node* pHead, PNode* pNode, int id, int sort);
/*
按照学校编号输出分数
*/
void PrintGrade(Node* pHead);
/*
打印项目以及取得名词的学校
*/
void PrintProgram(Node* pHead, PNode* pNode);
/*
排序输出成绩
*/
void ManGradeSort(Node** pHead);
void WomanGradeSort(Node** pHead);
void SchoolGradeSort(Node** pHead);
void Sort(Node** pHead);

/*
学校文件读写
*/
void SFileRead(Node** pHead, Node** pEnd);
void SFileWrite(Node* pHead);
/*
项目文件读写
*/
void PFileRead(PNode** ppHead, PNode** ppEnd);
void PFileWrite(PNode* ppHead);
void Fun_7(PNode** ppHead, PNode** ppEnd, Node** pHead, Node** pEnd);
void Fun_8(Node* pHead, PNode* ppHead);

int grade_31[3] = { 5, 3, 2 };
int grade_51[5] = { 7, 5, 3, 2, 1 };
int g_menu;
 int id_s = 1;
int id_p = 1;
int numss = 0;
char strs[1024];
bool flag = true;
const char path_s[] = "Info_s.txt";
const char path_p[] = "Info_p.txt";

int main1()
{
    Node* pHead = NULL;
    Node* pEnd = NULL;
    PNode* ppHead = NULL;
    PNode* ppEnd = NULL;

    while (1) {
        PrintMenu1();

        int n = CheckNum(&n, 8, 1);
        switch (n) {
        case 1: IntiInfo(&pHead, &pEnd, &ppHead, &ppEnd);
            break;
        case 2:  g_menu = 1;
            ManGradeSort(&pHead);
            break;
        case 3: g_menu = 2;
            WomanGradeSort(&pHead);
            break;
        case 4: g_menu = 3;
            SchoolGradeSort(&pHead);
            break;
        case 5: g_menu = 4;
            Sort(&pHead);
            break;
        case 6: PrintProgram(pHead, ppHead);
            break;
        case 7: Fun_7(&ppHead, &ppEnd, &pHead, &pEnd);
            break;
        case 8: Fun_8(pHead, ppHead);
            break;
        }
        printf("\t\t");
        system("pause");
    }
    return 0;
}

char Getchar() {
    char ch = getchar();
    fflush(stdin);
    return ch;
}

char* GetString() {
    int size = 5, count = 0;
    char* str = (char*)malloc(sizeof(char) * size);
    char ch;
    while ((ch = getchar()) != '\n') {
        str[count] = ch;
        if ((size - 2 == count) && (str[count] != '\0')) {
            str[size - 1] = '\0';
            size += 5;
            char* str1 = (char*)malloc(sizeof(char) * size);
            strcpy(str1, str);
            free(str);
            str = str1;
        }
        count++;
    }
    str[count] = '\0';
    return str;
}

void GetSchoolNode(Node** pHead, Node** pEnd) {
    Node* node = (Node*)malloc(sizeof(Node));
    printf("\t输入第%d个学校的名称: ", id_s);
    node->schoolId = id_s++;
    while (1) {
        node->schoolName = GetString();
        if (node->schoolName[0] == '\0') {
            printf("\t输入为空，请重新输入:");
        }
        else {
            break;
        }
    }
    node->manGrade = 0;
    node->womanGrade = 0;
    node->schoolGrade = 0;
    node->next = NULL;
    if (*pHead == NULL) {
        *pHead = node;
    }
    else {
        (*pEnd)->next = node;
    }
    *pEnd = node;
}

void GetProgramNode(PNode** ppHead, PNode** ppEnd) {
    PNode* node = (PNode*)malloc(sizeof(PNode));
    printf("\t输入第%d个项目的名称: ", id_p);
    node->programId = id_p++;
    while (1) {
        node->programName = GetString();
        if (node->programName[0] == '\0') {
            printf("\t输入为空，请重新输入:");
        }
        else {
            break;
        }
    }
    printf("\t男子（1）/女子（0）: ");
    node->sex = CheckNum(&(node->sex), 1, 0);
    while (1) {
        if (node->sex == 0) printf("\t女子%s", node->programName);
        else printf("\t男子%s", node->programName);
        printf("项目录入: 3:前三名 5:前五名: ");
        int power;
        fflush(stdin);
        scanf_s("%d", &power);
        fflush(stdin);
        if (power == 3) {
            node->power = power;
            break;
        }
        else if (power == 5) {
            node->power = power;
            break;
        }
        else {
            printf("于{3，5}中选择！");
        }
    }
    node->next = NULL;
    if (*ppHead == NULL) {
        *ppHead = node;
    }
    else {
        (*ppEnd)->next = node;
    }
    *ppEnd = node;
}

int CheckNum(int* num, int max, int min) {
    do
    {
        *num = min - 1;
        scanf_s("%d", num);
        while (getchar() != '\n');
        if (*num > max || *num < min)
            printf("输入有误,请重新输入[%d--%d]:", min, max);
    } while (*num > max || *num < min);
    return *num;
}

void IntiInfo(Node** pHead, Node** pEnd, PNode** ppHead, PNode** ppEnd) {
    int num_s, num_p;
    if (*pHead == NULL) {
        printf("\t录入学校个数<5 - 20>\n\t: ");
        num_s = CheckNum(&num_s, 20, 5);
    }
    else {
        printf("\t录入学校个数<0 - 20>\n\t: ");
        num_s = CheckNum(&num_s, 20, 0);
    }
    printf("\t录入项目个数<1 - 20>\n\t: ");
    num_p = CheckNum(&num_p, 20, 1);
    system("cls");
    for (int i = 0; i < num_s; i++) {
        GetSchoolNode(pHead, pEnd);
    }
    system("cls");
    for (int i = 0; i < num_p; i++) {
        GetProgramNode(ppHead, ppEnd);
        InitGrade1(*ppHead, *pHead, numss++);
        system("cls");
    }
}

void InitGrade1(PNode* pNode, Node* pHead, int i) {
    for (int j = 0; j < i; j++) {
        pNode = pNode->next;
    }//移动到当前项目节点

    int count = 0;//学校个数
    Node* mark = pHead;
    while (mark) {
        count++;
        mark = mark->next;
    }
    mark = pHead;
    system("cls");

    while (mark) 
    {
        printf("%d.%-20s", mark->schoolId, mark->schoolName);
        mark = mark->next;
    }
    printf("\n\n获得  %s前%d名<填写编号 1 - %d>:\n", pNode->programName, pNode->power, count);
    int num = 1;

    for (int i = 0; i < pNode->power; i++) 
    {
        printf("第%d名的学校: ", i + 1);
        int choose = CheckNum(&choose, count, 1);
        pNode->school[i] = choose;
        AddSchoolGrade1(pHead, pNode, choose, num);
        num++;
    }

}

void AddSchoolGrade1(Node* pHead, PNode* pNode, int id, int sort) {
    Node* mark = pHead;
    while (mark) {
        if (mark->schoolId == id) {
            if (pNode->sex == 1 && pNode->power == 3) {
                mark->manGrade += grade_31[sort - 1];
                mark->schoolGrade += grade_31[sort - 1];
            }
            if (pNode->sex == 1 && pNode->power == 5) {
                mark->manGrade += grade_51[sort - 1];
                mark->schoolGrade += grade_51[sort - 1];
            }
            if (pNode->sex == 0 && pNode->power == 3) {
                mark->womanGrade += grade_31[sort - 1];
                mark->schoolGrade += grade_31[sort - 1];
            }
            if (pNode->sex == 0 && pNode->power == 5) {
                mark->womanGrade += grade_51[sort - 1];
                mark->schoolGrade += grade_51[sort - 1];
            }
        }
        mark = mark->next;
    }
}

void PrintMenu1() {
    system("mode con cols=135 lines=30");//控制台 宽度135 高度20
    printf("\t\t\t\t运动会分数统计\n");
    printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
    printf("\t丨 1.添加 学校  项目                丨三名制(1,2,3)\n");
    printf("\t丨 2.按 男团体 总分排序输出         丨  \n");
    printf("\t丨 3.按 女团体 总分排序输出         丨  分数--5,3,2\n");
    printf("\t丨 4.按 学校   总分排序输出         丨\n");
    printf("\t丨 5.按 编号或名称 查询学校情况     丨五名制(1,2,3,4,5)  \n");
    printf("\t丨 6.显示比赛项目各学校名次情况     丨\n");
    printf("\t丨 7.读取已存在信息                 丨  分数--7,5,3,2,1\n");
    printf("\t丨 8.保存信息并退出                 丨\n");
    printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
    printf("输入您的选择(1-8):");
}

void PrintGrade(Node* pHead) {
    if (pHead == NULL) {
        printf("\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
        printf("\t\t当前未录入数据  请使用 <1>功能录入 或 <7>功能读取\n");
        printf("\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
        return;
    }
    system("cls");
    switch (g_menu) {
    case 1:  printf("\t\t按照男团降序排列：\n");
        break;
    case 2:  printf("\t\t按照女团降序排列：\n");
        break;
    case 3:  printf("\t\t按照学校总分降序排列：\n");
        break;
    case 4:  printf("\t\t按照学校编号降序排序：\n");
        break;
    }

    printf("——————————————————————————————————————————————————————————————\n");
    printf("\t学校编号(名称)\t\t团体总分\t男团总分\t女团总分\n");
    while (pHead) {
        printf("\t%d.%-15s\t%-3d\t\t%-3d\t\t%-3d\n", pHead->schoolId, pHead->schoolName, pHead->schoolGrade, pHead->manGrade, pHead->womanGrade);
        pHead = pHead->next;
    }
    printf("——————————————————————————————————————————————————————————————\n");
}

void PrintProgram(Node* pHead, PNode* pNode) {
    if (!pNode) {
        printf("\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
        printf("\t\t当前未录入数据  请使用 <1>功能录入 或 <7>功能读取\n");
        printf("\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
    }
    while (pNode) {
        printf("——————————————————————————————————————————————————————————————\n");
        printf("\t\t第%d个比赛项目:%s", pNode->programId, pNode->programName);
        if (pNode->sex == 1) printf("\t<男子> 只录入前%d名\n\n", pNode->power);
        else printf("\t<女子> 只录入前%d名\n\n", pNode->power);
        for (int i = 0; i < pNode->power; i++) {
            Node* mark = pHead;
            while (mark) {
                if (pNode->school[i] == mark->schoolId) {
                    printf("\t第%d名:%-15s", i + 1, mark->schoolName);
                }
                mark = mark->next;
            }
        }
        printf("\n");
        pNode = pNode->next;
    }
}

void ManGradeSort(Node** pHead) {
    if (*pHead == NULL) {
        printf("\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
        printf("\t\t当前未录入数据  请使用 <1>功能录入 或 <7>功能读取\n");
        printf("\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
        return;
    }
    Node* mark = *pHead;
    int count = 0;
    while (mark) {
        count++;
        mark = mark->next;
    }
    Node* pri, * mid, * tai, * p;
    while (count--)
    {
        mid = (*pHead)->next;
        if ((*pHead)->manGrade < (*pHead)->next->manGrade)
        {
            (*pHead)->next = mid->next;
            mid->next = *pHead;
            *pHead = mid;
        }
        pri = *pHead;
        mid = (*pHead)->next;
        tai = mid->next;
        while (mid->next != NULL)
        {
            if (mid->manGrade < tai->manGrade)
            {
                pri->next = mid->next;
                mid->next = tai->next;
                tai->next = mid;
            }
            pri = pri->next;
            mid = pri->next;
            tai = mid->next;
        }
    }
    PrintGrade(*pHead);
}

void WomanGradeSort(Node** pHead) {
    if (*pHead == NULL) {
        printf("\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
        printf("\t\t当前未录入数据  请使用 <1>功能录入 或 <7>功能读取\n");
        printf("\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
        return;
    }
    Node* mark = *pHead;
    int count = 0;
    while (mark) {
        count++;
        mark = mark->next;
    }
    Node* pri, * mid, * tai, * p;
    while (count--)
    {
        mid = (*pHead)->next;
        if ((*pHead)->womanGrade < (*pHead)->next->womanGrade)
        {
            (*pHead)->next = mid->next;
            mid->next = *pHead;
            *pHead = mid;
        }
        pri = *pHead;
        mid = (*pHead)->next;
        tai = mid->next;
        while (mid->next != NULL)
        {
            if (mid->womanGrade < tai->womanGrade)
            {
                pri->next = mid->next;
                mid->next = tai->next;
                tai->next = mid;
            }
            pri = pri->next;
            mid = pri->next;
            tai = mid->next;
        }
    }
    PrintGrade(*pHead);
}

void SchoolGradeSort(Node** pHead) {
    if (*pHead == NULL) {
        printf("\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
        printf("\t\t当前未录入数据  请使用 <1>功能录入 或 <7>功能读取\n");
        printf("\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t");
        return;
    }
    Node* mark = *pHead;
    int count = 0;
    while (mark) {
        count++;
        mark = mark->next;
    }
    Node* pri, * mid, * tai, * p;
    while (count--)
    {
        mid = (*pHead)->next;
        if ((*pHead)->schoolGrade < (*pHead)->next->schoolGrade)
        {
            (*pHead)->next = mid->next;
            mid->next = *pHead;
            *pHead = mid;
        }
        pri = *pHead;
        mid = (*pHead)->next;
        tai = mid->next;

        while (mid->next != NULL)
        {
            if (mid->schoolGrade < tai->schoolGrade)
            {
                pri->next = mid->next;
                mid->next = tai->next;
                tai->next = mid;
            }
            pri = pri->next;
            mid = pri->next;
            tai = mid->next;
        }
    }
    PrintGrade(*pHead);
}

void Sort(Node** pHead) {
    if (*pHead == NULL) {
        return;
    }
    Node* mark = *pHead;
    int count = 0;
    while (mark) {
        count++;
        mark = mark->next;
    }
    Node* pri, * mid, * tai, * p;
    while (count--)
    {
        mid = (*pHead)->next;
        if ((*pHead)->schoolId > (*pHead)->next->schoolId)
        {
            (*pHead)->next = mid->next;
            mid->next = *pHead;
            *pHead = mid;
        }
        pri = *pHead;
        mid = (*pHead)->next;
        tai = mid->next;
        while (mid->next != NULL)
        {
            if (mid->schoolId > tai->schoolId)
            {
                pri->next = mid->next;
                mid->next = tai->next;
                tai->next = mid;
            }
            pri = pri->next;
            mid = pri->next;
            tai = mid->next;
        }
    }
    PrintGrade(*pHead);
}

void SFileRead(Node** pHead, Node** pEnd) {
    FILE* file = NULL;
    file = fopen(path_s, "r+");
    if (!file) {
        printf("\n\tERROR: 打开文件失败\n");
        exit(0);
    }
    char buf[1024];
    fgets(buf, sizeof(buf), file);
    while (1) {
        char* a = (char*)malloc(sizeof(char) * 100);
        char* schoolName = a;
        int schoolId;
        int schoolGrade;
        int manGrade;
        int womanGrade;
        //fseek(file, 0, SEEK_SET);
        if (fscanf_s(file, "%d %s %d %d %d", &schoolId, schoolName, &schoolGrade, &manGrade, &womanGrade) != EOF) {
            Node* p = (Node*)malloc(sizeof(Node));
            id_s = p->schoolId = schoolId;
            p->schoolName = schoolName;
            p->schoolGrade = schoolGrade;
            p->manGrade = manGrade;
            p->womanGrade = womanGrade;
            p->next = NULL;
            if (*pHead == NULL) {
                *pHead = p;
            }
            else {
                (*pEnd)->next = p;
            }
            *pEnd = p;
        }
        else break;
    }
    id_s++;
    fclose(file);
}

void SFileWrite(Node* pHead) {
    FILE* file = NULL;
    file = fopen(path_s, "w+");
    fprintf(file, "学校编号   学校名称        学校成绩 男团成绩 女团成绩\n");
    while (pHead) {
        fprintf(file, "%-8d %-15s   %-8d %-8d %-8d\n", pHead->schoolId, pHead->schoolName, pHead->schoolGrade, pHead->manGrade, pHead->womanGrade);
        pHead = pHead->next;
    }
    fclose(file);
}

void PFileRead(PNode** ppHead, PNode** ppEnd) {
    FILE* file = NULL;
    file = fopen(path_p, "r+");
    if (!file) {
        printf("\n\tERROR: 打开文件失败\n");
        exit(0);
    }
    char buf[1024];
    fgets(buf, sizeof(buf), file);
    while (1) 
    {

        int programId;
        char* programName = (char*)malloc(sizeof(char) * 100);
        int sex;
        int power;
        int a, b, c, d, e, flag;
        PNode* p = NULL;
        flag = fgetc(file);

        if (flag == 51) {
            fseek(file, -1, SEEK_CUR);
            fscanf_s(file, "%d %d %d %s %d %d %d", &power, &sex, &programId, programName, &a, &b, &c);                               
            fgetc(file);
            numss++;
            p = (PNode*)malloc(sizeof(PNode));
            p->next = NULL;
            p->power = power;
            p->sex = sex; 
            id_p = p->programId = programId;
            p->programName = programName; 
            p->school[0] = a;
            p->school[1] = b;
            p->school[2] = c;
        }
        else if (flag == 53) {
            fseek(file, -1, SEEK_CUR);
            fscanf_s(file, "%d %d %d %s %d %d %d %d %d", &power, &sex, &programId, programName, &a, &b, &c, &d, &e);
            fgetc(file);
            numss++;
            p = (PNode*)malloc(sizeof(PNode));
            p->next = NULL;
            p->power = power; 
            p->sex = sex; 
            id_p = p->programId = programId;
            p->programName = programName;
            p->school[0] = a;
            p->school[1] = b; 
            p->school[2] = c;  
            p->school[3] = d; 
            p->school[4] = e;
        }
        else break;

        if (*ppHead == NULL) {
            *ppHead = p;
        }
        else {
            (*ppEnd)->next = p;
        }
        *ppEnd = p;
    }
    id_p++;
    fclose(file);
}

void PFileWrite(PNode* ppHead) {
    FILE* file = NULL;
    file = fopen(path_p, "w+");
    fprintf(file, "前几名 性别 项目编号 项目名称   获奖学校编号\n");
    while (ppHead) {
        if (ppHead->power == 5) fprintf(file, "%-5d  %-5d %-4d %11s    %d %d %d %d %d\n", ppHead->power, ppHead->sex, ppHead->programId, ppHead->programName, ppHead->school[0], ppHead->school[1], ppHead->school[2], ppHead->school[3], ppHead->school[4]);
        else fprintf(file, "%-5d  %-5d %-4d %11s    %d %d %d\n", ppHead->power, ppHead->sex, ppHead->programId, ppHead->programName, ppHead->school[0], ppHead->school[1], ppHead->school[2]);
        ppHead = ppHead->next;
    }
    fclose(file);
}

void Fun_7(PNode** ppHead, PNode** ppEnd, Node** pHead, Node** pEnd) {
    if (flag) {       SFileRead(pHead, pEnd);
        PFileRead(ppHead, ppEnd);
        flag = false;
        printf("\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t\t丨               数据已读入             丨\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
    }
    else printf("\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t\t丨               请勿重复读写             丨\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
}

void Fun_8(Node* pHead, PNode* ppHead) {
    printf("\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t\t丨           确定覆盖？<Y/N>           丨\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n\t\t\t\t");
    char ch = Getchar();
    if (ch == 'Y' || ch == 'y') {
        printf("\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\t\t丨           文件覆盖成功           丨\n\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
        SFileWrite(pHead);
        PFileWrite(ppHead);
        exit(0);
    }
    else return;
}

 