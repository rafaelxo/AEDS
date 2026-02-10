#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    float E = 1;
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        int fat = 1;
        for (int cont2 = 1; cont2 <= cont1; cont2++) {
            fat *= cont2;
        }
        E += 1.0/fat;
    }
    printf("%.2f", E);
}