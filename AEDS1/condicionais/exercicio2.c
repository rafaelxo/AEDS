#include <stdio.h>
#include <stdlib.h>

int main() {
    float n1, n2, n3, media, n_exame;
    printf("Insira as 3 notas do aluno:\n");
    scanf("%f%f%f", &n1, &n2, &n3);
    media = (n1 + n2 + n3) / 3.0;
    if (media >=0 && media < 3 || media <=0) {
        printf("\nAluno reprovado!\n");
    }
    else if (media >=3 && media < 7) {
        n_exame = 12 - media;
        printf("\nAluno ficou para exame e precisa tirar %.2f para passar!\n", n_exame);
    }
    else if (media >=7 && media <= 10 || media > 10) {
        printf("\nAluno aprovado!\n");
    }
}
