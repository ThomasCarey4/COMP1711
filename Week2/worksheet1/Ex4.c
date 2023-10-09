#include <stdio.h>
#define __USE_MISC
#include <math.h>
int main(){
    float r,a;
    printf("What is the radius? ");
    scanf("%f", &r);
    a = M_PI * r*r;
    printf("The area is %f\n", a);
    return 0;
}