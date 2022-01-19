// Created by yxn on 2021/11/10.
//��ĿҪ��
//��1��ϵͳ���ܣ��Ӽ��̻��ļ��ж���ͨѶ����Ϣ��ͨ��������š���������
//�𡢵绰�Լ���ַ���������ʵ��ͨѶ����Ϣ�Ĳ��롢��ѯ��ɾ���������Լ�
//ͨѶ¼���������ȹ��ܡ�
//��2������ɶ��������ݵ��ݴ��Խ��м�飬��֤���ݵĺϷ��ԣ����Ա�ȡ
//ֵֻ��Ϊ�л�Ů��
//��3���û�������Ѻ��ԣ�������ṩ���û�֮�����Ľ����Լ���Ӧ�Ĳ�
//�����û�ѡ��
//��ĿĿ�ģ�
//��1��������Ա�Ĵ洢��ʾ�������������
//��2������ļ��Ĵ򿪡��رղ�����
#include <conio.h>
#include <fstream>//�ļ��������
#include <iomanip>//ʹ��setw()����
#include <iostream>
#include <cstdio>
#include <windows.h>


using namespace std;

/**ͨѶ¼�ڵ����ݶ���*/
typedef struct
{
    string stuid;  //ѧ��
    string name;   //����
    string sex;    //�Ա�
    string phone;  //�绰����
    string addr;   //ͨѶ��ַ
} DataType;

/**�ڵ����Ͷ���*/
typedef struct Node
{
    DataType data;     //�ڵ�������
    struct Node *next; //�ڵ�ָ����
} ListNode, *LinkList;

/**��Ķ���*/
class StudentDirectory
{
public:
    StudentDirectory()      //����������һ��������
    {
        head = new ListNode;
        head->next = nullptr;
    }

    ~StudentDirectory();        //�鹹����

    void menu_0();              //��ʼ��¼ҳ��

    void menu();                //��ʼ��¼ҳ��

    void Build();               //����ͨѶ¼

    void Add();                 //���

    void Check();               //����

    void Expurgate();           //ɾ��

    void PrintList();           //ͨѶ¼���

    void Cin_file();            //��ȡ�ļ�

    void Preservation_file();   //�����ļ�

    void D();                   //����

    int ListLength();           //ͨѶ¼����

    void Drop_out();            //�˳�����

public:
    LinkList head;//listNode *head
};

/**ͨѶ¼����Ľ���*/
void StudentDirectory::Build()
{
    system("cls"); //����
    fflush(stdin); //��ջ�����
    string StuID;
    bool isFlag = false;
    LinkList p;

    printf("�� �� ͨ Ѷ ¼\n");
    printf("****************************************************************\n");
    printf("����������\t\tѧ�š�\t������ \t�Ա�\t�绰���롢\t��ϵ��ַ\n");
    printf("�밴�մ˸�ʽ�������룺\t0001\t����\t��\t1**********\t���챱��\n\n");

    while (!isFlag)
    {
        char ch = 'Y';
        cout << "ѧ��(��-1���ز˵�)��";
        cin >> StuID;
        if (StuID != "-1")
        {
            p = new ListNode;
            p->data.stuid = StuID;
            printf("\n����������: ");
            cin >> p->data.name;
            printf("\n�������Ա�: ");
            cin >> p->data.sex;
            printf("\n������绰: ");
            cin >> p->data.phone;
            printf("\n�������ַ: ");
            cin >> p->data.addr;

            p->next = nullptr;
            //ͷ�巨
            p->next = head->next;// �½���next�����׽�㣨ͷ������һ����㣩
            head->next = p;// ͷָ����ǰ��
            printf("\n*********************\n");
            cout << "�Ƿ��������ѧ����ͨѶ¼��Ϣ��(Y/N):";
            cin >> ch;
            if (ch == 'N' || ch == 'n')
            {
                system("cls");
                isFlag = true;
            }
        }
        else
        {
            system("cls");
            break;
        }
    }
}

/**��ȡ������*/
int StudentDirectory::ListLength()
{
    LinkList p = head->next;
    int n = 0;
    while (p)
    {
        n++;
        p = p->next;
    }
    return n;
}

/**�������������ͷſռ�*/
StudentDirectory::~StudentDirectory()
{
    ListNode *p, *q; //p����ѭ��,qָ��ǰɾ���ڵ�
    p = head;
    q = p->next;
    delete p; //�ͷſռ�
    while (q)
    {
        p = q;
        q = p->next;
        delete p;
    }
}

