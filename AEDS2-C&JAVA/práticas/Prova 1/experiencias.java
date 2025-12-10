import java.util.*;

public class experiencias {
    public static Scanner sc = new Scanner (System.in);
    public static void main (String[] args) {
        int n = sc.nextInt();
        int coelhos = 0, ratos = 0, sapos = 0, total = 0;
        for (int i = 0; i < n; i++) {
            int num = sc.nextInt();
            char c = sc.next().charAt(0);
            if (c == 'C') coelhos += num;
            else if (c == 'R') ratos += num;
            else if (c == 'S') sapos += num;
            total += num;
        }
        System.out.println("Total de cobaias: " + total);
        System.out.println("Total de coelhos: " + coelhos);
        System.out.println("Total de ratos: " + ratos);
        System.out.println("Total de sapos: " + sapos);
        System.out.printf(Locale.US, "Percentual de coelhos: %.2f %%\n", (coelhos * 100.0 / total));
        System.out.printf(Locale.US, "Percentual de ratos: %.2f %%\n", (ratos * 100.0 / total));
        System.out.printf(Locale.US, "Percentual de sapos: %.2f %%\n", (sapos * 100.0 / total));
    }
}
