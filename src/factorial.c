// Computes the factorial of a (large) number using recursion.

#include <stdio.h>

long long factorial(long long n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    long long n = 20; // Largest factorial representable as 64-bit integer
    printf("factorial(%lld) = %lld\n", n, factorial(n));
    return 0;
}
