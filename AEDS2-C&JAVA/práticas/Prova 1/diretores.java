import java.util.*;

public class diretores {
    public static Scanner sc = new Scanner (System.in);

    public static void main (String[] args) {
        while (sc.hasNextInt()) {
            int n = sc.nextInt(); int k = sc.nextInt();
            int t = (k - (n - 1)) / n;
            if (t < 1) t = 1;
            System.out.println(t);
        }
    }
}
