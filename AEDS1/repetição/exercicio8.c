#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, n1 = 2, n2 = 7, n3 = 3, s = 4;
    printf("Insira quantos termos quer calcular da sequencia:\n");
    scanf("%d", &N);
    printf("\nO valor dos tres primeiros termos equivalem, respectivamente, a:\n%d, %d e %d\n", n1, n2, n3);
    while (s != N) {
        n1 *= 2;
        printf("\ne o valor do proximo termo e:\n%d\n", n1);
        n2 *= 3;
        printf("\ne o valor do proximo termo e:\n%d\n", n2);
        n3 *= 4;
        printf("\ne o valor do proximo termo e:\n%d\n", n3);
        s += 1;
    }
}
