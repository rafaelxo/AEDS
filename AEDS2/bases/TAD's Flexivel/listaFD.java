public class listaFD {
    static class CelulaDupla {
        int elemento;
        CelulaDupla ant, prox;
        public CelulaDupla (int x) {
            this.elemento = x;
            this.ant = this.prox = null;
        }
    }

    static class Lista {
        private CelulaDupla primeiro, ultimo;
        public Lista () {
            primeiro = new CelulaDupla(0);
            ultimo = primeiro;
        }

        public void inserirIni (int x) {
            primeiro.elemento = x;
            CelulaDupla tmp = new CelulaDupla(0);
            tmp.prox = primeiro;
            primeiro.ant = tmp;
            primeiro = tmp;
            tmp = null;
        }
        public void inserirPos (int x, int pos) {
            if (pos < 0 || pos > tamanho()) throw new RuntimeException("Erro!");
            else if (pos == 0) inserirIni(x);
            else if (pos == tamanho()) inserirFim(x);
            else {
                CelulaDupla i = primeiro;
                for (int j = 0; j < pos; j++) i = i.prox;
                CelulaDupla tmp = new CelulaDupla(x);
                tmp.ant = i;
                tmp.prox = i.prox;
                i.prox = tmp.prox.ant = tmp;
                i = tmp = null;
            }
        }
        public void inserirFim (int x) {
            ultimo.prox = new CelulaDupla(x);
            ultimo.prox.ant = ultimo;
            ultimo = ultimo.prox;
        }

        public int removerIni () {
            if (primeiro == ultimo) throw new RuntimeException("Erro!");
            CelulaDupla tmp = primeiro.prox;
            int resp = tmp.elemento;
            primeiro.prox = tmp.prox;
            if (primeiro.prox != null) primeiro.prox.ant = primeiro;
            else ultimo = primeiro;
            tmp = tmp.prox = tmp.ant = null;
            return resp;
        }
        public int removerPos (int pos) {
            if (primeiro == ultimo || pos < 0 || pos >= tamanho()) throw new RuntimeException("Erro!");
            else if (pos == 0) return removerIni();
            else if (pos == tamanho() - 1) return removerFim();
            else {
                CelulaDupla i = primeiro.prox;
                for (int j = 0; j < pos; j++) i = i.prox;
                int resp = i.elemento;
                i.ant.prox = i.prox;
                i.prox.ant = i.ant;
                i = i.ant = i.prox = null;
                return resp;
            }
        }
        public int removerFim () {
            if (primeiro == ultimo) throw new RuntimeException("Erro!");
            int resp = ultimo.elemento;
            ultimo = ultimo.ant;
            ultimo.prox.ant = ultimo.prox = null;
            return resp;
        }

        public void inserirOrd (int x) {
            if (primeiro == ultimo || x >= ultimo.elemento) inserirFim(x);
            else if (x <= primeiro.prox.elemento) inserirIni(x);
            else {
                CelulaDupla i = primeiro;
                while (i.prox != null && i.prox.elemento < x) i = i.prox;
                CelulaDupla tmp = new CelulaDupla(x);
                tmp.ant = i;
                tmp.prox = i.prox;
                if (i.prox != null) i.prox.ant = tmp;
                i.prox = tmp;
                i = tmp = null;
            }
        }

        public void inverter () {
            CelulaDupla atual = primeiro.prox, next = null;
            while (atual != null) {
                next = atual.prox;
                atual.prox = atual.ant;
                atual.ant = next;
                atual = next;
            }
            CelulaDupla aux = primeiro.prox;
            primeiro.prox = ultimo;
            ultimo = aux;
            if (primeiro.prox != null) primeiro.prox.ant = primeiro;
            if (ultimo != null) ultimo.prox = null;
        }

        public int tamanho () {
            int tamanho = 0;
            for (CelulaDupla i = primeiro.prox; i != null; i = i.prox) tamanho++;
            return tamanho;
        }

        public void mostrar () {
            System.out.print("[ ");
            for (CelulaDupla i = primeiro.prox; i != null; i = i.prox) System.out.print(i.elemento + " ");
            System.out.println("]");
        }
        public void mostrarRec (CelulaDupla i) {
            if (i == primeiro.prox) System.out.print("[ ");
            if (i != null) {
                System.out.print(i.elemento + " ");
                mostrarRec(i.prox);
            } else System.out.println("]");
        }
        public void mostrarInvRec (CelulaDupla i) {
            if (i != null) {
                mostrarInvRec(i.ant);
                System.out.print(i.elemento + " ");
            } else System.out.println("[ ");
            if (i == primeiro.prox) System.out.println("]");
        }
    }
}
