#include <stdio.h>
#include <stdlib.h>

void conversao(int segundos) {
    int h, min, r, seg;
    h = segundos/3600;
    r = segundos%3600;
    min = r/60;
    seg = r%60;
    printf("\nOs segundos inseridos transformados em hora equivale a:\n%d horas : %d minutos : %d segundos", h, min, seg);
}

int main() {
   int seg;
   printf("Insira os segundos para realizar a conversao:\n");
   scanf("%d", &seg);
   conversao(seg);
}
