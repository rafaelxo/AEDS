public class hashListaF {
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

        public void inserir (int x) {
            ultimo.prox = new Celula(x);
            ultimo = ultimo.prox;
        }

        public int remover (int x) {
            if (primeiro == ultimo) throw new RuntimeException("Erro!");
            else {
                Celula tmp = primeiro;
                Celula i = primeiro.prox;
                int pos = 0;
                while (i != null && i.elemento != x) {
                    tmp = i;
                    i = i.prox;
                    pos++;
                }
                if (i != null) {
                    tmp.prox = i.prox;
                    i.prox = null;
                    if (i == ultimo) ultimo = tmp;
                    return pos;
                }
            }
            return -1;
        }

        public int pesquisar (int x) {
            int pos = 0;
            for (Celula i = primeiro.prox; i != null; i = i.prox, pos++) {
                if (i.elemento == x) return pos;
            }
            return -1;
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
    }

    static class Hash {
        private Lista[] tabela;
        private int tam;

        public Hash (int x) {
            this.tam = x;
            tabela = new Lista[tam];
            for (int i = 0; i < tam; i++) tabela[i] = null;
        }

        private int hashar (int x) { return x % tam; }

        public void inserir (int x) {
            int i = hashar(x);
            tabela[i].inserir(x);
        }

        public int remover (int x) {
            int i = hashar(x);
            return tabela[i].remover(x);
        }

        public int pesquisar (int x) {
            int i = hashar(x);
            return tabela[i].pesquisar(x);
        }
    }
}
