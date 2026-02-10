#include <stdlib.h>
#include <stdio.h>

int main () {
    int num[8], pos[8], neg[8], contpos = 0, contneg = 0;
    for (int cont1 = 0; cont1 < 8; cont1++) {
        printf("Digite o valor da posicao %d do vetor:\n", cont1 + 1);
        scanf("%d", &num[cont1]);
        if (num[cont1] > 0) {
            pos[contpos] = num[cont1];
            contpos++;
        } else if (num[cont1] < 0) {
            neg[contneg] = num[cont1];
            contneg++;
        }
    }
    if (contpos > 0) {
        printf("\nO vetor de numeros positivos equivale, respectivamente, a:\n");
        for (int cont2 = 0; cont2 < contpos; cont2++) printf("%d na posicao %d\n", pos[cont2], cont2 + 1);
        printf("\n");
    } else printf("Vetor de poitivos vazio!\n");
    if (contneg > 0) {
        printf("\nO vetor de numeros negativos equivale, respectivamente, a:\n");
        for (int cont3 = 0; cont3 < contneg; cont3++) printf("%d na posicao %d\n", neg[cont3], cont3 + 1);
        printf("\n");
    } else printf("Vetor de negativos vazio!\n");
}