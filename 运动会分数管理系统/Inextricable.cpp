/*
* 
* 
* 
* @���Զ��û�н��������ļ���ȡ����
* 
* 
* 
* 
* 
* 
void EFileRead2(eventNode** Ehead, eventNode** Eend)
{
    FILE* file = NULL;
    file = fopen("Edata.txt", "r+");
    if (!file) {
        printf("\n\tERROR: ���ļ�ʧ��\n");
        exit(0);
    }
    char buf[1024];
    fgets(buf, sizeof(buf), file);//��ȡ�ļ��ı���
    while (1)
    {
        int eventID;
        int sex;
        int gradeWeight;
        int awardCollege[25];
        int competeCollege;
        char  eventName[100];
        char line[1024];
        char buf[1024];
       fgets(buf, sizeof(buf), file);
        while (1)
        {
            if (fgets(line, sizeof(line), file) == NULL)
            {
                perror("ERROR:��ȡ�ļ�ʧ��");
                    exit(0);
            }

            if (sscanf(line, "%s %d %d %d %d", eventName, &eventID, &sex, &gradeWeight, &competeCollege) != 5)
            {
                break;
            }

                int i = 1;
                while (fscanf(file, "%d", &awardCollege[i]) == 1)
                {
                    i++;
                    if (fgetc(file) == '\n')
                        break;
                }

                eventNode* temp = (eventNode*)malloc(sizeof(collegeNode));
                strcpy(temp->eventName, eventName);
                id_event = temp->eventID = eventID;
                temp->sex = sex;
                temp->gradeWeight = gradeWeight;
                memmove(temp->awardCollege, awardCollege, sizeof(awardCollege));
                temp->next = NULL;


                if (*Ehead == NULL)
                    *Ehead = temp;
                else
                    (*Eend)->next = temp;
                *Eend = temp;


        }
      id_event++;
      if (feof(file))
          break;
    }
    fclose(file);
}





void EFileRead1(eventNode** Ehead, eventNode** Eend)
{
    FILE* file = NULL;
    file = fopen("Edata.txt", "r+");
    if (!file) {
        printf("\n\tERROR: ���ļ�ʧ��\n");
        exit(0);
    }
    char buf[1024];
    fgets(buf, sizeof(buf), file);
    while (1)
    {
        int eventID;
        int sex;
        int gradeWeight;
        int awardCollege[25];
        int competeCollege;
        char  eventName[100];
        char line[1024];

        while (1)
        {
            fseek(file, -1, SEEK_CUR);
            // ��ȡ�ļ���һ�У����洢��line������
            if (fgets(line, sizeof(line), file) == NULL)
            {
                perror("ERROR:��ȡ�ļ�ʧ��");
                exit(0);
            }

            // ��"_"����ո�
            if (sscanf(line, "%[^_]_%d_%d_%d_%d", eventName, &eventID, &sex, &gradeWeight, &competeCollege) != 5)
            {
                break;
            }

            // �޸Ĳ��֣���ȡʣ���һ����Ϊһ���ַ��������洢��rest������
            char rest[1024];
            fgets(rest, sizeof(rest), file);

            eventNode* temp = (eventNode*)malloc(sizeof(collegeNode));



            // ����eventName�����е����ݵ�tempָ��Ľṹ���е�eventName��Ա��
            // �޸Ĳ��֣���"_"�滻�ؿո�
            for (int i = 0; i < strlen(eventName); i++) {
                if (eventName[i] == '_') {
                    eventName[i] = ' ';
                }
            }


            strcpy(temp->eventName, eventName);
            id_event = temp->eventID = eventID;
            temp->sex = sex;
            temp->gradeWeight = gradeWeight;



            // ��һ��ѭ������rest�е�ÿ������ת��Ϊ���������洢��awardCollege��
            int i = 0;
            char* token = strtok(rest, " ");
            while (token != NULL) {
                awardCollege[i] = atoi(token);
                i++;
                token = strtok(NULL, " ");
            }


            // ����awardCollege�����е����ݵ�tempָ��Ľṹ���е�awardCollege��Ա��
            memmove(temp->awardCollege, awardCollege, sizeof(awardCollege));
            temp->next = NULL;

            if (*Ehead == NULL)
                *Ehead = temp;
            else
                (*Eend)->next = temp;
            *Eend = temp;


        }
        // id_event��1
        id_event++;
        // ����ļ��������������ѭ��
        if (feof(file))
            break;
    }
    // �ر��ļ�������
    fclose(file);
}




void EFileRead3(eventNode** Ehead, eventNode** Eend)
{
    FILE* file = NULL;
    file = fopen("Edata.txt", "r+");
    if (!file) {
        printf("\n\tERROR: ���ļ�ʧ��\n");
        exit(0);
    }
    char buf[1024];
    fgets(buf, sizeof(buf), file);//��ȡ�ļ��ı���
    while (1)
    {
        int eventID;
        int sex;
        int gradeWeight;
        int awardCollege[25];
        int competeCollege;
        char  eventName[100];
        char line[1024];
        char buf[1024];
        fgets(buf, sizeof(buf), file);
        while (1)
        {
            if (fgets(line, sizeof(line), file) == NULL)
            {
                perror("ERROR:��ȡ�ļ�ʧ��");
                exit(0);
            }

            //�޸ģ���һ���������洢���������
            int data[30]; //���������30������
            int count = 0; //��¼���ݵĸ���

            //�޸ģ���һ��ѭ������ȡ���е����ݣ�����������
            char* p = line; //��һ��ָ���������ַ���
            while (*p != '\0') //��û�е����ַ���ĩβʱ
            {
                if (count == 0) //����ǵ�һ�����ݣ���sscanf������ȡ�ַ���
                {
                    if (sscanf(p, "%s", eventName) == 1) //����ɹ���ȡһ���ַ���
                    {
                        printf("%s", eventName);
                        count++; //�������ݵĸ���
                        while (*p != ' ' && *p != '\n' && *p != '\0') //�������ַ�������Ŀո���з�
                            p++;
                    }
                    else //�����ȡʧ�ܣ�˵�������˷��ַ����ַ�������ѭ��
                        break;
                }
                else //������ǵ�һ�����ݣ���sscanf������ȡ����
                {
                    if (sscanf(p, "%d", &data[count]) == 1) //����ɹ���ȡһ������
                    {


                        printf("%d", data[count]);
                        system("pause");


                        count++; //�������ݵĸ���

                        while (*p != ' ' && *p != '\n' && *p != '\0') //��������������Ŀո���з�
                            p++;
                    }
                    else //�����ȡʧ�ܣ�˵�������˷������ַ�������ѭ��
                        break;
                }
            }

            //�޸ģ��ж����ݵĸ����Ƿ���ȷ���������ȷ��˵����ʽ��������ѭ��
            if (count < 6) //����Ӧ��6�����ݣ�ǰ5���ǹ̶��ģ�����������һ��
            {
                break;
            }

            //�޸ģ��������е����ݸ�ֵ����Ӧ�ı���
            eventID = data[1]; //�ڶ����������¼�ID
            sex = data[2]; //�������������Ա�
            gradeWeight = data[3]; //���ĸ������ǵȼ�Ȩ��
            competeCollege = data[4]; //����������Ǿ���ѧԺ
            memmove(awardCollege, data + 5, (count - 5) * sizeof(int)); //ʣ�µ������ǽ���ѧԺ����memmove�������Ƶ�awardCollege������

            eventNode* temp = (eventNode*)malloc(sizeof(collegeNode));
            strcpy(temp->eventName, eventName); //��strcpy��������eventName������temp->eventName��
            id_event = temp->eventID = eventID;
            temp->sex = sex;
            temp->gradeWeight = gradeWeight;
            memmove(temp->awardCollege, awardCollege, sizeof(awardCollege));
            temp->next = NULL;

            if (*Ehead == NULL)
                *Ehead = temp;
            else
                (*Eend)->next = temp;
            *Eend = temp;


        }
        id_event++;
        if (feof(file))
            break;
    }
    fclose(file);
}





void EFileRead4(eventNode** Ehead, eventNode** Eend)
{
    FILE* file = NULL;
    file = fopen("Edata.txt", "r+");
    if (!file) {
        printf("\n\tERROR: ���ļ�ʧ��\n");
        exit(0);
    }
    char buf[1024];
    fgets(buf, sizeof(buf), file);//��ȡ�ļ��ı���
    while (1)
    {
        int eventID;
        int sex;
        int gradeWeight;
        int awardCollege[25];
        int competeCollege;
        char  eventName[100];
        char line[1024];
        char buf[1024];
        fgets(buf, sizeof(buf), file);
        while (1)
        {
            if (fgets(line, sizeof(line), file) == NULL)
            {
                perror("ERROR:��ȡ�ļ�ʧ��");
                exit(0);
            }

            //�޸ģ���һ���������洢���������
            int data[30]; //���������30������
            int count = 0; //��¼���ݵĸ���

            //�޸ģ���һ��ѭ������ȡ���е����ݣ�����������
            char* p = line; //��һ��ָ���������ַ���
            while (*p != '\0') //��û�е����ַ���ĩβʱ
            {
                if (count == 0) //����ǵ�һ�����ݣ���sscanf������ȡ�ַ���
                {
                    if (sscanf(p, "%s", eventName) == 1) //����ɹ���ȡһ���ַ���
                    {
                        printf("%s", eventName);
                        count++; //�������ݵĸ���
                        while (*p != ' ' && *p != '\n' && *p != '\0') //�������ַ�������Ŀո���з�
                            p++;
                    }
                    else //�����ȡʧ�ܣ�˵�������˷��ַ����ַ�������ѭ��
                        break;
                }

                else //������ǵ�һ�����ݣ���sscanf������ȡ����
                {
                    if (sscanf(p, "%d", &data[count]) == 1) //����ɹ���ȡһ������
                    {


                        printf("%d", data[count]);
                        system("pause");


                        count++; //�������ݵĸ���
                        //while (*p != ' ' && *p != '\n' && *p != '\0') //��������������Ŀո���з�
                        while (*p != ' ' && *p != '\n' && *p != '\0') //��������������Ŀո���з�
                            p++;
                    }
                    else //�����ȡʧ�ܣ�˵�������˷������ַ�������ѭ��
                        break;
                }
            }

            //�޸ģ��ж����ݵĸ����Ƿ���ȷ���������ȷ��˵����ʽ��������ѭ��
            if (count < 6) //����Ӧ��6�����ݣ�ǰ5���ǹ̶��ģ�����������һ��
            {
                break;
            }

            //�޸ģ��������е����ݸ�ֵ����Ӧ�ı���
            eventID = data[1]; //�ڶ����������¼�ID
            sex = data[2]; //�������������Ա�
            gradeWeight = data[3]; //���ĸ������ǵȼ�Ȩ��
            competeCollege = data[4]; //����������Ǿ���ѧԺ
            memmove(awardCollege, data + 5, (count - 5) * sizeof(int)); //ʣ�µ������ǽ���ѧԺ����memmove�������Ƶ�awardCollege������

            eventNode* temp = (eventNode*)malloc(sizeof(collegeNode));
            strcpy(temp->eventName, eventName); //��strcpy��������eventName������temp->eventName��
            id_event = temp->eventID = eventID;
            temp->sex = sex;
            temp->gradeWeight = gradeWeight;
            memmove(temp->awardCollege, awardCollege, sizeof(awardCollege));
            temp->next = NULL;

            if (*Ehead == NULL)
                *Ehead = temp;
            else
                (*Eend)->next = temp;
            *Eend = temp;


        }
        id_event++;
        if (feof(file)) //�޸ģ���fread�ķ���ֵ���ж��Ƿ��ȡ���
            break;
    }
    fclose(file);
}





*/