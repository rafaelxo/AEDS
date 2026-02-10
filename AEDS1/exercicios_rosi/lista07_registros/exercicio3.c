#include <stdlib.h>
#include <stdio.h>

typedef struct cliente {
    int codigo;
    char *email;
    int horas;
    char pagina;
} Cl;

int main () {
    int N; scanf ("%d", &N);
    Cl clientes[N];
    float final;
    for (int i = 0; i < N; i++) {
        scanf("%d", &clientes[i].codigo);
        clientes[i].email = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", clientes[i].email);
        scanf("%d", &clientes[i].horas);
        scanf(" %c", &clientes[i].pagina);
    }
    for (int i = 0; i < N; i++) {
        final = 0;
        if (clientes[i].horas <= 20) final = 35;
        else final = 35 + (clientes[i].horas - 20) * 2.5;
        if (clientes[i].pagina == 'S') final += 40;
        else final = final;
        printf("Cliente %d:\nCodigo: %d\nE-mail: %s\nHoras de Acesso: %d\nPossui Pagina: %c\nValor a Pagar: %.2f Quanzas\n", i + 1, clientes[i].codigo, clientes[i].email, clientes[i].horas, clientes[i].pagina, final);
        printf("\n");
    }
    for (int i = 0; i < N; i++) free(clientes[i].email);
}