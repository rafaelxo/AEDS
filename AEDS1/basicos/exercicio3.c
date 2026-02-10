#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2, n3, p1, p2, p3;
    float media;
    printf("Digite 3 numeros positivos e inteiros e seus respectivos pesos:\n");
    scanf("%d%d%d%d%d%d", &n1, &n2, &n3, &p1, &p2, &p3);
    media = (n1*p1 + n2*p2 + n3*p3)/(p1 + p2 + p3*1.0);
    printf("\nA media ponderada desses valores e de:\n%.3f\n", media);
    return 0;
}
