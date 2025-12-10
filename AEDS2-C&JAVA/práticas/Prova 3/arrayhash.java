import java.util.*;

public class arrayhash {
    public static Scanner sc = new Scanner (System.in);

    public static void main (String[] args) {
        int n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            int l = sc.nextInt();
            String[] str = new String[l];
            for (int j = 0; j < l; j++) str[j] = sc.next();
            int total = 0;
            for (int j = 0; j < l; j++) {
                for (int k = 0; k < str[j].length(); k++) total += j + k + (int)(str[j].charAt(k) - 'A');
            }
            System.out.println(total);
        }
    }
}
