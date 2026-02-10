#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float n1, n2, n3, n4, media;
    printf("Insira as 4 notas do aluno para calcular a media aritmetica:\n");
    scanf("%f%f%f%f", &n1, &n2, &n3, &n4);
    media = (n1 + n2 + n3 + n4) / 4.0;
    if (media >= 7) {
        printf("\nMedia de %.2f e aluno Aprovado!\n", media);
    } else {
        printf("\nMedia de %.2f e aluno Reprovado!\n", media);
    }
}
