#include <stdio.h>
#include <stdlib.h>

int main() {
    int cont1 = 1, cont2, N, idade, m_18 = 0, M_80 = 0, s_idades = 0;
    float altura, peso, m_idades = 0, m_alturas = 0, porcentagem = 0, s_alturas = 0;
    printf("Insira quantos times estao inscritos no campeonato:\n");
    scanf("%d", &N);
    for (cont1 = 1; cont1 <= N; cont1++) {
        for (cont2 = 1; cont2 <= 11; cont2++) {
            printf("\nInsira a idade, o peso e a altura do jogador:\n");
            scanf("%d%f%f", &idade, &peso, &altura);
            s_idades += idade;
            s_alturas += altura;
            if (idade < 18) {
                m_18 += 1;
            }
            if (peso > 80) {
                M_80 += 1;
            }
        }
        m_idades = s_idades*1.0/11;
        printf("\nA media das idades dos jogadores desse time e de:\n%.2f\n", m_idades);
    }
    m_alturas = s_alturas/(11.0*N);
    porcentagem = M_80*(100.0/(11*N));
    printf("\nA quantidade de jogadores menores de 18 anos, a media das alturas e a porcentagem de jogadores com mais de 80kg de todo o campeonato equivalem, respectivamente, a:\n%d\n%.2f\n%.2f\n", m_18, m_alturas, porcentagem);
}
