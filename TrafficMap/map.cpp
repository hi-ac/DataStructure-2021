//
// Created by yxn on 2021/12/10.
//����ǰ��IO��û�õ����ľ���,���Ա�ʵ�����ְ����ĳ�C���ļ�������
//��ĿҪ��
//
//1��ϵͳ���ܣ�Ҫ�����һ�����׵Ľ�ͨ��ѯϵͳ�������û���ѯ������
//������֮�����̾��롢��ͻ��ѻ�����ʱ������⡣
//
//2�����ڲ�ͬ����ѯҪ��������ѯ�����ݡ�
//
//3���û�������Ѻ��ԣ��������ṩ �˵����û�ѡ���Լ���Ӧ�Ľ�����Ϣ��
//��ĿĿ�ģ�
//
//1��ͼ�Ĵ洢��ʾ�����������ʵ�֡�
//
//2�����·���㷨��

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <conio.h>

#define   M 40      //������ݹ�ģ
#define   INF 99999 //��99999��������

using namespace std;

/**����ṹ�����ʹ洢���ṹ*/
typedef struct node
{
    float distance;  //����
    int vexNode;     //����
    struct node *next; //ָ����һ������ָ��
} Arcnode;

/**��ͨͼ�ڵ�Ԫ������*/
typedef struct vertexnode
{
    char name[30];         //����
    char information[100]; //��Ӧ��Ϣ
    Arcnode *head;         //��һ��·��
} Line;

/**ͼ�Ĵ洢�ṹ����*/
typedef struct adjlist
{
    Line point[M];  //���㼯��
    int arcnum;     //������
    int vexnum;     //����
} map;

/**���нṹ������ʵ�ֵϽ�˹�����㷨*/
typedef struct quene
{
    int father;
    int son;
    struct quene *next;
} Quene;

/**��С�������ڵ㶨��:��������·��*/
typedef struct mst_point
{
    int father;
    int son;
    struct mst_point *next;
} MST_point;

/**��ʼ������*/
void init_matrix(float (*matrix)[M])
{
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            matrix[i][j] = INF;
        }
    }
}

/**���ٿռ��ŵص����͵ص���Ϣ*/
void init_map(map *g)
{
    for (auto &i: g->point)
    {
        //void *memset(void *s,int c,size_t n)
        //�ܵ����ã����ѿ����ڴ�ռ� s ���� n ���ֽڵ�ֵ��Ϊֵ c
        memset(i.name, 0, 30 * sizeof(char));
        memset(i.information, 0, 100 * sizeof(char));
    }
    for (auto &i: g->point)
    {
        i.name[29] = '\n';
        i.information[29] = '\n';
    }
}

/**��ͼ�Ĵ���*/
void creat_map(map *g, float (*matrix)[M], FILE *fp)
{
    Arcnode *temp;
    int vexnum;
    int w;
    int vexnode;
    float distance;
    init_map(g);
    cout << "������Ҫ�����Ľڵ�(�ص�:��ͬ)����: " << endl;
    cin >> vexnum;
    fprintf(fp, "%d\n", vexnum);
    g->vexnum = vexnum;
    for (int i = 0; i < vexnum; ++i)
    {
        g->point[i].head = (Arcnode *) malloc(sizeof(Arcnode));
        g->point[i].head->next = nullptr;
        printf("\n---���ڴ����� %d/%d �����ڵ�---\n", i + 1, vexnum);
        printf("===>>>�������[%d]�����ڵ������:", i + 1);
        cin >> g->point[i].name;
        fwrite(g->point[i].name, 30, 1, fp);
        printf("===>>>������ص�'%s'���Ļ�����Ϣ\n", g->point[i].name);
        cin >> g->point[i].information;
        fwrite(g->point[i].information, 100, 1, fp);
        printf("\n�����ж��ٽڵ����ӵ����ڵ�'%s': ", g->point[i].name);
        cin >> w;
        fprintf(fp, "%d\n", w);//��ʽ���������ļ�

        for (int j = 0; j < w; ++j)
        {
            printf("**��ʼ�������ӵ�'%s'�Ľڵ�,��ǰ: %d/%d ���ڵ�**\n", g->point[i].name, j + 1, w);
            temp = (Arcnode *) malloc(sizeof(Arcnode));
            printf("�������%d�����ӵ� '%s' �Ľڵ��Ӧ�����ֱ��===>>> ", j + 1, g->point[i].name);
            cin >> vexnode;
            printf("������ýڵ㵽 '%s' �ľ���===>>> ", g->point[i].name);
            cin >> distance;
            fprintf(fp, "%d %f\n", vexnode, distance);
            temp->vexNode = vexnode;
            temp->distance = distance;

            temp->next = g->point[i].head->next;
            g->point[i].head->next = temp;

            matrix[i][vexnode] = distance;
            printf("\n�ص�(���ڵ�):'%s'==>��%d���ڵ�㴴���ɹ�!\n", g->point[i].name, j + 1);
        }
        printf("---������ %d���ڵ㴴���ɹ�,����:'%s',���:%d!---\n", i + 1, g->point[i].name, i);
        cout << "//********************************************************//" << endl;
        system("pause");
    }
}

