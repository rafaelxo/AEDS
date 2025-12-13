import java.util.*;

public class inposfixa {
    public static Scanner sc = new Scanner(System.in);

    static class Celula {
        char elemento;
        Celula prox;
        Celula (char x) {
            this.elemento = x;
            this.prox = null;
        }
    }

    static class Pilha {
        Celula topo;
        Pilha () { this.topo = null; }
        public void inserir (char x) {
            Celula tmp = new Celula(x);
            tmp.prox = topo;
            topo = tmp;
            tmp = null;
        }
        char remover () {
            if (topo == null) return '\0';
            char resp = topo.elemento;
            Celula tmp = topo;
            topo = topo.prox;
            tmp.prox = null;
            tmp = null;
            return resp;
        }
        char isTopo () {
            if (topo == null) return '\0';
            return topo.elemento;
        }
        boolean vazia () { return topo == null; }
    }

    public static int prioridade (char x) {
        if (x == '^') return 3;
        if (x == '*' || x == '/') return 2;
        if (x == '+' || x == '-') return 1;
        return 0;
    }

    public static String transformar (String str) {
        String nova = "";
        Pilha pilha = new Pilha();
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (Character.isLetterOrDigit(c)) nova += c;
            else if (c == '(') pilha.inserir(c);
            else if (c == ')') {
                while (!pilha.vazia() && pilha.isTopo() != '(') nova += pilha.remover();
                pilha.remover();
            } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                while (!pilha.vazia() && prioridade(pilha.isTopo()) >= prioridade(c)) nova += pilha.remover();
                pilha.inserir(c);
            }
        }
        while (!pilha.vazia()) nova += pilha.remover();
        return nova;
    }

    public static void main(String[] args) {
        int n = sc.nextInt();
        sc.nextLine();
        for (int i = 0; i < n; i++) {
            String str = sc.nextLine();
            str = transformar(str);
            System.out.println(str);
        }
    }
}
