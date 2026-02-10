import java.util.*;

public class grid {
    public static Scanner sc = new Scanner (System.in);
    
    public static int insercao (int[] vet, int n) {
        int mov = 0;
        for (int i = 1; i < n; i++) {
            int aux = vet[i];
            int j = i - 1;
            while (j >= 0 && vet[j] > aux) {
                vet[j + 1] = vet[j];
                j--;
                mov++;
            }
            vet[j + 1] = aux;
        }
        return mov;
    }

    public static int ultrapassagens (int[] largada, int[] chegada, int n) {
        int larg = insercao(largada, n);
        int cheg = insercao(chegada, n);
        if (larg > cheg) return larg - cheg;
        else return cheg - larg;
    }

    public static void main (String[] args) {
        while (sc.hasNext()) {
            int n = sc.nextInt();
            int[] largada = new int[n]; for (int i = 0; i < n; i++) largada[i] = sc.nextInt();
            int[] chegada = new int[n]; for (int i = 0; i < n; i++) chegada[i] = sc.nextInt();
            System.out.println((ultrapassagens(largada, chegada, n)));
        }
    }
}
