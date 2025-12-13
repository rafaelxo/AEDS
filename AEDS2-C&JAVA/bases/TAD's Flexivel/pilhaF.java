public class pilhaF {
    static class Celula {
        int elemento;
        Celula prox;
        public Celula(int x) {
            this.elemento = x;
            this.prox = null;
        }
    }

    static class Pilha {
        private Celula topo;
        public Pilha () {
            topo = null;
        }

        public void inserir (int x) {
            Celula tmp = new Celula(x);
            tmp.prox = topo;
            topo = tmp;
            tmp = null;
        }

        public int remover () {
            if (topo == null) throw new RuntimeException("Erro!");
            int resp = topo.elemento;
            Celula tmp = topo;
            topo = topo.prox;
            tmp = tmp.prox = null;
            return resp;
        }

        public int tamanho () {
            int tamanho = 0;
            for (Celula i = topo; i != null; i = i.prox) tamanho++;
            return tamanho;
        }

        public int somar () {
            int soma = 0;
            for (Celula i = topo; i != null; i = i.prox) soma += i.elemento;
            return soma;
        }
        public int somarRec (Celula i) {
            if (i == null) return 0;
            else return i.elemento + somarRec(i.prox);
        }

        public int maior () {
            if (topo == null) throw new RuntimeException("Erro!");
            int maior = topo.elemento;
            for (Celula i = topo.prox; i != null; i = i.prox) {
                if (i.elemento > maior) maior = i.elemento;
            }
            return maior;
        }
        public int maiorRec (Celula i) {
            if (i == null) return 0;
            else return (i.elemento > maiorRec(i.prox) ? i.elemento : maiorRec(i.prox));
        }

        public void mostrar () {
            System.out.print("[ ");
            for (Celula i = topo; i != null; i = i.prox) System.out.print(i.elemento + " ");
            System.out.println("]");
        }
        public void mostrarRec (Celula i) {
            if (i == topo) System.out.print("[ ");
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
            if (i == topo) System.out.println("]");
        }
    }
}
