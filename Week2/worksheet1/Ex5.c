#include <stdio.h>

int main(){
    int a,b,t;
    a = 3;
    b = 5;
    t;
    t = a, a = b, b = t;
    printf("%d\n", a);
    printf("%d\n", b);
    return 0;
}