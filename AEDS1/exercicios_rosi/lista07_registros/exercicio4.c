#include <stdlib.h>
#include <stdio.h>

typedef struct livro {
    int codigo;
    char doacao;
    char *nome;
    char *autor;
    char *editora;
    char area;
} Lv;

int main () {
    Lv *exatas = (Lv*)malloc(500*sizeof(Lv));
    Lv *humanas = (Lv*)malloc(500*sizeof(Lv));
    Lv *biologicas = (Lv*)malloc(500*sizeof(Lv));
    for (int i = 0; i < 500; i++) {
        scanf("%d", (exatas + i)->codigo);
        scanf(" %c", (exatas + i)->doacao);
        (exatas + i)->nome = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (exatas + i)->nome);
        (exatas + i)->autor = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (exatas + i)->autor);
        (exatas + i)->editora = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (exatas + i)->editora);
        scanf(" %c", &(exatas + i)->area);
    }
    for (int i = 0; i < 500; i++) {
        scanf("%d", (humanas + i)->codigo);
        scanf(" %c", (humanas + i)->doacao);
        (humanas + i)->nome = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (humanas + i)->nome);
        (humanas + i)->autor = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (humanas + i)->autor);
        (humanas + i)->editora = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (humanas + i)->editora);
        scanf(" %c", &(humanas + i)->area);
    }
    for (int i = 0; i < 500; i++) {
        scanf("%d", (biologicas + i)->codigo);
        scanf(" %c", (biologicas + i)->doacao);
        (biologicas + i)->nome = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (biologicas + i)->nome);
        (biologicas + i)->autor = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (biologicas + i)->autor);
        (biologicas + i)->editora = (char*)malloc(100*sizeof(char));
        scanf(" %[^\n]", (biologicas + i)->editora);
        scanf(" %c", &(biologicas + i)->area);
    }
    int codigo;
    char area;
    scanf("%d %c", &codigo, &area);
    while (codigo != -1) {
        int achou = 0;
        for (int i = 0; i < 500 && !achou; i++) {
            if (codigo == exatas[i].codigo && area == exatas[i].area) {
                printf("Código: %d\n", exatas[i].codigo);
                printf("Doação: %c\n", exatas[i].doacao);
                printf("Nome: %s\n", exatas[i].nome);
                printf("Autor: %s\n", exatas[i].autor);
                printf("Editora: %s\n", exatas[i].editora);
                printf("Área: Exatas\n");
                achou = 1;
            }
        }
        for (int i = 0; i < 500 && !achou; i++) {
            if (codigo == humanas[i].codigo && area == humanas[i].area) {
                printf("Código: %d\n", humanas[i].codigo);
                printf("Doação: %c\n", humanas[i].doacao);
                printf("Nome: %s\n", humanas[i].nome);
                printf("Autor: %s\n", humanas[i].autor);
                printf("Editora: %s\n", humanas[i].editora);
                printf("Área: Humanas\n");
                achou = 1;
            }
        }
        for (int i = 0; i < 500 && !achou; i++) {
            if (codigo == biologicas[i].codigo && area == biologicas[i].area) {
                printf("Código: %d\n", biologicas[i].codigo);
                printf("Doação: %c\n", biologicas[i].doacao);
                printf("Nome: %s\n", biologicas[i].nome);
                printf("Autor: %s\n", biologicas[i].autor);
                printf("Editora: %s\n", biologicas[i].editora);
                printf("Área: Biológicas\n");
                achou = 1;
            }
        }
        if (achou == 0) printf("Livro nao encontrado.\n");
        scanf("%d %s", &codigo, area);
    }
    for (int i = 0; i < 500; i++) {
        free(exatas[i].nome);
        free(exatas[i].autor);
        free(exatas[i].editora);
        free(humanas[i].nome);
        free(humanas[i].autor);
        free(humanas[i].editora);
        free(biologicas[i].nome);
        free(biologicas[i].autor);
        free(biologicas[i].editora);
    }
    free(exatas);
    free(humanas);
    free(biologicas);
}