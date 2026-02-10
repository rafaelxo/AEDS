#include <iostream>
#include <iomanip>
using namespace std;

class Autor {
    private:
        string nomeA;
    public:
        Autor () { setNomeA("nenhum"); }
        Autor (string texto) { setNomeA(texto); }
        void setNomeA(string texto) {
            try {
                if (texto.length() > 5) nomeA = texto;
                else throw invalid_argument ("Nome invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        string getNomeA() { return nomeA; }
        void preenche () {
            string frase;
            getline(cin, frase);
            setNomeA(frase);
        }
        void exibe () { cout << "Autor: " << getNomeA() << endl; }
};

class Livro {
    private:
        string nomeL;
        int ano;
        Autor *autor;
    public:
        Livro () {
            setNomeL("nenhum");
            setAno(1);
            setAutor(nullptr);
        }
        Livro (string frase, int num, Autor *a) {
            setNomeL(frase);
            setAno(num);
            setAutor(a);
        }
        void setNomeL(string frase) {
            try {
                if (frase.length() > 5) nomeL = frase;
                else throw invalid_argument ("Nome invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void setAno(int num) {
            try {
                if (num > 0) ano = num;
                else throw invalid_argument ("Ano invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void setAutor(Autor *a) { autor = a; }
        string getNomeL() { return nomeL; }
        int getAno() { return ano; }
        Autor *getAutor () { return autor; }
        void preenche () {
            string frase;
            int ano;
            getline(cin, frase);
            setNomeL(frase);
            cin >> ano;
            setAno(ano);
        }
        void exibe() {
            cout << "Detalhes do Livro:" << endl;
            cout << "Título: " << getNomeL() << endl;
            cout << "Ano de Publicação: " << getAno() << endl;
            autor->exibe();
        }
};



int main () {
    Autor *a = new Autor();
    a->preenche();
    Livro l;
    l.preenche(); l.setAutor(a); l.exibe();
}