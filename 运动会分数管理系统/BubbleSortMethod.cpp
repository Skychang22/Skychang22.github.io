/***********************************************************************************\

void CollegeSort(collegeNode** Chead)
{//按学院总分排序输出（冒泡排序）
    if (*Chead == NULL)
    {
        printf("====================\n");
        printf("当前没有任何数据\n");
        printf("====================\n");
        system("pause");
        return;
    }

    collegeNode* pri, * mid, * tail;
    collegeNode* p = *Chead;
    int count = 0;//学院个数

    while (p) {
        count++;
        p = p->next;
    }//统计节点个数


    while (count--)
    {
        mid = (*Chead)->next;
        if ((*Chead)->collegeGrade < (*Chead)->next->collegeGrade)
        {
            (*Chead)->next = mid->next;
            mid->next = *Chead;
            *Chead = mid;
        }//比较第一和第二个节点

        pri = *Chead;          //头节点
        mid = (*Chead)->next;  //第二个节点
        tail = mid->next;      //第三个节点

        while (mid->next != NULL)
        {
            if (mid->collegeGrade < tail->collegeGrade)
            {
                pri->next = mid->next;
                mid->next = tail->next;
                tail->next = mid;
            }//交换mid和tail

            pri = pri->next;
            mid = pri->next;
            tail = mid->next;//三个指针各向后移动一步
        }
    }
    GradePrint(*Chead);//打印排序结果
}
/**********************************************************************\
函数名称:
    WomSort
功能描述:
    按女团总分排序输出（冒泡排序）
函数参数:
    collegeNode** Chead
返回值:
    无
模块  :
    梁子昌于2023年3月19日创建本模块，
\*********************************************************************/
/***********************************************************************************\
void WomSort(collegeNode** Chead)
{//按女团总分排序输出（冒泡排序）
    if (*Chead == NULL)
    {
        printf("====================\n");
        printf("当前没有任何数据\n");
        printf("====================\n");
        system("pause");
        return;
    }

    collegeNode* pri, * mid, * tail;
    collegeNode* p = *Chead;
    int count = 0;

    while (p)
    {
        count++;
        p = p->next;
    }//统计节点个数


    while (count--)
    {
        mid = (*Chead)->next;
        if ((*Chead)->womGrade < (*Chead)->next->womGrade)
        {
            (*Chead)->next = mid->next;
            mid->next = *Chead;
            *Chead = mid;
        }//比较第一和第二个节点

        pri = *Chead;          //头节点
        mid = (*Chead)->next;  //第二个节点
        tail = mid->next;      //第三个节点

        while (mid->next != NULL)
        {
            if (mid->womGrade < tail->womGrade)
            {
                pri->next = mid->next;
                mid->next = tail->next;
                tail->next = mid;
            }//交换mid和tail

            pri = pri->next;
            mid = pri->next;
            tail = mid->next;//三个指针各向后移动一步
        }
    }
    GradePrint(*Chead);//打印排序结果
}
/**********************************************************************\
函数名称:
    ManSort
功能描述:
    按男团总分排序输出（冒泡排序）
函数参数:
    collegeNode** Chead
返回值:
    无
模块  :
    梁子昌于2023年3月19日创建本模块，
\*********************************************************************/
/***********************************************************************************\
void ManSort(collegeNode** Chead)
{//按男团总分排序输出（冒泡排序）
    if (*Chead == NULL)
    {
        printf("====================\n");
        printf("当前没有任何数据\n");
        printf("====================\n");
        system("pause");
        return;
    }

    collegeNode* pri, * mid, * tail;
    collegeNode* p = *Chead;
    int count = 0;

    while (p)
    {
        count++;
        p = p->next;
    }//统计节点个数


    while (count--)
    {
        mid = (*Chead)->next;
        if ((*Chead)->manGrade < (*Chead)->next->manGrade)
        {
            (*Chead)->next = mid->next;
            mid->next = *Chead;
            *Chead = mid;
        }//比较第一和第二个节点

        pri = *Chead;          //头节点
        mid = (*Chead)->next;  //第二个节点
        tail = mid->next;      //第三个节点

        while (mid->next != NULL)
        {
            if (mid->manGrade < tail->manGrade)
            {
                pri->next = mid->next;
                mid->next = tail->next;
                tail->next = mid;
            }//交换mid和tail

            pri = pri->next;
            mid = pri->next;
            tail = mid->next;//三个指针各向后移动一步
        }
    }
    GradePrint(*Chead);//打印排序结果
}

\**************************************************************************************************************/

/*



// 如果a和b是相邻的节点，那么只需要交换它们的next指针
if ((*a)->next == *b) {
    (*a)->next = (*b)->next;
    (*b)->next = *a;
    return;
}
if ((*b)->next == *a) {
    (*b)->next = (*a)->next;
    (*a)->next = *b;
    return;
}

// 如果a和b不是相邻的节点，那么需要找到它们的前驱和后继
collegeNode* pre_a = NULL; // a的前驱
collegeNode* pre_b = NULL; // b的前驱
collegeNode* next_a = (*a)->next; // a的后继
collegeNode* next_b = (*b)->next; // b的后继
collegeNode* p = *head; // 用来遍历链表的指针

while (p != NULL) {
    if (p->next == *a) pre_a = p; // 找到a的前驱
    if (p->next == *b) pre_b = p; // 找到b的前驱
    p = p->next;
}

// 交换a和b的位置，注意要更新它们的前驱和后继的链接
if (pre_a != NULL) pre_a->next = *b; // 如果a不是头节点，那么让它的前驱指向b
if (pre_b != NULL) pre_b->next = *a; // 如果b不是头节点，那么让它的前驱指向a
(*a)->next = next_b; // 让a指向b原来的后继
(*b)->next = next_a; // 让b指向a原来的后继
}



*/


