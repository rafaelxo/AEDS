#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool vogais (char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        char c = str[i];
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) return false;
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') return false;
        i++;
    }
    return true;
}

bool consoantes (char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        char c = str[i];
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) return false;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return false;
            i++;
        }
    return true;
}

bool inteiros (char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') return false;
        i++;
    }
    return true;
}

bool reais (char str[]) {
    int i = 0, virgula = 0;
    while (str[i] != '\0') {
        if (str[i] == '.') {
            virgula++;
            if (virgula > 1) return false;
        }
        else if ((str[i] < '0' && str[i] > '9') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) return false;
        i++;
    }
    if (virgula == 1) return true;
}

int main () {
    char str[500];
    scanf(" %[^\n]", str);
    while (!(str[0] == 'F' && str[1] == 'I' && str[2] == 'M' && str[3] == '\0')) {
        bool x1 = vogais(str);
        bool x2 = consoantes(str);
        bool x3 = inteiros(str);
        bool x4 = reais(str);
        printf("%s %s %s %s\n", x1 ? "SIM" : "NAO", x2 ? "SIM" : "NAO", x3 ? "SIM" : "NAO", x4 ? "SIM" : "NAO");
        scanf(" %[^\n]", str);
    }
    return 0;
}
