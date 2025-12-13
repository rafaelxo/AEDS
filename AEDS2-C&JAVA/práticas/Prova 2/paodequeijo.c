#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    char str[100];
    scanf(" %[^\n]", str);
    while (strcmp(str, "FIM") != 0) {
        int n = 0, m = 0, i = 0;
        while (str[i] != ' ') n = n * 10 + (str[i++] - '0');
        i++;
        while (str[i] != '\0') m = m * 10 + (str[i++] - '0');
        int mat[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) scanf("%d", &mat[i][j]);
        }
        int result[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 0) {
                    int soma = 0;
                    if (i - 1 >= 0 && mat[i - 1][j] == 1) soma++;
                    if (i + 1 < n && mat[i + 1][j] == 1) soma++;
                    if (j - 1 >= 0 && mat[i][j - 1] == 1) soma++;
                    if (j + 1 < m && mat[i][j + 1] == 1) soma++;
                    result[i][j] = soma;
                } else if (mat[i][j] == 1) result[i][j] = 9;
                else result[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) printf("%d", result[i][j]);
            printf("\n");
        }
        scanf(" %[^\n]", str);
    }
    return 0;
}
