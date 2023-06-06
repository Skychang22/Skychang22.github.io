/***********************************************************************************\

void CollegeSort(collegeNode** Chead)
{//��ѧԺ�ܷ����������ð������
    if (*Chead == NULL)
    {
        printf("====================\n");
        printf("��ǰû���κ�����\n");
        printf("====================\n");
        system("pause");
        return;
    }

    collegeNode* pri, * mid, * tail;
    collegeNode* p = *Chead;
    int count = 0;//ѧԺ����

    while (p) {
        count++;
        p = p->next;
    }//ͳ�ƽڵ����


    while (count--)
    {
        mid = (*Chead)->next;
        if ((*Chead)->collegeGrade < (*Chead)->next->collegeGrade)
        {
            (*Chead)->next = mid->next;
            mid->next = *Chead;
            *Chead = mid;
        }//�Ƚϵ�һ�͵ڶ����ڵ�

        pri = *Chead;          //ͷ�ڵ�
        mid = (*Chead)->next;  //�ڶ����ڵ�
        tail = mid->next;      //�������ڵ�

        while (mid->next != NULL)
        {
            if (mid->collegeGrade < tail->collegeGrade)
            {
                pri->next = mid->next;
                mid->next = tail->next;
                tail->next = mid;
            }//����mid��tail

            pri = pri->next;
            mid = pri->next;
            tail = mid->next;//����ָ�������ƶ�һ��
        }
    }
    GradePrint(*Chead);//��ӡ������
}
/**********************************************************************\
��������:
    WomSort
��������:
    ��Ů���ܷ����������ð������
��������:
    collegeNode** Chead
����ֵ:
    ��
ģ��  :
    ���Ӳ���2023��3��19�մ�����ģ�飬
\*********************************************************************/
/***********************************************************************************\
void WomSort(collegeNode** Chead)
{//��Ů���ܷ����������ð������
    if (*Chead == NULL)
    {
        printf("====================\n");
        printf("��ǰû���κ�����\n");
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
    }//ͳ�ƽڵ����


    while (count--)
    {
        mid = (*Chead)->next;
        if ((*Chead)->womGrade < (*Chead)->next->womGrade)
        {
            (*Chead)->next = mid->next;
            mid->next = *Chead;
            *Chead = mid;
        }//�Ƚϵ�һ�͵ڶ����ڵ�

        pri = *Chead;          //ͷ�ڵ�
        mid = (*Chead)->next;  //�ڶ����ڵ�
        tail = mid->next;      //�������ڵ�

        while (mid->next != NULL)
        {
            if (mid->womGrade < tail->womGrade)
            {
                pri->next = mid->next;
                mid->next = tail->next;
                tail->next = mid;
            }//����mid��tail

            pri = pri->next;
            mid = pri->next;
            tail = mid->next;//����ָ�������ƶ�һ��
        }
    }
    GradePrint(*Chead);//��ӡ������
}
/**********************************************************************\
��������:
    ManSort
��������:
    �������ܷ����������ð������
��������:
    collegeNode** Chead
����ֵ:
    ��
ģ��  :
    ���Ӳ���2023��3��19�մ�����ģ�飬
\*********************************************************************/
/***********************************************************************************\
void ManSort(collegeNode** Chead)
{//�������ܷ����������ð������
    if (*Chead == NULL)
    {
        printf("====================\n");
        printf("��ǰû���κ�����\n");
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
    }//ͳ�ƽڵ����


    while (count--)
    {
        mid = (*Chead)->next;
        if ((*Chead)->manGrade < (*Chead)->next->manGrade)
        {
            (*Chead)->next = mid->next;
            mid->next = *Chead;
            *Chead = mid;
        }//�Ƚϵ�һ�͵ڶ����ڵ�

        pri = *Chead;          //ͷ�ڵ�
        mid = (*Chead)->next;  //�ڶ����ڵ�
        tail = mid->next;      //�������ڵ�

        while (mid->next != NULL)
        {
            if (mid->manGrade < tail->manGrade)
            {
                pri->next = mid->next;
                mid->next = tail->next;
                tail->next = mid;
            }//����mid��tail

            pri = pri->next;
            mid = pri->next;
            tail = mid->next;//����ָ�������ƶ�һ��
        }
    }
    GradePrint(*Chead);//��ӡ������
}

\**************************************************************************************************************/

/*



// ���a��b�����ڵĽڵ㣬��ôֻ��Ҫ�������ǵ�nextָ��
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

// ���a��b�������ڵĽڵ㣬��ô��Ҫ�ҵ����ǵ�ǰ���ͺ��
collegeNode* pre_a = NULL; // a��ǰ��
collegeNode* pre_b = NULL; // b��ǰ��
collegeNode* next_a = (*a)->next; // a�ĺ��
collegeNode* next_b = (*b)->next; // b�ĺ��
collegeNode* p = *head; // �������������ָ��

while (p != NULL) {
    if (p->next == *a) pre_a = p; // �ҵ�a��ǰ��
    if (p->next == *b) pre_b = p; // �ҵ�b��ǰ��
    p = p->next;
}

// ����a��b��λ�ã�ע��Ҫ�������ǵ�ǰ���ͺ�̵�����
if (pre_a != NULL) pre_a->next = *b; // ���a����ͷ�ڵ㣬��ô������ǰ��ָ��b
if (pre_b != NULL) pre_b->next = *a; // ���b����ͷ�ڵ㣬��ô������ǰ��ָ��a
(*a)->next = next_b; // ��aָ��bԭ���ĺ��
(*b)->next = next_a; // ��bָ��aԭ���ĺ��
}



*/


