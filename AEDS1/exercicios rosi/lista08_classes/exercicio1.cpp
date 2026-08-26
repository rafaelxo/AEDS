#include <iostream>
using namespace std;

class Pessoa {
    private:
        string nome;
        int idade;
        float altura;
    public:
        Pessoa() { inicializaTudo("nenhum", 1, 1); }
        Pessoa(string nNome, int nIdade, float nAltura) { inicializaTudo(nNome, nIdade, nAltura); }
        void preenche() {
            string nome, enter;
            int idade;
            float altura;
            getline(cin, enter);
            cin >> nome;
            setNome(nome);
            cin >> idade;
            setIdade(idade);
            cin >> altura;
            setAltura(altura);
        }
        void exibe() {
            cout << "Nome: " << getNome() << endl;
            cout << "Idade: " << getIdade() << " anos" << endl;
            cout << "Altura: " << getAltura() << " metros" << endl;
        }
        void setNome(string texto) {
            try {
                if (texto.length() >= 3) nome = texto;
                else throw invalid_argument ("Nome invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void setIdade(int num) {
            try {
                if (num > 0) idade = num;
                else throw invalid_argument ("Idade invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        void setAltura(float val) {
            try {
                if (val > 0) altura = val;
                else throw invalid_argument ("Ano invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        string getNome() { return nome; }
        int getIdade() { return idade; }
        float getAltura() { return altura; }
    private:
        void inicializaTudo(string nome, int idade, float altura) {
            setNome(nome);
            setIdade(idade);
            setAltura(altura);
        }
};

void preencheGrupo(Pessoa grupo[], int N) {
    for (int i = 0; i < N; i++) grupo[i].preenche();
}

void exibeGrupo(Pessoa grupo[], int N) {
    for (int i = 0; i < N; i ++) {
        cout << "Dados da pessoa:" << endl;
        grupo[i].exibe();
        cout << endl;
    }
}

int main () {
    int N; cin >> N;
    Pessoa grupo[N];
    preencheGrupo(grupo, N);
    exibeGrupo(grupo, N);
}