#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Astronauta {
private:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

public:
    Astronauta(string cpf, string nome, int idade) {
        this->cpf = cpf;
        this->nome = nome;
        this->idade = idade;
        vivo = true;
        disponivel = true;
    }

    Astronauta(string cpf, string nome, int idade, bool vivo, bool disponivel) {
        this->cpf = cpf;
        this->nome = nome;
        this->idade = idade;
        this->vivo = vivo;
        this->disponivel = disponivel;
    }

    string getCpf() const { return cpf; }
    string getNome() const { return nome; }
    int getIdade() const { return idade; }
    bool estaVivo() const { return vivo; }
    bool estaDisponivel() const { return disponivel; }

    void embarcar() { disponivel = false; }

    void desembarcar() {
        if (vivo) {
            disponivel = true;
        }
    }

    void morrer() {
        vivo = false;
        disponivel = false;
    }
};

class Voo {
private:
    int codigo;
    string estado;
    vector<string> cpfs;

public:
    Voo(int codigo) {
        this->codigo = codigo;
        estado = "planejado";
    }

    int getCodigo() const { return codigo; }
    string getEstado() const { return estado; }
    int getQuantidadeAstronautas() const { return cpfs.size(); }
    string getCpf(int posicao) const { return cpfs[posicao]; }

    bool temAstronauta(string cpf) const {
        for (int i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) {
                return true;
            }
        }
        return false;
    }

    void adicionarAstronauta(string cpf) { cpfs.push_back(cpf); }

    bool removerAstronauta(string cpf) {
        for (int i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) {
                cpfs.erase(cpfs.begin() + i);
                return true;
            }
        }
        return false;
    }

    void setEstado(string novoEstado) { estado = novoEstado; }
    void lancar() { estado = "em curso"; }
    void explodir() { estado = "finalizado com explosao"; }
    void finalizar() { estado = "finalizado com sucesso"; }
};

class Agencia {
private:
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    int buscarAstronauta(string cpf) {
        for (int i = 0; i < astronautas.size(); i++) {
            if (astronautas[i].getCpf() == cpf) {
                return i;
            }
        }
        return -1;
    }

    int buscarVoo(int codigo) {
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].getCodigo() == codigo) {
                return i;
            }
        }
        return -1;
    }

    bool participou(int posVoo, string cpf) {
        return voos[posVoo].getEstado() != "planejado" && voos[posVoo].temAstronauta(cpf);
    }

    int voosLancados(string cpf) {
        int total = 0;
        for (int i = 0; i < voos.size(); i++) {
            if (participou(i, cpf)) {
                total++;
            }
        }
        return total;
    }

    int vooEmCurso(string cpf) {
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].getEstado() == "em curso" && voos[i].temAstronauta(cpf)) {
                return voos[i].getCodigo();
            }
        }
        return -1;
    }

    int contarVoos(string estado) {
        int total = 0;
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].getEstado() == estado) {
                total++;
            }
        }
        return total;
    }

    void montarVooDemo(int codigo, vector<string> cpfs, string estado) {
        Voo voo(codigo);
        for (int i = 0; i < cpfs.size(); i++) {
            voo.adicionarAstronauta(cpfs[i]);
        }
        voo.setEstado(estado);
        voos.push_back(voo);
        for (int i = 0; i < cpfs.size(); i++) {
            int pos = buscarAstronauta(cpfs[i]);
            if (estado == "em curso") {
                astronautas[pos].embarcar();
            } else if (estado == "finalizado com explosao") {
                astronautas[pos].morrer();
            }
        }
    }

