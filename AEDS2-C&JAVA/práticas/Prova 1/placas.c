#include <stdio.h>

int length (char str[]) {
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

int validacao (char str[]) {
    if (length(str) == 7) {
        if ((str[0] >= 'A' && str[0] <= 'Z') && (str[1] >= 'A' && str[1] <= 'Z') && (str[2] >= 'A' && str[2] <= 'Z') && (str[3] >= '0' && str[3] <= '9') && (str[4] >= 'A' && str[4] <= 'Z') && (str[5] >= '0' && str[5] <= '9') && (str[6] >= '0' && str[6] <= '9')) return 2;
    } else if (length(str) == 8) {
        if ((str[0] >= 'A' && str[0] <= 'Z') && (str[1] >= 'A' && str[1] <= 'Z') && (str[2] >= 'A' && str[2] <= 'Z') && (str[3] == '-') && (str[4] >= '0' && str[4] <= '9') && (str[5] >= '0' && str[5] <= '9') && (str[6] >= '0' && str[6] <= '9') && (str[7] >= '0' && str[7] <= '9')) return 1;
    } else return 0;
}

int main () {
    char placa[8];
    while (scanf("%s", placa) != EOF) printf("%d\n", validacao(placa));
    return 0;
}
