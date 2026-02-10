#include <stdio.h>
#include <stdlib.h>

int main() {
    float trabalho, avaliacao, exame, media;
    printf("Insira as notas do trabalho, da avaliacao e do exame do aluno:\n");
    scanf("%f%f%f", &trabalho, &avaliacao, &exame);
    media = (trabalho * 2 + avaliacao * 3 + exame * 5) / 10.0;
    printf("\nA media do aluno e de:\n%.2f\n", media);
    if (media >= 8 && media <= 10 || media > 10) {
        printf("\nObteve conceito A\n");
    } else if (media >= 7 && media < 8) {
        printf("\nObteve conceito B\n");
    } else if (media >= 6 && media < 7) {
        printf("\nObteve conceito C\n");
    } else if (media >= 5 && media < 6) {
        printf("\nObteve conceito D\n");
    } else if (media >= 0 && media < 5 || media < 0) {
        printf("\nObteve conceito E\n");
    }

    return 0;
}
