// divide.c
// Divide two 32-bit signed integers without using *, /, or % operators.
// Truncate toward zero and handle overflow.

#include <stdio.h>
#include <limits.h>

int divide(int dividend, int divisor) {
    // Handle overflow case: INT_MIN / -1
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }

    // Determine sign of result
    int negative = ( (dividend < 0) ^ (divisor < 0) );

    // Work with positive longs to avoid overflow when taking abs(INT_MIN)
    long long dvd = dividend;
    long long dvs = divisor;
    if (dvd < 0) dvd = -dvd;
    if (dvs < 0) dvs = -dvs;

    long long quotient = 0;
    // Subtract multiples of divisor by shifting
    for (int shift = 31; shift >= 0; --shift) {
        if ( (dvd >> shift) >= dvs ) {
            quotient += 1LL << shift;
            dvd -= dvs << shift;
        }
    }

    // Apply sign
    if (negative) quotient = -quotient;

    // Clamp to 32-bit range just in case
    if (quotient > INT_MAX) return INT_MAX;
    if (quotient < INT_MIN) return INT_MIN;
    return (int)quotient;
}

int main(void) {
    int dividend, divisor;
    if (scanf("%d %d", &dividend, &divisor) != 2) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    // divisor guaranteed non-zero by problem statement
    int result = divide(dividend, divisor);
    printf("%d\n", result);
    return 0;
}