/**ͨѶ¼�����*/
void StudentDirectory::Add()
{
    LinkList p;
    bool isFlag = true;
    while (isFlag)
    {
        p = new ListNode;
        printf("����������\t\tѧ�š��������Ա𡢵绰���롢��ϵ��ַ\n");
        printf("������ѧ��: ");
        cin >> p->data.stuid;
        printf("\n����������: ");
        cin >> p->data.name;
        printf("\n�������Ա�: ");
        cin >> p->data.sex;
        printf("\n������绰: ");
        cin >> p->data.phone;
        printf("\n�������ַ: ");
        cin >> p->data.addr;

        p->next = nullptr;
        p->next = head->next;//�½ڵ��ָ����ָ����һ���ڵ�
        head->next = p;//ͷ�ڵ��ָ��ָ���½ڵ�,�½ڵ����ͷ�ڵ�֮��

        printf("\n�Ƿ�������?(Y/N): ");
        char YN;
        cin >> YN;
        system("cls");
        if (YN == 'Y' || YN == 'y') { isFlag = true; }
        else { isFlag = false; }
    }
}

/**ͨѶ¼�Ĳ�ѯ*/
void StudentDirectory::Check()
{
    LinkList c;
    int i;
    string StuID, NAME;
    c = head->next;
    bool isFlag;
    while (isFlag)
    {
        bool isExist = false;
        if (head->next != nullptr)//����ǿ�
        {
            printf("\n��ѡ��Ҫ��ѯ�ķ�ʽ(��1��ѧ�� ��2������): \n");
            printf("=====>>>>�˳������롾0��\n");
            cin >> i;
            if (i == 0)
            {
                isFlag = false;
                system("cls");
            }
            else if (i == 1)
            {
                cout << "������ѧ��:" << endl;
                cin >> StuID;
                while (c)
                {
                    if (c->data.stuid == StuID)
                    {
                        isExist = true;
                        printf("��ѯ����ͨѶ¼��Ϣ����: \n");
                        printf("**************************************************************\n");
                        printf("ѧ��\t����\t�Ա�   \t�绰     \tͨ�ŵ�ַ\n");
                        printf("**************************************************************\n");
                        cout << c->data.stuid << setw(8)
                             << c->data.name << setw(6)
                             << c->data.sex << setw(16)
                             << c->data.phone << setw(16)
                             << c->data.addr << endl;
                        break;
                    }//�ҵ���ӦID
                    c = c->next;
                }
                if (!isExist)
                {
                    cout << ">>>�ܱ�Ǹ,���޴���!<<<" << endl;
                }
            }
            else if (i == 2)
            {
                cout << "����������:" << endl;
                cin >> NAME;
                while (c)
                {
                    if (c->data.name == NAME)
                    {
                        isExist = true;
                        printf("��ѯ����ͨѶ¼��Ϣ����: \n");
                        printf("**************************************************************\n");
                        printf("ѧ��\t����\t�Ա�   \t�绰     \tͨ�ŵ�ַ\n");
                        printf("**************************************************************\n");
                        cout << c->data.stuid << setw(8)
                             << c->data.name << setw(6)
                             << c->data.sex << setw(16)
                             << c->data.phone << setw(16)
                             << c->data.addr << endl;
                        break;
                    }//�ҵ���Ӧ����
                    c = c->next;
                }
                if (!isExist)
                {
                    cout << ">>>�ܱ�Ǹ,���޴���!<<<" << endl;
                }
            }
            else
            {
                printf("�����,����󱿵�...��\n");
            }
        }
        else//����Ϊ��
        {
            printf("\n�ܱ�Ǹ��δ���ҵ���ѧ��\n\n");
            printf("��ȥ����ͨѶ¼�ٽ��в���Ŷ~\n");
        }
    }

}

