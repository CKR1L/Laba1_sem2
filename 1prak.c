#include <stdio.h>
int main(){
    int a=0, b=0, c;
    scanf("%d",&a);
    scanf("%d",&b);
    if (b==0){
        printf("На 0 делить нельзя!");
        return 0;
    }
    c=(a/b);
    printf("%d", c);
    return 0;
}
