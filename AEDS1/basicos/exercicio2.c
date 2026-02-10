#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2, n3;
    float media;
    printf("Digite 3 numeros positivos e inteiros para realizar a media:\n");
    scanf("%d%d%d", &n1, &n2, &n3);
    media = (n1 + n2 + n3)/3.0;
    printf("\nA media desses valores e de:\n%.2f\n", media);
    return 0;
}
