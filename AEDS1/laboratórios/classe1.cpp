#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class Endereco {
    private:
        string logradouro;
        int numero;
        string complemento;
    public:
        Endereco() {
            inicializaEnd(string ("nenhum"), 1, string("nenhum"));
        }
        Endereco(string nLogradouro, int nNumero, string nComplemento) {
            inicializaEnd(nLogradouro, nNumero, nComplemento);
        }
        void setLogradouro(string log) {
            if(log.length() > 5) logradouro = log;
            else throw invalid_argument ("Logradouro invalido!");
        }
        void setNumero(int num) {
            if (num > 0) numero = num;
            else throw invalid_argument ("Numero invalido!");
        }
        void setComplemento(string comp) {
            if (comp.length() > 3) complemento = comp;
            else throw invalid_argument ("Complemento invalido!");
        }
        string getLogradouro() { return logradouro; }
        int getNumero() { return numero; }
        string getComplemento() { return complemento; }
        string getEndereco () {
            string texto = getLogradouro() + ", " + to_string(getNumero()) + " - " + getComplemento();
            return texto;
        }
    private:
        void inicializaEnd(string log, int num, string comp) {
            try {
                setLogradouro(log);
                setNumero(num);
                setComplemento(comp);
            } catch (invalid_argument &i) {
                cerr << i.what();
            } catch (exception &e) {
                cerr << "Nao inicializou o endereco corretamente!" << endl;
            }
        }
};

class Data {
    private:
        int dia, mes, ano;
    public:
        Data () { setData(1, 1, 2000); }
        Data(int d, int m, int a) { setData(d, m, a); }
        void setData(int d, int m, int a) {
            switch (m) {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    if (d >= 1 && d <= 31) dia = d;
                break;
                case 2:
                    if (d >= 1 && d <= 28) dia = d;
                break;
                case 4: case 6: case 9: case 11:
                    if (d >= 1 && d <= 30) dia = d;
                break;
                default:
                    cout << "ERRO - Mes invalido!" << endl;
                break;
            }
            if (m >= 1 && m <= 12) mes = m;
            else cout << "ERRO - Mes inexistente!" << endl;
            if (a > 1910 && a <= 2025) ano = a;
            else cout << "ERRO - Ano improvavel!" << endl;
        }
        int getDia() { return dia; }
        string getMes() {
            switch (mes) {
                case 1: return string("Janeiro");
                case 2: return string("Fevereiro");
                case 3: return string("Marco");
                case 4: return string("Abril");
                case 5: return string("Maio");
                case 6: return string("Junho");
                case 7: return string("Julho");
                case 8: return string("Agosto");
                case 9: return string("Setembro");
                case 10: return string("Outubro");
                case 11: return string("Novembro");
                case 12: return string("Dezembro");
                default: return string("Mes invalido!");
            }
        }
        int getAno() { return ano; }
        string getData() {
            string texto = to_string(getDia()) + " de " + getMes() + " de " + to_string(getAno());
            return texto;
        }
};

