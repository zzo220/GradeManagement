#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


//비고 공용체 정의
union note
{
    int fall_num;
    char adoption;
};

//학생 정보 구조체 정의
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


void choice(strStu* stu, int n); //메뉴 함수
void sort(strStu* s, int n); //오름차순 정렬 함수
void stu_average(strStu* s, int n); //학생 개인 평균 구하는 함수
void stu_rank(strStu* s, int n); //학생 등수 구하는 함수
void bigo_note(strStu* s, int n); //비고 구분 함숫
void stu_rec(strStu* stu, int n); //전체 학생 출력 함수
void group_avg(strStu* s, int n); //과목별 반 평균 출력 함수
void dux(strStu* s, int n); //최우수 학생 출력 함수
void each_grade(strStu* s, int n); //개별 성적 출력 함수
void scholarship(strStu* s, int n); //장학생 명단 파일 출력 함수
void complete_stu(strStu* s, int n); //이수자 명단 파일 출력 함수
void ncomplete_stu(strStu* s, int n); //미이수자 명단 파일 출력 함수
void pauseClear(); //메뉴로 다시 돌아가는 함수

int main()
{
    int i, total_stu;
    strStu s[50]; //학생정보

    //학생 수 입력받기
    printf("학생 수를 입력하시오 : ");
    scanf("%d", &total_stu);
    
    //학생 정보 입력받기
    for (i = 0; i < total_stu; i++)
    {
        printf("번호, 이름, 국어점수, 영어점수, 수학점수를 차례로 입력하시오 : ");
        scanf("%d %s %d %d %d", &s[i].num, s[i].name, &s[i].kor, &s[i].eng, &s[i].mat);
    }
    system("cls");

    sort(&s, total_stu); //정렬 함수 호출
    stu_average(&s, total_stu); //평균 구하는 함수 호출
    stu_rank(&s, total_stu); //등수 구하는 함수 호출
    bigo_note(&s, total_stu); //비고 구분하는 함수 호출

    choice(&s, total_stu); //메뉴 호출
}

//메뉴 호출 함수
void choice(strStu* stu, int n)
{
    //MENU 목록 출력
    char ch;
    printf("\n------------MENU------------\n");
    printf("> a:전체 학생 정보 출력\n");
    printf("> b:과목별 반 평균 출력\n");
    printf("> c:최우수 학생 조회\n");
    printf("> d:학생 개별 성적 조회\n");
    printf("> e:장학생 정보 파일 저장\n");
    printf("> f:이수자 명단 파일 저장\n");
    printf("> g:미이수자 명단 파일 저장\n");
    printf("> x:프로그램 종료\n");
    printf("----------------------------\n");
    printf("조회하고 싶은 메뉴를 선택하세요 > ");

    //메뉴 선택
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

//정렬 함수
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

//평균 구하는 함수
void stu_average(strStu* s, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        s[i].total = s[i].kor + s[i].eng + s[i].mat;
        s[i].avg = s[i].total / (double)3;
    }
}

//등수 구하는 함수
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

