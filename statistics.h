#include <math.h> 
void count_statistic(short int array[11],short int rus_points,short int math_points,short int phis_points,short int inf_points,short int benefit, short int stud_count,short int error_of_input){
    array[3]=300;
    array[4]=0;
    for(int i=0;i<30;i++){
            
 
            array[1]+=rus_points+math_points+fmax(inf_points,phis_points);
            if(benefit==4){
                array[2]+=300;
            }
            else{
                array[2]+=rus_points+math_points+fmax(inf_points,phis_points);
            }
            if(array[3]>rus_points+math_points+fmax(inf_points,phis_points)){
                array[3]=rus_points+math_points+fmax(inf_points,phis_points);
            }
            if(array[4]<rus_points+math_points+fmax(inf_points,phis_points)){
                array[4]=rus_points+math_points+fmax(inf_points,phis_points);
            }
            if(benefit==1) array[5]+=1;
            if(benefit==2) array[6]+=1;
            if(benefit==3) array[7]+=1;
            array[8]+=math_points;
            array[9]+=rus_points;
            array[10]+=inf_points;
            array[11]+=phis_points;
            }
    array[1]/=30;
    array[2]/=30;
    array[8]/=30;
    array[9]/=30;
    array[10]/=30;
    array[11]/=30;
}