/**ͨѶ¼��ɾ��*/
void StudentDirectory::Expurgate()
{
    LinkList p, q, s;
    string StuID;
    bool flag = true;
    int i = 0;
    char YN = 'Y';
    p = head;
    q = p->next;
    while (flag)
    {
        if (!q)//ͷ�ڵ㲻����
        {
            cout << "ͨѶ¼��Ϊ��,�����������������...";
            while (getch())
            {
                system("cls");
                return;
            }
        }
        cout << "������Ҫɾ��ѧ����ѧ��: " << endl;
        cin >> StuID;
        while (q->data.stuid != StuID && q->next != nullptr)
        {
            s = q;
            q = q->next;
        }
        if (StuID == q->data.stuid)
        {
            if (q == p)//ɾ������ͷ�ڵ�
            {
                p = q->next;
                i++;
                delete p;
            }
            else//һ�����
            {
                s->next = q->next;

                printf("ɾ��ѧ����Ϣ����: \n");
                printf("**************************************************************\n");
                printf("ѧ��\t����\t�Ա�\t�绰\t  ͨ�ŵ�ַ\n");
                printf("**************************************************************\n");
                cout << q->data.stuid << "\t"
                     << q->data.name << "\t"
                     << q->data.sex << "\t"
                     << q->data.phone << "\t"
                     << q->data.addr << endl << endl;
                delete q;//�ͷſսڵ�
                q->next = s;
                i++;
            }

            cout << "ɾ�������ѳɹ�!" << endl;
            if (p)
            {
                printf("\n���ɹ�ɾ��%d����¼...", i);
                cout << "�Ƿ����ɾ��?(Y/N): ";
                cin >> YN;
                system("cls");
                if (YN == 'Y' || YN == 'y')
                {
                    p = head;
                    q = p->next;
                    flag = true;
                }
                else if (YN == 'N' || YN == 'n')
                {
                    system("cls");
                    flag = false;
                }
                else
                {
                    p = head;
                    q = p->next;
                    flag = true;
                    printf("�ⶼ�������������\n");
                }
            }
        }
        else
        {
            cout << "С������������" << endl << " ���޴�����!  " << endl;
            if (p)
            {
                printf("\n���ɹ�ɾ��%d����¼...", i);
                cout << "�Ƿ����ɾ��?(Y/N): ";
                cin >> YN;
                system("cls");
                if (YN == 'Y' || YN == 'y')
                {
                    p = head;
                    q = p->next;
                    flag = true;
                }
                else if (YN == 'N' || YN == 'n')
                {
                    system("cls");
                    flag = false;
                }
                else
                {
                    p = head;
                    q = p->next;
                    flag = true;
                    printf("�ⶼ�������������\n");
                }
            }
        }
    }
}

/**��ģ�鱾�����ڲ���,�㿴����ʱ�����Ѿ�����������*/
void StudentDirectory::D()
{
    cout << "�㲻����Ϊ�Լ�������ʲô�´�½��!�����,ɵx!����������...." << endl;
    cout << "\n�����������������...\n";
    cout << "��û�з���,�԰� ����������...." << endl;
    Sleep(1000);
    cout << "�Ǿ��ٰ�һ�����԰�...." << endl;
    system("purse");
    while (getch())
    {
        system("cls");
        return;
    }
}

/**ͨѶ¼�����*/
void StudentDirectory::PrintList()
{
    ListNode *p, *q, *s, *Max, *Min, *first;
    int count = 0;
    printf("#������������������������������������������������������������������������������������������#\n");
    printf("|       +++          ͨѶ¼ȫ����Ϣ          +++         |\n");
    printf("ѧ��\t����\t �Ա�\t    �绰\t      ͨѶ��ַ\n");
    printf("#������������������������������������������������������������������������������������������#\n");
    if (head->next)
    {
        first = new ListNode;
        s = first;
        while (head->next)
        {
            Min = head->next;
            Max = Min->next;
            q = head;
            while (Max && Min)
            {
                if (Max->data.stuid < Min->data.stuid)
                {
                    Min = Max;
                    Max = Max->next;
                }
                else { Max = Max->next; }
            }
            while (q->next != Min) { q = q->next; }

            q->next = Min->next;
            s->next = Min;
            s = Min;
            s->next = nullptr;
        }
        delete head;
        head = first;
        p = head->next;
        while (p)
        {
            cout << p->data.stuid
                 << setw(8) << p->data.name
                 << setw(8) << p->data.sex
                 << setw(16) << p->data.phone
                 << setw(16) << p->data.addr << endl;
            p = p->next;
            count++;
            if (p)
            {
                printf("|--------------------------------------------------------|\n");
            }
        }
        printf("\n���� %d ����¼...\n", count - 1);
        printf("#������������������������������������������������������������������������������������������#\n");
        printf("\n�����������������....\n");
    }
    else
    {
        printf("|-----                  ͨѶ¼Ϊ��               -----|\n");
        printf("#������������������������������������������������������������������������������������������#\n");
        printf("\n���� %d ����¼...\n", count);
        printf("�����������������....\n");
    }
    while (char a = getch())
    {
        system("cls");
        return;
    }
}

