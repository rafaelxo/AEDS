#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main () {
    FILE *arquivo = fopen("entrada10.txt", "w");
    float num, media = 0, menor, maior;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 100; i++) {
        num = ((float)rand() / RAND_MAX) * 100;
        fprintf(arquivo, "%f\n", num);
    }
    fclose(arquivo);
    arquivo = fopen("entrada10.txt", "r");
    for (int i = 0; i < 100; i++) {
        fscanf(arquivo, "%f", &num);
        media += num;
        if (i == 0) {
            menor = num; maior = num;
        } else {
            if (num < menor) menor = num;
            if (num > maior) maior = num;
        }
    }
    fclose(arquivo);
    printf("%.2f\n%.2f\n%.2f", maior, menor, media/100);
}