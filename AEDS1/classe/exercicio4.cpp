#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class Imovel {
    private:
        string proprietario, quadra;
        int lote, situacao;
        float area, v_venda, v_comissao;
        void inicializa(string prop, string quad, int lot, int sit, float ar, float venda, float comissao) {
            setProprietario(prop);
            setQuadra(quad);
            setLote(lot);
            setSituacao(sit);
            setArea(ar);
            setVenda(venda);
            setComissao(comissao);
        }
    public:
        Imovel() { inicializa("nenhum", "nenhuma", 1, 1, 1, 1, 0); }
        Imovel(string prop, string quad, int lot, int sit, float ar, float venda, float comissao) { inicializa(prop, quad, lot, sit, ar, venda, comissao); }
        void setProprietario(string prop) {
            try {
                if (prop.length() > 2) proprietario = prop;
                else throw invalid_argument("Proprietario invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        string getProprietario() { return proprietario; }
        void setQuadra(string quad) {
            try {
                if (quad.length() > 2) quadra = quad;
                else throw invalid_argument("Proprietario invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        string getQuadra() { return quadra; }
        void setLote(int lot) {
            try {
                if (lot > 0) lote = lot;
                else throw invalid_argument("Lote invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        int getLote() { return lote; }
        void setSituacao(int sit) {
            try {
                if (sit > 0) situacao = sit;
                else throw invalid_argument("Situacao invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        int getSituacao() { return situacao; }
        void setArea(float ar) {
            try {
                if (ar > 0) area = ar;
                else throw invalid_argument("Area invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getArea() { return area; }
        void setVenda(float venda) {
            try {
                if (venda > 0) v_venda = venda;
                else throw invalid_argument("Valor de venda invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getVenda() { return v_venda; }
        void setComissao(float comissao) {
            try {
                if (comissao > 0) v_comissao = comissao;
                else throw invalid_argument("Valor de comissao invalido!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getComissao() { return v_comissao; }
        virtual float calcularIptu() {}
};

class Casa : public Imovel {
    private:
        float a_construida;
    public:
        Casa() : Imovel() {
            setAreaConstruida(1);
        }
        Casa(string prop, string quad, int lot, int sit, float ar, float venda, float comissao, float constr)
            : Imovel(prop, quad, lot, sit, ar, venda, comissao) {
            setAreaConstruida(constr);
        }
        void setAreaConstruida(float constr) {
            try {
                if (constr < getArea()) a_construida = constr;
                else throw invalid_argument("Area construida invalida!");
            } catch (exception &e) { cerr << e.what() << endl; }
        }
        float getAreaConstruida() { return a_construida; }
        float calcularIptu() { return getVenda() * 0.01; }
};

class Terreno : public Imovel {
    public:
        Terreno() : Imovel() {}
        Terreno(string prop, string quad, int lot, int sit, float ar, float venda, float comissao)
            : Imovel(prop, quad, lot, sit, ar, venda, comissao) {}
        float calcularIptu() { return getVenda() * 0.02; }
};

int menu() {
    int opcao;
    cout << endl << "Menu:" << endl << endl;
    cout << "1 - Cadastrar imovel" << endl;
    cout << "2 - Alterar situacao" << endl;
    cout << "3 - Mostrar somatorio dos valores" << endl;
    cout << "4 - Mostrar somatorio das comissoes" << endl;
    cout << "5 - Sair" << endl << endl;
    cout << "Insira a opcao desejada: ";
    cin >> opcao; return opcao;
}

Casa geraNovaCasa() {
    string prop, quad;
    int lot, sit;
    float ar, venda, comissao = 0, constr;
    cout << "Proprietario: "; cin >> prop;
    cout << "Quadra: "; cin >> quad;
    cout << "Lote: "; cin >> lot;
    cout << "Area: "; cin >> ar;
    cout << "Valor de venda: "; cin >> venda;
    cout << "Situacao (1 - a venda, 2 - vendido, 3 - em negociacao): "; cin >> sit;
    if (sit == 2) {
        float percent;
        cout << "Percentual de comissao (<= 10%): ";
        cin >> percent;
        if (percent > 10 || percent < 0) {
            cout << "Percentual invalido!" << endl;
            getchar();
            throw invalid_argument("Percentual de comissao invalido!");
        }
        comissao = venda * (percent / 100);
    }
    cout << "Area construida: ";
    cin >> constr;
    return Casa(prop, quad, lot, sit, ar, venda, comissao, constr);
}

Terreno geraNovoTerreno() {
    string prop, quad;
    int lot, sit;
    float ar, venda, comissao = 0;
    cout << "Proprietario: ";
    cin >> prop;
    cout << "Quadra: ";
    cin >> quad;
    cout << "Lote: ";
    cin >> lot;
    cout << "Area: ";
    cin >> ar;
    cout << "Valor de venda: ";
    cin >> venda;
    cout << "Situacao (1 - a venda, 2 - vendido, 3 - em negociacao): ";
    cin >> sit;
    if (sit == 2) {
        float percent;
        cout << "Percentual de comissao (<= 10%): ";
        cin >> percent;
        if (percent > 10 || percent < 0) {
            cout << "Percentual invalido!" << endl;
            getchar();
            throw invalid_argument("Percentual de comissao invalido!");
        }
        comissao = venda * (percent / 100);
    }
    return Terreno(prop, quad, lot, sit, ar, venda, comissao);
}

int cadastraNovoImovel(Imovel *imoveis[], int contImovel, Imovel *novoImovel) {
    if (contImovel >= 30) {
        cout << "Limite de 30 imoveis atingido!" << endl;
        getchar();
        delete novoImovel;
        return contImovel;
    }
    imoveis[contImovel] = novoImovel;
    cout << (dynamic_cast<Casa *>(novoImovel) ? "Casa" : "Terreno") << " cadastrado com sucesso!" << endl;
    getchar();
    return contImovel + 1;
}

void alterarSituacaoImovel(Imovel *imoveis[], int contImovel) {
    if (contImovel == 0) {
        cout << "Nenhum imovel cadastrado!" << endl;
        getchar();
        return;
    }
    cout << endl << "Imoveis cadastrados:" << endl;
    for (int i = 0; i < contImovel; i++) {
        cout << (dynamic_cast<Casa *>(imoveis[i]) ? "Casa" : "Terreno") << " " << i
             << ": " << imoveis[i]->getProprietario() << ", Quadra " << imoveis[i]->getQuadra()
             << ", Lote " << imoveis[i]->getLote() << ", Situacao " << imoveis[i]->getSituacao() << endl;
    }
    int idx;
    cout << "Indice do imovel (0 a " << contImovel - 1 << "): ";
    cin >> idx;
    if (idx < 0 || idx >= contImovel) {
        cout << "Indice invalido!" << endl;
        getchar();
        return;
    }
    int novaSit;
    cout << "Nova situacao (1 - a venda, 2 - vendido, 3 - em negociacao): ";
    cin >> novaSit;
    if (novaSit == 1 || novaSit == 3) imoveis[idx]->setComissao(0);
    else if (novaSit == 2) {
        float percent;
        cout << "Percentual de comissao (<= 10%): ";
        cin >> percent;
        if (percent > 10 || percent < 0) {
            cout << "Percentual invalido!" << endl;
            getchar();
            return;
        }
        float comissao = imoveis[idx]->getVenda() * (percent / 100);
        imoveis[idx]->setComissao(comissao);
    }
    imoveis[idx]->setSituacao(novaSit);
    cout << "Situacao alterada com sucesso!" << endl;
    getchar();
}

float gerarValorTotalDosImoveis(Imovel* imoveis[], int contImovel) {
    float total = 0;
    for (int i = 0; i < contImovel; i++) total += imoveis[i]->getVenda();
    return total;
}

float gerarValorTotalComissaoImoveis(Imovel *imoveis[], int contImovel) {
    float total = 0;
    for (int i = 0; i < contImovel; i++) total += imoveis[i]->getComissao();
    return total;
}

int main() {
    Imovel *imoveis[30];
    int contImovel = 0, opcao;
    do {
        opcao = menu();
        if (opcao == 1) {
            int tipo;
            cout << "Escolha o tipo de imovel:" << endl << "1 - Casa "<< endl << "2 - Terreno: " << endl; cin >> tipo;
            try {
                if (tipo == 1) {
                    Casa *auxCasa = new Casa(geraNovaCasa());
                    contImovel = cadastraNovoImovel(imoveis, contImovel, auxCasa);
                } else if (tipo == 2) {
                    Terreno *auxTerreno = new Terreno(geraNovoTerreno());
                    contImovel = cadastraNovoImovel(imoveis, contImovel, auxTerreno);
                } else {
                    cout << "Escolha Errada. Observe os tipos de imoveis validos!" << endl;
                    getchar();
                }
            } catch (exception &e) {
                cout << "Erro ao cadastrar: " << e.what() << endl;
                getchar();
            }
        }
        if (opcao == 2) alterarSituacaoImovel(imoveis, contImovel);
        if (opcao == 3) {
            float valorTotalImoveis = gerarValorTotalDosImoveis(imoveis, contImovel);
            cout << fixed << setprecision(2);
            cout << "O somatorio do valor de venda dos imoveis e R$ " << valorTotalImoveis << endl;
            getchar();
        }
        if (opcao == 4) {
            float valorTotalComissoes = gerarValorTotalComissaoImoveis(imoveis, contImovel);
            cout << fixed << setprecision(2);
            cout << "O somatorio do valor das comissoes dos imoveis vendidos e R$ " << valorTotalComissoes << endl;
            getchar();
        }
        if (opcao == 5) {
            cout << "Finalizando execucao da aplicacao." << endl;
            getchar();
        }
        if (opcao < 1 || opcao > 5) {
            cout << "Opcao invalida." << endl;
            getchar();
        }
    } while (opcao != 5);
    for (int i = 0; i < contImovel; i++) delete imoveis[i];
}
