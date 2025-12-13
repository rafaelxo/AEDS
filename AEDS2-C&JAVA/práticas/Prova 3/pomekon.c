#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash (char *str) {
    int tot = 0;
    for (int i = 0; str[i] != '\0'; i++) tot += (int)str[i];
    return tot % 151;
}

int main () {
    int n;
    scanf ("%d", &n);
    char vet[151][100];
    for (int i = 0; i < 151; i++) vet[i][0] = '\0';
    for (int i = 0; i < n; i++) {
        char nome[100];
        scanf ("%s", nome);
        int pos = hash(nome);
        if (vet[pos][0] == '\0') strcpy(vet[pos], nome);
    }
    int capt = 0;
    for (int i = 0; i < 151; i++) if (vet[i][0] != '\0') capt++;
    printf ("Falta(m) %d pomekon(s).\n", 151 - capt);
    return 0;
}
