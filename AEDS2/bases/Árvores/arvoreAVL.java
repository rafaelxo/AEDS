public class arvoreAVL {
    public class No {
        private int elemento, nivel;
        private No esq, dir;
        public No (int x) {
            this.elemento = x;
            this.nivel = 0;
            this.esq = this.dir = null;
        }
        public int getNivel (No i) {
            return (i == null) ? 0 : i.nivel;
        }
        public void setNivel () {
            this.nivel = 1 + Math.max(getNivel(this.esq), getNivel(this.dir));
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
            return balancear(i);
        }
        public void inserir (int x) {
            raiz = inserirRef(x, raiz);
        }

        private No balancear (No i) {
            if (i != null) {
                int fator = i.getNivel(i.dir) - i.getNivel(i.esq);
                if (Math.abs(fator) <= 1) i.setNivel();
                else if (fator == 2) {
                    int fatorFilhoDir = i.dir.getNivel(i.dir.dir) - i.dir.getNivel(i.dir.esq);
                    if (fatorFilhoDir == -1) i.dir = rotacionarDir(i.dir);
                    i = rotacionarEsq(i);
                }
                else if (fator == -2) {
                    int fatorFilhoEsq = i.esq.getNivel(i.esq.dir) - i.esq.getNivel(i.esq.esq);
                    if (fatorFilhoEsq == 1) i.esq = rotacionarEsq(i.esq);
                    i = rotacionarDir(i);
                } else throw new RuntimeException ("Erro!");
            }
            return i;
        }

        private No rotacionarEsq (No i) {
            No noDir = i.dir;
            No noDirEsq = noDir.esq;
            noDir.esq = i;
            i.dir = noDirEsq;
            i.setNivel();
            noDir.setNivel();
            return noDir;
        }
        private No rotacionarDir (No i) {
            No noEsq = i.esq;
            No noEsqDir = noEsq.dir;
            noEsq.dir = i;
            i.esq = noEsqDir;
            i.setNivel();
            noEsq.setNivel();
            return noEsq;
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
            return balancear(i);
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
