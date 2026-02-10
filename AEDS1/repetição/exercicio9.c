#include <stdio.h>
#include <stdlib.h>

int main() {
    int cont1, N, n1, n2, t_aprovados = 0, t_exames = 0, t_reprovados = 0;
    float m_aluno, m_classe, t_classe = 0;
    printf("Insira quantos alunos deseja calcular a media:\n");
    scanf("%d", &N);
    for (cont1 = 1; cont1 <= N; cont1++) {
        printf("\nInsira as duas notas do aluno:\n");
        scanf("%d%d", &n1, &n2);
        m_aluno = (n1 + n2)/2.0;
        if (m_aluno <= 3) {
            t_reprovados += 1;
            printf("\nAluno reprovado!\n");
        } else if (m_aluno < 7) {
            t_exames += 1;
            printf("\nAluno em exame!\n");
        } else {
            t_aprovados += 1;
            printf("\nAluno aprovado!\n");
        }
        t_classe += m_aluno;
    }
    printf("\nAlunos reprovados:\n%d\n", t_reprovados);
    printf("\nAlunos em exame:\n%d\n", t_exames);
    printf("\nAlunos aprovados:\n%d\n", t_aprovados);
    m_classe = t_classe * 1.0/N;
    printf("\nA media da classe e de:\n%.2f\n", m_classe);
}
