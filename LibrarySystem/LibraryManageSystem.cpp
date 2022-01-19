// Created by yxn on 2021/12/10.
//��ĿҪ��
//
//1��ϵͳ���ܣ�ͼ��ɱࡢͼ���ѯ��ͼ����ͨ�͸�����Ϣ�ȹ���
//
//2�������ܶ��������ݵ��ݴ��Խ��м�飬��֤���ݵĺϷ��ԡ�
//
//3���û�������Ѻ��ԣ�������ṩ�˵����û�ѡ�����Ӧ�Ľ�����Ϣ��
//��ĿĿ�ģ�
//
//1�����Ͻṹ�ı�ʾ��ʵ�֡�
//
//2�����Һ������㷨��ʵ�֡�
//
//3���ļ��Ĵ�ȡ������

#include <iostream>
#include <fstream>
#include<cstring>
#include <ctime>
#include <utility>
#include <conio.h>
#include <synchapi.h>

using namespace std;

//====================����ע��͵�¼����===================//
/**����ע��͵�¼����*/
class Syuser
{
    /**����ʵ��ע��͵�¼���ܵĽṹ��*/
    typedef struct syuser
    {
        char userid[12];    //��ϵͳĬ��ѧ�ź��ֻ��Ŷ���11λ��,�������
        char password[8];
        struct syuser *next;
    } User;
public:
    static bool check_userid(User *user);

    static bool checkUserValid(User *user);

    bool check_login_success = false;//�ڻ�ӭ������ʾ�û�����ʱ���õ�
    char user_number[12]{};            //�ڻ�ӭ������ʾ�û��˺���ʱ���õ�

    void welcome_title();

    int create_user();

    int login();
};

/**����û��˺��Ƿ��ѱ�ע��:û��ע�������true*/
bool Syuser::check_userid(User *user)
{
    int check = true;
    char usrno[12];
    strcpy(usrno, user->userid);
    char usrno_f[12];
    FILE *fp;
    fp = fopen("user.txt", "r+");
    if (fp == nullptr) fopen("user.txt", "w");
    while (fscanf(fp, "%s%*s", usrno_f) != EOF)
    {
        if (strcmp(usrno, usrno_f) == 0)
        {
            check = false;
            break;
        }
    }
    if (fclose(fp))
    {
        printf("Can not close the file!\n");
        exit(0);
    }
    return check;
}

