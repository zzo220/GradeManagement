#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


//��� ����ü ����
union note
{
    int fall_num;
    char adoption;
};

//�л� ���� ����ü ����
typedef struct student
{
    int num;
    char name[10];
    int kor;
    int eng;
    int mat;
    int total;
    double avg;
    int rank;
    union note bigo;
}strStu;


void choice(strStu* stu, int n); //�޴� �Լ�
void sort(strStu* s, int n); //�������� ���� �Լ�
void stu_average(strStu* s, int n); //�л� ���� ��� ���ϴ� �Լ�
void stu_rank(strStu* s, int n); //�л� ��� ���ϴ� �Լ�
void bigo_note(strStu* s, int n); //��� ���� �Լ�
void stu_rec(strStu* stu, int n); //��ü �л� ��� �Լ�
void group_avg(strStu* s, int n); //���� �� ��� ��� �Լ�
void dux(strStu* s, int n); //�ֿ�� �л� ��� �Լ�
void each_grade(strStu* s, int n); //���� ���� ��� �Լ�
void scholarship(strStu* s, int n); //���л� ��� ���� ��� �Լ�
void complete_stu(strStu* s, int n); //�̼��� ��� ���� ��� �Լ�
void ncomplete_stu(strStu* s, int n); //���̼��� ��� ���� ��� �Լ�
void pauseClear(); //�޴��� �ٽ� ���ư��� �Լ�

int main()
{
    int i, total_stu;
    strStu s[50]; //�л�����

    //�л� �� �Է¹ޱ�
    printf("�л� ���� �Է��Ͻÿ� : ");
    scanf("%d", &total_stu);
    
    //�л� ���� �Է¹ޱ�
    for (i = 0; i < total_stu; i++)
    {
        printf("��ȣ, �̸�, ��������, ��������, ���������� ���ʷ� �Է��Ͻÿ� : ");
        scanf("%d %s %d %d %d", &s[i].num, s[i].name, &s[i].kor, &s[i].eng, &s[i].mat);
    }
    system("cls");

    sort(&s, total_stu); //���� �Լ� ȣ��
    stu_average(&s, total_stu); //��� ���ϴ� �Լ� ȣ��
    stu_rank(&s, total_stu); //��� ���ϴ� �Լ� ȣ��
    bigo_note(&s, total_stu); //��� �����ϴ� �Լ� ȣ��

    choice(&s, total_stu); //�޴� ȣ��
}

//�޴� ȣ�� �Լ�
void choice(strStu* stu, int n)
{
    //MENU ��� ���
    char ch;
    printf("\n------------MENU------------\n");
    printf("> a:��ü �л� ���� ���\n");
    printf("> b:���� �� ��� ���\n");
    printf("> c:�ֿ�� �л� ��ȸ\n");
    printf("> d:�л� ���� ���� ��ȸ\n");
    printf("> e:���л� ���� ���� ����\n");
    printf("> f:�̼��� ��� ���� ����\n");
    printf("> g:���̼��� ��� ���� ����\n");
    printf("> x:���α׷� ����\n");
    printf("----------------------------\n");
    printf("��ȸ�ϰ� ���� �޴��� �����ϼ��� > ");

    //�޴� ����
    scanf("%c", &ch);

    switch (tolower(ch))
    {
    case 'a':
        system("cls");
        stu_rec(stu, n);
        choice(stu, n);
    case 'b':
        system("cls");
        group_avg(stu, n);
        choice(stu, n);
    case 'c': 
        system("cls");
        dux(stu, n);
        choice(stu, n);
    case 'd': 
        system("cls");
        each_grade(stu, n);
        choice(stu, n);
    case 'e': 
        system("cls");
        scholarship(stu, n);
        choice(stu, n);
    case 'f': 
        system("cls");
        complete_stu(stu, n);
        choice(stu, n);
    case 'g':
        system("cls");
        ncomplete_stu(stu, n);
        choice(stu, n);
    case 'x':
        exit(1);

    default: system("cls");
        choice(stu, n);
    }
}

//���� �Լ�
void sort(strStu* s, int n)
{
    int i, j;
    strStu tmp;

    for(i=0; i<n-1; i++)
        for(j=i; j<n; j++)
            if (s[i].num > s[j].num)
            {
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
}

//��� ���ϴ� �Լ�
void stu_average(strStu* s, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        s[i].total = s[i].kor + s[i].eng + s[i].mat;
        s[i].avg = s[i].total / (double)3;
    }
}

//��� ���ϴ� �Լ�
void stu_rank(strStu* s, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
        s[i].rank = 1;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (s[i].avg < s[j].avg)
                s[i].rank++;
}

//��� �����ϴ� �Լ�
void bigo_note(strStu* s, int n)
{
    int i, failure_num;

    for (i = 0; i < n; i++)
    {
        //���̼���
        if (s[i].avg < 70)
        {
            failure_num = 0;
            if (s[i].kor < 60)
                failure_num++;
            if (s[i].eng < 60)
                failure_num++;
            if (s[i].mat < 60)
                failure_num++;

            s[i].bigo.fall_num = failure_num;
        }
        //�̼���
        else
            if (s[i].rank <= n * 10 / 100)
            {
                if (s[i].avg >= 80)
                    s[i].bigo.adoption = 'Y';
                else
                    s[i].bigo.adoption = 'N';
            }
            else
                s[i].bigo.adoption = 'N';
    }
}

