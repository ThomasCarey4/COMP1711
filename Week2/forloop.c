#include <stdio.h>

int main() {
    int a [10];

    for (int count = 0; count < 10; ++count){
        a[count] = count * 10 + count;
    }

    printf("The first and second elements are %d and %d\n", a[0], a[1]);
    printf("Or, via pointers, %d and %d\n", *a, *(a + 1));
    return 0;
}
