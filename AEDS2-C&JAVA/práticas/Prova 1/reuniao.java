import java.util.*;

public class reuniao {
    public static Scanner sc = new Scanner (System.in);
    
    public static void main (String[] args) {
        int N = sc.nextInt(); int K = sc.nextInt();
        int T = (K - (N - 1)) / N;
        if (T < 1) T = 1;
        System.out.println(T);
    }
}
