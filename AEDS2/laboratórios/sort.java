import java.util.*;

public class sort {
    public static Scanner sc = new Scanner (System.in);

    public static void insercao (int[] vet, int n) {
        for (int i = 1; i < n; i++) {
            int aux = vet[i];
            int j = i - 1;
            while (j >= 0 && vet[j] > aux) {
                vet[j + 1] = vet[j];
                j--;
            }
            vet[j + 1] = aux;
        }
    }

    public static void esquematizacao (int[] vet, int n, int m) {
        insercao(vet, n);
        for (int mod = -(m - 1); mod < m; mod++) {
            for (int i = n - 1; i >= 0; i--) {
                if (vet[i] % m == mod && vet[i] % 2 != 0) System.out.println(vet[i]);
            }
            for (int i = 0; i < n; i++) {
                if (vet[i] % m == mod && vet[i] % 2 == 0) System.out.println(vet[i]);
            }
        }
    }
    
    public static void main (String[] args) {
        int n = sc.nextInt(); int m = sc.nextInt();
        while (n != 0 && m != 0) {
            System.out.println(n + " " + m);
            int[] nums = new int[n];
            for (int i = 0; i < n; i++) nums[i] = sc.nextInt();
            esquematizacao(nums, n, m);
            n = sc.nextInt(); m = sc.nextInt();
        }
        System.out.println(n + " " + m);
    }
}
