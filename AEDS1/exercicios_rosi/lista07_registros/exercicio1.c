#include <stdlib.h>
#include <stdio.h>

typedef struct pessoa {
    char *nome;
    int dia_a;
    int mes_a;
} pss;

int main () {
    pss p[40];
    for (int i = 0; i < 40; i++) {
        (p + i)->nome = (char *)malloc(100*sizeof(char));
        scanf(" %s", p[i].nome);
        scanf("%d", &p[i].dia_a);
        scanf("%d", &p[i].mes_a);
    }
    for (int i = 1; i <= 12; i++) {
        printf("Aniversariantes do mes %d:\n", i);
        for (int j = 0; j < 40; j++) {
            if(p[j].mes_a == i) printf("Nome: %s, Dia: %d\n", p[j].nome, p[j].dia_a);
        }
        printf("\n");
    }
    for (int i = 0; i < 40; i++) free(p[i].nome);
}