/**�����ļ���Ϣ*/
void StudentDirectory::Preservation_file()
{
    ofstream outfile("Address_book.txt", ios::out);//�ļ�д���� �ڴ�д��洢�豸
    if (!outfile)//����ļ�������
    {
        cerr << "Open ERROR!" << endl;
        exit(1);
    }
    LinkList p;
    p = head->next;
    while (p)
    {
        outfile << p->data.stuid
                << setw(8) << p->data.name
                << setw(8) << p->data.sex
                << setw(16) << p->data.phone
                << setw(16) << p->data.addr << endl;
        p = p->next;
    }
    outfile.close();
    cout << "��¼�ѱ���..." << "�����������..." << endl;
    while (char a = getch())
    {
        system("cls");
        return;
    }
}

/**�����ļ�*/
void StudentDirectory::Cin_file()
{
    ifstream inFile;
    inFile.open("Address_book.txt", ios::in); // �Զ��ķ�ʽ���ļ�
    if (!inFile.is_open())
    {
        printf("���ļ�ʧ��!");
        inFile.close();
        system("cls");
        return;
    }
    //���ﵽ�ļ�β
    while (!inFile.eof())
    { // ��δ���ļ�β
        auto newNode = new Node(); // �½����
        // ���ļ�����������
        inFile >> newNode->data.stuid >> setw(8)
               >> newNode->data.name >> setw(8)
               >> newNode->data.sex >> setw(16)
               >> newNode->data.phone >> setw(16)
               >> newNode->data.addr;

        newNode->next = head->next; // �½���next�����׽�㣨ͷ������һ����㣩
        head->next = newNode; // ͷָ����ǰ��
    }
    inFile.close(); // �ر��ļ�
    printf("\n�����ļ��ѳɹ���ף��ʹ����죡\n\n");
    printf("�밴���������ҳ��˵���\n");
    while (char a = getch())
    {
        system("cls");
        return;
    }
}

/**��ʼ��¼ҳ��*/
void StudentDirectory::menu_0()
{
    time_t timep;    //ϵͳʱ��
    struct tm *p_1;
    time(&timep);
    p_1 = gmtime(&timep);

    printf("\t\t\t\t\t\t  ��ǰʱ��%02dʱ%02d��\n", 8 + p_1->tm_hour, p_1->tm_min);
    printf("\t\t\t\t\t\t   %d��%02d��%02d��\n", 1900 + p_1->tm_year, 1 + p_1->tm_mon, p_1->tm_mday);
    printf("\t������������������������������������������������������\n\n");
    printf("\t��\t\t\t\t\t������Զ�����������ֺ��� \t\t\t\t\t��\n\n");
    printf("\t��\t\t\t*****************************************************\t\t\t\t��\n\n");
    printf("\t��\t\t\t\t\t Huffman����/�������\t\t\t\t\t\t��\n\n");
    printf("\t��\t\t\t  ������:*** רҵ:���ܿ�ѧ�뼼�� ѧ��:***************\t\t\t��\n\n");
    printf("\t��\t\t\t*****************************************************\t\t\t\t��\n\n");
    printf("\t��\t\t\t  ��ӭʹ��ѧ��ͨѶ¼ϵͳ,ף��ʹ�����! \t\t\t\t\t\t��\n\n");
    printf("\t������������������������������������������������������\n\n");
    printf("��������λ��½���룡(123456)\n");

    int i = 4;
    while (1)
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
    Sleep(1000);
    printf("\nͨѶ¼ϵͳ�����ѳɹ���ף��ʹ����죡\n\n");
    printf("�밴���������ҳ��˵���\n\n");
    system("pause");
    system("cls");    //����
}

/**�˳�����,��ӡһ������ͼ��*/
void StudentDirectory::Drop_out()
{
    int save = 0;
    cout << "�Ƿ񱣴汾�������ڼ��������޸�?" << endl;
    cout << "��1����  ��2����" << endl;
    cin >> save;
    if (save == 1) { this->Preservation_file(); }
    system("cls");
    //����ͼ��
    float y, x, b;
    for (y = 1.5f; y > -1.5f; y -= 0.1f)
    {
        for (x = -1.5f; x < 1.5f; x += 0.05f)
        {
            b = x * x + y * y - 1;
            putchar(b * b * b - x * x * y * y * y <= 0.0f ? '*' : ' ');
        }
        putchar('\n');
    }
    Sleep(1000);  //����
    printf("��ӭ�´μ���ʹ�ñ���Ʒ!\n");
    printf("�����˳������Ժ�.");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    cout << endl;
}

