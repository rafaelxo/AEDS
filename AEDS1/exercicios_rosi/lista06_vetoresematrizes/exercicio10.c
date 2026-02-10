#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main () {
    char *texto = (char*)malloc(100*sizeof(char));
    scanf(" %[^\n]", texto);
    int tam = strlen(texto);
    char letra;
    int vogais = 0, consoantes = 0;
    for (int i = 0; i < tam; i++) {
        letra = *(texto + i);
        letra = tolower(letra);
        if (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u') vogais++;
        else if (letra >= 'a' && letra <= 'z') consoantes++;
    }
    printf("Vogais: %d\nConsoantes: %d\n", vogais, consoantes);
    free(texto);
}