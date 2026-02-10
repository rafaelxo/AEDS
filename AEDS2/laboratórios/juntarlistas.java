public class juntarlistas {
    static class Celula {
        private int elemento;
        private Celula prox;

        public Celula() {
            this(0);
        }

        public Celula(int elemento) {
            this.elemento = elemento;
            this.prox = null;
        }
    }

    static class Lista {
        private Celula primeiro;
        private Celula ultimo;

        public Lista() {
            this.primeiro = new Celula();
            this.ultimo = this.primeiro;
        }

        public void inserirInicio(int x) {
            Celula tmp = new Celula(x);
            tmp.prox = this.primeiro.prox;
            this.primeiro.prox = tmp;
            if (this.primeiro == this.ultimo)
                this.ultimo = tmp;
            tmp = null;
        }

        public void inserirFim(int x) {
            this.ultimo.prox = new Celula(x);
            this.ultimo = this.ultimo.prox;
        }

        public void inserirPos(int x, int pos) {
            if (pos < 0 || pos > tamanho())
                throw new RuntimeException("Erro!");
            else if (pos == 0)
                inserirInicio(x);
            else if (pos == tamanho())
                inserirFim(x);
            else {
                Celula i = this.primeiro;
                for (int j = 0; j < pos - 1; i = i.prox)
                    j++;
                Celula tmp = new Celula(x);
                tmp.prox = i.prox;
                i.prox = tmp;
                tmp = null;
            }
        }

        public int removerInicio() {
            if (this.primeiro == this.ultimo)
                throw new RuntimeException("Erro!");
            Celula tmp = this.primeiro;
            this.primeiro = this.primeiro.prox;
            int elemento = this.primeiro.elemento;
            tmp.prox = null;
            return elemento;
        }

        public int removerFim() {
            if (this.primeiro == this.ultimo)
                throw new RuntimeException("Erro!");
            Celula i;
            for (i = this.primeiro; i.prox != this.ultimo; i = i.prox)
                ;
            int elemento = this.ultimo.elemento;
            this.ultimo = i;
            i = this.ultimo.prox = null;
            return elemento;
        }

        public int removerPos(int pos) {
            if (this.primeiro == this.ultimo || pos < 0 || pos >= tamanho())
                throw new RuntimeException("Erro!");
            else if (pos == 0)
                return removerInicio();
            else if (pos == tamanho() - 1)
                return removerFim();
            else {
                Celula i = this.primeiro;
                for (int j = 0; j < pos - 1; i = i.prox)
                    j++;
                Celula tmp = i.prox;
                int elemento = tmp.elemento;
                i.prox = tmp.prox;
                tmp.prox = null;
                return elemento;
            }
        }

        int tamanho() {
            int tamanho = 0;
            for (Celula i = this.primeiro; i != null; i = i.prox)
                tamanho++;
            return tamanho;
        }

        public void juntar(Lista l1, Lista l2) {
            Celula i = l1.primeiro.prox;
            Celula j = l2.primeiro.prox;

            while (i != null || j != null) {
                if (i != null && (j == null || i.elemento < j.elemento)) {
                    int pos = 0;
                    for (Celula k = this.primeiro.prox; k != null && k.elemento < i.elemento; k = k.prox) pos++;
                    this.inserirPos(i.elemento, pos + 1);
                    i = i.prox;
                } else if (j != null) j = j.prox;
            }
        }

        public void mostrar() {
            System.out.print("[ ");
            for (Celula i = this.primeiro.prox; i != null; i = i.prox)
                System.out.print(i.elemento + " ");
            System.out.println("]");
        }
    }

    public static void main(String[] args) {
        Lista l1 = new Lista();
        Lista l2 = new Lista();
        l1.inserirFim(1);
        l1.inserirFim(2);
        l1.inserirFim(8);
        l2.inserirFim(5);
        l2.inserirFim(14);
        l1.mostrar();
        l2.mostrar();
        l2.juntar(l1, l2);
        l2.mostrar();
    }
}
