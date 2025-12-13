public class filaF {
    static class Celula {
        int elemento;
        Celula prox;
        public Celula (int x) {
            this.elemento = x;
            this.prox = null;
        }
    }

    static class Fila {
        private Celula primeiro, ultimo;
        public Fila () {
            primeiro = new Celula(0);
            ultimo = primeiro;
        }

        public void inserir (int x) {
            ultimo.prox = new Celula(x);
            ultimo = ultimo.prox;
        }

        public int remover () {
            if (primeiro == ultimo) throw new RuntimeException("Erro!");
            Celula tmp = primeiro.prox;
            int resp = tmp.elemento;
            primeiro.prox = tmp.prox;
            tmp = tmp.prox = null;
            if (primeiro.prox == null) ultimo = primeiro;
            return resp;
        }

        public int somar () {
            int soma = 0;
            for (Celula i = primeiro.prox; i != null; i = i.prox) soma += i.elemento;
            return soma;
        }
        public int somarRec (Celula i) {
            if (i == null) return 0;
            else return i.elemento + somarRec(i.prox);
        }

        public int maior () {
            int maior = primeiro.prox.elemento;
            for (Celula i = primeiro.prox.prox; i != null; i = i.prox) {
                if (i.elemento > maior) maior = i.elemento;
            }
            return maior;
        }
        public int maiorRec (Celula i) {
            if (i == null) return 0;
            else return (i.elemento > maiorRec(i.prox) ? i.elemento : maiorRec(i.prox));
        }

        public void inverter () {
            Celula prev = null, next = null, atual = primeiro.prox;
            while (atual != null) {
                next = atual.prox;
                atual.prox = prev;
                prev = atual;
                atual = next;
            }
            ultimo = primeiro.prox;
            primeiro.prox = prev;
            if (ultimo != null) ultimo.prox = null;
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
            } else System.out.println("]");
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
