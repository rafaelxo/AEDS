#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class Cargo {
    private:
        int codigo;
        float v_hora;
    public:
        Cargo() {
            codigo = 1; v_hora = 10;
        }
        Cargo(int i, float f) {
            codigo = i; v_hora = f;
        }
        int getCodigo() { return codigo; }
        float getVHora() { return v_hora; }
};

class Funcionario {
    private:
        string nome;
        int cargo, horas_t;
        char sexo;
    public:
        Funcionario() {
            setNome("nenhum");
            setCargo(1);
            setSexo('M');
            setHorasT(10);
        }
        Funcionario(string n, int c, char s, int h) {
            setNome(n);
            setCargo(c);
            setSexo(s);
            setHorasT(h);
        }
        void setNome(string n) {
            try {
                if (n.length() > 2) nome = n;
                else throw invalid_argument("Nome inválido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        string getNome() { return nome; }
        void setCargo(int c) {
            try {
                if (c > 0) cargo = c;
                else throw invalid_argument("Cargo inválido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        int getcargo() { return cargo; }
        void setSexo(char s) {
            s = toupper(s);
            try {
                if (s == 'M' || s == 'F') sexo = s;
                else throw invalid_argument("Sexo inválido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        char getSexo() { return sexo; }
        void setHorasT(int h) {
            try {
                if (h > 0) horas_t = h;
                else throw invalid_argument("Horas inválidas!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        int getHorasT() { return horas_t; }
        float calcular(Cargo c[], char s) {
            float salario = horas_t * c[cargo - 1].getVHora();
            if (s == 'F') salario *= 1.2;
            return salario;
        }
};

int main () {
    Cargo c[3] = { Cargo(1, 10), Cargo(2, 20), Cargo(3, 30) };
    Funcionario f;
    int cod, horas;
    char sexo;
    string nome;
    cout << "Insira o nome do funcionário: ";
    getline(cin, nome); f.setNome(nome);
    cout << "Insira o código do cargo: ";
    cin >> cod; f.setCargo(cod);
    cout << "Insira o sexo do funcionário (M ou F): ";
    cin >> sexo; f.setSexo(sexo);
    cout << "Insira o número de horas trabalhadas pelo funcionário: ";
    cin >> horas; f.setHorasT(horas);
    cout << "Salário do funcionário: " << f.calcular(c, sexo) << " reais" << endl;
}
