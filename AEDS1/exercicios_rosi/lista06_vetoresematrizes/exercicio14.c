#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main () {
    int N;
    scanf("%d", &N);
    char *texto = (char*)malloc(N*sizeof(char));
    scanf(" %[^\n]", texto);
    char *inverso = (char*)malloc(N*sizeof(char));
    int i = 0;
    while (*(texto + i) != '\0') {
        *(inverso + i) = *(texto + N - 1 - i);
        i++;
    }
    *(inverso + i) = '\0';
    printf("%s", inverso);
    free(texto); free(inverso);
}