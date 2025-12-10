import java.util.Scanner;

public class sorvete {
    public static Scanner sc = new Scanner (System.in);

    public static void ordenar (int[][] intervalos, int n) {
        for (int i = 1; i < n; i++) {
            int[] aux = intervalos[i];
            int j = i - 1;
            while (j >= 0 && intervalos[j][0] > aux[0]) {
                intervalos[j + 1] = intervalos[j];
                j--;
            }
            intervalos[j + 1] = aux;
        }
    }

    public static void main (String[] args) {
        int p = sc.nextInt(), s = sc.nextInt();
        int teste = 1;

        while (p != 0 && s != 0) {
            int[][] intervalos = new int[s][2];
            for (int i = 0; i < s; i++) {
                intervalos[i][0] = sc.nextInt();
                intervalos[i][1] = sc.nextInt();
            }
            ordenar(intervalos, s);
            int qtdMesclados = 1;
            int[][] mesclados = new int[s][2];
            mesclados[0][0] = intervalos[0][0];
            mesclados[0][1] = intervalos[0][1];
            for (int i = 1; i < s; i++) {
                int ultimoFim = mesclados[qtdMesclados - 1][1];
                int atuaIni = intervalos[i][0];
                int atualFim = intervalos[i][1];
                if (atuaIni <= ultimoFim) {
                    if (atualFim > ultimoFim) mesclados[qtdMesclados - 1][1] = atualFim;
                } else {
                    mesclados[qtdMesclados][0] = atuaIni;
                    mesclados[qtdMesclados][1] = atualFim;
                    qtdMesclados++;
                }
            }
            System.out.println("Teste " + teste);
            for (int i = 0; i < qtdMesclados; i++) System.out.println(mesclados[i][0] + " " + mesclados[i][1]);
            teste++;
            p = sc.nextInt(); s = sc.nextInt();
        }
    }
}
