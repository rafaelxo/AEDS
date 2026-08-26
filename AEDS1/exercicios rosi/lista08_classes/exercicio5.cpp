#include <iostream>
#include <iomanip>
using namespace std;

class Elevador {
    private:
        int andarAtual, totalAndares, capacidade, pessoasPresentes;
    public:
        Elevador() { inicializaTudo(0, 1, 1, 0); }
        Elevador (int capac, int total) { inicializaTudo(0, capac, total, 0); }
        void setAndar(int andar) {
            try {
                if (andar >= 0 && andar <= totalAndares) andarAtual = andar;
                else throw invalid_argument ("Andar invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void setTotal(int total) {
            try {
                if (total > 0 && total <= 30) totalAndares = total;
                else throw invalid_argument ("Total de andares invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void setCapacidade(int capac) {
            try {
                if (capac > 0 && capac <= 20) capacidade = capac;
                else throw invalid_argument ("Capacidade de pessoas invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void setPessoas(int quant) {
            try {
                if (quant >= 0 && quant <= capacidade) pessoasPresentes = quant;
                else throw invalid_argument ("Quantidade de pessoas presentes invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void entra() {
            try {
                if (pessoasPresentes < capacidade) pessoasPresentes++;
                else throw invalid_argument ("Capacidade máxima atingida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void sai() {
            try {
                if (pessoasPresentes > 0) pessoasPresentes--;
                else throw invalid_argument ("Elevador vazio!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void sobe() {
            try {
                if (andarAtual < totalAndares) andarAtual++;
                else throw invalid_argument ("Já está no último andar!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void desce() {
            try {
                if (andarAtual > 0) andarAtual--;
                else throw invalid_argument ("Já está no térreo!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        int getAndar() { return andarAtual; }
        int getTotal() { return totalAndares; }
        int getCapacidade() { return capacidade; }
        int getPessoas() { return pessoasPresentes; }
    private:
        void inicializaTudo (int andar, int total, int capac, int quant) {
            setTotal(total);
            setAndar(andar);
            setCapacidade(capac);
            setPessoas(quant);
        }
};

int main () {
    int capacidade, andares;
    cin >> capacidade >> andares;
    Elevador e[2] = { Elevador(capacidade, andares), Elevador(capacidade, andares) };
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        string acao;
        cin >> acao;
        if (acao == "entrar") e[0].entra();
        else if (acao == "sair") e[0].sai();
        else if (acao == "subir") e[0].sobe();
        else if (acao == "descer") e[0].desce();
        cout << "Andar atual: " << e[0].getAndar() << endl;
        cout << "Pessoas presentes: " << e[0].getPessoas() << endl;
    }
}