//��ü �л� ��� �Լ�
void stu_rec(strStu* s, int n)
{
    int i;

    printf("\n==============================================================================\n");
    printf("�й�\t�̸�\t\t����\t����\t����\t����\t���\t���\t���\n");
    printf("==============================================================================\n");

    for (i = 0; i < n; i++)
    {
        if(s[i].bigo.fall_num<=3 && s[i].bigo.fall_num>=0)
            printf("%d\t%s\t\t%d\t%d\t%d\t%d\t%0.1f\t%d\t%d\n", s[i].num, s[i].name, s[i].kor, s[i].eng, s[i].mat, s[i].total, s[i].avg, s[i].rank, s[i].bigo.fall_num);
        else if(s[i].bigo.adoption=='Y'|| s[i].bigo.adoption=='N')
            printf("%d\t%s\t\t%d\t%d\t%d\t%d\t%0.1f\t%d\t%c\n", s[i].num, s[i].name, s[i].kor, s[i].eng, s[i].mat, s[i].total, s[i].avg, s[i].rank, s[i].bigo.adoption);
    }

    printf("==============================================================================\n\n");
    pauseClear();
}

//���� �� ��� ��� �Լ�
void group_avg(strStu* s, int n)
{
    int i, kor_tot=0, eng_tot=0, mat_tot=0;

    printf("===========���� �� �� ���============\n");
    for (i = 0; i < n; i++)
    {
        kor_tot += s[i].kor;
        eng_tot += s[i].eng;
        mat_tot += s[i].mat;
    }
    
    printf("���� ��� : %0.1f\n���� ��� : %0.1f\n���� ��� : %0.1f\n", (double)kor_tot / n, (double)eng_tot / n, (double)mat_tot / n);
    printf("======================================\n\n");

    pauseClear();
}

//�ֿ�� �л� ���
void dux(strStu *s, int n)
{
    int i;

    for(i=0;i<n;i++)
        if (s[i].rank == 1)
        {
            printf("========�ֿ�� �л�=======\n");
            printf("\t   %s\n", s[i].name);
            printf("==========================\n\n");
        }

    pauseClear();
}

//��ȸ �Լ�
void each_grade(strStu* s, int n)
{
    int stu_num;
    int i;

    printf("��ȸ�ϰ� ���� �л��� �й��� �Է��Ͻÿ� > ");
    scanf("%d", &stu_num);
    if (stu_num > n || stu_num <= 0)
    {
        printf("�л��� �������� �ʽ��ϴ�\n");
        each_grade(s, n);
    }
    getchar('\n');

    for (i = 0; i < n; i++)
        if (s[i].num == stu_num)
        {
            printf("=====================================\n");
            printf("�й�\t�̸�\t\t���\t���\n");
            printf("-------------------------------------\n");
            printf("%d\t%s\t\t%0.1f\t%d\n", s[i].num, s[i].name, s[i].avg, s[i].rank);
            printf("=====================================\n\n");
        }

    pauseClear();
}

//���л� ���� ��� �Լ�
void scholarship(strStu* s, int n)
{
    FILE* fs;
    int i;

    fs = fopen("s.txt", "w");

    fprintf(fs, "                                       <���л� ���>\n");
    fprintf(fs,"\n======================================================\n");
    fprintf(fs,"�й�\t�̸�\t����\t����\t����\t����\t���\t���\t���\n");
    fprintf(fs,"======================================================\n");

    for(i=0;i<n;i++)
        if(s[i].bigo.adoption=='Y')
            fprintf(fs,"%d\t%s\t%d\t%d\t%d\t%d\t%0.1f\t%d\t%c\n", s[i].num, s[i].name, s[i].kor, s[i].eng, s[i].mat, s[i].total, s[i].avg, s[i].rank, s[i].bigo.adoption);
    fprintf(fs,"======================================================\n\n");
    fclose(fs);

    pauseClear();
}

//�̼��� ���� ��� �Լ�
void complete_stu(strStu* s, int n)
{
    FILE* fs;
    int i;

    fs = fopen("s.txt", "w");

    fprintf(fs, "                                       <�̼��� ���>\n");
    fprintf(fs, "\n======================================================\n");
    fprintf(fs, "�й�\t�̸�\t����\t����\t����\t����\t���\t���\t���\n");
    fprintf(fs, "======================================================\n");

    for (i = 0; i < n; i++)
        if(s[i].avg>=70)
            fprintf(fs, "%d\t%s\t%d\t%d\t%d\t%d\t%0.1f\t%d\t%c\n", s[i].num, s[i].name, s[i].kor, s[i].eng, s[i].mat, s[i].total, s[i].avg, s[i].rank, s[i].bigo.fall_num);
    fprintf(fs, "======================================================\n\n");
    fclose(fs);

    pauseClear();
}

//���̼��� ���� ��� �Լ�
void ncomplete_stu(strStu* s, int n)
{
    FILE* fs;
    int i;

    fs = fopen("s.txt", "w");

    fprintf(fs, "                                      <���̼��� ���>\n");
    fprintf(fs, "\n======================================================\n");
    fprintf(fs, "�й�\t�̸�\t����\t����\t����\t����\t���\t���\t���\n");
    fprintf(fs, "======================================================\n");

    for (i = 0; i < n; i++)
        if (s[i].avg <= 70)
            fprintf(fs, "%d\t%s\t%d\t%d\t%d\t%d\t%0.1f\t%d\t%d\n", s[i].num, s[i].name, s[i].kor, s[i].eng, s[i].mat, s[i].total, s[i].avg, s[i].rank, s[i].bigo.fall_num);
    fprintf(fs, "======================================================\n\n");
    fclose(fs);

    pauseClear();
}

//�޴��� ���ư��� �Լ�
void pauseClear()
{
    printf("�ƹ�Ű�� ������ ���θ޴��� ���ư��ϴ�\n");
    getch();
    system("cls");
}