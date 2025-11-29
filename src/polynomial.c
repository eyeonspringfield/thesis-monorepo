// Evaluates a polynomial over a given range using Horner's method.
// Polynomial is: P(x) = { x >= 0: 3x^3 + 5x^2 - 7x + 11
//                         x < 0: -2x^2 + 9x - 13 }}

#include <stdio.h>

int evaluate_polynomial(int x) {
    if (x >= 0) {
        return ((3 * x + 5) * x - 7) * x + 11;
    } else {
        return (-2 * x + 9) * x - 13;
    }
}

int main() {
    int start = -50;
    int end = 150;

    for (int x = start; x <= end; x++) {
        int result = evaluate_polynomial(x);
        printf("P(%d) = %d\n", x, result);
    }

    return 0;
}