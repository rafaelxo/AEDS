#include <stdio.h>
#include <stdbool.h>

bool isFim (char str[]) {
    return (str[0] == 'F' && str[1] == 'I' && str[2] == 'M' && str[3] == '\0');
}

int contMaiusc(char str[]) {
    int quant = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') quant++;
    }
    return quant;
}

int main() {
    char str[100]; scanf(" %[^\n]", str);
    while (!isFim(str)) {
        printf("%d\n", contMaiusc(str));
        scanf(" %[^\n]", str);
    }
    return 0;
}
