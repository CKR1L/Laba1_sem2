#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include "statistics.h"
int main(){
    //������� �� ������� ����
    setlocale(LC_ALL,"Rus");
    //���������� �����
    FILE* file;
    file=fopen("list.txt","r");
 
    //���������� �������� ������ �� ��������
    short int rus[50];
    short int math[50];
    short int phis[50];
    short int inf[50];
    short int benefit[50];
 
    //���������� ��������� �������� � ����������
    short int answers[11];
    for(long int i=0; i<sizeof(answers);i++) answers[i]=0;
    char name_of_sub[13];
    
    short int error_of_input=0;
    short int stud_count=0;
    short int num_of_sub=0;    
    short int end_of_file=0;
    while(1)
    {
        
        num_of_sub=0;
        file=fopen("inlist.txt","r");
        //����� ������ �������
        printf("| ����������� |������� ��� �����|������� � ������ �����|����������� ����� ������|������������ ����� ������|���������� ����������(��,��,��)|������� ���� �� ��������(�,�,�,�)|������|���������|\n");
        end_of_file=0;
        while(end_of_file==0)
        {
            memset(name_of_sub,0,sizeof(name_of_sub));
            answers[2]=1000;
            read_statistic(file,rus,math,phis,inf,benefit,name_of_sub,&error_of_input,&stud_count,&end_of_file,&num_of_sub);
            printf("|%13.13s|",name_of_sub);
            count_statistic(answers,rus,math,phis,inf,benefit,stud_count,error_of_input);
            printf("%23d|%18d|%24d|%25d|%25d,%2d,%2d|%24d,%2d,%2d,%2d|%6d|%9d|\n",answers[0],answers[1],answers[2],answers[3],answers[4],answers[5],answers[6],answers[7],answers[8],answers[9],answers[10],error_of_input,stud_count-1);
        }
        printf("���� ������� %d �����������\n",num_of_sub);
        fclose(file);
        if(read_repeat()==0) break;
         
    }
}