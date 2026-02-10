#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool verificacao (int num) {
    return num > 0;
}

int main () {
    int N, num;
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        scanf("%d", &num);
        if (verificacao(num)) printf("SIM\n");
        else printf("NAO\n");
    }
}