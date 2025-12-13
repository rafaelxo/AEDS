public class arvoreBIN {
    public class No {
        private int elemento;
        private No esq, dir;
        public No (int x) {
            this.elemento = x;
            this.esq = this.dir = null;
        }
    }

    public class Arvore {
        private No raiz;
        public Arvore () {
            this.raiz = null;
        }

        private No inserirRef (int x, No i) {
            if (i == null) i = new No(x);
            else if (x < i.elemento) i.esq = inserirRef(x, i.esq);
            else if (x > i.elemento) i.dir = inserirRef(x, i.dir);
            else throw new RuntimeException ("Erro!");
            return i;
        }
        public void inserir (int x) {
            raiz = inserirRef(x, raiz);
        }

        private void inserirPai (int x, No i, No pai) {
            if (i == null) {
                if (x < pai.elemento) pai.esq = new No (x);
                else pai.dir = new No (x);
            }
            else if (x < i.elemento) inserirPai(x, i.esq, i);
            else if (x > i.elemento) inserirPai(x, i.dir, i);
            else throw new RuntimeException ("Erro!");
        }
        public void inserirPai (int x) {
            if (raiz == null) raiz = new No (x);
            else if (x < raiz.elemento) inserirPai(x, raiz.esq, raiz);
            else if (x > raiz.elemento) inserirPai(x, raiz.dir, raiz);
            else throw new RuntimeException ("Erro!");
        }

        private boolean pesquisar (int x, No i) {
            if (i == null) return false;
            else if (x == i.elemento) return true;
            else if (x < i.elemento) return pesquisar(x, i.esq);
            else return pesquisar(x, i.dir);
        }
        public boolean pesquisar (int x) {
            return pesquisar(x, raiz);
        }

        public void caminharCentral (No i) {
            if (i != null) {
                caminharCentral(i.esq);
                System.out.print(i.elemento + " ");
                caminharCentral(i.dir);
            }
        }
        public void caminharPre (No i) {
            if (i != null) {
                System.out.print(i.elemento + " ");
                caminharPre(i.esq);
                caminharPre(i.dir);
            }
        }
        public void caminharPos (No i) {
            if (i != null) {
                caminharPos(i.esq);
                caminharPos(i.dir);
                System.out.print(i.elemento + " ");
            }
        }

        private No remover (int x, No i) {
            if (i == null) throw new RuntimeException ("Erro!");
            else if (x < i.elemento) i.esq = remover(x, i.esq);
            else if (x > i.elemento) i.dir = remover(x, i.dir);
            else if (i.dir == null) i = i.esq;
            else if (i.esq == null) i = i.dir;
            else i.esq = maiorEsq(i, i.esq);
            return i;
        }
        public void remover (int x) {
            raiz = remover(x, raiz);
        }

        private No maiorEsq (No i, No j) {
            if (j.dir == null) {
                i.elemento = j.elemento;
                j = j.esq;
            }
            else j.dir = maiorEsq(i, j.dir);
            return j;
        }
        private No menorDir (No i, No j) {
            if (j.esq == null) {
                i.elemento = j.elemento;
                j =j.dir;
            }
            else j.esq = menorDir(i, j.esq);
            return j;
        }

        public int getAlturaRec (No i) {
            if (i == null) return 0;
            else {
                int altEsq = getAlturaRec(i.esq);
                int altDir = getAlturaRec(i.dir);
                return (altEsq > altDir ? altEsq : altDir) + 1;
            }
        }

        public int getMaior () {
            if (raiz == null) throw new RuntimeException ("Erro!");
            No i;
            for (i = raiz; i.dir != null; i = i.dir);
            return i.elemento;
        }
        public int getMenor () {
            if (raiz == null) throw new RuntimeException ("Erro!");
            No i;
            for (i = raiz; i.esq != null; i = i.esq);
            return i.elemento;
        }

        public int somarRec (No i) {
            if (i == null) return 0;
            else return i.elemento + somarRec(i.esq) + somarRec(i.dir);
        }

        private boolean igual (No a, No b) {
            if (a == null && b == null) return true;
            else if (a == null || b == null) return false;
            else if (a.elemento != b.elemento) return false;
            else return igual(a.esq, b.esq) && igual(a.dir, b.dir);
        }
        public boolean igual (Arvore b) {
            return igual(this.raiz, b.raiz);
        }
        private boolean espelho (No a, No b) {
            if (a == null && b == null) return true;
            else if (a == null || b == null) return false;
            else if (a.elemento != b.elemento) return false;
            else return espelho(a.esq, b.dir) && espelho(a.dir, b.esq);
        }
        public boolean espelho (Arvore b) {
            return espelho(this.raiz, b.raiz);
        }
    }
}
