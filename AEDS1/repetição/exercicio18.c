#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int N, quadrado, cubo;
    float raiz;
    printf("Insira um numero inteiro para realizar os calculos:\n");
    scanf("%d", &N);
    while (N > 0) {
        quadrado = pow (N, 2);
        cubo = pow (N, 3);
        raiz = sqrt(N);
        printf("O quadrado do numero, seu cubo e sua raiz quadrada equivalem, respectivamente, a:\n%d\n%d\n%.2f\n", quadrado, cubo, raiz);
        scanf("%d", &N);
    }
}