#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    float S = 0;
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        S += 1.0/cont1;
    }
    printf("%.2f", S);
}