//비고 구분하는 함수
void bigo_note(strStu* s, int n)
{
    int i, failure_num;

    for (i = 0; i < n; i++)
    {
        //미이수자
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
        //이수자
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

//전체 학생 출력 함수
void stu_rec(strStu* s, int n)
{
    int i;

    printf("\n==============================================================================\n");
    printf("학번\t이름\t\t국어\t영어\t수학\t총점\t평균\t등수\t비고\n");
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

//과목별 반 평균 출력 함수
void group_avg(strStu* s, int n)
{
    int i, kor_tot=0, eng_tot=0, mat_tot=0;

    printf("===========과목 별 반 평균============\n");
    for (i = 0; i < n; i++)
    {
        kor_tot += s[i].kor;
        eng_tot += s[i].eng;
        mat_tot += s[i].mat;
    }
    
    printf("국어 평균 : %0.1f\n영어 평균 : %0.1f\n국어 평균 : %0.1f\n", (double)kor_tot / n, (double)eng_tot / n, (double)mat_tot / n);
    printf("======================================\n\n");

    pauseClear();
}

//최우수 학생 출력
void dux(strStu *s, int n)
{
    int i;

    for(i=0;i<n;i++)
        if (s[i].rank == 1)
        {
            printf("========최우수 학생=======\n");
            printf("\t   %s\n", s[i].name);
            printf("==========================\n\n");
        }

    pauseClear();
}

//조회 함수
void each_grade(strStu* s, int n)
{
    int stu_num;
    int i;

    printf("조회하고 싶은 학생의 학번을 입력하시오 > ");
    scanf("%d", &stu_num);
    if (stu_num > n || stu_num <= 0)
    {
        printf("학생이 존재하지 않습니다\n");
        each_grade(s, n);
    }
    getchar('\n');

    for (i = 0; i < n; i++)
        if (s[i].num == stu_num)
        {
            printf("=====================================\n");
            printf("학번\t이름\t\t평균\t등수\n");
            printf("-------------------------------------\n");
            printf("%d\t%s\t\t%0.1f\t%d\n", s[i].num, s[i].name, s[i].avg, s[i].rank);
            printf("=====================================\n\n");
        }

    pauseClear();
}

//장학생 파일 출력 함수
void scholarship(strStu* s, int n)
{
    FILE* fs;
    int i;

    fs = fopen("s.txt", "w");

    fprintf(fs, "                                       <장학생 명단>\n");
    fprintf(fs,"\n======================================================\n");
    fprintf(fs,"학번\t이름\t국어\t영어\t수학\t총점\t평균\t등수\t비고\n");
    fprintf(fs,"======================================================\n");

    for(i=0;i<n;i++)
        if(s[i].bigo.adoption=='Y')
            fprintf(fs,"%d\t%s\t%d\t%d\t%d\t%d\t%0.1f\t%d\t%c\n", s[i].num, s[i].name, s[i].kor, s[i].eng, s[i].mat, s[i].total, s[i].avg, s[i].rank, s[i].bigo.adoption);
    fprintf(fs,"======================================================\n\n");
    fclose(fs);

    pauseClear();
}

//이수자 파일 출력 함수
void complete_stu(strStu* s, int n)
{
    FILE* fs;
    int i;

    fs = fopen("s.txt", "w");

    fprintf(fs, "                                       <이수자 명단>\n");
    fprintf(fs, "\n======================================================\n");
    fprintf(fs, "학번\t이름\t국어\t영어\t수학\t총점\t평균\t등수\t비고\n");
    fprintf(fs, "======================================================\n");

    for (i = 0; i < n; i++)
        if(s[i].avg>=70)
            fprintf(fs, "%d\t%s\t%d\t%d\t%d\t%d\t%0.1f\t%d\t%c\n", s[i].num, s[i].name, s[i].kor, s[i].eng, s[i].mat, s[i].total, s[i].avg, s[i].rank, s[i].bigo.fall_num);
    fprintf(fs, "======================================================\n\n");
    fclose(fs);

    pauseClear();
}

//미이수자 파일 출력 함수
void ncomplete_stu(strStu* s, int n)
{
    FILE* fs;
    int i;

    fs = fopen("s.txt", "w");

    fprintf(fs, "                                      <미이수자 명단>\n");
    fprintf(fs, "\n======================================================\n");
    fprintf(fs, "학번\t이름\t국어\t영어\t수학\t총점\t평균\t등수\t비고\n");
    fprintf(fs, "======================================================\n");

    for (i = 0; i < n; i++)
        if (s[i].avg <= 70)
            fprintf(fs, "%d\t%s\t%d\t%d\t%d\t%d\t%0.1f\t%d\t%d\n", s[i].num, s[i].name, s[i].kor, s[i].eng, s[i].mat, s[i].total, s[i].avg, s[i].rank, s[i].bigo.fall_num);
    fprintf(fs, "======================================================\n\n");
    fclose(fs);

    pauseClear();
}

//메뉴로 돌아가는 함수
void pauseClear()
{
    printf("아무키나 누르면 메인메뉴로 돌아갑니다\n");
    getch();
    system("cls");
}