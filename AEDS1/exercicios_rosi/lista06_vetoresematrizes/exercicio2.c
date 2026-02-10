#include <stdlib.h>
#include <stdio.h>

int main () {
    int dias = 0;
    float temp[31], menor_t, maior_t, media_t = 0;
    for (int i = 0; i < 31; i++) {
        scanf("%f", &temp[i]);
        media_t += temp[i];
        if (i == 0) {
            menor_t = temp[i];
            maior_t = temp[i];
        }
        else {
            if (temp[i] > maior_t) maior_t = temp[i];
            else if (temp[i] < menor_t) menor_t = temp[i];
        }
    }
    media_t /= 31;
    for (int i = 0; i < 31; i++) if (temp[i] < media_t) dias++;
    printf("Menor e maior temperatura: %.0f e %.0f\n", menor_t, maior_t);
    printf("Media de temperatura: %.2f\n", media_t);
    printf("Numero de dias nos quais a temperatura foi inferior a temperatura media: %d\n", dias);
}