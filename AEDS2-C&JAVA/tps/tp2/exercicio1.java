import java.util.*;

public class exercicio1 {
    public static Scanner sc = new Scanner(System.in);
    static int carac(char c) {
        if (c == '!') return 3;
        if (c == '&') return 2;
        if (c == '|') return 1;
        return 0;
    }

    public static boolean avaliaExpressao(String str, boolean[] valores) {
        char[] ops = new char[512];
        int topOps = -1;
        char[] postfix = new char[2048];
        int p = 0;
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (c == ' ' || c == '\t' || c == '\r' || c == '\n') continue;
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                if (c >= 'a' && c <= 'z') c = (char) (c - ('a' - 'A'));
                postfix[p++] = c;
            } else if (c == '(') {
                ops[++topOps] = c;
            } else if (c == ')') {
                while (topOps >= 0 && ops[topOps] != '(') postfix[p++] = ops[topOps--];
                if (topOps >= 0 && ops[topOps] == '(') topOps--;
            } else if (c == '!' || c == '&' || c == '|') {
                if (c == '!') {
                    while (topOps >= 0 && carac(ops[topOps]) > carac(c)) postfix[p++] = ops[topOps--];
                    ops[++topOps] = c;
                } else {
                    while (topOps >= 0 && carac(ops[topOps]) >= carac(c)) postfix[p++] = ops[topOps--];
                    ops[++topOps] = c;
                }
            } else { }
        }
        while (topOps >= 0) postfix[p++] = ops[topOps--];
        boolean[] st = new boolean[2048];
        int topSt = -1;
        for (int i = 0; i < p; i++) {
            char t = postfix[i];
            if (t >= 'A' && t <= 'Z') {
                int idx = t - 'A';
                boolean val = false;
                if (idx >= 0 && idx < valores.length) val = valores[idx];
                st[++topSt] = val;
            } else if (t == '!') {
                if (topSt >= 0) {
                    boolean a = st[topSt--];
                    st[++topSt] = !a;
                }
            } else if (t == '&') {
                if (topSt >= 1) {
                    boolean b = st[topSt--];
                    boolean a = st[topSt--];
                    st[++topSt] = a & b;
                }
            } else if (t == '|') {
                if (topSt >= 1) {
                    boolean b = st[topSt--];
                    boolean a = st[topSt--];
                    st[++topSt] = a | b;
                }
            }
        }
        return (topSt >= 0) ? st[topSt] : false;
    }

    public static void main(String[] args) {
        int n = sc.nextInt();
        while (n != 0) {
            boolean[] valores = new boolean[26];
            for (int i = 0; i < n; i++) {
                if (sc.hasNextInt()) {
                    int v = sc.nextInt();
                    valores[i] = (v == 1);
                } else { valores[i] = false; }
            }
            String rest = sc.nextLine();
            String expr = rest != null ? rest.trim() : "";
            if (expr.length() == 0) {
                if (sc.hasNextLine()) expr = sc.nextLine().trim();
            }
            boolean result = avaliaExpressao(expr, valores);
            if (result) System.out.println("1");
            else System.out.println("0");
            n = sc.nextInt();
        }
    }
}
