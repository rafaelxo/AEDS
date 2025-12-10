import java.util.Scanner;

public class pilha {
    public static Scanner sc = new Scanner (System.in);

    static class Celula {
        public int elemento;
        public Celula prox;
        public Celula (int x) {
            elemento = x;
            prox = null;
        }
    }
    static class Pilha {
        private Celula topo;
        public Pilha () { topo = null; }
        public void push (int x) {
            Celula tmp = new Celula (x);
            tmp.prox = topo;
            topo = tmp;
            tmp = null;
        }
        public int pop () {
            if (topo == null) throw new RuntimeException ("Erro!");
            int resp = topo.elemento;
            Celula tmp = topo;
            topo = topo.prox;
            tmp.prox = null;
            tmp = null;
            return resp;
        }
    }

    private static boolean jogar (Pilha p1, Pilha p2, Pilha p3, int soma) {
        if (soma > 0 && soma % 3 == 0) return true;
        if (p1.topo != null) {
            int valor = p1.pop();
            if (jogar(p1, p2, p3, soma + valor)) {
                p1.push(valor);
                return true;
            }
            p1.push(valor);
        }
        if (p2.topo != null) {
            int valor = p2.pop();
            if (jogar(p1, p2, p3, soma + valor)) {
                p2.push(valor);
                return true;
            }
            p2.push(valor);
        }
        if (p3.topo != null) {
            int valor = p3.pop();
            if (jogar(p1, p2, p3, soma + valor)) {
                p3.push(valor);
                return true;
            }
            p3.push(valor);
        }
        return false;
    }

    public static void main (String[] args) {
        int n = sc.nextInt();
        while (n != 0) {
            Pilha p1 = new Pilha (), p2 = new Pilha (), p3 = new Pilha ();
            for (int i = 0; i < n; i++) {
                int valor = sc.nextInt(); p1.push (valor);
                valor = sc.nextInt(); p2.push (valor);
                valor = sc.nextInt(); p3.push (valor);
            }
            System.out.println(jogar(p1, p2, p3, 0) ? "1" : "0");
            n = sc.nextInt();
        }
    }
}
