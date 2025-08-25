#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Calculates the 1-based lexicographical index of a permutation.
 * @param p A 0-based permutation array.
 * @param n The number of elements in the permutation.
 * @return The 1-based lexicographical index.
 */

long long pindex(size_t *p, size_t n) {
    // Pre-compute factorials.
    long long* factorials = malloc(20 * sizeof(long long));
    factorials[0] = 1;
    for (size_t i = 1; i < 20; i++) {
        factorials[i] = factorials[i - 1] * i;
    }
    // `count` tracks which numbers are still available to be used.
    size_t *count = malloc(n * sizeof(size_t));
    for (size_t i = 0; i < n; i++) {
        count[i] = 1;
    }
    long long ind = 0;
    for (size_t i = 0; i < n; i++) {
        size_t sum = 0;
        // Count available numbers smaller than p[i].
        for (size_t j = 0; j < p[i]; j++) {
            sum += count[j];
        } 
        // Add to index based on factoradic system.
        if (n - i - 1 < 20) {
            ind += sum * factorials[n - i - 1];
        }
        // Mark p[i] as used.
        count[p[i]] = 0;
    }
    free(count);
    free(factorials);
    // Return 1-based index.
    return ++ind;
}

int main() {
    size_t n;
    scanf("%zu", &n);

    size_t *p = malloc(n * sizeof(size_t));
    for (size_t i = 0; i < n; i++) {
        scanf("%zu", &p[i]);
        p[i]--; // Convert 1-based input to 0-based for the algorithm.
    }

    printf("%lld\n", pindex(p, n));

    free(p);
    return 0;
}
