public class matrizF {
    static class Celula {
        int elemento;
        Celula esq, dir, sup, inf;
        public Celula (int x) {
            this.elemento = x;
            this.esq = this.dir = this.sup = this.inf = null;
        }
    }
    static class Matriz {
        Celula inicio;
        int linhas, colunas;
        public Matriz construir (int l, int c) {
            if (l <= 0 || c <= 0) throw new IllegalArgumentException("Erro!");
            Matriz m = new Matriz();
            m.linhas = l;
            m.colunas = c;
            m.inicio = new Celula(0);
            Celula lin = m.inicio, col = m.inicio;
            for (int j = 1; j < c; j++) {
                col.dir = new Celula(0);
                col.dir.esq = col;
                col = col.dir;
            }
            for (int i = 1; i < l; i++) {
                lin.inf = new Celula(0);
                lin.inf.sup = lin;
                lin = lin.inf;
                col = lin;
                for (int j = 1; j < c; j++) {
                    col.dir = new Celula(0);
                    col.dir.esq = col;
                    col = col.dir;
                    col.sup = col.esq.sup.dir;
                    col.sup.inf = col;
                }
            }
            return m;
        }

        public int somaDiagPrinc () {
            if (this.linhas != this.colunas || this.inicio == null) throw new IllegalArgumentException("Erro!");
            Celula i = this.inicio;
            int soma =  i.elemento;
            while (i.dir != null && i.inf != null) {
                i = i.dir.inf;
                soma += i.elemento;
            }
            i = null;
            return soma;
        }

        public void circular () {
            Celula ini = this.inicio;
            Celula fim;
            for (fim = ini; fim.inf != null; fim = fim.inf);
            while (ini.dir != null) {
                fim.inf = ini;
                ini.sup = fim;
                ini = ini.dir;
                fim = fim.dir;
            }
            ini = this.inicio;
            for (fim = ini; fim.dir != null; fim = fim.dir);
            while (ini.inf != null) {
                fim.dir = ini;
                ini.esq = fim;
                ini = ini.inf;
                fim = fim.inf;
            }
        }

        public void mostrar () {
            Celula tmp = this.inicio;
            for (int i = 0; i < this.linhas; i++) {
                System.out.print("[ ");
                Celula atual = tmp;
                for (int j = 0; j < this.colunas && atual != null; j++) {
                    System.out.print(atual.elemento + " ");
                    atual = atual.dir;
                }
                System.out.println("]");
                tmp = tmp.inf;
            }
        }
    }
}
