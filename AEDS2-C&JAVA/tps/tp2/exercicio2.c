#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool Vogais (char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        char c = str[i];
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) return false;
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') return false;
        i++;
    }
    return true;
}

int main () {

    return 0;
}
