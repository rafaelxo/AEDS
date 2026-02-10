#include <stdio.h>
#include <stdlib.h>

float medias (float n1, float n2, float n3, char opcao) {
    if (opcao == 'A') return (n1 + n2 + n3)/3;
    else if (opcao == 'P') return (n1*5 + n2*3 + n3*2)/8;
}

int main () {
    int N;
    float n1, n2, n3;
    char opcao;
    printf("Insira a quantidade de alunos que deseja calcular:\n");
    scanf("%d", &N);
    for (int cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira as 3 notas do aluno e a media que deseja calcular (A - aritmetica ou P - ponderada):\n");
        scanf("%f%f%f %c", &n1, &n2, &n3, &opcao);
        printf("\nO valor da media %c desse aluno e de %.2f pontos!\n", opcao, medias(n1, n2, n3, opcao));
    }
}
