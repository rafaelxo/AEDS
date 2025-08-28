#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int N, exp = 2, x, num = 1, sinal = -1, incr = 1;
    float S = 0;
    printf("Insira o numero de termos e o valor de X:\n");
    scanf("%d%d", &N, &x);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        int fat = 1;
        for (int cont2 = 1; cont2 <= num; cont2++) fat *= cont2;
        S += sinal * ((pow(x, exp))/fat);
        sinal *= -1;
        exp++;
        if (num == N) incr -= 1;
        else if (num == 1) incr += 1;
        num += incr;
    }
    printf("\nO valor da formula para %d termos e X = %d e de:\n%f\n", N, x, S);
}
