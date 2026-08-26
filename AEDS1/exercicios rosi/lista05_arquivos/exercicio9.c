#include <stdio.h>
#include <stdlib.h>

int main () {
    int opcao, matricula, telefone;
    scanf("%d", &opcao);
    FILE *arquivo = fopen("saida9.txt", "w");
    FILE *arquivo2;
    switch (opcao) {
        case 1:
            arquivo2 = fopen("entrada9.txt", "w");
            scanf("%d%d", &matricula, &telefone);
            while (matricula != -1) {
                fprintf(arquivo, "%d %d\n", matricula, telefone);
                fprintf(arquivo2, "%d %d\n", matricula, telefone);
                scanf("%d%d", &matricula, &telefone);
            }
            fclose(arquivo2);
            break;
        case 2: {
            arquivo2 = fopen("entrada9.txt", "r");
            while (fscanf(arquivo2, "%d%d", &matricula, &telefone) != EOF) fprintf(arquivo, "%d %d\n", matricula, telefone);
            fclose(arquivo2);
            break;
        }
    }
    fclose(arquivo);
}