/**������������*/
void Reverse_output(Node *h)
{//����ʱ���ϵ,�������id����һ���򵥵��������
    auto *temp = new ListNode;//�½��ڵ�
    //�������
    ListNode *current, *next;
    current = h->next;

    while (current != nullptr)
    {
        next = current->next;
        current->next = temp->next;
        temp->next = current;
        current = next;
    }
    h->next = temp->next;
    delete temp;
    while (h->next != nullptr)
    {
        cout << h->next->data.stuid << endl;
        h = h->next;
    }
    system("pause");
    system("cls");
}

/**��Ҫ���ܲ˵���ʾ*/
void StudentDirectory::menu()
{
    time_t timep;
    time(&timep);
    auto p_1 = gmtime(&timep);
    printf("\t\t\t\t\t\t   ��ǰʱ��%02dʱ%02d��\n", 8 + p_1->tm_hour, p_1->tm_min);
    printf("\t\t\t\t\t\t    %d��%02d��%02d��\n", 1900 + p_1->tm_year, 1 + p_1->tm_mon, p_1->tm_mday);
    printf("\n");
    printf("\t\t\t\t\t\t    ҳ  ��  ��  ��\n");
    printf("\n");
    printf("\t\t�������������������������������������������������������������������������������������������������\n\n");
    printf("\t\t\t   | 1.����ͨѶ¼\t\t  2.�����ϵ��    \t\t3.��ϵ�˲���     |\n\n");
    printf("\t\t\t   | 4.ɾ����ϵ��\t\t  5.��ӡ��ϵ���б�\t\t6.����������ϵ��  |\n\n");
    printf("\t\t\t   | 7.������ϵ����Ϣ\t\t  8.�������(����)  \t\t0.�˳�ϵͳ       |\n\n");
    printf("\t\t�������������������������������������������������������������������������������������������������\n");
    printf("\t\t\t\t\t\t          * \n");
    printf("\t\t\t\t\t\t         *** \n");
    printf("\t\t\t\t\t\t        ***** \n");
    printf("\t\t\t\t\t\t       *******\n");
    printf("\t\t\t\t\t\t      *********\n");
    printf("\t\t\t\t\t\t     *********** \n");
    printf("\t\t\t\t\t\t ********************\n");
    printf("\t\t\t\t\t\t  ******************\n");
    printf("\t\t\t\t\t\t   ******* ********\n");
    printf("\t\t\t\t\t\t  *******   ********\n");
    printf("\t\t\t\t\t\t ******       *******\n");
    printf("\t\t\t\t\t\t******          ******\n");
    printf("��ѡ����Ӧ��ţ�");
}

/**ʵ����Ҫ�߼�*/
int main(int argc, char const *argv[])
{
//    system("chcp 65001");//�����ʱ����Ҵ򿪻��߸ĳ� chcp 936����
    system("color b");//���ÿ���
    StudentDirectory SD;//ʵ��������
    int n = 1;
    ofstream file("Address_book.txt", ios::app | ios::binary);
    if (!file)
    {
        cerr << "Open ERROR!" << endl;
        abort();
    }
    file.close();
    SD.Cin_file();
    SD.menu_0();//�����¼����,û��ʵ�ü�ֵ
    while (n)
    {
        SD.menu();//��ʾ�˵�
        int choose;
        cin >> choose;
//        if (choose == 000) exit(0);//������
        system("cls");
        switch (choose)
        {
            case 1:SD.Build();//����
                break;
            case 2:SD.Add();//���
                break;
            case 3:SD.Check();//��ѯ
                break;
            case 4:SD.Expurgate();//ɾ��
                break;
            case 5:SD.PrintList();//��ӡ
                break;
            case 6:SD.Preservation_file();//����
                break;
            case 7:SD.Cin_file();//����
                break;
            case 8:
            {
                try
                {
                    LinkList head = SD.head;
                    Reverse_output(head);//���������
                }
                catch (runtime_error e)
                {
                    cout << "���㿴����仰��ʱ��,֤���������(����)�Ѿ���������,�ǳ���Ǹ\n" << flush;
                    system("pause");
                    while (getch())
                    {
                        system("cls");
                        break;
                    }
                    break;
                }
                break;
            }//�������
            case 9:SD.D();//����
                cout << "��ϲ�㷢���´�½,��ʱ����Ϊ" << endl << SD.ListLength()
                     << endl << "�����������������....." << endl;
                system("pause");//�ȴ��û��������
                system("cls");
                break;
            case 0:SD.Drop_out();//��ӡ�˳�����
                n = 0;
                printf("======<<<<<<<<<>>>>>>>>>>>>>>>>>>>>=======\n");
                printf("\t��л���ʹ��!ɽˮ�����!\n��Ե�ٻ�...\n");
                break;
            default:printf("û�и���ţ����������룺");
        }
    }
    return 0;
}