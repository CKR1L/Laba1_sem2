#include <stdio.h>
#include <limits.h>
int main(){
    int min_nomber = INT_MAX;
    int a[5] = {1, 2, 3, 4, 3};
    for(int i = 0; i < 5; i++){
        if (a[i]<min_nomber){
            min_nomber = a[i];
        }
    }
    printf("%d", min_nomber);
    return 0;
}