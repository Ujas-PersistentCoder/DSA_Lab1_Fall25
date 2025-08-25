#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Swaps two size_t values.
void swap(size_t *a, size_t *b) {
    size_t temp = *a;
    *a = *b;
    *b = temp;
}

// Reverses a sub-array from a start to an end index.
void reverse(size_t *arr, size_t start, size_t end) {
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

/**
 * @brief Generates the lexicographically previous permutation in-place.
 * @param n The number of elements in the permutation.
 * @param perm The permutation array to be modified.
 * @return True if a previous permutation exists, otherwise false.
 */

bool prev(size_t n, size_t *perm) {
    if (!n) return false;
    // 1. Find the rightmost element perm[ind] that is greater than its right neighbor.
    int ind = -1;
    for (int i = (int)n - 1; i > 0; i--) {
        if (perm[i - 1] > perm[i]) {
            ind = i - 1;
            break;
        }
    }
    // If no such element exists, the permutation is the first (e.g., 1 2 3).
    if (ind == -1) return false;
    // 2. Find the rightmost element in the suffix (to the right of ind) that is smaller than perm[ind].
    for (int j = (int)n - 1; j > ind; j--) {
        if (perm[j] < perm[ind]) {
            // 3. Swap these two elements.
            swap(&perm[ind], &perm[j]);
            break;
        }
    }
    // 4. Reverse the suffix to make it the largest possible sequence.
    reverse(perm, ind + 1, n - 1);
    return true;
}

int main(){
    size_t n;
    scanf("%zu", &n);
  
    size_t *p = malloc(n * sizeof(size_t));
    for (size_t i = 0; i < n; i++) scanf("%zu", &p[i]);
    // If a previous permutation exists, print it.
    if (prev(n, p)) {
        for (size_t i = 0; i < n; i++) printf("%zu ", p[i]);
    } else {
        // Otherwise, indicate it's the first permutation.
        printf("-1");
    }
  
    free(p);
    return 0;
}
