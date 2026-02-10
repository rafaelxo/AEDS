#include <stdio.h>
#include <stdlib.h>

int main() {
    int idade, homens = 0, mulheres = 0, q_mulheres21exp = 0, q_homensexp = 0, menoridadeexp;
    float m_i_homensexp = 0, perc_homens45 = 0;
    char sexo, experiencia;
    printf("Insira a idade do candidato:\n");
    scanf("%d", &idade);
    while (idade != 0) {
        printf("\nAgora, insira seu sexo (M ou F) e se possui experiencia (S ou N):\n");
        scanf(" %c %c", &sexo, &experiencia);
        if (sexo == 'F') {
            mulheres++;
            if (experiencia == 'S' && idade < 21) {
                q_mulheres21exp++;
            }
            if (experiencia == 'S' && idade < menoridadeexp) {
                menoridadeexp = idade;
            }
        } else if (sexo == 'M') {
            homens++;
            if (experiencia =='S') {
                m_i_homensexp += idade;
                q_homensexp++;
            }
            if (idade > 45) {
                perc_homens45++;
            }
        } else {
            printf("\nSexo invalido! Insira M ou F.\n");
        }
        printf("\nInsira a idade do candidato (ou 0 para encerrar):\n");
        scanf("%d", &idade);
    }
    printf("\nO numero de candidatas e candidatos equivalem, respectivamente, a: %d e %d!\n", mulheres, homens);
    m_i_homensexp /= q_homensexp;
    printf("\nA idade media dos homens que ja tem experiencia e de %.2f anos!\n", m_i_homensexp);
    perc_homens45 = perc_homens45*100.0/homens;
    printf("\nA porcentagem de homens com mais de 45 anos entre o total de homens e de %.2f!\n", perc_homens45);
    printf("\nO numero de mulheres com idade inferior a 21 anos, e a menor idade entre elas, com experiencia no servico equivale, respecitvamente, a:\n%d e %d\n", q_mulheres21exp, menoridadeexp);
}