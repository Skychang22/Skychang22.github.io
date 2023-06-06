/*
* 
* 
* 
* @尝试多次没有解决问题的文件读取函数
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
        printf("\n\tERROR: 打开文件失败\n");
        exit(0);
    }
    char buf[1024];
    fgets(buf, sizeof(buf), file);//读取文件的标题
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
                perror("ERROR:读取文件失败");
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
        printf("\n\tERROR: 打开文件失败\n");
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
            // 读取文件的一行，并存储在line数组中
            if (fgets(line, sizeof(line), file) == NULL)
            {
                perror("ERROR:读取文件失败");
                exit(0);
            }

            // 用"_"代替空格
            if (sscanf(line, "%[^_]_%d_%d_%d_%d", eventName, &eventID, &sex, &gradeWeight, &competeCollege) != 5)
            {
                break;
            }

            // 修改部分：读取剩余的一行作为一个字符串，并存储在rest数组中
            char rest[1024];
            fgets(rest, sizeof(rest), file);

            eventNode* temp = (eventNode*)malloc(sizeof(collegeNode));



            // 复制eventName数组中的内容到temp指向的结构体中的eventName成员中
            // 修改部分：把"_"替换回空格
            for (int i = 0; i < strlen(eventName); i++) {
                if (eventName[i] == '_') {
                    eventName[i] = ' ';
                }
            }


            strcpy(temp->eventName, eventName);
            id_event = temp->eventID = eventID;
            temp->sex = sex;
            temp->gradeWeight = gradeWeight;



            // 用一个循环来把rest中的每个数字转换为整数，并存储在awardCollege中
            int i = 0;
            char* token = strtok(rest, " ");
            while (token != NULL) {
                awardCollege[i] = atoi(token);
                i++;
                token = strtok(NULL, " ");
            }


            // 复制awardCollege数组中的内容到temp指向的结构体中的awardCollege成员中
            memmove(temp->awardCollege, awardCollege, sizeof(awardCollege));
            temp->next = NULL;

            if (*Ehead == NULL)
                *Ehead = temp;
            else
                (*Eend)->next = temp;
            *Eend = temp;


        }
        // id_event加1
        id_event++;
        // 如果文件结束，跳出外层循环
        if (feof(file))
            break;
    }
    // 关闭文件并返回
    fclose(file);
}




void EFileRead3(eventNode** Ehead, eventNode** Eend)
{
    FILE* file = NULL;
    file = fopen("Edata.txt", "r+");
    if (!file) {
        printf("\n\tERROR: 打开文件失败\n");
        exit(0);
    }
    char buf[1024];
    fgets(buf, sizeof(buf), file);//读取文件的标题
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
                perror("ERROR:读取文件失败");
                exit(0);
            }

            //修改：用一个数组来存储后面的数据
            int data[30]; //假设最多有30个数据
            int count = 0; //记录数据的个数

            //修改：用一个循环来读取所有的数据，存入数组中
            char* p = line; //用一个指针来遍历字符串
            while (*p != '\0') //当没有到达字符串末尾时
            {
                if (count == 0) //如果是第一个数据，用sscanf函数读取字符串
                {
                    if (sscanf(p, "%s", eventName) == 1) //如果成功读取一个字符串
                    {
                        printf("%s", eventName);
                        count++; //增加数据的个数
                        while (*p != ' ' && *p != '\n' && *p != '\0') //跳过该字符串后面的空格或换行符
                            p++;
                    }
                    else //如果读取失败，说明遇到了非字符串字符，跳出循环
                        break;
                }
                else //如果不是第一个数据，用sscanf函数读取整数
                {
                    if (sscanf(p, "%d", &data[count]) == 1) //如果成功读取一个整数
                    {


                        printf("%d", data[count]);
                        system("pause");


                        count++; //增加数据的个数

                        while (*p != ' ' && *p != '\n' && *p != '\0') //跳过该整数后面的空格或换行符
                            p++;
                    }
                    else //如果读取失败，说明遇到了非数字字符，跳出循环
                        break;
                }
            }

            //修改：判断数据的个数是否正确，如果不正确，说明格式有误，跳出循环
            if (count < 6) //至少应有6个数据，前5个是固定的，后面至少有一个
            {
                break;
            }

            //修改：把数组中的数据赋值给相应的变量
            eventID = data[1]; //第二个数据是事件ID
            sex = data[2]; //第三个数据是性别
            gradeWeight = data[3]; //第四个数据是等级权重
            competeCollege = data[4]; //第五个数据是竞争学院
            memmove(awardCollege, data + 5, (count - 5) * sizeof(int)); //剩下的数据是奖励学院，用memmove函数复制到awardCollege数组中

            eventNode* temp = (eventNode*)malloc(sizeof(collegeNode));
            strcpy(temp->eventName, eventName); //用strcpy函数复制eventName变量到temp->eventName中
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
        printf("\n\tERROR: 打开文件失败\n");
        exit(0);
    }
    char buf[1024];
    fgets(buf, sizeof(buf), file);//读取文件的标题
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
                perror("ERROR:读取文件失败");
                exit(0);
            }

            //修改：用一个数组来存储后面的数据
            int data[30]; //假设最多有30个数据
            int count = 0; //记录数据的个数

            //修改：用一个循环来读取所有的数据，存入数组中
            char* p = line; //用一个指针来遍历字符串
            while (*p != '\0') //当没有到达字符串末尾时
            {
                if (count == 0) //如果是第一个数据，用sscanf函数读取字符串
                {
                    if (sscanf(p, "%s", eventName) == 1) //如果成功读取一个字符串
                    {
                        printf("%s", eventName);
                        count++; //增加数据的个数
                        while (*p != ' ' && *p != '\n' && *p != '\0') //跳过该字符串后面的空格或换行符
                            p++;
                    }
                    else //如果读取失败，说明遇到了非字符串字符，跳出循环
                        break;
                }

                else //如果不是第一个数据，用sscanf函数读取整数
                {
                    if (sscanf(p, "%d", &data[count]) == 1) //如果成功读取一个整数
                    {


                        printf("%d", data[count]);
                        system("pause");


                        count++; //增加数据的个数
                        //while (*p != ' ' && *p != '\n' && *p != '\0') //跳过该整数后面的空格或换行符
                        while (*p != ' ' && *p != '\n' && *p != '\0') //跳过该整数后面的空格或换行符
                            p++;
                    }
                    else //如果读取失败，说明遇到了非数字字符，跳出循环
                        break;
                }
            }

            //修改：判断数据的个数是否正确，如果不正确，说明格式有误，跳出循环
            if (count < 6) //至少应有6个数据，前5个是固定的，后面至少有一个
            {
                break;
            }

            //修改：把数组中的数据赋值给相应的变量
            eventID = data[1]; //第二个数据是事件ID
            sex = data[2]; //第三个数据是性别
            gradeWeight = data[3]; //第四个数据是等级权重
            competeCollege = data[4]; //第五个数据是竞争学院
            memmove(awardCollege, data + 5, (count - 5) * sizeof(int)); //剩下的数据是奖励学院，用memmove函数复制到awardCollege数组中

            eventNode* temp = (eventNode*)malloc(sizeof(collegeNode));
            strcpy(temp->eventName, eventName); //用strcpy函数复制eventName变量到temp->eventName中
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
        if (feof(file)) //修改：用fread的返回值来判断是否读取完毕
            break;
    }
    fclose(file);
}





*/