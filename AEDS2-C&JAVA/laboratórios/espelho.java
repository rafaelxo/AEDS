import java.util.*;

public class espelho {
    public static Scanner sc = new Scanner (System.in);
    public static void imprimeInvertido (int n) {
        if (n < 10) System.out.print(n);
        else {
            System.out.print(n%10);
            imprimeInvertido(n/10);
        }
    }
    public static void espelhar (int n1, int n2) {
        for (int i = n1; i <= n2; i++) System.out.print(i);
        for (int i = n2; i >= n1; i--) imprimeInvertido(i);
    }
    public static void main (String[] args) {
        while (sc.hasNext()) {
            int n1 = sc.nextInt(); int n2 = sc.nextInt();
            espelhar(n1, n2); System.out.println();
        }
    }
}
