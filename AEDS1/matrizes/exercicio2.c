#include <stdlib.h>
#include <stdio.h>

int main () {
    int n_prova, q1 = 0, q2 = 0, q3 = 0;
    float N[10][3], menor_nota;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Insira a nota do aluno %d na prova %d:\n", i + 1, j + 1);
            scanf("%f", &N[i][j]);
        }
    }
    for (int i = 0; i < 10; i++) {
        n_prova = 0;
        menor_nota = N[i][0];
        for (int j = 0; j < 3; j++) {
            if (N[i][j] < menor_nota) {
                menor_nota = N[i][j];
                n_prova = j;
                
            }   
        }
        if (n_prova == 0) q1++;
        else if (n_prova == 1) q2++;
        else if (n_prova == 2) q3++;
        printf("\nO aluno de numero %d obeteve %.2f como sua menor nota na prova %d!", i + 1, menor_nota, n_prova + 1);
    }
    printf("\n\nA quantidade de notas menores na prova 1 foi %d!\n", q1);
    printf("A quantidade de notas menores na prova 2 foi %d!\n", q2);
    printf("A quantidade de notas menores na prova 3 foi %d!\n", q3);
}