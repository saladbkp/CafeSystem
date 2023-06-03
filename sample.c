#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>

//ȫ�ֱ���
int check_login_success = 0;//�ڻ�ӭ������ʾ�û�����ʱ���õ�
char user_number[12];//�ڻ�ӭ������ʾ�û��˺���ʱ���õ�
struct sysuser //����sysuser�ṹ�� 
{
    char usernum[12]; //ѧ�ź��ֻ��Ŷ���11λ��
    //����Уѧ����ֱ��ͨ��ѧ��+Ĭ������123��¼����������Ա����ͨ���ֻ���ע�� 
    //����ѧ�ź��ֻ��Ŷ���Ψһ�ģ�����ѧ�ź��ֻ��Ŷ�����Ϊsysuser������
    //����c���Թ涨�ڴ���ַ�����������Ҫ���ַ�����������������Ҳ���ǡ�\0��
    //��������usernum[]�ĳ���Ϊ�ַ��ܸ���11����һ����������\0��Ҳ����12 
    char password[8];
    struct sysuser* next; //һ��ָ��sysuser�����ָ��!!!!!һ��Ҫ�Լ��������nextָ�룡����Ҫ������������
    //ֻ��C#�����������ԲŻ�ĬĬ�����nextָ�������ĺ��C����Ҫ�Լ������� 
//Ϊ�˷�����Թ��ܣ���ע���˸��˺����붼Ϊ1���û������� 
};
struct book //����book�ṹ��
{
    int number;     //���
    char name[30];  //����
    char category[10];  //���
    int lent;       //�Ƿ������ѽ�Ϊ1��δ��Ϊ0��
    int year;       //���ʱ�䡪����
    int month;      //���ʱ�䡪����
    int day;        //���ʱ�䡪����
    struct book* next; //һ��ָ��book���Ͷ����ָ�� 
};


