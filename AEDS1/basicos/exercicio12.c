#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n1, n2, q1, q2;
    printf("Digite dois numeros inteiros e positivos para realizar os calculos:\n");
    scanf("%d%d", &n1, &n2);
    q1 = pow(n1, n2);
    q2 = pow(n2, n1);
    printf("\nOs resultados do primeiro numero elevado ao segundo, e viceversa e:\n%d\n%d\n", q1, q2);
}
