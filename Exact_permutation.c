#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Finds the k-th lexicographical permutation of numbers from 1 to n.
 * @param n The number of elements (from 1 to n).
 * @param k The 1-based rank of the desired permutation.
 * @return A pointer to an array containing the permutation.
 */

int* exact_permutation(int n, long long k) {
    // Pre-compute factorials up to 20!
    long long factorials[21];
    factorials[0] = 1;
    for (int i = 1; i < 21; i++) {
        factorials[i] = factorials[i - 1] * i;
    }
    int* result = malloc(n * sizeof(int));
    // Use an array to track which numbers (1 to n) are available.
    int count[n + 1];
    for (int i = 1; i <= n; i++) {
        count[i] = 1; // 1 means available, 0 means used.
    }
    k--; // Convert 1-based rank 'k' to 0-based index.
    // Determine one number of the permutation in each iteration.
    for (int i = 0; i < n; i++) {
        // Find which available number to pick using factoradic system.
        int temp = 0;
        if ((n - 1 - i) < 21) {
            temp = k / factorials[n - 1 - i];
            k %= factorials[n - 1 - i];
        }
        // Find the 'temp'-th available number.
        for (int j = 1; j <= n; j++) {
            if (count[j]) { // Check if number 'j' is available.
                if (temp == 0) {
                    result[i] = j;
                    count[j] = 0; // Mark as used.
                    break;
                }
                temp--;
            }
        }
    }
    return result;
}

int main(void) {
    int n;
    long long k;
    scanf("%d %lld", &n, &k);

    int* result = exact_permutation(n, k);

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }

    free(result);
    return 0;
}
