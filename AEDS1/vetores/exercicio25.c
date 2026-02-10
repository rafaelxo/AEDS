#include <stdlib.h>
#include <stdio.h>

int main() {
    int p[10], num = 101, cont_p = 0;
    do {
        int divisores = 0;
        for (int cont1 = 1; cont1 <+ num; cont1++) {
            if (num%cont1 == 0) divisores++;
        }
        if (divisores == 2) {
            p[cont_p] = num;
            cont_p++;
        }
        num++;
    } while (cont_p < 10);
    printf("Os dez primeiros numeros primos de 0 a 100 sao:\n");
    for (int cont1 = 0; cont1 < 10; cont1++) printf("%d ", p[cont1]);
}