//��ӭ����
void print_main_title()
{
    time_t time_login;
    struct tm* p;
    time(&time_login);
    p = gmtime(&time_login);

    if (check_login_success == 0)
    {
        printf("--------------------------------------------------------------------------------");
        printf("��ӭ�����װ����û���\n");
        printf("                                                                                ");
        printf("                           ��ӭʹ��ͼ�����ϵͳ                                 ");
        printf("                                                                                ");
        printf("                        ����ʱ�䣺%d��%d��%d�� %d:%d:%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
        printf("                                                                                ");
        printf("                                                                                ");
        printf("--------------------------------------------------------------------------------");
    }
    else
    {
        printf("--------------------------------------------------------------------------------");
        printf("��ӭ����%s��\n", user_number);
        printf("                                                                                ");
        printf("                           ��ӭʹ��ͼ�����ϵͳv2.5                             ");
        printf("                                                                                ");
        printf("                        ����ʱ�䣺%d��%d��%d�� %d:%d:%d\n", 1900 + p->tm_year, p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
        printf("                                                                                ");
        printf("                                                                                ");
        printf("--------------------------------------------------------------------------------");
    }

}


//����check_usernum()����(create_user()ʱ���ã�����û��˺��Ƿ�ע�����Ŀ����Ϊ�˱�֤usernum��Ϊ�����Ψһ��) 
int check_usernum(struct sysuser* user)
{
    int check = 0;

    char usrno[12];
    strcpy(usrno, user->usernum);

    char usrno_f[12];
    FILE* fp;
    fp = fopen("user.txt", "r+");
    if (fp == NULL) fopen("user.txt", "w");
    while (fscanf(fp, "%s%*s", usrno_f) != EOF)
    {
        if (strcmp(usrno, usrno_f) == 0)
        {
            check = 1;
            break;
        }
    }
    if (fclose(fp))
    {
        printf("Can not close the file!\n");
        exit(0);
    }

    return check; //��ע�������1��û��ע�������0 
}
//ע��
int create_user()
{
    struct sysuser su;//����һ��su��������sysuser�ṹ��ģ��Ϊsu��������ռ� 
    FILE* fp;
    //��user.txt������׼������ĩβ�����µ���  
    fp = fopen("user.txt", "a"); /*a������ʾ���Ը��ӵķ�ʽ��ֻд�ļ���
                                ���ļ������ڣ���Ὠ�����ļ���
                                ���ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�������ǲ��Ḳ�ǣ��ļ�ԭ�ȵ����ݻᱻ������*/
                                //���ڼ��user.txt������ʱ����user.txt�ļ� 
    if (fp == NULL) fopen("user.txt", "w"); /*w������ʾ����ֻд�ļ���
                                            ���ļ������򳤶���Ϊ0�����ļ�������������ʧ	��
                                            ���������򴴽����ļ���*/
create_loop:
    system("CLS");	//�����������һ���س������ݣ� 

    //��ӡע�����ʾ��Ϣ 
    printf("\n");
    printf("===================================ע�����û�===================================");
    printf("\n\n");
    printf("  ���û��˺š�Ϊ11λ�ֻ��ţ���ȷ�����Ľ�Ҫ����ע����ֻ���δ������ע�᱾ϵͳ\n\n");
    printf("           ��Уѧ������ע�ᣬ��ֱ��ʹ��11λѧ��+��ʼ����123ֱ�ӵ�¼        \n\n");
    printf("    �����롿�ĳ���ӦС�ڵ���8λ��������ʹ��Ӣ���ַ������֣��������ո�\n\n");
    printf("                p.s.Ϊ����������˽����������벻����ʾ����Ļ��\n\n");
    printf("================================================================================");
    printf("\n\n");

    //��ʾ���벢����su.usernum 
    printf("                �������µ��ֻ��ţ����س�������");
    scanf("%s", su.usernum);
    printf("\n");

    //�ж�������û��˺��Ƿ�ע���
    if (check_usernum(&su) == 0)
    {
        //��ʾ���벢�����û��״��������������su.password[i] 
        printf("                �������µ����룬���س�������");
        //scanf("%s",su.password);  //scanf()��Ĳ���������ָ�� 
                                    //1���Ѿ���ָ��Ĳ��� &������ char name[20]�е�name
                                    //2������ָ���Ҫ�� &������ float math�е�math 
        //printf("\n");
        int i = 0;
        while (0 < i < 8 && (su.password[i] = getch()) != '\r')//���û��������벢ȷ�ϣ�������Enter���� 
        {
            //�û�����������Ĺ�������ɾ����Ϊ��������backspace�˸���� 
            if (su.password[i] == '\b')//su.password[i]���鳤�ȼ���iλ 
            {
                if (i <= 0);
                else i--;
            }
            //������������ 
            else
            {
                i++;
                //��������볬����8λ����ʾ����8λ�������Զ�ɾ������8λ������룬ֻȡǰ��λ
                if (i > 8)
                {
                    printf("\n           ע�⣺�Ѿ��ﵽ8λ�ַ����ޣ�ֻ��ǰ8λ������ַ���Ч��\n");
                    i = i - 1;
                }
            }
        }
        su.password[i] = '\0';//�����ַ�����β����su.password[i]���� 


        //��ʾ�������û��ٴ���������� check_password[8] 
        char check_password[8];
        printf("\n\n                ���ٴ��������룬���س�������");
        //scanf("%s",check_password); 
        //printf("\n"); 
        i = 0;
        for (i = 0; i < 8; i++)
            check_password[i] = '\0';

        i = 0;
        while (0 < i < 8 && (check_password[i] = getch()) != '\r')
        {
            if (check_password[i] == '\b')
            {
                if (i <= 0);
                else i--;
            }
            else
            {
                i++;
                if (i > 8)
                {
                    printf("\n           ע�⣺�Ѿ��ﵽ8λ�ַ����ޣ�ֻ��ǰ8λ������ַ���ЧŶ\n");
                    i = i - 1;
                }
            }
        }
        check_password[i] = '\0';

        //�Ƚ�su.password[i]��check_password[8] 
        int check = 1;
        if (strcmp(check_password, su.password) == 0);
        else
        {
            printf("\n\n                  �����������벻һ�£�������ע��...\n");
            Sleep(2000);
            goto create_loop;
        }

        //��ʽ�����su������ֵ(su.usernum��su.password)��user.txt�ļ�    (��user.txt���һ��д����ע���û�) 
        fprintf(fp, "%s %s", su.usernum, su.password);
        fprintf(fp, "\n");
        fclose(fp);

        //��ӡע��ɹ�����ʾ��Ϣ 
        printf("\n\n\n\n");
        printf("ע��ɹ�!���ס�����û�����%s", su.usernum);
        printf("���������μ��������룡\n\n");

        //����������������ҷ�����ҳ���˵� 
        printf("\n\n\n\n��������������˵���ѡ��¼����");
        char ch;
        ch = getch();
        system("cls");
        return 1;
    }
    else
    {
        printf("                ����ֻ��ű�ע��������뻻���ֻ�����ע��Ŷ\n");
        printf("\n                �����������");
        char ch;
        ch = getch();  //����ǵ�д������Ȼ��getch()�Ļ���������������printf()�Ե��ġ�����֪������Ī�������gotoȥ�˲�֪���ĸ��ط����� 
        goto create_loop;
    }
}


//����checkUserValid()���� (��¼ʱ����,����û��Ϸ��ԣ� 
int checkUserValid(struct sysuser* user)
{

    //�򿪴洢�û��˺�������ļ�user.txt 
    FILE* user_file_p;
    user_file_p = fopen("user.txt", "r");

    if (user_file_p == NULL)
        user_file_p = fopen("user.txt", "w");

    char usr[30], pwd[10];  //usr[30]���û���ʱ����ģ�user->usernum��user->password���ɱ��������β�user��ֵ���� 
    char usr_f[30];  //usr_f[30]�Ǵ�user.txt���ȡ�ģ��û��˺�+�ո�+����+\n�� 

    int check = 0;

    //��(�û������ո����롢\n)���ӳ����ַ���usr��������user.txt�ļ��м��ƥ��
    strcpy(usr, user->usernum);
    strcat(usr, " ");
    strcpy(pwd, user->password);
    strcat(usr, pwd);
    strcat(usr, "\n");

    //���ļ��ж����û���Ϣ���ݣ������ж��û���ʱ����ĺ�user.txt��ģ��û��˺�+�ո�+����+\n���Ƿ�ƥ�� 
    while (feof(user_file_p) == 0)
    {
        fgets(usr_f, 30, user_file_p); //�����ж�һ�л�ָ�����ַ���ԭ����char *fgets(char *s, int n, FILE *stream);
        //�����ж�ȡ���n-1���ַ�������s���������ַ����ģ�
        //����ɹ��򷵻�s��ָ�룬���򷵻�NULL
        //���Ǵ�user_file_p����ļ��������ж�ȡ���30���ַ����浽user_f��
        //fgets()�ǰ���Ϊ��λ��ȡ�ģ����Բ���nҪ���õú������� 
        if (strcmp(usr, usr_f) == 0)
        {
            check = 1;
            break;
        }
    }

    //�ر��ļ�
    if (fclose(user_file_p))
    {
        printf("Can not close the file!\n");
        exit(0);
    }

    return check;
}

//��¼ 
int login()
{
    struct sysuser su;
    char ch;
    int check = 0;

    //���� 
    system("CLS");

    //��ӡ������ 
    print_main_title();
    printf("\n\n");

    //��ʾ���벢����su.usernum 
    printf("                  ������11λѧ�Ż��ֻ��ţ����س���������");
    scanf("%s", su.usernum);
    printf("\n\n");

    //��ʾ���벢����su.password 
    printf("                       ������С�ڵ���8λ������\n\n");
    printf("         ����������ʱ������ʾ����Ļ�ϣ�����ʱ�밴�س�������Ŷ\n\n");
    printf("                               ������ɣ�"); //scanf("%s", su.password);
    int i = 0;
    while (0 < i < 8 && (su.password[i] = getch()) != '\r')
    {
        if (su.password[i] == '\b')
        {
            if (i <= 0);
            else i--;
        }
        else
        {
            i++;
            if (i > 8)
            {
                printf("\n             ע�⣺�Ѿ��ﵽ8λ�ַ����ޣ����μ�����ַ�����Ч��\n\n");
                i = i - 1;
            }
        }
    }
    su.password[i] = '\0';


    //����û��Ϸ��� 
    if (checkUserValid(&su) == 1)
    {
        strcpy(user_number, su.usernum);
        check = 1;
        printf("\n\n\n");
        printf("                              ��¼�ɹ���\n");
        printf("\n");
        printf("��������������˵�...");
        ch = getch();
        system("cls");
    }

    else
    {
        printf("\n\n\n");
        printf("            ���û������ڻ����������˶Ժ����µ�¼����ע������˺ţ�\n\n");
        printf("                      ����������������Ա��ϵ!\n\n");
        printf("\n\n\n\n��������������˵�...");
        ch = getch();
        system("cls");
    }

    return check;
}

/*------------------------------------------------��library.txt�Ĳ�������غ�����ʼ------------------------------------------------*/

//���library.txt�Ƿ�Ϊ�գ���library.txt�ж�ȡ����������ʱ���ã� 
int check_void_file()
{
    FILE* fp;  //����fp��һ��ָ���ļ����͵��ļ�ָ�루FILE *��
    fp = fopen("library.txt", "r+");  //����fpҪָ���λ����library.txt�Ŀ�ͷ��r+��ʾ������д����ȡ��д��Ĺ�궼���ļ���ͷ�� 
    char ch;
    ch = fgetc(fp); //��ȡ�ļ��ĵ�һ���ַ� 
    fclose(fp); //�ر��ļ� 
    if (ch == EOF) return 0; //����ļ���һ���ַ�Ϊĩβ�ַ������ļ�Ϊ�գ�������0   //EOF�Ǹ��꣬���ڱ�ʶ�Ѿ������ļ�ĩβ�� 
    return 1; //�ļ��ǿգ�����1 
}

//��library.txt�ж�ȡ����������
struct book* make_linklist()   //�������ָ�뺯�������ʾ��Ƕκ������ڻ��������溯������code segment������ data segment���еĴ��ڣ�
    //���Ժ��������鶼�ǲ��Ķ�������������������֮��Ĭ�ϻ���������һ��ָ�������׵�ַ��ָ��
    //�������ָ������ָ�������/������һ�� 
    //make_linklist()�ķ���ֵ�ǣ�struct book *��    //��struct book *)����ָ������Ϊbook�Ľṹ���ָ�� 
{
    struct book* head;  //ָ��head���ڿ���ָ���κ�����Ϊbook�Ľṹ�� 
    head = (struct book*)malloc(sizeof(struct book));  //����book�ṹ���С���ڴ棬
    //��������ڴ水��book�ṹ��Ĵ�С���ֵ�Ԫ�� 
    //Ȼ������ڴ���׵�ַ��ֵ��ָ�����head����headΪͷָ�� 
    head->next = NULL; //��ͷ�ڵ��ָ����ֵΪnull������ʼ��һ����ͷ���ĵ����� 

    FILE* fp;  //����fp��һ��ָ���ļ����͵��ļ�ָ�루FILE *�� 
    fp = fopen("library.txt", "r+");  //����fpҪָ����ļ���library.txt     ��r+��ʾ������д�ļ��� 

    if (fp == NULL)  //���library.txt�ļ������� 
        fp = fopen("library.txt", "w+");  // w+ ������ļ��Ѿ����ڣ�������һ�����ļ�����ԭ�ļ�����ȱ�°�������������֧�ֶ�ȡ��
    //�˴����ڴ���library.txt�ļ� 

    if (check_void_file() == 0) //��⵽library.txtΪ�� 
    {
        printf("ͼ�����ݿ�Ϊ�գ�");
        return head;  //���ش���������ͷָ�룬���������������������Ϳ��Ա������ط������� 
    }

    struct book* p;
    p = head;  //��p��ֵΪͷָ�룬����pָ��ͷ�ڵ� 
    char ch;
    while (!feof(fp))  //���ļ�ָ��fpû�е���ĩβ��ѭ��ִ�д�library.txt��ȡ���ݵ����� 
        //��feof()���ڼ���ļ��Ƿ����,���û�н���,����ֵ��0,��������1�� 
    {
        struct book* new_book_init;   //ָ��new_book_init���ڿ���ָ������Ϊbook���κνṹ�� 
        new_book_init = (struct book*)malloc(sizeof(struct book));  //����book�ṹ���С���ڴ棬��������ڴ水��book�ṹ��Ĵ�С���ֵ�Ԫ�� 
        //Ȼ������ڴ���׵�ַ��ֵ��ָ�����new_book_init��
        //��new_book_initΪͷָ�� 
        fscanf(fp, "%d", &new_book_init->number);  //��ʽ������new_book_initָ��ָ��Ľṹ���number��Ա 
        ch = fgetc(fp);
        fscanf(fp, "%[^\n]%*c", new_book_init->name);
        fscanf(fp, "%[^\n]%*c", new_book_init->category);
        fscanf(fp, "%d", &new_book_init->lent);
        ch = fgetc(fp);
        fscanf(fp, "%d", &new_book_init->year);
        ch = fgetc(fp);
        fscanf(fp, "%d", &new_book_init->month);
        ch = fgetc(fp);
        fscanf(fp, "%d", &new_book_init->day);
        ch = fgetc(fp);
        new_book_init->next = NULL;  //��ʼ�������� ?

        p->next = new_book_init;
        p = p->next;
    }
    fclose(fp);
    return head;
}




//�����鱾���������Ĳ����� 
int input_new_book(struct book* head)
{
    FILE* fp;
    struct book newbook;
    struct book* p;
    p = head;
    if (p->next == NULL)
    {
        printf("������");
    }
input_loop:
    fp = fopen("library.txt", "a+");
    system("ClS");
    printf("\n");
    printf("===================================¼����ͼ��===================================");
    printf("\n\n    ��ע�⣺���Ҫ��Ϊ30λ���ڵĴ�����\n\n");
    printf("            ����Ҫ��Ϊ30��Ӣ���ַ����ڣ��ɰ����ո�һ�����ְ������ַ�����\n\n");
    printf("            ����Ҫ��Ϊ10��Ӣ���ַ����ڣ��ɰ����ո�һ�����ְ������ַ�����\n");
    printf("\n");
    printf("================================================================================");
    printf("\n");
input_number_loop:
    printf("                        ����������ı�ţ�");
    scanf("%d", &newbook.number);
    while (p->next != NULL)
    {
        if (newbook.number == p->number)  //�˴���p->numberΪpָ��Ľṹ��ĳ�Ա���� 
        {
            printf("\n                        �����Ѵ��ڣ���˶Ժ���������\n                        ");
            system("PAUSE");
            printf("\n");
            goto input_number_loop;
        }
        p = p->next;
    }
    p = head;  //��pָ��ͷ��� 
    printf("\n");
input_name_loop:
    printf("                        ��������������֣�");
    fflush(stdin);  //fflush()����ǿ�Ƚ��������ڵ�����д��stdin�� 
    scanf("%[^'\n']", newbook.name);
    while (p->next != NULL) //ѭ�������������� 
    {
        if (strcmp(p->name, newbook.name) == 0)
        {
            printf("\n                        �����Ѵ��ڣ���˶Ժ���������\n                        ");
            system("PAUSE");
            printf("\n");
            goto input_name_loop;
        }
        p = p->next;
    }
    p = head;
    fflush(stdin);
    printf("\n");
input_category_loop:
    printf("                        ����������ķ��ࣺ");
    scanf("%[^'\n']", newbook.category);
    fflush(stdin);
    p = head;

    newbook.lent = 0;
    newbook.year = 0;
    newbook.month = 0;
    newbook.day = 0;
    newbook.next = NULL;
    fprintf(fp, "%d ", newbook.number);
    fprintf(fp, "%s\n", newbook.name);
    fprintf(fp, "%s\n", newbook.category);
    fprintf(fp, "%d %d %d %d\n", newbook.lent, newbook.year, newbook.month, newbook.day);
    fclose(fp);
    printf("\n                        ¼��ɹ���\n\n");
    printf("                        ��¼����鱾�������£�\n");
    printf("                        ��ţ�%d\n", newbook.number);
    printf("                        ������%s\n", newbook.name);
    printf("                        ���ࣺ%s\n", newbook.category);
    printf("\n");
    printf("                        �Ƿ����¼�룿 y����  n���� ");
    fflush(stdin);
    char ch;
    scanf("%c", &ch);
    if (ch == 'y')
        goto input_loop;
    else
    {
        printf("\n\n������3��󷵻����˵�...");
        Sleep(3000);
        return 1;
    }
}

//ɾ���鱾����������ɾ����i����� 
struct book* delete_book(struct book* head, struct book* p)
{
    system("CLS");
    print_booklist_title();
    print_booknode(p);

    printf("                           ���棡�ò������ɻָ���\n\n");
    printf("                        WARNING!THIS CAN'T BE UNDONE!!\n\n");
    printf("                            �Ƿ������\n");
    printf("                            y����  ���������\n");
    printf("                            �������Ӧѡ����س�������");
    char ch;
    scanf("%c", &ch);

    if (ch == 'y')
    {
        struct book* q;
        q = head;
        while (q->next != p)
        {
            q = q->next;
        }
        q->next = p->next;
        free(p);
        printf("ɾ���ɹ���\n");
        system("pause");
        return head;
    }
    else
        return head;

}

//�޸��鱾 
struct book* modify_book(struct book* head, struct book* t)
{
    int i;
    char name_temp[30];
    for (i = 0; i < 30; i++)
        name_temp[i] = '\0';
    i = 0;

    char cate_temp[10];
    for (i = 0; i < 10; i++)
        cate_temp[i] = '\0';
    i = 0;

    int num_temp = 0;
    fflush(stdin);
    system("CLS");
    printf("\n==================================�޸�ͼ��======================================");
    printf("\n\n                           ���棡�ò������ɻָ���\n\n");
    printf("\n============================������Ҫ�޸ĵ�ͼ��==================================");
    print_booklist_title();
    print_booknode(t);
    printf("-------------------------------------------------------------------------------");
    printf("\n");
    printf("\n-----------------------------��ѡ����Ҫ���еĲ���-----------------------------");
    printf("\n\n");
    printf("                      1���޸�����\n\n");
    printf("                      2���޸ı��\n\n");
    printf("                      3���޸ķ���\n\n");
    //printf("4����ʾ�����鱾\n");
    printf("                      4���Ҿ���ʲôҲ�������뷵�����˵�\n\n");
    printf("������ѡ��ǰ�ı�ţ����س����룺");
    scanf("%d", &i);
    switch (i)
    {
    case 1:
        printf("��������30���ַ����ڣ�һ������Ϊ�����ַ�\n");
        printf("�������µ����ƣ�");
        fflush(stdin);
        gets(name_temp);
        strcpy(t->name, name_temp);
        printf("�޸ĳɹ���");
        system("PAUSE");
        return head;
    case 2:
        printf("�����ȫΪ���֣�����20λ����\n");
        printf("�������µı�ţ�");
        fflush(stdin);
        scanf("%d", t->number);
        printf("�޸ĳɹ���");
        system("PAUSE");
        return head;
    case 3:
        printf("��������10���ַ����ڣ�һ������Ϊ�����ַ�\n");
        printf("�������µķ��ࣺ");
        fflush(stdin);
        gets(cate_temp);
        strcpy(t->category, cate_temp);
        printf("�޸ĳɹ���");
        system("PAUSE");
        return head;
    case 4:
        return head;
    default:
        return head;
    }
}


//����������library.txt�������ԭlibrary.txt������
void override_to_file(struct book* head)
{
    FILE* fp;
    fp = fopen("library.txt", "w");
    struct book* p;
    p = head->next;  //��pָ��ڶ������ 
    while (p->next != NULL)
    {
        fprintf(fp, "%d ", p->number);
        fprintf(fp, "%s\n", p->name);
        fprintf(fp, "%s\n", p->category);
        fprintf(fp, "%d ", p->lent);
        fprintf(fp, "%d ", p->year);
        fprintf(fp, "%d ", p->month);
        fprintf(fp, "%d", p->day);
        fprintf(fp, "\n");
        p = p->next;   //��pָ����һ���ڵ� 
    }
    fclose(fp);
}



//�����鱾������ţ� 
struct book* search_by_number(struct book* head, int number)
{
    struct book* p;
    p = head->next; //��pָ��ͷ��� 
    if (p == NULL)
        return NULL;
    while (p->next != NULL) //ѭ�������������� 
    {
        if (p->number == number)
            return p;
        p = p->next;
    }
    //return NULL;
}

//�����鱾���������� 
struct book* search_by_name(struct book* head, char* name)
{
    struct book* p;
    p = head->next; //��pָ��ͷ��� 
    if (p == NULL)
        return NULL;
    while (p != NULL)
    {
        if (strcmp(name, p->name) == 0)
            return p;
        p = p->next;
    }
    //return NULL;
}

//�����鱾�������ࣩ 
int search_by_category(struct book* head, char* category)
{
    struct book* p;
    p = head->next; //��pָ��ͷ��� 
    int flag = 0;
    while (p->next != NULL)
    {
        if (strcmp(category, p->category) == 0) //�Ƚ������ַ����Ƿ���� 
        {
            print_booknode(p);
            flag = 1;
        }
        p = p->next;
    }
    if (flag == 0)
    {
        printf("û���ҵ��÷�����飡\n");
        printf("��������������˵�...\n");
        getch();
        return 0;
    }
    printf("��������������˵�...\n");
    getch();
    return 0;

}

//�����鱾�������ʱ�䣩 
struct book* search_by_time(struct book* head, int year, int month, int day)
{
    int flag = 0;
    struct book* p;
    p = head->next;  //��pָ��ͷ��� 
    if (p == NULL)
        flag = 0;
    while (p->next != NULL) //ѭ������ 
    {
        if ((p->year == year) && (p->month == month) && (p->day == day))
        {
            print_booknode(p);
            flag = 1;
        }
        p = p->next;
    }
    if (flag == 0)
        printf("û���ҵ��鱾��\n");
    system("PAUSE");
}

//����������Ϣ�����+����+����+�ڿ�/���ʱ�䣩 
void print_booklist_title()
{
    printf("�����ҵ���������ǣ�\n");
    printf("--------------------------------------------------------------------------------");
    printf("���                ����                          ����        ���ʱ��       \n");
    printf("--------------------------------------------------------------------------------");
}
void print_booknode(struct book* t)
{

    if (t != NULL)
    {
        printf("%-20d%-30s%-10s", t->number, t->name, t->category);
        if (t->lent == 1)
        {
            printf("  %d��%d��%d��\n", t->year, t->month, t->day);
        }
        else printf("  �ڿ�\n");
    }
    else
    {
        printf("û���ҵ����飡\n");
        printf("��������������˵�...\n");
        getch();
    }
}




//���������
int print_all_book(struct book* head)
{
    //���� 
    system("CLS");
    //��ӡС���� 
    printf("\n");
    printf("================================��ʾ�����鱾====================================");
    printf("\n");
    // 
    char ch;
    // 
    struct book* p;
    p = head->next;
    // 
    if (p == NULL)
    {
        printf("\n���ݿ���û���鱾��\n\n");
        printf("                  �����������...");
        ch = getch();
        return 0;
    }
    // 
    print_booklist_title();
    do
    {
        print_booknode(p);
        p = p->next;
    } while (p->next != NULL);
    printf("\n������������ϼ��˵�Ŷ...");
    ch = getch();
    return 1;
}

/*---------------------------------------------------��library.txt�Ĳ�����غ�������---------------------------------------------*/



/*---------------------------------------------------��user.txt�Ĳ�����غ�����ʼ---------------------------------------------*/
//���user.txt�Ƿ�Ϊ�գ���user.txt�ж�ȡ����������ʱ���ã� 
int check_sysuser_void_file()
{
    FILE* fp;  //����fp��һ��ָ���ļ����͵��ļ�ָ�루FILE *��
    fp = fopen("user.txt", "r+");  //����fpҪָ���λ����library.txt�Ŀ�ͷ��r+��ʾ������д����ȡ��д��Ĺ�궼���ļ���ͷ�� 
    char ch;
    ch = fgetc(fp); //��ȡ�ļ��ĵ�һ���ַ� 
    fclose(fp); //�ر��ļ� 
    if (ch == EOF) return 0; //����ļ���һ���ַ�Ϊĩβ�ַ������ļ�Ϊ�գ�������0   //EOF�Ǹ��꣬���ڱ�ʶ�Ѿ������ļ�ĩβ�� 
    return 1; //�ļ��ǿգ�����1 
}
//��user.txt�ж�ȡ����������
struct sysuser* make_sysuser_linklist()   //�������ָ�뺯�������ʾ��Ƕκ���
    //���ڻ��������溯������code segment����data segment���еĴ��ڣ�
   //���ķ���ֵ������(struct sysuser *),����һ��ָ������Ϊsysuser�ṹ���ָ�� 
{
    struct sysuser* sysuser_head;  //ָ��head���ڿ���ָ���κ�����Ϊ�Ľṹ�� 
    sysuser_head = (struct sysuser*)malloc(sizeof(struct sysuser));  //����sysuser�ṹ���С���ڴ棬
    //��������ڴ水��sysuser�ṹ��Ĵ�С���ֵ�Ԫ�� 
    //Ȼ������ڴ���׵�ַ��ֵ��ָ�����sysuser_head����sysuser_headΪͷָ�� 
    sysuser_head->next = NULL; //��ͷ�ڵ��ָ����ֵΪnull������ʼ��һ����ͷ���ĵ����� 

    FILE* fp;  //����fp��һ��ָ���ļ����͵��ļ�ָ�루FILE *�� 
    fp = fopen("user.txt", "r+");  //����fpҪָ����ļ���user.txt     ��r+��ʾ������д�ļ��� 

    if (fp == NULL)  //���user.txt�ļ������� 
        fp = fopen("user.txt", "w+");  // w+ ������ļ��Ѿ����ڣ�������һ�����ļ�����ԭ�ļ�����ȱ�°�������������֧�ֶ�ȡ��
    //�˴����ڴ���user.txt�ļ� 

    if (check_sysuser_void_file() == 0) //��⵽user.txtΪ�� 
    {
        printf("�û���Ϣ�ݿ�Ϊ�գ�");
        return sysuser_head;  //���ش���������ͷָ�룬���������������������Ϳ��Ա������ط������� 
    }

    struct sysuser* p;
    p = sysuser_head;  //��p��ֵΪͷָ�룬����pָ��ͷ�ڵ� 
    char ch;
    while (!feof(fp))  //���ļ�ָ��fpû�е���ĩβ��ѭ��ִ�д�user.txt��ȡ���ݵ����� 
        //��feof()���ڼ���ļ��Ƿ����,���û�н���,����ֵ��0,��������1�� 
    {
        struct sysuser* new_sysuser_init;   //ָ��new_sysuser_init���ڿ���ָ������Ϊbook���κνṹ�� 
        new_sysuser_init = (struct sysuser*)malloc(sizeof(struct sysuser));  //����sysuser�ṹ���С���ڴ棬��������ڴ水��sysuser�ṹ��Ĵ�С���ֵ�Ԫ�� 
        //Ȼ������ڴ���׵�ַ��ֵ��ָ�����new_sysuser_init��
        //(struct sysuser *)��ǿ������ת��(type)��ǿ��ת��Ϊָ��sysuser���͵Ľṹ���ָ��
        //��new_sysuser_initΪͷָ�� 
        fscanf(fp, "%s", &new_sysuser_init->usernum);  //��ʽ������new_sysuser_initָ��ָ��Ľṹ���number��Ա 
        ch = fgetc(fp); //��ȡһ���ո񣬲������ͬʱfpָ���Զ����Ƶ���һ����δ������������Ҫ�������ַ�
        fscanf(fp, "%[^\n]%*c", new_sysuser_init->password);
        //%[]��ʾҪ��ȡ��ָ���ַ������ı���eg: %[0-9]��ʾֻ��ȡ���֣������������ַ���ֹͣ��%[\n]��ʾֻ��ȡ\n�����������У�����ַ�
        //%[^]��ʾ��ȡ�䲹����eg��%[^\n]��ʾ��ȡ���з�֮��������ַ�
        //%*��ʾ���Զ�ȡ�����ַ�������˵��ȡ����ָ�����ַ������ǲ����浽�����С�
        //����%[^\n]%*c��ʾ��ȡ����һ���У�������\n������ֻ������һ�����������\n֮��������ַ����ܶ���֮%*c�������Իس����ġ�����
        new_sysuser_init->next = NULL;  //��ʼ�������� 

        p->next = new_sysuser_init;
        p = p->next;
    }
    fclose(fp);
    return sysuser_head;
}


//�����û������û��˺ţ� 
struct book* search_by_usernum(struct sysuser* sysuser_head, char* del_sysuser_num)
{
    struct sysuser* p;
    p = sysuser_head->next; //��pָ��ͷ��� 
    if (p == NULL)
        return NULL;
    while (p != NULL)
    {
        if (strcmp(del_sysuser_num, p->usernum) == 0)
            return p;
        p = p->next;
    }
    //return NULL;
}
//ɾ���û�
struct sysuser* delete_sysuser(struct sysuser* sysuser_head, struct sysuser* p)
{
    struct sysuser* q;
    q = sysuser_head;
    while (q->next != p)
    {
        q = q->next;
    }
    q->next = p->next;
    free(p);
    printf("ɾ���ɹ���\n");
    system("pause");
    return sysuser_head;
}
//����������user.txt�������ԭuser.txt������
void override_to_sysuser_file(struct sysuser* sysuser_head)
{
    FILE* fp;
    fp = fopen("user.txt", "w");
    struct sysuser* p;
    p = sysuser_head->next;  //��pָ��ڶ������ 
    while (p->next != NULL)
    {
        fprintf(fp, "%s ", p->usernum);
        fprintf(fp, "%s\n", p->password);
        p = p->next;   //��pָ����һ���ڵ� 
    }
    fclose(fp);
}


//������û�����Ϣ���û���+���룩 
void print_sysuserlist_title()
{
    printf("�����ҵ��û��������ǣ�\n");
    printf("--------------------------------------------------------------------------------");
    printf("   �û��˺�                                                      ����           \n");
    printf("--------------------------------------------------------------------------------");
}
void print_sysusernode(struct sysuser* m)
{
    if (m != NULL)
    {
        printf("%-64s%-10s\n", m->usernum, m->password);
    }
    else
    {
        printf("û���ҵ����û���\n");
        printf("��������������˵�...\n");
        getch();
    }
}

//��������û� 
int print_all_sysuser(struct sysuser* sysuser_head)
{
    //���� 
    system("CLS");
    //��ӡС���� 
    printf("\n");
    printf("================================��ʾ�����û�====================================");
    printf("\n");
    // 
    char ch;
    // 
    struct sysuser* p;
    p = sysuser_head->next;
    // 
    if (p == NULL)
    {
        printf("\n���ݿ���û���κ��û���Ϣ��\n\n");
        printf("                  �����������...");
        ch = getch();
        return 0;
    }
    // 
    print_sysuserlist_title();
    do
    {
        print_sysusernode(p);
        p = p->next;
    } while (p->next != NULL);
    printf("\n������������ϼ��˵�Ŷ...");
    ch = getch();
    return 1;
}
/*---------------------------------------------------��user.txt�Ĳ�����غ�������---------------------------------------------*/


//������
int main()
{
    //����login_temp��ţ���ž����Ӧ����������һ��printf��""���������Ļ��
    char login_temp;
loop:
    //��ӡ��ӭ����+�˵� 
    print_main_title();
    printf("\n\n");
    printf("                               1��ע��\n\n");
    printf("                               2����¼\n\n");
    printf("                               3�������\n\n");
    printf("                               4���˳�\n\n");
    printf("\n\n");
    printf("                      ������ѡ��ǰ�ı�ţ����س���������");
    //�����û������login_temp���
    scanf("%c", &login_temp);

    //234����Ҫ�õ��ı��� 
    int login_check_temp = 1; //2.��¼   
    char visitor_select; //3.�����
    char login_exit_temp; //4.�˳�  

    switch (login_temp)
    {
        //1.ע�� 
    case '1':
        create_user();
        goto loop;
        //2.��¼ 
    case '2':
        //����login()������˳����login_check_temp�����ʱ������ֵ 
        login_check_temp = login();
        //��¼���ɹ��򷵻����˵� 
        if (login_check_temp == 0)goto loop;
        //��¼�ɹ����޸ı�־�Ըı件ӭ������ʾ 
        check_login_success = 1;

        // 
        char menu_select; //��¼������Ĳ˵����
        int reader_select;//1,����

        int user_admin_select;//2,ϵͳ����Ա
        int del_sysuser_select;//2.1ɾ���û� 

        int book_admin_select; //3,ͼ�����Ա
        int search_select; //����
        int borrow_select; //3.1,���� 
        int back_select; //3.2,���� 
        int modify_select;//3.4,�޸�ͼ�� 
        int admin_delete_select;//3.5,ɾ��ͼ�� 

        struct sysuser* sysuser_head;
        struct book* head;
        char ch;
        char str_tmp[100];
        while (1)
        {
            //��library.txt�ж�ȡ���ݵ�����
            head = make_linklist();
        main_loop:
            //���� 
            system("CLS");
            //��ӡ��ӭ����+�˵� 
            print_main_title();
            printf("\n");

            printf("                                1�����ǡ����ߡ�\n\n");
            printf("                                2�����ǡ�ϵͳ����Ա��\n\n");
            printf("                                3�����ǡ�ͼ�����Ա��\n\n");
            printf("                                4���˳�\n");
            printf("\n");
            printf("                       ������Ҫʹ�ù��ܵı�ţ����س����룺");

            //��ȡ��ѡmeau_select��ֵ 
            scanf("%c", &menu_select);

            //����һ��ָ������Ϊsysuser�Ľṹ���ָ��m 
            struct sysuser* m;
            //����һ��ָ������Ϊbook�Ľṹ���ָ��t	 
            struct book* t;

            //���ݱ�Ų��ң����=temp 
            int temp = 0;
            //�����������ң�����=name_temp[30]
            int i;
            char name_temp[30];
            for (i = 0; i < 30; i++) name_temp[i] = 0;
            //���ݷ������ ,����=category_temp[10] 
            char category_temp[10];
            for (i = 0; i < 10; i++) category_temp[i] = 0;
            //���ݽ��ʱ����ң� 
            time_t timep; //time_tʵ���Ͼ��ǳ�����long int;�����������1970��1��1��0ʱ0��0�뵽����ʱ�̵���������time()���������ȡ��
            struct tm* time_p;
            time(&timep);
            time_p = gmtime(&timep);
            int year = 0;
            int month = 0;
            int day = 0;

            switch (menu_select)
            {
                //���� 
            case '1':
                break;
                //ϵͳ����Ա 
            case '2':
            user_admin_loop:
                system("CLS");
                print_main_title();
                printf("\n\n");
                printf("                        1��ɾ���û�\n\n");
                printf("                        2���г������û�\n\n");
                printf("                        3��������һ��\n");
                printf("\n\n");
                printf("                        �������Ӧ���ܵı�ţ����س����룺");
                scanf("%d", &user_admin_select);
                struct sysuser* m;
                while (1) {
                    //��user.txt�ж�ȡ���ݵ����� 
                    struct sysuser* sysuser_head;
                    sysuser_head = make_sysuser_linklist();
                    switch (user_admin_select) {
                        //ɾ���û� 
                    case 1:
                        system("CLS");
                        printf("\n\n");
                        printf("=====================================ɾ���û�===================================\n\n");
                        printf("                                     �����������                               \n\n");
                        printf("================================================================================\n\n");
                        printf("                        ϵͳ�趨λ��Ҫɾ�����û���\n\n");
                        printf("                        1�������û���11λ���û��˺�\n\n");
                        printf("                        2������\n\n");
                        printf("                ���������϶�Ӧѡ��ı�ţ����س�������");
                        scanf("%d", &del_sysuser_select);
                        printf("\n\n");
                        switch (del_sysuser_select)
                        {
                        case 1:
                            printf("��������Ҫɾ�����û����˺ţ�11λ����");
                            char temp[12];
                            scanf("%s", &temp);
                            printf("\n\n");
                            t = search_by_usernum(sysuser_head, temp);
                            if (t == NULL)
                            {
                                printf("û���ҵ����û�����˶Ժ�����������\n");
                                printf("����������ز˵�...\n");
                                getch();
                                break;
                            }
                            else
                            {
                                sysuser_head = delete_sysuser(sysuser_head, t);  //ɾ���û� 
                                override_to_sysuser_file(sysuser_head);  //����д��user.txt 
                                break;
                            }
                            break;
                        case 2:
                            goto user_admin_loop;
                        }
                        break;
                        //�г������û� 
                    case 2:
                        print_all_sysuser(sysuser_head);
                        goto user_admin_loop;
                        break;
                    }
                }
                break;
                //ͼ�����Ա
            case '3':
            book_admin_loop:
                system("CLS");
                print_main_title();
                printf("\n\n");
                printf("                        1������\n\n");
                printf("                        2������\n\n");
                printf("                        3��¼����ͼ�鵽���ݿ�\n\n");
                printf("                        4���޸�����ͼ�������\n\n");
                printf("                        5�������ݿ���ɾ��ͼ��\n\n");
                printf("                        6��������һ��\n");
                printf("\n\n");
                printf("                        �������Ӧ���ܵı�ţ����س����룺");
                scanf("%d", &book_admin_select);
                switch (book_admin_select)
                {
                    //����
                case 1:
                    //����+��ӡ����Ͳ˵�+�������� 
                borrow_loop:    system("CLS");
                    printf("\n");
                    printf("======================================����======================================");
                    printf("\n");
                    printf("                        ϵͳ��Ҫ��λ��Ҫ����飺\n\n");
                    printf("                        1�����ڴ�������ı��\n\n");
                    printf("                        2��������һ��\n\n");
                    printf("                        �������Ӧѡ��ı�ţ����س����룺");
                    scanf("%d", &borrow_select);
                    //���������� 
                    switch (borrow_select)
                    {
                    case 1:
                        //��ʾ 
                        printf("\n\n");
                        printf("                    ��������ı�ţ����س�������");
                        scanf("%d", &temp);
                        //����Ų��Ҷ�λҪ����鱾
                        t = search_by_number(head, temp);
                        //time_t timep;

                        if (t != NULL)
                        {
                            system("CLS");
                            printf("\n");
                            printf("======================================����======================================");
                            printf("\n\n");

                            print_booklist_title();
                            print_booknode(t);
                            if (t->lent == 0)
                            {
                                printf("\n\n");
                                printf("                        ��ȷ��Ҫ���Ȿ����1���� 2����");
                                scanf("%d", &temp);
                                if (temp == 1)
                                {
                                    t->lent = 1;
                                    t->year = 1900 + time_p->tm_year;
                                    t->month = time_p->tm_mon;
                                    t->day = time_p->tm_mday;

                                    printf("\n\n");
                                    printf("                        ����ɹ���");
                                    override_to_file(head);
                                    system("PAUSE");
                                    goto borrow_loop;
                                    break;
                                }
                            }
                            //else break;
                            printf("\n\n\n");
                            printf("                    ���󣺸����Ѿ��������˶Ժ�����������\n\n");
                            printf("                    �������������ϵ������Ա\n\n                    ");
                            system("PAUSE");
                            goto borrow_loop;
                            break;
                        }
                        else
                        {
                            printf("\n\n\n");
                            printf("                    ����û���ҵ����飡��˶Ժ�����������\n\n");
                            printf("                    �������������ϵ������Ա\n\n                    ");
                            system("PAUSE");
                            goto borrow_loop;
                            break;
                        }
                    case 2:
                        goto book_admin_loop;
                    default:
                        goto borrow_loop;
                        break;
                    }
                    break;
                    //���� 
                case 2:
                back_loop:
                    system("CLS");
                    printf("\n");
                    printf("======================================����======================================");
                    printf("\n");
                    printf("                        ϵͳ��Ҫ��λ��Ҫ�����飺\n\n");
                    printf("                        1�����ڴ�������ı��\n\n");
                    printf("                        2��������һ��\n\n");
                    printf("                        �������Ӧ����ǰ�ı�ţ����س�������");

                    scanf("%d", &back_select);

                    switch (back_select)
                    {
                    case 1://���
                        printf("\n\n");
                        printf("                        �������ţ����س�������");
                        scanf("%d", &temp);
                        t = search_by_number(head, temp);  //��ͼ���Ŷ�λҪ����ͼ�� 

                        if (t != NULL)
                        {
                            system("CLS");
                            printf("\n");
                            printf("======================================����======================================");
                            printf("\n\n");

                            print_booklist_title();
                            print_booknode(t);
                            if (t->lent == 1)
                            {
                                printf("\n\n");
                                printf("                        ��ȷ��Ҫ���Ȿ����1���� 2����");
                                scanf("%d", &temp);
                                if (temp == 1)
                                {
                                    t->lent = 0;
                                    t->year = 0;
                                    t->month = 0;
                                    t->day = 0;
                                    //print_booknode(t);
                                    printf("\n\n");
                                    printf("                        ����ɹ���");
                                    override_to_file(head);
                                    system("PAUSE");
                                    goto back_loop;
                                    break;
                                }
                            }
                            //else
                            printf("\n\n\n");
                            printf("                    ���󣺸����Ѿ��ڿ⣡��˶Ժ�����������\n\n");
                            printf("                    �������������ϵ������Ա\n\n                    ");
                            system("PAUSE");
                            goto back_loop;
                            break;
                        }
                        else
                        {
                            printf("\n\n\n");
                            printf("                    ����û���ҵ����飡��˶Ժ�����������\n\n");
                            printf("                    �������������ϵ������Ա\n\n                    ");
                            system("PAUSE");
                            goto back_loop;
                            break;
                        }
                        break;
                    default:
                        goto book_admin_loop;//break�����������ϲ�˵���ֻ��Ҫ�ص�����ʱ������Ҫ�Ӹ�loop��ʶ�� 
                    }
                    break;
                    //¼��
                case 3:
                    input_new_book(head);
                    goto book_admin_loop;
                    //�޸�
                case 4:
                modify_loop:
                    system("CLS");
                    printf("\n");
                    printf("====================================�޸�ͼ��====================================");
                    printf("\n");
                    printf("                           ���棡�ò������ɻָ���\n\n");
                    printf("                        WARNING!THIS CAN'T BE UNDONE!!\n\n");
                    printf("\n");
                    printf("           �������������޸����ݿ�����ı�š����ơ�����ͽ��ʱ��\n\n");
                    printf("                        ϵͳ�趨λ��Ҫ�޸����ݵ��飺\n\n");
                    printf("                        1���ڴ�������ı��\n\n");
                    printf("                        2������\n\n");
                    printf("                �������Ӧѡ��ı�ţ����س�������");
                    scanf("%d", &modify_select);
                    printf("\n\n");
                    switch (modify_select)
                    {
                    case 1://������ 
                        fflush(stdin);
                        printf("                    ��������ı�ţ����س�������");
                        scanf("%d", &temp);
                        printf("\n\n");
                        t = search_by_number(head, temp); //����Ŷ�λͼ�� 
                        if (t == NULL)
                        {
                            printf("û���ҵ����飡��˶Ժ�����������\n");
                            printf("��������������˵�...\n");
                            getch();
                            break;
                        }
                        else
                        {
                            head = modify_book(head, t);  //�޸�ͼ�� 
                            override_to_file(head);  //����д��library.txt 
                            break;
                        }
                        break;
                    case 2:
                        break;
                    default:
                        break;
                    }
                    break;
                    //��t�����޸�

                //ɾ��
                case 5:
                    system("CLS");
                    printf("\n");
                    printf("====================================ɾ��ͼ��====================================");
                    printf("\n");
                    printf("                           ���棡�ò������ɻָ���\n\n");
                    printf("                        WARNING!THIS CAN'T BE UNDONE!!\n\n");
                    printf("\n\n");
                    printf("\n\n");
                    printf("                        ϵͳ�趨λ��Ҫɾ�����飺\n\n");
                    printf("                        1�����ݱ�Ų���\n\n");
                    printf("                        2������\n\n");
                    printf("                        �������Ӧѡ��ı�ţ����س�������");
                    scanf("%d", &admin_delete_select);
                    printf("\n\n");
                    switch (admin_delete_select)
                    {
                    case 1://�����ɾ��
                        system("CLS");
                        printf("                           ���棡�ò������ɻָ���\n\n");
                        printf("                        WARNING!THIS CAN'T BE UNDONE!!\n\n");
                        printf("                       ������Ҫɾ������ı�ţ����س�������");
                        scanf("%d", &temp);
                        printf("\n\n");
                        fflush(stdin);
                        t = search_by_number(head, temp);
                        if (t != NULL)
                        {
                            head = delete_book(head, t);
                            override_to_file(head);
                        }
                        else
                        {
                            printf("û���ҵ����飡\n");
                            system("PAUSE");
                        }
                        break;
                    case 2:
                        break;
                    }
                default:
                    break;
                }
                break;
                //������һ�� 
            case '4':
            {
                printf("\n");
                printf("                      ��ȷ��Ҫ�˳���\n");
                printf("                      ��������˳�����n����\n");
                login_exit_temp = getch();
                if (login_exit_temp == 'n')
                {
                    system("CLS");
                    goto loop;
                }
                else return 1;
            }
            break;
            //�����˳���123456������������ 
            default:
                goto main_loop;
            }
        }
        break;
        //3.����� 
    case '3':                                //1.�г������鱾  //2.�����鱾
    visitor_loop:
        //���� 
        system("CLS");
        //��ӡ��ӭ����+�˵� 
        print_main_title();
        printf("\n\n");
        printf("                        1���г�����ͼ��\n\n");
        printf("                        2������ͼ��\n\n");
        printf("                        3��������һ��\n");
        printf("\n\n");
        printf("                        �������Ӧ���ܵı�ţ����س����룺");

        //�����û�ѡ��ı�� 
        fflush(stdin); //fflush()����ǿ�Ƚ��������ڵ�����д��stdin��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //����Ū������һ���ϣ���������û�����ֻ��scanf()�Ļ����䲻��������ȥ�ġ����������� 
        scanf("%c", &visitor_select);

        //2����ͼ��
        int visitor_search_select;
        //���ݱ�Ų��ң����=temp 
        int temp = 0;
        //�����������ң�����=name_temp[30]
        int i;
        char name_temp[30];
        for (i = 0; i < 30; i++) name_temp[i] = 0;
        //���ݷ������ ,����=category_temp[10] 
        char category_temp[10];
        for (i = 0; i < 10; i++) category_temp[i] = 0;
        //���ݽ��ʱ����ң� 
        time_t timep; //time_tʵ���Ͼ��ǳ�����long int;�����������1970��1��1��0ʱ0��0�뵽����ʱ�̵���������time()���������ȡ��
        struct tm* time_p;
        time(&timep);
        time_p = gmtime(&timep);

        int year = 0;
        int month = 0;
        int day = 0;

        struct book* t;
        while (1) {
            //��ȡlibrary.txt������ 
            struct book* visitor;
            visitor = make_linklist();
            //��������������������������������������������������case�����1��2��3��int�͵ģ�
            //����visitor_select���Ƕ�����char,����Ҫд'1','2','3' 
            switch (visitor_select) {
            case '1':
                print_all_book(visitor);
                goto visitor_loop;
                break;
            case '2':
            visitor_search_loop:    system("CLS");
                print_main_title();
                printf("\n\n");
                printf("                        1���������ֲ���\n\n");
                printf("                        2�����ݱ�Ų���\n\n");
                printf("                        3�����ݷ������\n\n");
                printf("                        4�����ݽ��ʱ�����\n\n");
                printf("                        5�������ϼ��˵�\n");
                printf("\n\n");
                printf("                        �������Ӧ���ܵı�ţ����س����룺");
                scanf("%d", &visitor_search_select);
                printf("\n\n");
                switch (visitor_search_select)
                {
                case 1://��������
                    printf("                      ������Ҫ���ҵ�����,���س�����:");
                    scanf("%s", name_temp);
                    printf("\n\n");
                    t = search_by_name(visitor, name_temp);
                    if (t != NULL)
                    {
                        print_booklist_title();
                        print_booknode(t);
                        printf("                               ��������������˵�...\n\n");
                        getch();
                        goto visitor_search_loop;
                    }
                    else
                    {
                        printf("û���ҵ����飡\n");
                        printf("��������������˵�...\n");
                        getch();
                        goto visitor_search_loop;
                    }
                    break;
                case 2://���ݱ��
                    printf("                       ������Ҫ���ҵ���ı��,���س�������");
                    scanf("%d", &temp);
                    printf("\n\n");
                    struct book* t;
                    t = search_by_number(visitor, temp);
                    if (t != NULL)
                    {
                        print_booklist_title();
                        print_booknode(t);
                        printf("��������������˵�...\n\n");
                        getch();
                        goto visitor_search_loop;
                    }
                    else
                    {
                        printf("û���ҵ����飡\n");
                        printf("��������������˵�...\n");
                        getch();
                        goto visitor_search_loop;
                    }
                    break;
                case 3://���ݷ���
                    system("CLS");
                    printf("            ������Ҫ���ҵķ���,���س�������");
                    scanf("%s", category_temp);
                    printf("\n\n");
                    search_by_category(head, category_temp);
                    printf("��������������˵�...\n");
                    getch();
                    goto visitor_search_loop;
                case 4://���ݽ��ʱ��
                    system("CLS");
                    printf("\n");
                    printf("================================���ݽ��ʱ�����================================");
                    printf("\n");
                    printf("\n������Ҫ���ҵ��鱾�Ľ�����,���س�������");
                    scanf("%d", &year);
                    printf("\n�������·�,���س�������");
                    scanf("%d", &month);
                    printf("\n����������,���س�������");
                    scanf("%d", &day);
                    printf("\n\n");
                    search_by_time(head, year, month, day);
                    goto visitor_loop;
                case 5://������һ��
                    goto visitor_loop;
                default:
                    goto visitor_search_loop;
                }
            case '3':
                goto loop;
            default:
                goto visitor_loop;
            }
        }
        break;
        //4.�˳�  
    case '4':
        //��ӡ��ʾ��Ϣ 
        printf("\n\n");
        printf("                      ��ȷ��Ҫ�˳���\n\n");
        printf("                      ��������˳�����n����\n\n");
        //�����û��˳�ʱ�����login_exit_temp��ֵ 
        login_exit_temp = getch();
        //����'n'�򷵻أ�����'�����'���˳� 
        if (login_exit_temp == 'n')
        {
            system("CLS");
            goto loop;
        }
        else exit(0);
        //������1234����Ĺ����� 
    default:
        system("CLS");
        goto loop;

    }
}







