#include <stdio.h>

int length (char str[]) {
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

void combinacao (char str1[], char str2[]) {
    int len1 = length(str1), len2 = length(str2);
    int maior = len1 > len2 ? len1 : len2;
    int i = 0;
    while (i < maior) {
        if (i < len1) printf("%c", str1[i]);
        if (i < len2) printf("%c", str2[i]);
        i++;
    }
}

int main () {
    char str1[100], str2[100];
    while (scanf("%s %s", str1, str2) != EOF) {
        combinacao(str1, str2);
        printf("\n");
    }
    return 0;
}
