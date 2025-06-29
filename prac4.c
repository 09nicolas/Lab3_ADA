// chemistries.c
// Divide n players into teams of 2 with equal total skill,
// and compute the sum of the products (chemistry) of each team.
// If impossible, print -1.

#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia < ib) ? -1 : (ia > ib);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0 || (n & 1)) {
        fprintf(stderr, "Invalid input: n must be a positive even integer\n");
        return 1;
    }

    int *skill = malloc(n * sizeof(int));
    if (!skill) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &skill[i]) != 1) {
            fprintf(stderr, "Error reading skill[%d]\n", i);
            free(skill);
            return 1;
        }
    }

    // Sort skills ascending
    qsort(skill, n, sizeof(int), cmp_int);

    // The required sum for each pair:
    long long target = (long long)skill[0] + skill[n-1];
    long long total_chemistry = 0;

    // Pair smallest with largest, next smallest with next largest, ...
    for (int i = 0; i < n/2; i++) {
        long long s = (long long)skill[i] + skill[n-1-i];
        if (s != target) {
            printf("-1\n");
            free(skill);
            return 0;
        }
        total_chemistry += (long long)skill[i] * skill[n-1-i];
    }

    printf("%lld\n", total_chemistry);
    free(skill);
    return 0;
}
