public class listaF {
    static class Celula {
        private int elemento;
        private Celula prox;
        public Celula (int x) {
            this.elemento = x;
            this.prox = null;
        }
    }

    static class Lista {
        private Celula primeiro, ultimo;
        public Lista () {
            primeiro = new Celula(0);
            ultimo = primeiro;
        }

        public void inserirIni (int x) {
            primeiro.elemento = x;
            Celula tmp = new Celula(0);
            tmp.prox = primeiro;
            primeiro = tmp;
        }
        public void inserirPos (int x, int pos) {
            if (pos < 0 || pos > tamanho()) throw new RuntimeException("Erro!");
            else if (pos == 0) inserirIni(x);
            else if (pos == tamanho()) inserirFim(x);
            else {
                Celula i = primeiro;
                for (int j = 0; j < pos; j++) i = i.prox;
                Celula tmp = new Celula(x);
                tmp.prox = i.prox;
                i.prox = tmp;
                i = tmp = null;
            }
        }
        public void inserirFim (int x) {
            ultimo.prox = new Celula(x);
            ultimo = ultimo.prox;
        }

        public int removerIni () {
            if (primeiro == ultimo) throw new RuntimeException("Erro!");
            Celula tmp = primeiro.prox;
            int resp = tmp.elemento;
            primeiro.prox = tmp.prox;
            if (primeiro.prox == null) ultimo = primeiro;
            tmp = tmp.prox = null;
            return resp;
        }
        public int removerPos (int pos) {
            if (primeiro == ultimo || pos < 0 || pos >= tamanho()) throw new RuntimeException("Erro!");
            else if (pos == 0) return removerIni();
            else if (pos == tamanho() - 1) return removerFim();
            else {
                Celula i = primeiro;
                for (int j = 0; j < pos; j++) i = i.prox;
                Celula tmp = i.prox;
                int resp = tmp.elemento;
                i.prox = tmp.prox;
                i = tmp = tmp.prox = null;
                return resp;
            }
        }
        public int removerFim () {
            if (primeiro == ultimo) throw new RuntimeException("Erro!");
            Celula i = primeiro;
            while (i.prox != ultimo) i = i.prox;
            int resp = ultimo.elemento;
            ultimo = i;
            i = ultimo.prox = null;
            return resp;
        }

        public void inserirOrd (int x) {
            if (primeiro == ultimo || x >= ultimo.elemento) inserirFim(x);
            else if (x <= primeiro.prox.elemento) inserirIni(x);
            else {
                Celula i = primeiro;
                while (i.prox != null && i.prox.elemento < x) i = i.prox;
                Celula tmp = new Celula(x);
                tmp.prox = i.prox;
                i.prox = tmp;
                if (tmp.prox == null) ultimo = tmp;
            }
        }

        public int tamanho () {
            int tamanho = 0;
            for (Celula i = primeiro.prox; i != null; i = i.prox) tamanho++;
            return tamanho;
        }

        public void mostrar () {
            System.out.print("[ ");
            for (Celula i = primeiro.prox; i != null; i = i.prox) System.out.print(i.elemento + " ");
            System.out.println("]");
        }
        public void mostrarRec (Celula i) {
            if (i == primeiro.prox) System.out.print("[ ");
            if (i != null) {
                System.out.print(i.elemento + " ");
                mostrarRec(i.prox);
            } else System.out.print("]");
        }
        public void mostrarInvRec (Celula i) {
            if (i != null) {
                mostrarInvRec(i.prox);
                System.out.print(i.elemento + " ");
            } else System.out.print("[ ");
            if (i == primeiro.prox) System.out.println("]");
        }
    }
}