class Aluno {
    private:
        string nome;
        int idade;
        float notas[3];
        Data nasc;
        Endereco ende;
    public:
        Aluno() {
            float val[3] = {1, 1, 1};
            setNome("nenhum");
            setIdade(1);
            setNotas(val);
            nasc.setData(1, 1, 2000);
            try {
                ende.setLogradouro("nenhum");
                ende.setNumero(1);
                ende.setComplemento("nenhum");
            } catch (invalid_argument &i) {
                cerr << i.what();
            } catch (exception &e) {
                cerr << "Nao inicializou o endereco corretamente!" << endl;
            }
        }
        Aluno(string nNome, int nIdade, float nNotas[3], int nDia, int nMes, int nAno, string nLog, int nNum, string nComp) {
            setNome(nNome);
            setIdade(nIdade);
            setNotas(nNotas);
            nasc.setData(nDia, nMes, nAno);
            try {
                ende.setLogradouro(nLog);
                ende.setNumero(nNum);
                ende.setComplemento(nComp);
            } catch (exception &e) {
                cerr << e.what();
            } catch (invalid_argument &ex) {
                cerr << "Nao inicializou endereco corretamente" << endl;
            }
        }
        void setNome(string texto) {
            if (texto.length() > 2) nome = texto;
            else cout << "ERRO - Nome com menos de 2 caracteres!" << endl;
        }
        void setIdade(int numero) {
            if (numero > 0) idade = numero;
            else cout << "ERRO - Idade nula ou negativa!" << endl;
        }
        void setNotas(float vet[3]) {
            for (int i = 0; i < 3; i++) {
                if (vet[i] >= 0) notas[i] = vet[i];
                else cout << "ERRO - Nota negativa para prova " << (i + 1) << "!" << endl;
            }
        }
        void preenche() {
            string enter, texto, log, comp;
            int valor, diaN, mesN, anoN, num;
            float val[3];
            cout << "Nome: ";
            getline(cin, texto);
            setNome(texto);
            cout << "Idade: ";
            cin >> valor;
            setIdade(valor);
            cout << "Notas: ";
            for (int i = 0; i < 3; i++) cin >> val[i];
            setNotas(val);
            cout << "Data do nascimento (dd mm aaaa): ";
            cin >> diaN >> mesN >> anoN;
            nasc.setData(diaN, mesN, anoN);
            getline(cin, enter);
            cout << "Logradouro: ";
            getline(cin, log);
            try {
                ende.setLogradouro(texto);
            } catch (invalid_argument &i) {
                cerr << i.what();
            } catch (exception &e) {
                cerr << "Nao inicializou endereco corretamente" << endl;
            }
            cout << "Numero: ";
            cin >> num;
            ende.setNumero(num);
            getline(cin, enter);
            cout << "Complemento: ";
            getline(cin, comp);
            ende.setComplemento(comp);
        }
        void exibe() {
            cout << "Nome: " << getNome() << endl;
            cout << "Idade: " << getIdade() << endl;
            cout << "Notas: ";
            for (int i = 0; i < 3; i++) cout << getNotas()[i] << " ";
            cout << endl;
            cout << "Data de nascimento: " << nasc.getData() << endl;
            cout << "Endereco: " << ende.getEndereco() << endl;
        }
        string getNome() { return nome; }
        int getIdade() { return idade; }
        float *getNotas() { return notas; }
};

class AlunoGrad : public Aluno {
    private:
        string TCC;
    public:
        AlunoGrad() { setTCC("inicializacao"); }
        AlunoGrad(string texto) { setTCC(texto); }
        AlunoGrad(string nomeAluno, int idadeAluno, float notasAluno[3], int diaNasc, int mesNasc, int anoNasc, string logEnd, int numEnd, string compEnd, string tcc)
            : Aluno(nomeAluno, idadeAluno, notasAluno, diaNasc, mesNasc, anoNasc, logEnd, numEnd, compEnd) {
            setTCC(tcc);
        }
        void setTCC(string texto) {
            if (texto.length() > 10) TCC = texto;
            else cout << "ERRO - TCC deve ter mais de 10 caracteres!" << endl;
        }
        string getTCC() { return TCC; }
        void preenche() {
            string texto;
            Aluno::preenche();
            cout << "TCC: ";
            getline(cin, texto);
            setTCC(texto);
        }
        void exibe() {
            Aluno::exibe();
            cout << "TCC: " << getTCC() << endl;
        }
};

void preencheTurma(AlunoGrad turma[2]) {
    cout << endl << "Preenche dados dos alunos" << endl << endl;
    for (int pos = 0; pos < 2; pos++) {
        cout << "Aluno " << (pos + 1) << endl;
        turma[pos].preenche();
        cout << endl;
    }
}

void exibeTurma(AlunoGrad turma[2]) {
    cout << "Exibe dados dos alunos" << endl << endl;
    for (int pos = 0; pos < 2; pos++) {
        cout << "Aluno " << (pos + 1) << endl;
        turma[pos].exibe();
        cout << endl;
    }
}

float mediaIdades(AlunoGrad turma[2]) {
    float soma = 0;
    for (int i = 0; i < 2; i++) soma += turma[i].getIdade();
    return soma / 2;
}

float mediaNotas(AlunoGrad turma[2]) {
    float soma = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) soma += turma[i].getNotas()[j];
    }
    return soma / (2*3);
}

int main() {
    AlunoGrad turma[2];
    preencheTurma(turma);
    exibeTurma(turma);
    float idades = mediaIdades(turma);
    float notas = mediaNotas(turma);
    cout << "A media das idades e " << idades << " anos!" << endl;
    cout << "A media das notas e " << notas << " pontos!" << endl;
}
