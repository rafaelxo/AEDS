#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class Tipo {
    private:
        int codigo;
        float percentual;
    public:
        Tipo() { setCodigo(1); }
        void setCodigo(int num) {
            try {
                if (num == 1) {
                    codigo = 1;
                    percentual = 10;
                }
                else if (num == 2) {
                    codigo = 2;
                    percentual = 20;
                }
                else throw invalid_argument("Codigo invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        int getCodigo() { return codigo; }
        string formataCod() {
            if (codigo == 1) return "Alimentacao";
            else if (codigo == 2) return "Limpeza";
            else return "Desconhecido";
        }
        float getPercentual() { return percentual; }
        void preenche() {
            int n;
            cout << "Tipo do produto: ";
            cin >> n; setCodigo(n);
            cout << endl;
        }
        void exibe() { cout << "Tipo do produto: " << formataCod() << endl << "Percentual de imposto: " << getPercentual() << endl; }
};

class Produto {
    private:
        string descricao;
        Tipo tipo;
        float preco, imposto;
    public:
        Produto() {
            setDescricao("nenhum");
            tipo.setCodigo(1);
            setPreco(1);
            setImposto();
        }
        Produto(string d, int n, float p) {
            setDescricao(d);
            tipo.setCodigo(n);
            setPreco(p);
            setImposto();
        }
        void setDescricao(string d) {
            try {
                if (d.length() > 3) descricao = d;
                else throw invalid_argument("Descricao invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        string getDescricao() { return descricao; }
        void setPreco(float p) {
            try {
                if (p > 0) preco = p;
                else throw invalid_argument("Preco invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getPreco() { return preco; }
        float getImposto() { return imposto; }
        float getFinal() { return getPreco() + getImposto(); }
        void preenche() {
            string txt;
            float val;
            cout << "Descricao do produto: ";
            getline(cin, txt); setDescricao(txt);
            cout << "Preco do produto: ";
            cin >> val; setPreco(val);
            setImposto();
            tipo.preenche();
        }
        void exibe() {
            cout << "Descricao: " << getDescricao() << endl << "Preco: " << getPreco() << " reais" << endl << "Imposto: " << getImposto() << " reais" << endl;
            tipo.exibe();
        }
    private:
        void setImposto() { imposto = getPreco() * tipo.getPercentual() / 100; }
};

int main() {
    float media = 0;
    Produto p[5];
    for (int i = 0; i < 5; i++) p[i].preenche();
    for (int i = 0; i < 5; i++) p[i].exibe();
    for (int i = 0; i < 5; i++) {
        cout << "Preco final do produto " << (i + 1) << ":" << p[i].getFinal() << " reais" << endl;
        media += p[i].getFinal();
    }
    media /= 5;
    cout << "Média de preco dos produtos: " << media << endl << endl;
    for (int i = 0; i < 5; i++) {
        if (p[i].getFinal() > media) cout << "Produto " << (i + 1) << " tem preço acima da média!" << endl;
        else if (p[i].getFinal() < media) cout << "Produto " << (i + 1) << " tem preço abaixo da média!" << endl;
        else cout << "Produto " << (i + 1) << " tem preço igual à média!" << endl;
    }
}
