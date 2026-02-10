#include <stdlib.h>
#include <stdio.h>

int main() {
    int maior_mes, menor_mes;
    float t[12], maior_t, menor_t;
    for (int cont1 = 0; cont1 < 12; cont1++) {
        printf("Digite a temperatura media do mes %d: ", cont1 + 1);
        scanf("%f", &t[cont1]);
        if (cont1 == 0) {
            maior_t = t[cont1];
            menor_t = t[cont1];
            maior_mes = cont1 + 1;
            menor_mes = cont1 + 1;
        } else {
            if (t[cont1] > maior_t) {
                maior_t = t[cont1];
                maior_mes = cont1 + 1;
            }
            if (t[cont1] < menor_t) {
                menor_t = t[cont1];
                menor_mes = cont1 + 1;
            }
        }
    }
    printf("\nA maior media de temperatura, equivalente a %.2f graus, foi no mes %d!\n", maior_t, maior_mes);
    printf("A menor media de temperatura, equivalente a %.2f graus, foi no mes %d!\n", menor_t, menor_mes);
}