#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, n1 = 1, n2 = 1, r;
    scanf("%d", &N);
    printf("%d %d ", n1, n2);
    for (int cont1 = 3; cont1 <= N; cont1++) {
        r = n1 + n2;
        printf("%d ", r);
        n1 = n2;
        n2 = r;
    }
}
