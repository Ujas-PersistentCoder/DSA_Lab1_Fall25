#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
bool le ( size_t *p , size_t *q , size_t n ){
    for (size_t i = 0; i < n; i++){
        if (p[i] > q[i])return false;
        if (p[i] < q[i])return true;
    }
    return true;
}

int main(){
    size_t n;
    scanf("%zu", &n);
    size_t *p = malloc(n * sizeof(size_t));
    size_t *q = malloc(n * sizeof(size_t));
    if (!p || !q) {
        printf("Error in memory allocation");
        return 1;
    }
    for (size_t i = 0; i < n; i++)scanf("%zu", &p[i]);
    for (size_t i = 0; i < n; i++)scanf("%zu", &q[i]);
    if (le(p, q, n))printf("YES");
    else printf("NO");
    free(p); free(q);
    return 0;
}
