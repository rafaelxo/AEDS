#include <stdlib.h>
#include <stdio.h>

int main () {
    int x[10], y[10], u[20], d[10], s[10], p[10], i[10], uniao = 0, diferenca = 0, intersecao = 0, cont2, cont3;
    for (int cont1 = 0; cont1 < 10; cont1++) {
        printf("Digite o valor da posicao %d do vetor X:\n", cont1 + 1);
        scanf("%d", &x[cont1]);
        printf("Digite o valor da posicao %d do vetor Y:\n", cont1 + 1);
        scanf("%d", &y[cont1]);
    }
    for (int cont1 = 0; cont1 < 10; cont1++) {
        cont2 = 0;
        while (cont2 < uniao && x[cont1] != u[cont2]) cont2++;
        if (cont2 >= uniao) {
            u[uniao] = x[cont1];
            uniao++;
        }
    }
    for (int cont1 = 0; cont1 < 10; cont1++) {
        cont2 = 0;
        while (cont2 < uniao && y[cont1] != u[cont2]) cont2++;
        if (cont2 >= uniao) {
            u[uniao] = y[cont1];
            uniao++;
        }
    }
    printf("\nA uniao dos vetores X e Y e:\n");
    for (int cont1 = 0; cont1 < uniao; cont1++) printf("%d ", u[cont1]);
    for (int cont1 = 0; cont1 < 10; cont1++) {
        cont2 = 0;
        while (x[cont1] != y[cont2] && cont2 < 10) cont2++;
        if (cont2 >= 10) {
            cont3 = 0;
            while (cont3 < diferenca && x[cont1] != d[cont3]) cont3++;
            if (cont3 >= diferenca) {
                d[diferenca] = x[cont1];
                diferenca++;
            }
        }
    }
    printf("\nA diferenca dos vetores X e Y e:\n");
    for (int cont1 = 0; cont1 < diferenca; cont1++) printf("%d ", d[cont1]);
    for (int cont1 = 0; cont1 < 10; cont1++) {
        s[cont1] = x[cont1] + y[cont1];
        p[cont1] = x[cont1] * y[cont1];
    }
    for (int cont1 = 0; cont1 < 10; cont1++) printf("\nA soma e o produto dos vetores X e Y na posicao %d equivalem, respectivamente, a:\n%d e %d\n", cont1 + 1, s[cont1], p[cont1]);
    for (int cont1 = 0; cont1 < 10; cont1++) {
        cont2 = 0;
        while (cont2 < 10 && x[cont1] != y[cont2]) cont2++;
        if (cont2 < 10) {
            cont3 = 0;
            while (cont3 < intersecao && x[cont1] != i[cont3]) cont3++;
            if (cont3 >= intersecao) {
                i[intersecao] = x[cont1];
                intersecao++;
            }
        }
    }
    printf("\nA intersecao dos vetores X e Y e:\n");
    for (int cont1 = 0; cont1 < intersecao; cont1++) printf("%d ", i[cont1]);
}