public:
    void cadastrarAstronauta(string cpf, string nome, int idade) {
        if (buscarAstronauta(cpf) != -1) {
            cout << "ERRO: astronauta com CPF " << cpf << " ja cadastrado" << endl;
            return;
        }
        astronautas.push_back(Astronauta(cpf, nome, idade));
        cout << "OK: astronauta " << cpf << " cadastrado" << endl;
    }

    void cadastrarVoo(int codigo) {
        if (buscarVoo(codigo) != -1) {
            cout << "ERRO: voo " << codigo << " ja cadastrado" << endl;
            return;
        }
        voos.push_back(Voo(codigo));
        cout << "OK: voo " << codigo << " cadastrado" << endl;
    }

    void adicionarAstronauta(string cpf, int codigo) {
        int a = buscarAstronauta(cpf);
        if (a == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        int v = buscarVoo(codigo);
        if (v == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[v].getEstado() != "planejado") {
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if (!astronautas[a].estaVivo()) {
            cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
            return;
        }
        if (voos[v].temAstronauta(cpf)) {
            cout << "ERRO: astronauta " << cpf << " ja esta no voo " << codigo << endl;
            return;
        }
        voos[v].adicionarAstronauta(cpf);
        cout << "OK: astronauta " << cpf << " adicionado ao voo " << codigo << endl;
    }

    void removerAstronauta(string cpf, int codigo) {
        int a = buscarAstronauta(cpf);
        if (a == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        int v = buscarVoo(codigo);
        if (v == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[v].getEstado() != "planejado") {
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if (!voos[v].removerAstronauta(cpf)) {
            cout << "ERRO: astronauta " << cpf << " nao esta no voo " << codigo << endl;
            return;
        }
        cout << "OK: astronauta " << cpf << " removido do voo " << codigo << endl;
    }

    void lancarVoo(int codigo) {
        int v = buscarVoo(codigo);
        if (v == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[v].getEstado() != "planejado") {
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if (voos[v].getQuantidadeAstronautas() == 0) {
            cout << "ERRO: voo " << codigo << " nao possui astronautas" << endl;
            return;
        }
        for (int i = 0; i < voos[v].getQuantidadeAstronautas(); i++) {
            string cpf = voos[v].getCpf(i);
            int a = buscarAstronauta(cpf);
            if (!astronautas[a].estaVivo()) {
                cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
                return;
            }
            if (!astronautas[a].estaDisponivel()) {
                cout << "ERRO: astronauta " << cpf << " esta indisponivel" << endl;
                return;
            }
        }
        for (int i = 0; i < voos[v].getQuantidadeAstronautas(); i++) {
            astronautas[buscarAstronauta(voos[v].getCpf(i))].embarcar();
        }
        voos[v].lancar();
        cout << "OK: voo " << codigo << " lancado" << endl;
    }

    void explodirVoo(int codigo) {
        int v = buscarVoo(codigo);
        if (v == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[v].getEstado() != "em curso") {
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }
        for (int i = 0; i < voos[v].getQuantidadeAstronautas(); i++) {
            astronautas[buscarAstronauta(voos[v].getCpf(i))].morrer();
        }
        voos[v].explodir();
        cout << "OK: voo " << codigo << " explodiu" << endl;
    }

    void finalizarVoo(int codigo) {
        int v = buscarVoo(codigo);
        if (v == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[v].getEstado() != "em curso") {
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }
        for (int i = 0; i < voos[v].getQuantidadeAstronautas(); i++) {
            astronautas[buscarAstronauta(voos[v].getCpf(i))].desembarcar();
        }
        voos[v].finalizar();
        cout << "OK: voo " << codigo << " finalizado com sucesso" << endl;
    }

    void listarVoos() {
        string estados[4] = {"planejado", "em curso", "finalizado com sucesso", "finalizado com explosao"};
        cout << "LISTA DE VOOS" << endl;
        for (int e = 0; e < 4; e++) {
            cout << "== " << estados[e] << " ==" << endl;
            bool algum = false;
            for (int i = 0; i < voos.size(); i++) {
                if (voos[i].getEstado() != estados[e]) {
                    continue;
                }
                algum = true;
                cout << "Voo " << voos[i].getCodigo() << ": ";
                if (voos[i].getQuantidadeAstronautas() == 0) {
                    cout << "sem astronautas";
                }
                for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                    if (j > 0) {
                        cout << ", ";
                    }
                    string cpf = voos[i].getCpf(j);
                    cout << cpf << " " << astronautas[buscarAstronauta(cpf)].getNome();
                }
                cout << endl;
            }
            if (!algum) {
                cout << "(nenhum)" << endl;
            }
        }
    }

    void listarMortos() {
        cout << "ASTRONAUTAS MORTOS" << endl;
        bool algum = false;
        for (int i = 0; i < astronautas.size(); i++) {
            if (astronautas[i].estaVivo()) {
                continue;
            }
            algum = true;
            cout << astronautas[i].getCpf() << " " << astronautas[i].getNome() << " - voos:";
            bool voou = false;
            for (int j = 0; j < voos.size(); j++) {
                if (participou(j, astronautas[i].getCpf())) {
                    cout << " " << voos[j].getCodigo();
                    voou = true;
                }
            }
            if (!voou) {
                cout << " nenhum";
            }
            cout << endl;
        }
        if (!algum) {
            cout << "(nenhum)" << endl;
        }
    }

    void listarAstronautas() {
        cout << "LISTA DE ASTRONAUTAS" << endl;
        cout << "== disponiveis ==" << endl;
        bool algum = false;
        for (int i = 0; i < astronautas.size(); i++) {
            if (astronautas[i].estaVivo() && vooEmCurso(astronautas[i].getCpf()) == -1) {
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome()
                     << " (" << astronautas[i].getIdade() << " anos)" << endl;
                algum = true;
            }
        }
        if (!algum) {
            cout << "(nenhum)" << endl;
        }
        cout << "== em voo ==" << endl;
        algum = false;
        for (int i = 0; i < astronautas.size(); i++) {
            int codigo = vooEmCurso(astronautas[i].getCpf());
            if (astronautas[i].estaVivo() && codigo != -1) {
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome()
                     << " (" << astronautas[i].getIdade() << " anos) - voo " << codigo << endl;
                algum = true;
            }
        }
        if (!algum) {
            cout << "(nenhum)" << endl;
        }
        cout << "== mortos ==" << endl;
        algum = false;
        for (int i = 0; i < astronautas.size(); i++) {
            if (!astronautas[i].estaVivo()) {
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome()
                     << " (" << astronautas[i].getIdade() << " anos)" << endl;
                algum = true;
            }
        }
        if (!algum) {
            cout << "(nenhum)" << endl;
        }
    }

    void historico(string cpf) {
        int a = buscarAstronauta(cpf);
        if (a == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        cout << "HISTORICO DE " << cpf << " " << astronautas[a].getNome() << endl;
        bool algum = false;
        for (int i = 0; i < voos.size(); i++) {
            if (participou(i, cpf)) {
                cout << "voo " << voos[i].getCodigo() << ": " << voos[i].getEstado() << endl;
                algum = true;
            }
        }
        if (!algum) {
            cout << "(nenhum voo)" << endl;
        }
    }

    void salvar(string arquivo) {
        ofstream saida(arquivo.c_str());
        if (!saida.is_open()) {
            cout << "ERRO: nao foi possivel salvar em " << arquivo << endl;
            return;
        }
        for (int i = 0; i < astronautas.size(); i++) {
            saida << "ASTRONAUTA " << astronautas[i].getCpf() << " " << astronautas[i].getIdade()
                  << " " << (astronautas[i].estaVivo() ? 1 : 0)
                  << " " << (astronautas[i].estaDisponivel() ? 1 : 0)
                  << " " << astronautas[i].getNome() << endl;
        }
        for (int i = 0; i < voos.size(); i++) {
            saida << "VOO " << voos[i].getCodigo() << endl;
            saida << "ESTADO " << voos[i].getEstado() << endl;
            saida << "CPFS";
            for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                saida << " " << voos[i].getCpf(j);
            }
            saida << endl;
        }
        saida.close();
        if (saida.fail()) {
            cout << "ERRO: nao foi possivel salvar em " << arquivo << endl;
            return;
        }
        cout << "OK: dados salvos em " << arquivo << endl;
    }

    void carregar(string arquivo) {
        ifstream entrada(arquivo.c_str());
        if (!entrada.is_open()) {
            cout << "ERRO: nao foi possivel carregar de " << arquivo << endl;
            return;
        }
        vector<Astronauta> novosAstronautas;
        vector<Voo> novosVoos;
        bool valido = true;
        string linha;
        while (valido && getline(entrada, linha)) {
            istringstream ss(linha);
            string tag;
            if (!(ss >> tag)) {
                continue;
            }
            if (tag == "ASTRONAUTA") {
                string cpf, nome;
                int idade, vivo, disponivel;
                if (!(ss >> cpf >> idade >> vivo >> disponivel)) {
                    valido = false;
                    break;
                }
                getline(ss >> ws, nome);
                novosAstronautas.push_back(Astronauta(cpf, nome, idade, vivo == 1, disponivel == 1));
            } else if (tag == "VOO") {
                int codigo;
                if (!(ss >> codigo)) {
                    valido = false;
                    break;
                }
                novosVoos.push_back(Voo(codigo));
            } else if (tag == "ESTADO" && !novosVoos.empty()) {
                string estado;
                getline(ss >> ws, estado);
                if (estado != "planejado" && estado != "em curso" &&
                    estado != "finalizado com sucesso" && estado != "finalizado com explosao") {
                    valido = false;
                    break;
                }
                novosVoos.back().setEstado(estado);
            } else if (tag == "CPFS" && !novosVoos.empty()) {
                string cpf;
                while (ss >> cpf) {
                    novosVoos.back().adicionarAstronauta(cpf);
                }
            } else {
                valido = false;
            }
        }
        if (!valido) {
            cout << "ERRO: nao foi possivel carregar de " << arquivo << endl;
            return;
        }
        astronautas = novosAstronautas;
        voos = novosVoos;
        cout << "OK: dados carregados de " << arquivo << endl;
    }

    void relatorio() {
        int sucessos = contarVoos("finalizado com sucesso");
        int explosoes = contarVoos("finalizado com explosao");
        int vivos = 0;
        int mortos = 0;
        int melhor = -1;
        int melhorVoos = 0;
        for (int i = 0; i < astronautas.size(); i++) {
            if (astronautas[i].estaVivo()) {
                vivos++;
            } else {
                mortos++;
            }
            int n = voosLancados(astronautas[i].getCpf());
            if (n > melhorVoos) {
                melhorVoos = n;
                melhor = i;
            }
        }
        cout << "RELATORIO" << endl;
        cout << "voos planejados: " << contarVoos("planejado") << endl;
        cout << "voos em curso: " << contarVoos("em curso") << endl;
        cout << "voos finalizados com sucesso: " << sucessos << endl;
        cout << "voos finalizados com explosao: " << explosoes << endl;
        cout << "astronautas cadastrados: " << astronautas.size() << endl;
        cout << "astronautas vivos: " << vivos << endl;
        cout << "astronautas mortos: " << mortos << endl;
        if (melhor == -1) {
            cout << "astronauta mais experiente: (nenhum)" << endl;
        } else {
            cout << "astronauta mais experiente: " << astronautas[melhor].getCpf() << " "
                 << astronautas[melhor].getNome() << " (voos lancados: " << melhorVoos << ")" << endl;
        }
        int finalizados = sucessos + explosoes;
        if (finalizados == 0) {
            cout << "taxa de sucesso: (nenhum voo finalizado)" << endl;
        } else {
            cout << "taxa de sucesso: " << (sucessos * 100 / finalizados) << "%" << endl;
        }
    }

    void demo() {
        astronautas.clear();
        voos.clear();
        astronautas.push_back(Astronauta("111", "Ana Maria", 30));
        astronautas.push_back(Astronauta("222", "Bruno Costa", 35));
        astronautas.push_back(Astronauta("333", "Carla Souza", 28));
        astronautas.push_back(Astronauta("444", "Diego Lima", 41));
        astronautas.push_back(Astronauta("555", "Elisa Rocha", 33));
        vector<string> tripulacao;
        tripulacao.push_back("111");
        tripulacao.push_back("222");
        montarVooDemo(10, tripulacao, "finalizado com sucesso");
        tripulacao.clear();
        tripulacao.push_back("333");
        tripulacao.push_back("444");
        montarVooDemo(20, tripulacao, "finalizado com explosao");
        tripulacao.clear();
        tripulacao.push_back("111");
        tripulacao.push_back("555");
        montarVooDemo(30, tripulacao, "em curso");
        tripulacao.clear();
        tripulacao.push_back("222");
        montarVooDemo(40, tripulacao, "planejado");
        cout << "OK: cenario de demonstracao carregado" << endl;
    }
};

int main() {
    Agencia agencia;
    string comando;

    while (cin >> comando) {
        if (comando == "FIM") {
            break;
        } else if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);
            agencia.cadastrarAstronauta(cpf, nome, idade);
        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.cadastrarVoo(codigo);
        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.adicionarAstronauta(cpf, codigo);
        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.removerAstronauta(cpf, codigo);
        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.lancarVoo(codigo);
        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.explodirVoo(codigo);
        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.finalizarVoo(codigo);
        } else if (comando == "LISTAR_VOOS") {
            agencia.listarVoos();
        } else if (comando == "LISTAR_MORTOS") {
            agencia.listarMortos();
        } else if (comando == "LISTAR_ASTRONAUTAS") {
            agencia.listarAstronautas();
        } else if (comando == "HISTORICO") {
            string cpf;
            cin >> cpf;
            agencia.historico(cpf);
        } else if (comando == "SALVAR") {
            string arquivo;
            cin >> arquivo;
            agencia.salvar(arquivo);
        } else if (comando == "CARREGAR") {
            string arquivo;
            cin >> arquivo;
            agencia.carregar(arquivo);
        } else if (comando == "RELATORIO") {
            agencia.relatorio();
        } else if (comando == "DEMO") {
            agencia.demo();
        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}
