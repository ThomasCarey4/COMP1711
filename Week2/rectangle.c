#include <stdio.h>

int main(){
    float l,w,a;
    printf("Please enter the length of the rectange: ");
    scanf("%f", &l);
    printf("Please enter the width of the rectange: ");
    scanf("%f", &w);
    a = l * w;
    printf("The area is %.2f\n", a);

    return 0;
}