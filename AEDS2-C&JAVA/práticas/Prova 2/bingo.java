import java.util.*;

public class bingo {
    public static Scanner sc = new Scanner(System.in);

    public static void main (String[] args) {
        int N = sc.nextInt(); int B = sc.nextInt();
        while (N != 0 && B != 0) {
            int[] bolas = new int[B];
            for (int i = 0; i < B; i++) bolas[i] = sc.nextInt();
            boolean[] possiveis = new boolean[N + 1];
            for (int i = 0; i < B; i++) {
                for (int j = i; j < B; j++) {
                    int diff = Math.abs(bolas[i] - bolas[j]);
                    if (diff <= N) possiveis[diff] = true;
                }
            }
            boolean bingo = true;
            for (int i = 0; i <= N; i++) {
                if (!possiveis[i]) {
                    bingo = false;
                    i = N + 1;
                }
            }
            if (bingo) System.out.println("Y");
            else System.out.println("N");
            N = sc.nextInt(); B = sc.nextInt();
        }
    }
}
