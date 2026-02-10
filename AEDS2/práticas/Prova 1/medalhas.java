import java.util.*;

public class medalhas {
    public static Scanner sc = new Scanner(System.in);
    
    public static class Pais {
        private String nome;
        private int ouro, prata, bronze;
        Pais () {
            this.nome = "nenhum";
            this.ouro = 0;
            this.prata = 0;
            this.bronze = 0;
        }
        Pais (String str, int o, int p, int b) {
            this.nome = str;
            this.ouro = o;
            this.prata = p;
            this.bronze = b;
        }
        public String getNome() { return nome; }
        public int getOuro() { return ouro; }
        public int getPrata() { return prata; }
        public int getBronze() { return bronze; }
    }

    public static int comparaNomes(String a, String b) {
        int tam = (a.length() < b.length()) ? a.length() : b.length();
        for (int i = 0; i < tam; i++) {
            if (a.charAt(i) < b.charAt(i)) return 1;
            if (a.charAt(i) > b.charAt(i)) return 0;
        }
        if (a.length() < b.length()) return 1;
        if (a.length() > b.length()) return 0;
        return 0;
    }

    public static void swap (Pais[] ps, int i, int j) {
        Pais aux = ps[i];
        ps[i] = ps[j];
        ps[j] = aux;
    }

    public static void selecao (Pais[] ps, int n) {
        for (int i = 0; i < n - 1; i++) {
            int melhor = i;
            for (int j = i + 1; j < n; j++) {
                if (ps[j].getOuro() > ps[melhor].getOuro()) melhor = j;
                else if (ps[j].getOuro() == ps[melhor].getOuro()) {
                    if (ps[j].getPrata() > ps[melhor].getPrata()) melhor = j;
                    else if (ps[j].getPrata() == ps[melhor].getPrata()) {
                        if (ps[j].getBronze() > ps[melhor].getBronze()) melhor = j;
                        else if (ps[j].getBronze() == ps[melhor].getBronze()) {
                            if (comparaNomes(ps[j].getNome(), ps[melhor].getNome()) == 1) melhor = j;
                        }
                    }
                }
            }
            swap(ps, i, melhor);
        }
    }

    public static void main (String[] args) {
        int n = sc.nextInt();
        Pais[] paises = new Pais[n];
        for (int i = 0; i < n; i++) {
            String nome = sc.next();
            int ouro = sc.nextInt();
            int prata = sc.nextInt();
            int bronze = sc.nextInt();
            paises[i] = new Pais(nome, ouro, prata, bronze);
        }
        selecao(paises, n);
        for (int i = 0; i < n; i++) System.out.println(paises[i].getNome() + " " + paises[i].getOuro() + " " + paises[i].getPrata() + " " + paises[i].getBronze());
    }
}
