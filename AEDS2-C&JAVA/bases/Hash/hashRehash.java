public class hashRehash {
    static class Hash {
        private int tam;
        private int[] tabela;

        public Hash (int x) {
            this.tam = x;
            this.tabela = new int[x];
            for (int i = 0; i < x; i++) tabela[i] = -1;
        }

        public int hashar (int x) { return x % tam; }
        public int rehashar (int x) { return ++x % tam; }

        public void inserir (int x) {
            if (x != -1) {
                int i = hashar(x);
                if (tabela[i] == -1) tabela[i] = x;
                else if (tabela[i] != x) {
                    int j = rehashar(x);
                    if (tabela[j] == -1) tabela[j] = x;
                }
                else throw new RuntimeException("Erro!");
            }
        }

        public int pesquisar (int x) {
            int i = hashar(x);
            if (tabela[i] == x) return i;
            if (tabela[i] != -1) {
                int j = rehashar(x);
                if (tabela[j] == x) return j;
            }
            return -1;
        }

        int remover (int x) {
            int i = hashar(x);
            if (tabela[i] == x) {
                tabela[i] = -1;
                return i;
            } else {
                int j = rehashar(x);
                if (tabela[j] == x) {
                    tabela[j] = -1;
                    return j;
                }
            }
            return -1;
        }
    }
}
