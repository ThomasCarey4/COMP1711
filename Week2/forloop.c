#include <stdio.h>

int main() {
    int a;

    for (a = 0; a < 5; ++a) {
        printf ("a is equal to %d\n", a);
    }
    printf ("I've finished the loop and a is equal to %d\n", a);
    
    return 0;
}