/**��ʾ����洢��Ϣ*/
void show_matrix(map *g, float (*matrix)[M])
{
    Arcnode *temp;
    printf("��ǰ���нڵ����: %d\n", g->vexnum);
    printf("\t===��������===\n");
    for (int i = 0; i < g->vexnum; ++i)
    {
        for (int j = 0; j < g->vexnum; ++j)
        {
            printf("%10.2f  ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n %d \n", g->vexnum);
    for (int i = 0; i < g->vexnum; ++i)
    {
        temp = g->point[i].head->next;
        printf("���ӵ� '%s' �ĵص���:", g->point[i].name);
        while (temp)
        {
            printf(" (%s,����:%.1f) ", g->point[temp->vexNode].name, temp->distance);
            temp = temp->next;
        }
        printf("\n��ϸ��ϢΪ: %s\n\n\n", g->point[i].information);
    }
}

/**��ʼ������*/
Quene *init_Quene()
{
    auto *head = (Quene *) malloc(sizeof(Quene));
    head->next = nullptr;
    return head;
}

/**�ж϶����Ƿ�Ϊ��*/
int isEmpty(Quene *head)
{
    if (head->next) { return 0; }
    else { return -1; }
}

/**��Ӳ��� ����Ԫ��,i:���׽ڵ�   j:���ӽڵ�*/
void push(Quene *head, int i, int j)
{

    auto *temp = (Quene *) malloc(sizeof(Quene));
    if (temp)
    {
        temp->father = i;
        temp->son = j;
        temp->next = head->next;
        head->next = temp;
    }
}

/**���Ӳ���*/
void pop(Quene *head, int &i, int &j)
{
    Quene *temp;
    if (!isEmpty(head))
    {
        temp = head->next;
        i = temp->father;
        j = temp->son;
        head->next = temp->next;
        free(temp);
    }
}

/**��ʾ��ǰ����*/
void print_Quene(Quene *head)
{
    Quene *temp;
    temp = head->next;
    printf("��ǰ��������: \n");
    while (temp)
    {
        printf("���ڵ�:%d ,���ӽڵ�:%d ", temp->father, temp->son);
        temp = temp->next;
    }
}

/**�ҵ�����֮�������·��*/
void print_rout(map *g, Quene *head, int end)
{
    Quene *temp = head->next;
    printf("����֮�������·������: \n");
    printf("%s <- ", g->point[end].name);
    while (temp)
    {
        printf("%s <- ", g->point[temp->father].name);
        temp = temp->next;
    }
    printf("\n");
}

/**�Ƿ������һ���ڵ�*/
int get_next(map *g, int &father, int &son)
{
    Arcnode *temp = g->point[father].head->next;
    if (son == -1)
    {
        if (temp)
        {
            son = temp->vexNode;
            return 1;
        }
        else { return 0; }
    }
    else
    {
        while (temp->vexNode != son)
        {
            temp = temp->next;
        }
        if (temp->next)
        {
            son = temp->next->vexNode;
            return 1;
        }
        else { return 0; }
    }
}

/**�鿴father�Ƿ���son�ڵ�,�з���0*/
int continue_find(map *g, int father, int son, int start)
{

    Arcnode *temp = g->point[father].head->next;
    while (temp->vexNode != son)
    {
        temp = temp->next;
    }
    if (temp->next != nullptr) { return 1; }
    else { return 0; }
}

/**������������·��*/
void all_routes(map *g, Quene *head, int start, int end)
{
    head = init_Quene();
    int in_stack[M];
    int father = start;
    int son;
    int count = 0;

    for (int &i: in_stack) i = 0;
    if (g->point[start].head->next)
    {
        son = g->point[start].head->next->vexNode;
        push(head, father, son);
        in_stack[start] = 1;
        if (g->point[start].head->next->vexNode == end)
        {
            print_rout(g, head, end);
            count++;
            in_stack[father] = 0;
        }
        else
        {
            father = son;
            son = -1;
        }
    }

    else
    {
        printf("�������ص���ʱ��֧��ֱ�ӵ���Ӵ~~~ \n");
        return;
    }
    while ((isEmpty(head) == 0) || (continue_find(g, father, son, start)))
    {
        if (get_next(g, father, son))
        {
            if (in_stack[father] == 0)
            {
                if (son != end)
                {
                    push(head, father, son);
                    in_stack[father] = 1;
                    father = son;
                    son = -1;
                }
                else
                {
                    push(head, father, son);
                    in_stack[father] = 1;
                    print_rout(g, head, son);
                    count++;
                }
            }
        }
        else
        {
            pop(head, father, son);
            in_stack[father] = 0;
        }
    }
    printf("�ܹ���ѯ�� %d �ֵ��﷽ʽ \n", count);
}

/**dijkstra�㷨������֮������·��*/
void dijkstra(map *g, float (*matrix)[M], int start, int end, int dist[M], int path[M][M + 1])
{
    cout << "���ڵ���dijkstra�㷨" << endl;
    int mindist;
    int t, k;
    for (int i = 0; i < g->vexnum; ++i)
    {
        path[i][0] = 0;
    }
    for (int i = 0; i < g->vexnum; ++i)
    {
        for (int j = 1; j < M + 1; ++j)
        {
            path[i][j] = -1;
        }
    }

    for (int i = 0; i < g->vexnum; ++i)
    {
        dist[i] = matrix[start][i];
        if (matrix[start][i] != INF)
        {
            path[i][1] = start;
        }
    }
    path[start][0] = 1;
    for (int i = 1; i < g->vexnum; ++i)
    {
        mindist = INF;
        for (int j = 0; j < g->vexnum; ++j)
        {
            if (!path[j][0] && dist[j] < mindist)
            {
                k = j;
                mindist = dist[j];
            }
        }

        if (mindist == INF)
        {
            printf("����δ��ѯ�������·��!\n");
            return;
        }
        path[k][0] = 1;
        for (int j = 1; j < M; ++j)
        {
            if (!path[j][0] && matrix[k][j] < INF && (dist[k] + matrix[k][j] < dist[j]))
            {
                dist[j] = dist[k] + matrix[k][j];
                t = 1;
                while (path[k][t] != -1)
                {
                    path[j][t] = path[k][t];
                    t++;
                }
                path[j][t] = k;
            }
        }
    }
    printf("%s �� %s ֮������·��Ϊ: \n", g->point[start].name, g->point[end].name);
    t = 1;
    while ((k = path[end][t]) != -1)
    {
        printf("%s ->", g->point[k].name);
        t++;
    }
    printf("%s\n", g->point[end].name);
    printf("\n����Ϊ: %d\n", dist[end]);
}

/**��ʾdijkstra�洢������ʾ��ͼ*/
void print_dijs_matrix(int *dist, int path[][M + 1])
{
    printf("\t====������������������ʾ====\n");
    for (int i = 0; i < M; ++i)
    {
        printf("%d ", dist[i]);
    }
    printf("\n\t====�洢·��������������ʾ====\n");
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M + 1; ++j)
        {
            printf("%d  ", path[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**Prim�㷨��ȡ��С������*/
MST_point *prim(map *g, float(*matrix)[M], int start)
{
    auto *head = (MST_point *) malloc(sizeof(MST_point));
    MST_point *temp;
    struct
    {
        int adjvex;
        int lowcost;
    } closedge[M];

    int s, min;
    head->next = nullptr;
    closedge[start].lowcost = 0;
    for (int i = 0; i < g->vexnum; ++i)
    {
        if (i != start)
        {
            closedge[i].adjvex = start;
            closedge[i].lowcost = matrix[start][i];
        }
    }

    for (int i = 0; i < g->vexnum - 1; ++i)
    {
        min = INF;
        for (int j = 0; j < g->vexnum; ++j)
        {
            if (closedge[j].lowcost != 0 && closedge[j].lowcost < min)
            {
                s = j;
                min = closedge[j].lowcost;
            }
        }
        temp = (MST_point *) malloc(sizeof(MST_point));
        temp->father = closedge[s].adjvex;
        temp->son = s;
        temp->next = head->next;
        head->next = temp;
        closedge[s].lowcost = 0;

        for (int j = 0; j < g->vexnum; ++j)
        {
            if (j != s && matrix[s][j] < closedge[j].lowcost)
            {
                closedge[j].lowcost = matrix[s][j];
                closedge[j].adjvex = s;
            }
        }
    }
    return head;
}

/**�鿴��С������*/
void print_mst(MST_point *head)
{
    MST_point *temp;
    temp = head->next;
    printf("��С����������: \n");
    while (temp)
    {
        printf("(%d,%d)  ", temp->father, temp->son);
        temp = temp->next;
    }
    printf("\n");
}

/**�ļ�����*/
void cin_file(map *g, float (*matrix)[M], FILE *fp)
{
    Arcnode *temp;
    int vexnum;
    int w;
    int vexnode;
    float distance;
    fscanf(fp, "%d\n", &vexnum);
    g->vexnum = vexnum;
    for (int i = 0; i < vexnum; ++i)
    {
        g->point[i].head = (Arcnode *) malloc(sizeof(Arcnode));
        g->point[i].head->next = nullptr;
        fread(g->point[i].name, 30, 1, fp);
        fread(g->point[i].information, 100, 1, fp);
        fscanf(fp, "%d\n", &w);
        for (int j = 0; j < w; ++j)
        {
            temp = (Arcnode *) malloc(sizeof(Arcnode));
            fscanf(fp, "%d %f\n", &vexnode, &distance);
            temp->vexNode = vexnode;
            temp->distance = distance;
            temp->next = g->point[i].head->next;
            g->point[i].head->next = temp;
            matrix[i][vexnode] = distance;
        }
    }
    show_matrix(g, matrix);
}

/**�ڵ���Ϣ��ѯģ��*/
void point_display(map *g)
{
    int choice;
    printf("\n+++++++++��ǰ�ɹ���ѯ�ص���Ϣ����+++++++++    \n");
    for (int i = 0; i < g->vexnum; ++i)
    {
        printf("\t%d : %s\n", i, g->point[i].name);
    }
    cout << "������Ҫ��ѯ�ĵص��Ӧ������: " << endl;
    cout << "=======>>> ";
    cin >> choice;
    printf("��ѯ�� '%s'��Ӧ��Ϣ����: \n", g->point[choice].information);
    printf("ʡ�����: %s\n", g->point[choice].information);
    cout << "\n-----��ѯ����-----" << endl;
}

/**��Ӧ�ڵ�ѡ��ģ��*/
void select_point(map *g)
{
    for (int i = 0; i < g->vexnum; ++i)
    {
        printf("%d: %s\n", i, g->point[i].name);
    }
}

/**��ʾ�����ͨ·��*/
void display_mst(map *g, MST_point *head)
{
    print_mst(head);
    MST_point *temp;
    temp = head->next;
    printf("��ѯ���������ͨ·������:\n");
    while (temp)
    {
        printf("%s --> %s\n", g->point[temp->father].name, g->point[temp->son].name);
        temp = temp->next;
    }
}

/**�ڵ����*/
void point_add(map *g, float(*matrix)[M], int start, int end, float distance)
{
    auto *temp = (Arcnode *) malloc(sizeof(Arcnode));
    temp->vexNode = end;
    temp->distance = distance;
    temp->next = g->point[start].head->next;
    g->point[start].head->next = temp;
    matrix[start][end] = distance;
}

/**�ڵ㳷��*/
void point_revoke(map *g, float(*matrix)[M], int start, int end)
{
    Arcnode *temp = g->point[start].head;
    Arcnode *p;
    while (temp->next->vexNode != end)
    {
        temp = temp->next;
    }
    p = temp->next;
    temp->next = temp->next->next;
    free(p);
    matrix[start][end] = INF;

}

/**���ڵ�����*/
void add_point(map *g, float (*matrix)[M], FILE *fp)
{
    Arcnode *temp;
    int vexnum;
    int w;
    int vexnode;
    float distance;
    init_map(g);
    cout << "������Ҫ��ӵĽڵ�(�ص�:��ͬ)����: " << endl;
    cin >> vexnum;
    fprintf(fp, "%d\n", vexnum);
    g->vexnum = vexnum;
    for (int i = 0; i < vexnum; ++i)
    {
        g->point[i].head = (Arcnode *) malloc(sizeof(Arcnode));
        g->point[i].head->next = nullptr;
        printf("\n---������ӵ� %d/%d �����ڵ�---\n", i + 1, vexnum);
        printf("===>>>�������[%d]�����ڵ������:", i + 1);
        cin >> g->point[i].name;
        fwrite(g->point[i].name, 30, 1, fp);
        printf("===>>>������ص�'%s'���Ļ�����Ϣ\n", g->point[i].name);
        cin >> g->point[i].information;
        fwrite(g->point[i].information, 100, 1, fp);
        printf("\n�����ж��ٽڵ����ӵ����ڵ�'%s': ", g->point[i].name);
        cin >> w;
        fprintf(fp, "%d\n", w);//��ʽ���������ļ�

        for (int j = 0; j < w; ++j)
        {
            printf("**��ʼ�������ӵ�'%s'�Ľڵ�,��ǰ: %d/%d ���ڵ�**\n", g->point[i].name, j + 1, w);
            temp = (Arcnode *) malloc(sizeof(Arcnode));
            printf("�������%d�����ӵ� '%s' �Ľڵ��Ӧ�����ֱ��===>>> ", j + 1, g->point[i].name);
            cin >> vexnode;
            printf("������ýڵ㵽 '%s' �ľ���===>>> ", g->point[i].name);
            cin >> distance;
            fprintf(fp, "%d %f\n", vexnode, distance);
            temp->vexNode = vexnode;
            temp->distance = distance;

            temp->next = g->point[i].head->next;
            g->point[i].head->next = temp;

            matrix[i][vexnode] = distance;
            printf("\n�ص�(���ڵ�):'%s'==>��%d���ڵ�㴴���ɹ�!\n", g->point[i].name, j + 1);
        }
        printf("---��ӵ� %d���ڵ㴴���ɹ�,����:'%s',���:%d!---\n", i + 1, g->point[i].name, i);
        cout << "//********************************************************//" << endl;
        system("pause");
    }
    show_matrix(g, matrix);
}

/**������˵�*/
void menu_0()
{
    printf("                        �� ͨ �� ѯ ϵ ͳ V1.0       \n\n ");
    printf("                                   ����ҳ��         \n");
    printf("      0. ��ͼ�Ļ�����Ϣ.                             \n");
    printf("      1. �ɹ���ѯ�ĵص㼰�������Ϣ����                \n");
    printf("      2. ��ѯ������������е�·��                      \n");
    printf("      3. ��ѯ��������·��                           \n");
    printf("      4. ��ѯ��ĳ�����������λ�õ������ͨ·��         \n");
    printf("      5. ·��������                                  \n");
    printf("      6. ·���ĳ���                                  \n");
    printf("      7. �½����ŵ�ͼ                                \n");
    printf("      8. ��ӽڵ�                                    \n");
    printf("      9. ɾ���ڵ�                                    \n");
    printf("      10.�˳���ϵͳ                                   \n");
    printf("\n\n ��������������ѡ��   ");
}

/**ʵ����Ҫ�߼�*/
int main(int argc, char const *argv[])
{
//    system("chcp 65001");
    system("color e");
    system("cls");
    map g; //��ʼ��ͼ
    Quene *head = nullptr;
    float matrix[M][M]; //����һ��40*40�����ŵص���Ϣ
    int path[M][M + 1];
    int start, end;
    int dist[M];
    MST_point *Head;
    init_matrix(matrix); //��ʼ������
    int choice = 0;
    FILE *fp;
    float distance;
    while (true)
    {
        menu_0();//��ʾ�˵�
        cin >> choice;
        if (choice == 10)
        {
            printf("\n\n��л���ʹ��,�ټ�...\n\n");
            system("pause");
            system("cls");
            break;
        }//�˳���ϵͳ
        switch (choice)
        {
            case 0://��ʾ��ͼ�Ļ�����Ϣ
            {
                fp = fopen("map.txt", "rt");//t��txt�ļ�д,����ʡ�Բ�д
                cin_file(&g, matrix, fp);
                fclose(fp);
                cout << "�����������..." << endl;
                while (getch())
                {
                    system("cls");
                    break;
                }
            }
                break;
            case 1://�ɹ���ѯ�ĵص㼰�������Ϣ����
            {
                fp = fopen("map.txt", "rt");
                cin_file(&g, matrix, fp);
                fclose(fp);
                point_display(&g);
                cout << "�����������..." << endl;
                while (getch())
                {
                    system("cls");
                    break;
                }
            }
                break;
            case 2://��ѯ������������е�·��
            {
                fp = fopen("map.txt", "rt");
                cin_file(&g, matrix, fp);
                fclose(fp);
                select_point(&g);
                cout << "====>>>��������ʼ��: " << endl;
                cin >> start;
                cout << "====>>>�������յ�: " << endl;
                cin >> end;
                all_routes(&g, head, start, end);
                cout << "�����������..." << endl;
                while (getch())
                {
                    system("cls");
                    break;
                }
            }
                break;
            case 3://��ѯ��������·��
            {
                fp = fopen("map.txt", "rt");
                cin_file(&g, matrix, fp);
                fclose(fp);
                select_point(&g);
                cout << "====>>>��������ʼ��: " << endl;
                cin >> start;
                cout << "====>>>�������յ�: " << endl;
                cin >> end;
                dijkstra(&g, matrix, start, end, dist, path);
                cout << "�����������..." << endl;
                while (getch())
                {
                    system("cls");
                    break;
                }
            }
                break;
            case 4://��ѯ��ĳ������������ͨ·��
            {
                fp = fopen("map.txt", "rt");
                cin_file(&g, matrix, fp);
                fclose(fp);
                select_point(&g);
                cout << "====>>>������Ҫ��ѯ�����: " << endl;
                cin >> start;
                Head = prim(&g, matrix, start);
                display_mst(&g, Head);
                cout << "�����������..." << endl;
                while (getch())
                {
                    system("cls");
                    break;
                }
            }
                break;
            case 5://·��������
            {
                fp = fopen("map.txt", "rt");
                cin_file(&g, matrix, fp);
                select_point(&g);
                fclose(fp);
                cout << "====>>>������Ҫ�����·�����" << endl;
                cout << "��ʼ�ڵ�: ";
                cin >> start;
                cout << "�����ڵ�: ";
                cin >> end;
                cout << "�����������Ϊ: ";
                cin >> distance;
                printf("\n");
                point_add(&g, matrix, start, end, distance);
                cout << "�����ĵ�ͼ������ʾ:" << endl;
                show_matrix(&g, matrix);
                cout << "�����������..." << endl;
                while (getch())
                {
                    system("cls");
                    break;
                }
            }
                break;
            case 6://·���ĳ���
            {
                fp = fopen("map.txt", "rt");
                cin_file(&g, matrix, fp);
                select_point(&g);
                fclose(fp);
                cout << "====>>>��������Ҫ������·�����:" << endl;
                cout << "��ʼ�ڵ�: ";
                cin >> start;
                cout << "�����ڵ�: ";
                cin >> end;
                printf("\n");
                point_revoke(&g, matrix, start, end);
                cout << "����·����ĵ�ͼ������ʾ:" << endl;
                show_matrix(&g, matrix);
            }
                break;
            case 7://�½����ŵ�ͼ
            {
                int yn;
                cout << "!!!!>>> �ò����Ḳ��ԭ���ļ� <<<!!!!,�Ƿ����?1=��,2=��" << endl;
                cin >> yn;
                if (yn == 2)
                {
                    cout << "���ڷ���..." << endl;
                    while (getch())
                    {
                        system("cls");
                        break;
                    }
                    break;
                }
                else
                {
                    int password = 0;
                    cout << "���������Ա����!!!" << endl;
                    cin >> password;
                    if (password == 123456)
                    {
                        fp = fopen("map.txt", "wt");
                        creat_map(&g, matrix, fp);
                        fclose(fp);
                        show_matrix(&g, matrix);
                        cout << "�����������..." << endl;
                        while (getch())
                        {
                            system("cls");
                            break;
                        }
                    }
                    else
                    {
                        cout << "�������,����ϵ����Ա...." << endl;
                    }
                }
            }
                break;
            case 8://��Ӹ��ڵ�
            {
                fp = fopen("map.txt", "at");
                cin_file(&g, matrix, fp);
                fclose(fp);
                add_point(&g, matrix, fp);
                show_matrix(&g, matrix);
                fclose(fp);
                cout << "�����������..." << endl;
                while (getch())
                {
                    system("cls");
                    break;
                }
            }
                break;
            case 9://ɾ�����ڵ�
            {
                fp = fopen("map.txt", "rt");
                cin_file(&g, matrix, fp);
                select_point(&g);
                fclose(fp);
                show_matrix(&g, matrix);
                cout << "�����������..." << endl;
                while (getch())
                {
                    system("cls");
                    break;
                }
            }
                break;
            default:printf("�����,���޴˹���!\n");
                break;
        }
    }
    return 0;
}

