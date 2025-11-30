import java.util.*;

public class contMaiusc {
    public static Scanner sc = new Scanner (System.in);
    public static boolean isFim(String str) {
        return (str.length() == 3 && str.charAt(0) == 'F' && str.charAt(1) == 'I' && str.charAt(2) == 'M');
    }
    public static int contarMaiusculas (String str) {
        int quant = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) >= 'A' && str.charAt(i) <= 'Z') quant++;
        }
        return quant;
    }
    public static void main (String[] args) {
        String str = sc.nextLine();
        while (!isFim(str)) {
            System.out.println(contarMaiusculas(str));
            str = sc.nextLine();
        }
        sc.close();
    }
}
