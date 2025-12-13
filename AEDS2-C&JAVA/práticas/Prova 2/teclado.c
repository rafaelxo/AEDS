#include <stdio.h>
#include <string.h>

int main() {
    char str[1000];

    while (scanf("%s", str) != EOF) {
        int abriu = 0;
        char dentro[1000] = "";
        char normal[1000] = "";
        int iDentro = 0;
        int iNormal = 0;

        str[strcspn(str, "\n")] = 0;

        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == '[') abriu++;
            if (str[i] == ']') abriu--;
            if (abriu > 0 && str[i] != '[') dentro[iDentro++] = str[i];
            if (abriu == 0 && (str[i] != '[' && str[i] != ']')) normal[iNormal++] = str[i];
        }
        dentro[iDentro] = '\0';
        normal[iNormal] = '\0';

        if (strlen(dentro) > 1) printf("%s%s\n", dentro, normal);
        else printf("%s\n", normal);
    }

    return 0;
}
