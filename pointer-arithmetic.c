#include <stdio.h>
int test(int *add) {
    printf("%d\n", *add);
    return 0;
}
int main() {
    int array[5] = {1, 2, 3, 4, 5};
    printf("%p\n", array); // Returns memory address
    test(array); // Returns 1
    test(array + 1); // Returns 2
    test(array + 2); // Returns 3
    return 0;
}
