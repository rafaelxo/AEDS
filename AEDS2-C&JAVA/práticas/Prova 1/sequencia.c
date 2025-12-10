#include <stdio.h>

int main () {
    int A, B;
    while (scanf("%d%d", &A, &B) != EOF) {
        int SA[A], SB[B];
        for (int i = 0; i < A; i++) scanf("%d", &SA[i]);
        for (int i = 0; i < B; i++) scanf("%d", &SB[i]);
        int i = 0, j = 0;
        while (i < A && j < B) {
            if (SA[i] == SB[j]) j++;
            i++;
        }
        if (j == B) printf("S\n");
        else printf("N\n");
    }
    return 0;
}
