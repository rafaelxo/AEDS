import java.util.*;

public class aplicativo {
    public static Scanner sc = new Scanner(System.in);

    public static class Processo {
        private int tempo, ciclos;
        Processo (int x, int y) {
            this.tempo = x;
            this.ciclos = y;
        }
    }

    public static void main (String[] args) {
        while (sc.hasNextInt()) {
            int N = sc.nextInt();
            Processo[] proc = new Processo[N];
            for (int i = 0; i < N; i++) {
                int t = sc.nextInt(), c = sc.nextInt();
                proc[i] = new Processo(t, c);
            }
            int result = 0;
            for (int i = 1; i < N; i++) {
                if (i == 1) result += proc[i].tempo;
                result += proc[i].ciclos;
            }
            System.out.println(result);
        }
    }
}
