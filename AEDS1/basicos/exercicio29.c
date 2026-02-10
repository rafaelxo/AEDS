#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2;
    float media;
    printf("Insira as duas notas para realizar a media:\n");
    scanf("%d%d", &n1, &n2);
    media = (n1*2 + n2*3)/5.0;
    printf("\nA media dessas notas e:\n%.2f\n", media);
}
