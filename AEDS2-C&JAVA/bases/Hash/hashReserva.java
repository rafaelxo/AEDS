public class hashReserva {
    static class Hash {
        private int tamTab;
        private int tabela[];
        private int tamRes;
        private int reserva[];
        private int qnt;

        public Hash (int x, int y) {
            this.tamTab = x;
            this.tamRes = y;
            this.reserva = new int[y];
            this.tabela = new int[x + y];
            for (int i = 0; i < x; i++) tabela[i] = -1;
            for (int i = 0; i < y; i++) reserva[i] = -1;
            this.qnt = 0;
        }

        public int hashar (int x) { return x % tamTab; }

        public void inserir (int x) {
            if (x != -1) {
                int i = hashar(x);
                if (tabela[i] == -1) tabela[i] = x;
                else if (qnt < tamRes) reserva[qnt++] = x;
                else throw new RuntimeException("Erro!");
            }
        }

        public int pesquisar (int x) {
            int i = hashar(x);
            if (tabela[i] == x) return i;
            if (tabela[i] != -1) {
                for (int j = 0; j < tamRes; j++) {
                    if (reserva[j] == x) return tamTab + j;
                }
            }
            return -1;
        }

        int remover (int x) {
            int i = hashar(x);
            if (tabela[i] == x) {
                tabela[i] = -1;
                return i;
            } else {
                for (int j = 0; j < tamRes; j++) {
                    if (reserva[j] == x) {
                        reserva[j] = -1;
                        qnt--;
                        return tamTab + j;
                    }
                }
            }
            return -1;
        }
    }
}
