#include <stdio.h>
int test(int *add) {
    *add = 5;
    printf("%p\n", add);
    return 0;
}
int main() {
    int num = 10;
    printf("num is %d\n", num); // Returns 10
    test(&num);
    printf("num is %d\n", num); // Returns 5
    return 0;
}
