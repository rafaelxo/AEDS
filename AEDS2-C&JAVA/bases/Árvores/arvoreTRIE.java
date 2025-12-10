public class arvoreTRIE {
    public class No {
        private char elemento;
        private final int tamanho = 256;
        private No[] prox;
        private boolean folha;
        public No (char x) {
            this.elemento = x;
            this.prox = new No[tamanho];
            for (int i = 0; i < tamanho; i++) this.prox[i] = null;
            this.folha = false;
        }
        public int hash (char x) {
            return (int)x;
        }
    }

    public class Arvore {
        private No raiz;
        public Arvore () {
            this.raiz = null;
        }

        private No inserirRef (String s, No no, int i) {
            if (no.prox[s.charAt(i)] == null) {
                no.prox[s.charAt(i)] = new No (s.charAt(i));
                if (i == s.length() - 1) no.prox[s.charAt(i)].folha = true;
                else no.prox[s.charAt(i + 1)] = inserirRef(s, no.prox[s.charAt(i)], i + 1);
            }
            else {
                if (i == s.length() - 1) no.prox[s.charAt(i)].folha = true;
                else no.prox[s.charAt(i)] = inserirRef(s, no.prox[s.charAt(i)], i + 1);
            }
        }
        public void inserir (String s) {
            raiz = inserirRef(s, raiz, 0);
        }

        private boolean pesquisar (String s, No no, int i) {
            if (no.prox[s.charAt(i)] == null) return false;
            else if (i == s.length() - 1) return (no.prox[s.charAt(i)].folha);
            else if (i < s.length() - 1) return pesquisar(s, no.prox[s.charAt(i)], i + 1);
            else throw new RuntimeException ("Erro!");
        }
        public boolean pesquisar (String s) {
            return pesquisar(s, raiz, 0);
        }

        private No remover (String s, No no, int i) {
            if (no.prox[s.charAt(i)] == null) return null;
            else if (i < s.length() - 1) {
                no.prox[s.charAt(i)] = remover(s, no.prox[s.charAt(i)], i + 1);
                return no;
            }
            else {
                if (no.prox[s.charAt(i)].folha == true) {
                    no.prox[s.charAt(i)].folha = false;
                    return no;
                }
                else return no;
            }
        }
        public void remover (String s) {
            raiz = remover(s, raiz, 0);
        }

        public void mostrar (String s, No no) {
            if (no.folha == true) System.out.println(s + no.elemento);
            else {
                for (int i = 0; i < no.prox.length; i++) {
                    if (no.prox[i] != null) mostrar(s + no.prox[i].elemento, no.prox[i]);
                }
            }
        }
    }
}
