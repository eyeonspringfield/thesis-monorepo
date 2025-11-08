#include <stdio.h>

int square(int x) {
    return x * x;
}

int main(void) {
    int n = 5;
    printf("square(%d) = %d\n", n, square(n));
    return 0;
}
