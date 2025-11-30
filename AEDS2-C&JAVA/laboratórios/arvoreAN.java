public class arvoreAN {
    public class NoAN {
        private int elemento;
        private boolean cor;
        private NoAN esq, dir;
        public NoAN (int x) {
            this.elemento = x;
            this.cor = true;
            this.esq = this.dir = null;
        }

        public boolean isNoTipo4() {
            return (this.esq != null && this.dir != null && this.esq.cor == true && this.dir.cor == true);
        }
    }

    public class Arvore {
        private NoAN raiz;
        public Arvore () {
            this.raiz = null;
        }

        private void inserirRef (int x, NoAN bis, NoAN avo, NoAN pai, NoAN i) {
            if (i == null) {
                if (x < pai.elemento) i = pai.esq = new NoAN(x);
                else i = pai.dir = new NoAN(x);
                if (pai.cor == true) balancear(bis, avo, pai, i);
            } else {
                if (i.esq != null && i.dir != null && i.esq.cor == true && i.dir.cor == true) {
                    i.cor = true;
                    i.esq.cor = i.dir.cor = false;
                    if (i == raiz) i.cor = false;
                    else if (pai.cor == true) balancear(bis, avo, pai, i);
                }
                if (x < i.elemento) inserirRef(x, avo, pai, i, i.esq);
                else if (x > i.elemento) inserirRef(x, avo, pai, i, i.dir);
                else throw new RuntimeException ("Erro!");
            }

        }
        public void inserir (int x) {
            if (raiz == null) raiz = new NoAN(x);
            else if (raiz.esq == null && raiz.dir == null) {
                if (x < raiz.elemento) raiz.esq = new NoAN(x);
                else raiz.dir = new NoAN(x);
            } else if (raiz.esq == null) {
                if (x < raiz.elemento) raiz.esq = new NoAN(x);
                else if (x < raiz.dir.elemento) {
                    raiz.esq = new NoAN(raiz.elemento);
                    raiz.elemento = x;
                } else {
                    raiz.esq = new NoAN(raiz.elemento);
                    raiz.elemento = raiz.dir.elemento;
                    raiz.dir.elemento = x;
                }
                raiz.esq.cor = raiz.dir.cor = false;
            } else if (raiz.dir == null) {
                if (x > raiz.elemento) raiz.dir = new NoAN(x);
                else if (x > raiz.esq.elemento) {
                    raiz.dir = new NoAN(raiz.elemento);
                    raiz.elemento = x;
                } else {
                    raiz.dir = new NoAN(raiz.elemento);
                    raiz.elemento = raiz.esq.elemento;
                    raiz.esq.elemento = x;
                }
                raiz.esq.cor = raiz.dir.cor = false;
            } else inserirRef(x, null, null, null, raiz);
            raiz.cor = false;
        }

        public void fragmentar (NoAN i) {
            if (i != null) {
                if (i.isNoTipo4()) {
                    i.cor = true;
                    i.esq.cor = i.dir.cor = false;
                    if (i == raiz) i.cor = false;
                }
                fragmentar(i.esq);
                fragmentar(i.dir);
            }
        }

        private void balancear (NoAN bis, NoAN avo, NoAN pai, NoAN i) {
            if (pai.cor == true) {
                if (pai.elemento > avo.elemento) {
                    if (i.elemento > pai.elemento) avo = rotacionarEsq(avo);
                    else avo = rotacionarDirEsq(avo);
                } else {
                    if (i.elemento < pai.elemento) avo = rotacionarDir(avo);
                    else avo = rotacionarEsqDir(avo);
                }
                if (bis == null) raiz = avo;
                else if (avo.elemento < bis.elemento) bis.esq = avo;
                else bis.dir = avo;
                avo.cor = false;
                avo.esq.cor = avo.dir.cor = true;
            }
        }

        private NoAN rotacionarDir (NoAN i) {
            NoAN noEsq = i.esq;
            NoAN noEsqDir = noEsq.dir;
            noEsq.dir = i;
            i.esq = noEsqDir;
            return noEsq;
        }
        private NoAN rotacionarEsq (NoAN i) {
            NoAN noDir = i.dir;
            NoAN noDirEsq = noDir.esq;
            noDir.esq = i;
            i.dir = noDirEsq;
            return noDir;
        }
        private NoAN rotacionarDirEsq (NoAN i) {
            i.dir = rotacionarDir(i.dir);
            return rotacionarEsq(i);
        }
        private NoAN rotacionarEsqDir (NoAN i) {
            i.esq = rotacionarEsq(i.esq);
            return rotacionarDir(i);
        }

        private boolean pesquisar (int x, NoAN i) {
            if (i == null) return false;
            else if (x == i.elemento) return true;
            else if (x < i.elemento) return pesquisar(x, i.esq);
            else return pesquisar(x, i.dir);
        }
        public boolean pesquisar (int x) {
            return pesquisar(x, raiz);
        }

        public void caminharCentral (NoAN i) {
            if (i != null) {
                caminharCentral(i.esq);
                System.out.print(i.elemento + ((i.cor) ? "(P) " : "(B) "));
                caminharCentral(i.dir);
            }
        }
        public void caminharPre (NoAN i) {
            if (i != null) {
                System.out.print(i.elemento + ((i.cor) ? "(P) " : "(B) "));
                caminharPre(i.esq);
                caminharPre(i.dir);
            }
        }
        public void caminharPos (NoAN i) {
            if (i != null) {
                caminharPos(i.esq);
                caminharPos(i.dir);
                System.out.print(i.elemento + ((i.cor) ? "(P) " : "(B) "));
            }
        }

        private NoAN remover (int x, NoAN i) {
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

        private NoAN maiorEsq (NoAN i, NoAN j) {
            if (j.dir == null) {
                i.elemento = j.elemento;
                j = j.esq;
            }
            else j.dir = maiorEsq(i, j.dir);
            return j;
        }
        private NoAN menorDir (NoAN i, NoAN j) {
            if (j.esq == null) {
                i.elemento = j.elemento;
                j =j.dir;
            }
            else j.esq = menorDir(i, j.esq);
            return j;
        }

        public int getAlturaRec (NoAN i) {
            if (i == null) return 0;
            else {
                int altEsq = getAlturaRec(i.esq);
                int altDir = getAlturaRec(i.dir);
                return (altEsq > altDir ? altEsq : altDir) + 1;
            }
        }

        public int getMaior () {
            if (raiz == null) throw new RuntimeException ("Erro!");
            NoAN i;
            for (i = raiz; i.dir != null; i = i.dir);
            return i.elemento;
        }
        public int getMenor () {
            if (raiz == null) throw new RuntimeException ("Erro!");
            NoAN i;
            for (i = raiz; i.esq != null; i = i.esq);
            return i.elemento;
        }

        public int somarRec (NoAN i) {
            if (i == null) return 0;
            else return i.elemento + somarRec(i.esq) + somarRec(i.dir);
        }

        private boolean igual (NoAN a, NoAN b) {
            if (a == null && b == null) return true;
            else if (a == null || b == null) return false;
            else if (a.elemento != b.elemento) return false;
            else return igual(a.esq, b.esq) && igual(a.dir, b.dir);
        }
        public boolean igual (Arvore b) {
            return igual(this.raiz, b.raiz);
        }
        private boolean espelho (NoAN a, NoAN b) {
            if (a == null && b == null) return true;
            else if (a == null || b == null) return false;
            else if (a.elemento != b.elemento) return false;
            else return espelho(a.esq, b.dir) && espelho(a.dir, b.esq);
        }
        public boolean espelho (Arvore b) {
            return espelho(this.raiz, b.raiz);
        }
    }

    public static void main (String[] args) {
        Arvore arvore = new arvoreAN().new Arvore();
        arvore.inserir(4);
        arvore.inserir(35);
        arvore.inserir(10);
        arvore.inserir(13);
        arvore.inserir(3);
        arvore.inserir(30);
        arvore.inserir(15);
        arvore.inserir(12);
        arvore.inserir(7);
        arvore.inserir(40);
        arvore.inserir(20);
        arvore.caminharCentral(arvore.raiz);
    }
}
