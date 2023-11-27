#include <stdio.h>
int test(int *add) {
    printf("%d\n", *add);
    return 0;
}
int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    printf("%p\n", arr); // Returns memory address
    test(arr); // Returns 1
    test(arr + 1); // Returns 2
    test(arr + 2); // Returns 3
    return 0;
}