/**��¼ʱ���ڼ���û��Ϸ���:��ȷ����true*/
bool Syuser::checkUserValid(User *user)
{

    //�򿪴洢�û��˺�������ļ�user.txt
    FILE *user_file_p;
    user_file_p = fopen("user.txt", "r");
    if (user_file_p == nullptr)
    {
        user_file_p = fopen("user.txt", "w");
    }
    char usr[30], pwd[10];  //usr[30]���û���ʱ����ģ�user->userid��user->password���ɱ��������β�user��ֵ����
    char usr_f[30];  //usr_f[30]�Ǵ�user.txt���ȡ�ģ��û��˺�+�ո�+����+\n��
    bool check = false;
    //��(�û������ո����롢\n)���ӳ����ַ���usr��������user.txt�ļ��м��ƥ��
    strcpy(usr, user->userid);
    strcat(usr, " ");
    strcpy(pwd, user->password);
    strcat(usr, pwd);
    strcat(usr, "\n");
    //���ļ��ж����û���Ϣ���ݣ������ж��û���ʱ����ĺ�user.txt��ģ��û��˺�+�ո�+����+\n���Ƿ�ƥ��
    while (feof(user_file_p) == 0)
    {
        fgets(usr_f, 30, user_file_p); //�����ж�һ�л�ָ�����ַ�

        if (strcmp(usr, usr_f) == 0)
        {
            cout << "check = true" << endl;
            check = true;
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

/**��ӭ����*/
void Syuser::welcome_title()
{
    time_t time_login;
    struct tm *p;
    time(&time_login);
    p = gmtime(&time_login);

    if (!check_login_success)
    {
        printf("--------------------------------------------------------------------------------\n");
        printf("��ӭ�����װ����û���\n");
        cout << "\t              �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
        cout << "\t              �U    ��ӭ����ͼ�����ϵͳ  �U" << endl;
        cout << "\t              �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
        printf("                        ����ʱ�䣺%d��%d��%d�� %d:%d:%d\n", 1900 + p->tm_year,
               1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
        printf("                                                                                \n");
        printf("                              Author :---    ***************          \n");
        printf("                                                                                \n");
        printf("--------------------------------------------------------------------------------\n");
    }
    else
    {
        printf("--------------------------------------------------------------------------------\n");
        printf("��ӭ����%s��\n", user_number);
        cout << "\t              �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
        cout << "\t              �U    ��ӭ����ͼ�����ϵͳV1.0  �U" << endl;
        cout << "\t              �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
        printf("                        ����ʱ�䣺%d��%d��%d�� %d:%d:%d\n", 1900 + p->tm_year,
               p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
        printf("                                                                                \n");
        printf("                              Author :---    ***************          \n");
        printf("                                                                                \n");
        printf("--------------------------------------------------------------------------------\n");
    }

}

/**ע��*/
int Syuser::create_user()
{
    User user;//����user����������ռ�
    FILE *fp;
    fp = fopen("user.txt", "a"); //׷�ӷ�ʽ���ļ�
    //��user.txt�����򴴽�user.txt�ļ�
    if (fp == nullptr) fopen("user.txt", "w"); //ֻд��ʽ���ļ�
a:
    system("cls");
    //��ӡע�����ʾ��Ϣ
    printf("\n");
    printf("===================================ע�����û�===================================");
    printf("\n\n");
    printf("  ����ܰ����:��\n\n");
    printf("  ���û��˺š�������11λ�ֻ���,��ע�����ֱ�ӵ�¼\n\n");
    printf("  �����롿����<=8λ��������ʹ��Ӣ���ַ������֣�������ո�\n\n");
    printf("           p.s.Ϊ����������˽����������벻����ʾ����Ļ��\n\n");
    printf("================================================================================");
    printf("\n\n");
    printf("==========>>>>>>�������µ��ֻ��ţ����س�������");
    scanf("%s", user.userid);
    printf(user.userid);
    printf("\n");

    //�ж�������û��˺��Ƿ�ע���
    if (this->check_userid(&user))
    {
        //��ʾ���벢�����û��״��������������user.password[i]
        printf("==========>>>>>>�������µ����룬���س�������");
        int i = 0;
        while (0 < i < 8 && (user.password[i] = getch()) != '\r')//���û��������벢ȷ�ϣ�������Enter����
        {
            //�û�����������Ĺ�������ɾ����Ϊ��������backspace�˸����
            if (user.password[i] == '\b')//user.password[i]���鳤�ȼ���iλ
            {
                if (i <= 0) {}
                else { i--; }
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
        user.password[i] = '\0';//�����ַ�����β����user.password[i]����

        //��ʾ�������û��ٴ���������� check_password[8]
        char check_password[8];
        printf("\n\n==========>>>>>>���ٴ��������룬���س�������");
        i = 0;
        for (i = 0; i < 8; i++)
        {
            check_password[i] = '\0';
        }
        i = 0;
        while (0 < i < 8 && (check_password[i] = getch()) != '\r')
        {
            if (check_password[i] == '\b')
            {
                if (i <= 0) {}
                else { i--; }
            }
            else
            {
                i++;
                if (i > 8)
                {
                    printf("\n       ע�⣺�Ѿ��ﵽ8λ�ַ����ޣ�ֻ��ǰ8λ������ַ���ЧŶ\n");
                    i = i - 1;
                }
            }
        }
        check_password[i] = '\0';
        printf(user.userid);

        //�Ƚ�user.password[i]��check_password[8]
        if (strcmp(check_password, user.password) == 0) {}
        else
        {
            printf("\n\n========>>!!!!!!!�����������벻һ�£�������ע��...\n");
            Sleep(1000);
            goto a;
        }

        printf(user.userid);
        //��user������ֵ(user.userid��user.password)��ʽ�������user.txt�ļ�
        fprintf(fp, "%s ", user.userid);
        fprintf(fp, "%s", user.password);
        fprintf(fp, "\n");
        fclose(fp);
        //��ӡע��ɹ�����ʾ��Ϣ
        printf("\n\n\n\n");
        printf("ע��ɹ�!���ס�����û�����%s", user.userid);
        printf("���������μ��������룡\n\n");
        //����������������ҷ�����ҳ���˵�
        printf("\n\n\n\n��������������˵���ѡ��¼����");
        system("pause");
        system("cls");
        return 1;
    }
    else
    {
        printf("%s ����ֻ��ű�ע�����Ŷ~\n", user.userid);
        cout << "�Ƿ����ע��?[1]�� [2]��:" << endl;
        int ch;
        cin >> ch;
        if (ch == 1) { goto a; }
        else { return 0; }
    }
}

/**��¼*/
int Syuser::login()
{
    User user;
    int check = 0;
    system("cls");
    this->welcome_title();//��ӡ������
    //��ʾ���벢����su.userid
    printf("\n\n=======>>>>>>������11λ�ֻ��ţ����س���������");
    scanf("%s", user.userid);// TODO �����ļ���д��user.idû��д��ȥ,δ֪ԭ��
    printf("\n\n");
    //��ʾ���벢����su.password
    printf("                       ������С�ڵ���8λ������\n\n");
    printf("         ����������ʱ������ʾ����Ļ�ϣ�����ʱ�밴�س�������Ŷ\n\n");
    printf("======================>>>>>>>>>�����룺");
//    scanf("%s", user.password);
    int i = 0;
    while ((0 < i < 8) && (user.password[i] = getch()) != '\r')
    {
        if (user.password[i] == '\b')
        {
            if (i <= 0) {}
            else { i--; }
        }
        else
        {
            i++;
            if (i > 8)
            {
                printf("\n===>>!!!!ע�⣺�Ѿ��ﵽ8λ�ַ����ޣ����μ�����ַ�����Ч��\n\n");
                i = i - 1;
            }
        }
    }
    user.password[i] = '\0';
    //����û��Ϸ���
    // TODO ����Ū����,����û�취,��������ļ��������,��û���ü���
    if (!this->checkUserValid(&user))
    {
        strcpy(user_number, user.userid);
        check = 1;
        printf("\n\n\n");
        printf("\t\t<<<<<<<<<<<<<��¼�ɹ�!>>>>>>>>>>\n");
        printf("\n");
        printf("��������������˵�...");
        char ch = getch();
        system("cls");
    }
    else
    {
        printf("\n\n\n");
        printf("======!!!!���û������ڻ����������˶Ժ����µ�¼����ע������˺ţ�\n\n");
        printf("                   ����������������Ա��ϵ!\n\n");
        printf("\n\n\n\n��������������˵�...");
        char ch = getch();
        system("cls");
    }
    return check;
}

//=======================Bookͼ����������=================//
/**����һ��Books������:����ͼ������*/
class Books
{
public:
    //�麯��
    virtual void showInfo() = 0;  //��ʾ�鼮��Ϣ

//    virtual string Category() = 0;//ͼ�����

    int book_ID;        //ͼ����

    string book_Name;   //ͼ����

    int book_kindId;    //ͼ������

    double book_Price;  //ͼ��۸�

    int book_Num;       //ͼ������
};

//=======================ͼ���������=================//
class BookKind : public Books
{

public:
    void showInfo() override;

    static string Category(int x_id);

    BookKind(int id, string name, int x_id, double price, int num)
    {
        this->book_ID = id;
        this->book_Name = std::move(name);
        this->book_kindId = x_id;
        this->book_Price = price;
        this->book_Num = num;
    }
};

/**���ͼ���������*/
void BookKind::showInfo()
{
    cout << "ͼ���ţ� " << this->book_ID
         << "\t ͼ������" << this->book_Name
         << "\t ͼ����ࣺ " << BookKind::Category(book_kindId)
         << "\t ͼ��۸�" << this->book_Price
         << "\t ͼ���棺" << this->book_Num << endl;
}

/**���ض�Ӧ��ͼ�����*/
string BookKind::Category(int x_id)
{
    if (x_id == 1) { return "�������"; }
    else if (x_id == 2) { return "��ѧ��"; }
    else if (x_id == 3) { return "��Ȼ��ѧ��"; }
    else if (x_id == 4) { return "����ѧ��"; }
    else if (x_id == 5) { return "С˵"; }
    else if (x_id == 6) { return "�������"; }
    else { return "δ֪����"; }
}

//=======================ʵ��ϵͳ��Ҫ���ܵ���=================//
/**������:���ͼ�������ز���*/
class Library
{
public:
    Library();//���캯��:��ʼ��

    Books **book_Array; //���ڴ��ͼ�������

    int book_Total;     //ͼ������

    bool isFile = false;        //�ж��ļ��Ƿ�Ϊ��,��:false

    void Add_book();    //���ͼ��

    void Show_book() const;     //ͼ����Ϣ��ʾ

    void Borrow_and_return();   //ͼ��黹�����

    void Find_book() const;     //����Ż���������ͼ��

    void Revise_book();         //�޸�ͼ��

    void Delete_book();         //ɾ��ͼ��

    void Sort_book();           //����������

    void Save_file();           //�����ļ�

    void Clean_file();          //���ͼ���б�

    void Cin_file();            //�ļ�����

    int Total_num();            //ͳ������

    int Exist_or_not(const string &name) const;//�жϽ������Ƿ����

    static void menu_1();      //���߲˵�
    static void menu_2();      //ͼ�����Ա�˵�
    static void menu_3();      //ϵͳ����Ա�˵�

    ~Library()
    {
        if (this->book_Array != nullptr)
        {
            delete[]this->book_Array;
            this->book_Array = nullptr;
        }
    }           //�鹹���������ͷſռ�

};

/**���캯��������Library�ĳ�ʼ��*/
Library::Library()
{
//��ʼ������
    fstream file("library.txt");
//    file.open("library.txt");
    if (!file.is_open()) //�ļ�������
    {
        cout << "�ļ������� \n";
        this->book_Total = 0;
        this->isFile = false;
        this->book_Array = nullptr;
        file.close();
        return;
    }
    //�ļ�����
    char ch;
    file >> ch;
    if (file.eof())//�ж��ļ��Ƿ�Ϊ��
    {
        cout << "�ļ�Ϊ��! \n";
        this->book_Total = 0;
        this->isFile = false;
        this->book_Array = nullptr;
        file.close();
        return;
    }
    if (file)
    {
        //���ļ��������ļ�������
        int num = this->Total_num();
        cout << "����ͼ������Ϊ��" << num << endl;
        this->book_Total = num;
        //����ͼ�����������鲢���ٿռ�
        cout << "ͼ���ļ����سɹ�...." << endl;
        this->book_Array = new Books *[this->book_Total];
        //�ļ����ݵ������������
        int id;
        string name;
        int x_id;
        double price;
        int number;

        int index = 0;
        while (file >> id && file >> name && file >> x_id && file >> price && file >> number)
        {
            Books *Book;
            Book = new BookKind(id, name, x_id, price, number);
            this->book_Array[index] = Book;
            index++;
        }
        file.close();
        isFile = true;
        printf("\n�����ļ��ѳɹ���ף��ʹ����죡\n\n");
//        this->Cin_file();//�в�ͨ
        Sleep(1000);
    }
}

/**���߲˵�*/
void Library::menu_1()
{
    system("cls");
    printf("\t       ++++ͼ�����ϵͳ++++\n");
    printf("\t\t\n");
    cout << "	***************************************************" << endl;
    cout << "	*           ��ѡ���Ӧ����                        *" << endl;
    cout << "	***************************************************" << endl;
    cout << "	* 1.��ʾ����ͼ����Ϣ                              *" << endl;
    cout << "	* 2.ͼ�������黹                                *" << endl;
    cout << "	* 3.ͼ�����                                      *" << endl;
    cout << "	* 4.ͼ������鿴                                  *" << endl;
    cout << "	* 5.�����ϼ��˵�                                  *" << endl;
    cout << "	* 6.�������˵�                                    *" << endl;
    cout << "	* 0.ֱ���˳��ó���                                *" << endl;
    cout << "	***************************************************" << endl;
    cout << "=======>>>>>>  " << endl;
}

/**ͼ�����Ա�˵�*/
void Library::menu_2()
{
    printf("\t\t ͼ�����ϵͳ\n");
    printf("\t\t\n");
    cout << "	***************************************************" << endl;
    cout << "	*           �������Ӧ���ܵ�������ɲ���           *" << endl;
    cout << "	* 1.�ɱ����                                     *" << endl;
    cout << "	* 2.��ʾ����ͼ����Ϣ                              *" << endl;
    cout << "	* 3.�鿴ͼ�������黹��Ϣ                        *" << endl;
    cout << "	* 4.ͼ�����                                     *" << endl;
    cout << "	* 5.ͼ���޸�                                     *" << endl;
    cout << "	* 6.ͼ��ɾ��                                     *" << endl;
    cout << "	* 7.ͼ������                                     *" << endl;
    cout << "	* 8.�������ͼ��                                  *" << endl;
    cout << "	* 9.�����ϼ��˵�                                  *" << endl;
    cout << "	* 0.ֱ���˳��ó���                                *" << endl;
    cout << "	***************************************************" << endl;
}

/**ϵͳ����Ա�˵�*/
void Library::menu_3()
{
    system("cls");
    cout << ">>>>�������ڿ�����,�����ڴ�<<<<" << endl;
    cout << "������������ϼ��˵�...." << endl;
    while (getch()) { return; }
}

/**ʵ�ֲɱ���⹦��*/
void Library::Add_book()
{
    cout << "���������ͼ��������� \n";
    int addNum = 0;
    cin >> addNum;
    if (addNum > 0)
    {
        //���
        int newSize = this->book_Total + addNum;
        //�����¿ռ�
        auto **newSpace = new Books *[newSize];
        if (this->book_Array != nullptr)
        {
            for (int i = 0; i < this->book_Total; ++i)
            {
                newSpace[i] = this->book_Array[i];
            }
        }
        //���������
        for (int i = 0; i < addNum; ++i)
        {
            int id;
            string name;
            int dSelect;
            double price;
            int num;

            cout << "������� " << i + 1 << " ����ͼ��ı�ţ�" << endl;
            cin >> id;
            cout << "----------------------------" << endl;
            cout << "������� " << i + 1 << " ����ͼ������" << endl;
            cin >> name;
            cout << "----------------------------" << endl;
            cout << "1��������� " << endl
                 << "2����ѧ�� " << endl
                 << "3����Ȼ��ѧ�� " << endl
                 << "4������ѧ�� " << endl
                 << "5��С˵ " << endl
                 << "6��������� " << endl
                 << "��ѡ���ͼ������:" << endl;
            cin >> dSelect;
            cout << "----------------------------" << endl;
            cout << "������� " << i + 1 << " ����ͼ��ļ۸�" << endl;
            cin >> price;
            cout << "----------------------------" << endl;
            cout << "������� " << i + 1 << " ����ͼ��Ŀ�棺" << endl;
            cin >> num;
            cout << "----------------------------" << endl;
            Books *Book = nullptr;
            Book = new BookKind(id, name, dSelect, price, num);

            //������ָ�뱣����������
            newSpace[this->book_Total + i] = Book;
        }
        //�ͷ�ԭ�еĿռ�
        delete[]this->book_Array;
        //�ı�ռ�ָ��
        this->book_Array = newSpace;
        //����ͼ�鲻Ϊ�ձ�־
        this->isFile = true;
        //�ı�ָ�볤��
        this->book_Total = newSize;
        //��ӵ��ļ���
        cout << "�ɹ���� " << addNum << " ����ͼ�� \n";
        this->Save_file();//����
    }
    else { cout << "������������ \n"; }
    system("pause");
    system("cls");
}

/**��ʾ����ͼ����Ϣ*/
void Library::Show_book() const
{
    if (!this->isFile)
    {
        cout << "\n    ===>>>�ļ������ڻ���Ϊ�գ�<<<===" << endl;
    }
    else
    {
        for (int i = 0; i < book_Total; ++i)
        {
            this->book_Array[i]->showInfo();
        }
    }
    system("pause");
    system("cls");
}

/**����/�黹*/
void Library::Borrow_and_return()
{
    if (!this->isFile)
    {
        cout << "!!!!>>>>>>�ļ������ڻ��¼Ϊ�գ� \n";
        system("pause");
        system("cls");
    }
    else
    {
        cout << "======1.���� ======\n";
        cout << "======2.���� ======\n";
        int select = 0;
        cin >> select;

        cout << "======>>>������������\n";
        string name;
        cin >> name;
        int ret = this->Exist_or_not(name);
        if (ret != -1)
        {
            this->book_Array[ret]->showInfo();
            if (select == 1)
            {
                if (this->book_Array[ret]->book_Num != 0)
                {
                    this->book_Array[ret]->book_Num--;
                    cout << "����ɹ��� \n";
                }
                else { cout << "�����ѱ����꣡ \n"; }
            }
            else if (select == 2)
            {
                this->book_Array[ret]->book_Num++;
                cout << "����ɹ��� \n";
            }
            else { cout << "��������� \n"; }
            this->book_Array[ret]->showInfo();
        }
        else { cout << "���鲻����ͼ��ݣ� \n"; }
    }
    this->Save_file();//����
    system("pause");
    system("cls");
}

/**ͼ�����*/
void Library::Find_book() const
{
    if (!this->isFile)
    {
        cout << "�ļ������ڻ��¼Ϊ�գ� \n";
    }
    else
    {//���м򵥵�˳�����
        cout << "��������ҵķ�ʽ�� \n";
        cout << "=====1.��ͼ���Ų��� =====\n";
        cout << "=====2.��ͼ���������� =====\n";
        int select = 0;
        cin >> select;
        if (select == 2)
        {
            string name;
            cout << "��������ҵ�ͼ�������� \n";
            cin >> name;
            int ret;
            ret = this->Exist_or_not(name);

            if (ret != -1)
            {
                cout << "���ҳɹ�����ͼ����Ϣ���£� \n";
                this->book_Array[ret]->showInfo();
            }
            else { cout << "����ʧ�ܣ����޴��� \n"; }
        }
        else if (select == 1)
        {
            int id = 0;
            cout << "��������ҵ�ͼ���ţ� \n";
            cin >> id;
            bool flag = false;//�ҵ���Ϊtrue
            for (int i = 0; i < this->book_Total; ++i)
            {
                if (this->book_Array[i]->book_ID == id)
                {
                    cout << "���ҳɹ���ͼ����Ϊ�� "
                         << this->book_Array[i]->book_ID
                         << "��ͼ����Ϣ���£� \n";
                    flag = true;
                    this->book_Array[i]->showInfo();
                }
            }
            if (!flag) { cout << "����ʧ�ܣ����޴��飡 \n"; }
        }
        else { cout << "����ѡ������ \n"; }
    }
    system("pause");
    system("cls");
}

/**ͼ����Ϣ�޸�*/
void Library::Revise_book()
{
    if (!this->isFile) { cout << "�ļ������ڻ��¼Ϊ�գ� \n"; }
    else
    {
        cout << "�������޸�ͼ������֣� \n";
        string name;
        cin >> name;

        int ret = this->Exist_or_not(name);
        if (ret != -1)
        {
            //����
//            delete this->book_Array[ret];
            int newId = 0;
            string newName;
            int dSelect = 0;
            double price;
            int number;

            this->book_Array[ret]->showInfo();
            cout << "��������ͼ��ı�ţ� \n";
            cin >> newId;
            cout << "----------------------------" << endl;
            cout << "��������ͼ������ \n";
            cin >> newName;
            cout << "----------------------------" << endl;
            cout << "1��������� " << endl
                 << "2����ѧ�� " << endl
                 << "3����Ȼ��ѧ�� " << endl
                 << "4������ѧ�� " << endl
                 << "5��С˵ " << endl
                 << "6��������� " << endl
                 << "��ѡ���ͼ������:" << endl;
            cin >> dSelect;
            cout << "----------------------------" << endl;
            cout << "��������ͼ��ļ۸� \n";
            cin >> price;
            cout << "----------------------------" << endl;
            cout << "��������ͼ��Ŀ�棺 \n";
            cin >> number;
            cout << "----------------------------" << endl;

            Books *Book = nullptr;
            Book = new BookKind(newId, name, dSelect, price, number);
            //�������ݵ�������
            this->book_Array[ret] = Book;
            cout << "�޸ĳɹ��� \n";
            //���浽�ļ���
            this->Save_file();
        }
        else
        {
            cout << "�޸�ʧ�ܣ����޴��� \n";
        }
    }
    system("pause");
    system("cls");
}

/**ɾ����Ӧͼ��*/
void Library::Delete_book()
{
//��������ǰ�ƣ��ҵ�λ�õĺ�һλ��
    if (!this->book_Array) { cout << "�ļ������ڻ��ļ�Ϊ��! \n"; }
    else
    {
        //����ͼ�������ɾ��
        cout << "��������Ҫɾ����ͼ�����֣� \n";
        string name;
        cin >> name;
        int index = this->Exist_or_not(name);
        if (index != -1)
        {
            //book_Total = 1ʱ������ѭ��
            for (int i = 0; i < this->book_Total - 1; ++i)
            {
                //����ǰ��
                this->book_Array[i] = this->book_Array[i + 1];
            }
            //��������
            this->book_Total--;
            //����ͬ�����ļ���
            this->Save_file();

            cout << "ɾ���ɹ��� \n";
        }
        else { cout << "ɾ��ʧ�ܣ�δ�ҵ���ͼ�飡 \n"; }
    }
    this->Save_file();
    system("pause");
    system("cls");
}

/**ͼ������*/
void Library::Sort_book()
{
    if (!this->isFile)
    {
        cout << "�ļ������ڻ��¼Ϊ�գ� \n";
        system("pause");
        system("cls");
    }//�ļ�������
    else//���м�ѡ������
    {
        cout << "��ѡ������ʽ�� \n";
        cout << "1.��ͼ���Ž������� \n";
        cout << "2.��ͼ���Ž��н��� \n";

        int select = 0;
        cin >> select;
        for (int i = 0; i < book_Total; ++i)
        {
            int minOrMax = i;
            for (int j = i + 1; j < book_Total; ++j)
            {
                if (select == 1)//��ͼ���Ž�������
                {
                    if (book_Array[minOrMax]->book_ID > book_Array[j]->book_ID)
                    {
                        minOrMax = j;
                    }
                }
                else            //��ͼ���Ž��н���
                {
                    if (book_Array[minOrMax]->book_ID < book_Array[j]->book_ID)
                    {
                        minOrMax = j;
                    }
                }
            }
            if (i != minOrMax)
            {
                Books *temp = book_Array[i];
                book_Array[i] = book_Array[minOrMax];
                book_Array[minOrMax] = temp;
            }
        }
        cout << "����ɹ����������Ϊ�� \n";
        this->Save_file();
        this->Show_book();
    }
}

/**�ļ�����*/
void Library::Save_file()
{
    ofstream ofs;
    ofs.open("library.txt", ios::out);

    for (int i = 0; i < this->book_Total; ++i)
    {
        ofs << this->book_Array[i]->book_ID << " "
            << this->book_Array[i]->book_Name << " "
            << this->book_Array[i]->book_kindId << " "
            << this->book_Array[i]->book_Price << " "
            << this->book_Array[i]->book_Num << endl;
    }
    ofs.close();
}

/**���ͼ��*/
void Library::Clean_file()
{
    cout << "ȷ����գ� \n";
    cout << "!!!!>>>1. ȷ�� <<<!!!" << endl;
    cout << "!!!!>>>2. ���� <<<!!!" << endl;
    int select = 0;
    cin >> select;
    if (select == 1)
    {
        //trunc ��������ļ� ��ɾ�����ؽ�
        ofstream ofs("library.txt", ios::trunc);
        ofs.close();

        //�������
        if (this->book_Array != nullptr)
        {
            for (int i = 0; i < this->book_Total; ++i)
            {
                if (this->book_Array[i] != nullptr)
                {
                    delete this->book_Array[i];
                }
            }
            this->book_Total = 0;
            delete[]this->book_Array;
            this->book_Array = nullptr;
            this->isFile = false;
        }
        cout << "��ճɹ��� \n";
    }
    this->Save_file();
    system("pause");
    system("cls");
}

/**�ļ�����*/
void Library::Cin_file()
{
    ifstream ifs;
    ifs.open("library.txt", ios::in);

    int id;
    string name;
    int x_id;
    double price;
    int number;

    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> x_id && ifs >> price && ifs >> number)
    {
        Books *Book;
        Book = new BookKind(id, name, x_id, price, number);
        this->book_Array[index] = Book;
        index++;
    }
    ifs.close();
    printf("\n�����ļ��ѳɹ���ף��ʹ����죡\n\n");
}

/**ͳ��������*/
int Library::Total_num()
{
    ifstream ifs;
    ifs.open("library.txt", ios::in);

    int id;
    string name;
    int x_id;
    double price;
    int number;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> x_id && ifs >> price && ifs >> number)
    {
        num++;
    }
    ifs.close();

    return num;
}

/**�жϽ������Ƿ����*/
int Library::Exist_or_not(const string &name) const
{
    int index = -1;

    for (int i = 0; i < book_Total; ++i)
    {
        if (this->book_Array[i]->book_Name.find(name) != string::npos)
        {
            index = i;
            break;
        }
    }
    return index;
}

//==================Person��ʵ�ֲ�ͬ��ݲ���=========================//
/**����Person��ʵ�ֲ�ͬ��ݲ���*/
class Person : public Library
{
public:
    bool back_2 = true;

    Person() = default;//

    static void menu_0();      //�洫��¼����

    static void menu_start();  //��ʼ

    void function_1();  //�ṩ���ܽӿ�1:����ע���¼
    void function_2();  //�ṩ���ܽӿ�2:ͼ�����Ա
    void function_3();  //�ṩ���ܽӿ�3:ϵͳ����Ա
    void function_4();  //�ṩ���ܽӿ�4:���߾������
    void function_5();  //�ṩ���ܽӿ�4:���������


    static void Drop_out();//ȫ���˳�����
//    ~ Person();
};

/**��ʼ�˵�:���ѡ��*/
void Person::menu_start()
{
    system("cls");
    time_t time_login;
    struct tm *p;
    time(&time_login);
    p = gmtime(&time_login);
    printf("--------------------------------------------------------------------------\n");
    printf("+++++++++++>>>>>\n");
    cout << "\t              �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "\t              �U    ��ӭ����ͼ�����ϵͳ  �U" << endl;
    cout << "\t              �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    printf("                        ����ʱ�䣺%d��%d��%d�� %d:%d:%d\n", 1900 + p->tm_year,
           1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
    printf("                                                                                \n");
    printf("                              Author :---    ***************          \n");
    printf("                                                                                \n");
    printf("--------------------------------------------------------------------------\n");
    printf("\n\n===========================================================\n");
    printf("             1�����ǡ����ߡ�\n\n");
    printf("             2�����ǡ�ͼ�����Ա��\n\n");
    printf("             3�����ǡ�ϵͳ����Ա��\n\n");
    printf("             0���˳�ϵͳ\n\n");
    printf("=======>>>>>>>>>��ѡ��������ݣ�");

}

/**�洫��¼����*/
void Person::menu_0()
{
    system("cls");
    system("color b");
    time_t timep;    //ϵͳʱ��
    struct tm *p_1;
    time(&timep);
    p_1 = gmtime(&timep);

    printf("\t\t\t\t\t\t  ��ǰʱ��%02dʱ%02d��\n", 8 + p_1->tm_hour, p_1->tm_min);
    printf("\t\t\t\t\t\t   %d��%02d��%02d��\n", 1900 + p_1->tm_year, 1 + p_1->tm_mon, p_1->tm_mday);
    printf("\t������������������������������������������������������\n\n");
    printf("\t��\t\t\t\t\t������Զ�����������ֺ��� \t\t\t\t\t��\n\n");
    printf("\t��\t\t\t*****************************************************\t\t\t\t��\n\n");
    printf("\t��\t\t\t\t\t ͼ�����ϵͳ V1.0\t\t\t\t\t\t��\n\n");
    printf("\t��\t\t\t  ������:--- רҵ:���ܿ�ѧ�뼼�� ѧ��:--------------\t\t\t��\n\n");
    printf("\t��\t\t\t*****************************************************\t\t\t\t��\n\n");
    printf("\t��\t\t\t  ��ӭʹ��ѧ��ͨѶ¼ϵͳ,ף��ʹ�����! \t\t\t\t\t\t��\n\n");
    printf("\t������������������������������������������������������\n\n");
    printf("��������λ��½���룡(123456)\n");

    int i = 4;
    while (true)
    {
        int x = 0;
        char c;
        char code[20] = {'1', '2', '3', '4', '5', '6'}, passwoSD[20]; //��������
        while (x < 6 && c != 13)
        {
            c = getch();
            putchar('*');
            passwoSD[x] = c;
            x++;
        }
        passwoSD[x] = '\0';
        if (strcmp(passwoSD, code) != 0)
        {
            fflush(stdin);
            printf("\n������������������%d�λ��ᣬ���������룺", i--);
            if (i == -1)
            {
                cout << "\n��¼ʧ��!����ϵϵͳ����Ա..." << endl;
                Sleep(1500);
                exit(0);
            }
        }
        else { break; }
    }
    Sleep(500);
    printf("\nͼ�����ϵͳ�����ѳɹ����װ���ϵͳ����Ա ף��ʹ����죡\n\n");
    printf("�밴���������ҳ��˵���\n\n");
    system("pause");
    system("cls");    //����
}

/**�ṩ���ܽӿ�1:����ע�����*/
void Person::function_1()
{
    Syuser US;//ʵ�л�һ���û�����ע���¼
    int choice = 0;
    while (back_2)
    {
        system("cls");
        US.welcome_title();//��ӭ����
        printf("\n\n");
        printf(" *++*     *++*  1��ע��\n\n");
        printf("  *++++++++*    2����¼\n\n");
        printf("      *+*       3�������\n\n");
        printf("    *+++++*     4�������ϼ��˵�\n\n");
        printf(" *+++++*+++++*  0���˳���ϵͳ\n\n");
        printf("\n\n");
        printf("==================>>>>>������ѡ��ǰ�ı�ţ����س���������");
        cin >> choice;
        if (choice == 0)
        {
            Person::Drop_out();//�˳�����
            break;
        }
        if (choice == 1)
        {
            US.create_user();
        }
        else if (choice == 2)
        {
            if (US.login() == 1)
            {
                this->function_4();
            }
        }
        else if (choice == 3)
        {
            this->function_5();
        }
        else if (choice == 5)
        {
            back_2 = false;
            break;
        }
        else
        {
            cout << "=====>>>>�����...,��δ�����ù���1" << endl
                 << "====>>>����������" << endl << flush;
        }
    }
}

/**�ṩ���ܽӿ�2:ͼ�����Ա*/
void Person::function_2()
{
//    Library MA;//ʵ�л�һ��ͼ�����Ա����
//    this->Cin_file();//�Զ������ļ�
    int choice = 0;
    bool flag = true;
    while (flag)
    {
        system("cls");
        this->menu_2();
        cin >> choice;
        switch (choice)
        {
            case 0://ֱ���˳��ó���
                this->Save_file();//�˳�ǰ����
                Drop_out();
                break;
            case 1://�ɱ����
                this->Add_book();
                break;
            case 2://��ʾ����ͼ����Ϣ
                this->Show_book();
                break;
            case 3: //�鿴ͼ�������黹��Ϣ
                cout << "��δ����,�����ڴ�" << endl;
                system("pause");
                break;
            case 4://ͼ�����
                this->Find_book();
                break;
            case 5://ͼ���޸�
                this->Revise_book();
                break;
            case 6://ͼ��ɾ��
                this->Delete_book();
                break;
            case 7://ͼ������
                this->Sort_book();
                break;
            case 8://�������ͼ��
                this->Clean_file();
                break;
            case 9://�����ϼ��˵�
                flag = false;
                break;
            default://other
                cout << "ѡ����,ѡ����,�ù��ܻ�δ����..." << endl;
                break;
        }
    }
}

/**�ṩ���ܽӿ�3:ϵͳ����Ա*/
void Person::function_3()
{
    this->menu_3();
}

/**�ṩ���ܽӿ�4:���߾������*/
void Person::function_4()
{
    int choice;
    bool isFlag = true;
    while (isFlag)
    {
        this->menu_1();
        cin >> choice;
        switch (choice)
        {
            case 1://��ʾ����ͼ����Ϣ
                this->Show_book();
                break;
            case 2://ͼ�������黹
                this->Borrow_and_return();
                break;
            case 3://ͼ�����
                this->Find_book();
                break;
            case 4://ͼ������鿴
                this->Sort_book();
                break;
            case 5://�����ϼ��˵�
                return;
                break;
            case 6://ֱ�ӷ������˵�
                back_2 = isFlag = false;
                break;
            case 0://ֱ���˳��ó���
                Person::Drop_out();
                break;
            default://other
                cout << "ѡ����,ѡ����,�ù��ܿ��ܻ����ڿ����׶�..." << endl;
                system("cls");
                break;
        }
    }
}

/**�ṩ���ܽӿ�4:���������*/
void Person::function_5()
{
    int choice;
    bool isFlag = true;
    while (isFlag)
    {
        system("cls");
        printf("\t       ++++ͼ�����ϵͳ++++\n");
        printf("\t\t\n");
        cout << "	***************************************************" << endl;
        cout << "	*           ��ѡ���Ӧ����                        *" << endl;
        cout << "	***************************************************" << endl;
        cout << "	* 1.��ʾ����ͼ����Ϣ                              *" << endl;
        cout << "	* 2.ͼ�����                                      *" << endl;
        cout << "	* 3.ͼ������鿴                                  *" << endl;
        cout << "	* 4.�����ϼ��˵�                                  *" << endl;
        cout << "	* 5.�������˵�                                    *" << endl;
        cout << "	* 0.ֱ���˳��ó���                                *" << endl;
        cout << "	***************************************************" << endl;
        cout << "=======>>>>>>  " << endl;
        cin >> choice;
        switch (choice)
        {
            case 1://��ʾ����ͼ����Ϣ
                this->Show_book();
                break;
            case 2://ͼ�����
                this->Find_book();
                break;
            case 3://ͼ������鿴
                this->Sort_book();
                break;
            case 4://�����ϼ��˵�
                return;
                break;
            case 5://ֱ�ӷ������˵�
                back_2 = isFlag = false;
                break;
            case 0://ֱ���˳��ó���
                Person::Drop_out();
                break;
            default://other
                cout << "ѡ����,ѡ����,�ù��ܿ��ܻ����ڿ����׶�..." << endl;
                system("cls");
                break;
        }
    }
}

/**ȫ���˳�����*/
void Person::Drop_out()
{
//    system("cls");
    cout << "\t\t                      �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "\t\t                      �U    ��ӭ�ٴ�ʹ�ã��ټ�    �U" << endl;
    cout << "\t\t                      �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    system("pause");//�����������
    exit(0);//���������ĸ����ֵ���������� �˳����� 0 - �˳�����
}

//===================================================//
//������
int main(int argc, char const *argv[])
{
//    system("chcp 936");
    system("color a");
    Person person;
    int choice;
    while (true)
    {
        person.menu_start();//��ݽ���ѡ��
        cin >> choice;
        if (choice == 0)
        {
            person.Drop_out();//�˳�����
            break;
        }//�˳�
        if (choice == 1) { person.function_1(); } //����
        else if (choice == 2)
        {
            person.function_2();
        }//ͼ�����Ա
        else if (choice == 3)
        {
            person.menu_0();//����Ա��¼����
            person.function_3();//����Ա��������
        }//ϵͳ����Ա
        else
        {
            cout << "***************************************" << endl;
            cout << "\n=====>>>>��δ�����ù���,�����ڴ�" << endl
                 << "====>>>����������" << endl << flush;
            cout << "***************************************" << endl;
            continue;
        }
    }
    return 0;
}




