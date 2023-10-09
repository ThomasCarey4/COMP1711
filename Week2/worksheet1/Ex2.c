#include <stdio.h>

int main(){
    int l,w,a;
    printf("Please enter the first number: ");
    scanf("%d", &l);
    printf("Please enter the second number: ");
    scanf("%d", &w);
    a = l + w;
    printf("The sum of adding %d and %d is %d\n", l, w, a);

    return 0;
}