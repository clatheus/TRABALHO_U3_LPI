#include "Gerenciador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <set>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;

GerenciadorCaminhos::~GerenciadorCaminhos() {
    for (size_t i = 0; i < cadastroCidades.size(); ++i) {
        delete cadastroCidades[i];
    }
    for (size_t i = 0; i < rotasDisponiveis.size(); ++i) {
        delete rotasDisponiveis[i];
    }
    for (size_t i = 0; i < passageirosCadastrados.size(); ++i) {
        delete passageirosCadastrados[i];
    }

    for (Transporte* t : transportes) delete t;
    for (Viagem* v : viagens) delete v;
}

Cidade* GerenciadorCaminhos::acharCidadePeloNome(const string& nomeAlvo) const {
    for (Cidade* c : cadastroCidades) {
        if (c->getNome() == nomeAlvo) return c;
    }
    return nullptr;
}

bool GerenciadorCaminhos::cadastrarCidade(const string& nome) {
    if (acharCidadePeloNome(nome) != nullptr) {
        cout << "------- AVISO -------\n";
        cout << "Ignorado: '" << nome << "' ja possui cadastro ativo.\n";
        return false;
    }
    cadastroCidades.push_back(new Cidade(nome));
    return true;
}

bool GerenciadorCaminhos::cadastrarTrajeto(const string& nomeOrigem, const string& nomeDestino, char tipo, int distancia) {
    Cidade* destinoPt = acharCidadePeloNome(nomeDestino);
    Cidade* origemPt = acharCidadePeloNome(nomeOrigem);

    if (origemPt == nullptr || destinoPt == nullptr || distancia<=0) {
        cout << "------- ERRO -------";
        cout << "Não é possível linkar o trajeto: Origem ou Destino não existem.\n";
        return false;
    }
    rotasDisponiveis.push_back(new Trajeto(origemPt, destinoPt, tipo, distancia));
    return true;
}

bool GerenciadorCaminhos::existeTrajetoDireto(const string& nomeOrigem, const string& nomeDestino) const {
    for (Trajeto* rota : rotasDisponiveis) {
        if (rota->getOrigem()->getNome() == nomeOrigem && rota->getDestino()->getNome() == nomeDestino) {
            return true;
        }
    }
    return false;
}

vector<Trajeto*> GerenciadorCaminhos::buscarMelhorCaminho(const string& nomeOrigem, const string& nomeDestino) const {
    Cidade* inicio = acharCidadePeloNome(nomeOrigem);
    Cidade* fim = acharCidadePeloNome(nomeDestino);

    if (!inicio || !fim) return {};

    map<Cidade*, int> mapaDeCustos;
    map<Cidade*, Trajeto*> historicoCaminho;
    vector<Cidade*> filaPendentes;

    for (Cidade* c : cadastroCidades) {
        mapaDeCustos[c] = INT_MAX;
        filaPendentes.push_back(c);
    }
    mapaDeCustos[inicio] = 0;

    while (!filaPendentes.empty()) {
        auto menorAlvoIt = filaPendentes.end();
        int menorPesoEncontrado = INT_MAX;

        for (auto it = filaPendentes.begin(); it != filaPendentes.end(); ++it) {
            if (mapaDeCustos[*it] < menorPesoEncontrado) {
                menorPesoEncontrado = mapaDeCustos[*it];
                menorAlvoIt = it;
            }
        }

        if (menorAlvoIt == filaPendentes.end() || menorPesoEncontrado == INT_MAX) {
            break;
        }

        Cidade* atual = *menorAlvoIt;
        filaPendentes.erase(menorAlvoIt);

        if (atual == fim) break;

        for (Trajeto* link : rotasDisponiveis) {
            if (link->getOrigem() == atual) {
                Cidade* proximoNo = link->getDestino();
                int custoCalculado = mapaDeCustos[atual] + link->getDistancia();

                if (custoCalculado < mapaDeCustos[proximoNo]) {
                    mapaDeCustos[proximoNo] = custoCalculado;
                    historicoCaminho[proximoNo] = link;
                }
            }
        }
    }

    vector<Trajeto*> rotaFinal;
    Cidade* rastro = fim;

    while (historicoCaminho.find(rastro) != historicoCaminho.end()) {
        Trajeto* etapa = historicoCaminho[rastro];
        rotaFinal.push_back(etapa);
        rastro = etapa->getOrigem();
    }

    reverse(rotaFinal.begin(), rotaFinal.end());
    return rotaFinal;
}

Passageiro* GerenciadorCaminhos::procuraPassageiro(string cpf) {
    for (Passageiro* p : passageirosCadastrados) { //procura passageiro pelo cpf
        if (p->getCpf() == cpf) {
            return p;
        }
    }
    return nullptr;
}

bool GerenciadorCaminhos::cadastrarPassageiro(std::string nome,  std::string cpf, string nomeCidade){
    if(procuraPassageiro(cpf) != nullptr){
        return false;
    }
    Cidade* cid = nullptr;
    // se não estiver em trânsito busca o objeto da cidade
    if (nomeCidade != "EM_TRANSITO") {
        cid = acharCidadePeloNome(nomeCidade);
        if(cid == nullptr){
            return false; // cidade digitada inválida
        }
    }

    passageirosCadastrados.push_back(new Passageiro(nome, cpf, cid));
    return true;
}

const vector<Cidade*>& GerenciadorCaminhos::getCidades() const {
    return cadastroCidades;
}

const vector<Trajeto*>& GerenciadorCaminhos::getTrajetos() const {
    return rotasDisponiveis;
}

const vector<Passageiro*>& GerenciadorCaminhos::getPassageiros() const {
    return passageirosCadastrados;
}


bool GerenciadorCaminhos::cadastrarTransporte(string nome, char tipo, int capacidade, int velocidade, int distDescanso, int tempoDescanso, string nomeCidade) {
    if(procuraTransporte(nome) != nullptr){
        return false;
    }
    Cidade* cid = nullptr;
    if (nomeCidade != "EM_TRANSITO") {
        cid = acharCidadePeloNome(nomeCidade);
        if(cid == nullptr){
            return false;
        }
    }
    transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distDescanso, tempoDescanso, cid));
    return true;
}

Transporte* GerenciadorCaminhos::procuraTransporte(string nome) {
    for (Transporte* t : transportes) { //procura transporte existente
        if (t->getNome() == nome) {
            return t;
        }
    }
    return nullptr;
}

bool GerenciadorCaminhos::iniciarViagem(string nomeTransporte, vector<string> nomesPassageiros, string nomeOrigem, string nomeDestino) {
    Transporte* t = nullptr;
    for (Transporte* trans : transportes) {
        if (trans->getNome() == nomeTransporte) { t = trans; break; }
    }

    if (!t) { cout << "Erro: Transporte nao encontrado.\n"; return false; }
    Cidade* orig = acharCidadePeloNome(nomeOrigem);
    Cidade* dest = acharCidadePeloNome(nomeDestino);
    if (!orig || !dest) { cout << "Erro: Cidades invalidas.\n"; return false; }
    if (t->getLocalAtual() != orig) { cout << "Erro: Transporte nao esta na origem.\n"; return false; }
    if (nomesPassageiros.size() > (size_t)t->getCapacidade()) { cout << "Erro: Capacidade excedida.\n"; return false; }

    vector<Passageiro*> passSelecionados;
    for (const auto& nome : nomesPassageiros) {
        Passageiro* p = nullptr;
        for (Passageiro* cand : passageirosCadastrados) {
            if (cand->getNome() == nome) { p = cand; break; }
        }
        if (!p || p->getLocalAtual() != orig) {
            cout << "Erro: Passageiro '" << nome << "' invalido ou fora da origem.\n";
            return false;
        }
        passSelecionados.push_back(p);
    }

    vector<Trajeto*> rota = buscarMelhorCaminho(nomeOrigem, nomeDestino);
    if (rota.empty()) { cout << "Erro: Caminho inviavel.\n"; return false; }

    for (Trajeto* tr : rota) {
        if (tr->getTipo() != t->getTipo()) {
            cout << "Erro: Modal de transporte incompativel com o trajeto.\n";
            return false;
        }
    }

    Viagem* primeiraViagem = nullptr;
    Viagem* viagemAnterior = nullptr;

    for (Trajeto* tr : rota) {
        Viagem* novaPerna = new Viagem(t, passSelecionados, tr->getOrigem(), tr->getDestino(), tr->getDistancia());
        viagens.push_back(novaPerna);

        if (!primeiraViagem) {
            primeiraViagem = novaPerna;
        } else {
            viagemAnterior->setProxima(novaPerna);
        }
        viagemAnterior = novaPerna;
    }

    if (primeiraViagem) {
        primeiraViagem->iniciarViagem();
    }

    return true;
}
//----------------------------
void GerenciadorCaminhos::avancarHoras(int horas) {
    for (int h = 0; h < horas; ++h) {
        set<Transporte*> transportesMovidosNestaHora;
        for (Viagem* v : viagens) {
            if (v->isEmAndamento() && transportesMovidosNestaHora.find(v->getTransporte()) == transportesMovidosNestaHora.end()) {
                transportesMovidosNestaHora.insert(v->getTransporte());
                v->avancarHoras(1);

                if (!v->isEmAndamento() && v->getProxima() == nullptr) {
                    visitasCidades[v->getDestino()->getNome()];
                }
            }
        }
    }
}

//relatorios
void GerenciadorCaminhos::relatarEstado() {
    cout << "\n------- RELATORIOS OBRIGATORIOS -------\n";

    cout << "\n[1] LOCALIZACAO DE CADA PASSAGEIRO:\n";
    for (Passageiro* p : passageirosCadastrados) {
        cout << " - " << p->getNome() << ": ";
        if (p->getLocalAtual() != nullptr) {
            cout << "Na cidade de " << p->getLocalAtual()->getNome() << "\n";
        } else {
            for (Viagem* v : viagens) {
                if (v->isEmAndamento()) {
                    for (Passageiro* vp : v->getPassageiros()) {
                        if (vp->getNome() == p->getNome()) {
                            cout << "EM TRANSITO (" << v->getOrigem()->getNome() << " -> "
                                 << v->getDestino()->getNome() << ") no transporte: "
                                 << v->getTransporte()->getNome() << "\n";
                        }
                    }
                }
            }
        }
    }

    cout << "\n[2] LOCALIZACAO DE CADA TRANSPORTE:\n";
    for (Transporte* t : transportes) {
        cout << " - " << t->getNome() << " [" << t->getTipo() << "]: ";
        if (t->getLocalAtual() != nullptr) {
            cout << "Estacionado em " << t->getLocalAtual()->getNome() << "\n";
        } else {
            for (Viagem* v : viagens) {
                if (v->isEmAndamento() && v->getTransporte() == t) {
                    cout << "EM TRANSITO de " << v->getOrigem()->getNome() << " para " << v->getDestino()->getNome();
                    if (t->estaEmDescanso()) cout << " [PARADO EM DESCANSO]";
                    cout << "\n";
                }
            }
        }
    }

    cout << "\n[3] VIAGENS EM ANDAMENTO:\n";
    bool nenhumaAtiva = true;
    for (Viagem* v : viagens) {
        if (v->isEmAndamento()) {
            v->relatarEstado();
            nenhumaAtiva = false;
        }
    }
    if (nenhumaAtiva) cout << " Nenhuma viagem ativa no momento.\n";

    cout << "\n[4] CIDADES MAIS VISITADAS (RANKING DE CHEGADAS FINAIS):\n";
    if (visitasCidades.empty()) {
        cout << " Nenhuma chegada registrada ainda.\n";
    } else {
        for (const auto& par : visitasCidades) {
            cout << " - " << par.first << ": " << par.second << " visitas\n";
        }
    }
    cout << "---------------------------------------------\n\n";
}

const vector<Transporte*>& GerenciadorCaminhos::getTransportes() const { return transportes; }
const vector<Viagem*>& GerenciadorCaminhos::getViagens() const { return viagens; }

//SALVAR DADOS
void GerenciadorCaminhos::salvarDados(const string& prefixo) const {
    string pasta = "data/";
    std::filesystem::create_directories(pasta);
    ofstream fCidades(pasta + prefixo + "_cidades.csv");
    for (Cidade* c : cadastroCidades) fCidades << c->getNome() << "\n";

    ofstream fTrajetos(pasta + prefixo + "_trajetos.csv");
    for (Trajeto* t : rotasDisponiveis) fTrajetos << t->getOrigem()->getNome() << "," << t->getDestino()->getNome() << "," << t->getTipo() << "," << t->getDistancia() << "\n";

    ofstream fPassageiros(pasta + prefixo + "_passageiros.csv");
    for (Passageiro* p : passageirosCadastrados) fPassageiros << p->getNome() << "," << p->getCpf() << ","<< (p->getLocalAtual() ? p->getLocalAtual()->getNome() : "EM_TRANSITO") << "\n";

    ofstream fTransportes(pasta + prefixo + "_transportes.csv");
    for (Transporte* t : transportes) fTransportes << t->getNome() << "," << t->getTipo() << "," << t->getCapacidade() << "," << t->getVelocidade() << "," << t->getDistanciaEntreDescansos() << "," << t->getTempoDescanso() << "," << (t->getLocalAtual() ? t->getLocalAtual()->getNome() : "EM_TRANSITO") << "," << t->getTempoDescansoAtual() << "\n";

    ofstream fViagens(pasta + prefixo + "_viagens.csv");
    for (size_t i = 0; i < viagens.size(); ++i) {
        Viagem* v = viagens[i];
        fViagens << v->getTransporte()->getNome() << "," << v->getOrigem()->getNome() << "," << v->getDestino()->getNome() << "," << v->getHorasEmTransito() << "," << v->isEmAndamento() << "," << v->getDistanciaPercorrida() << "," << v->getDistanciaTotal() << ",";

        int idxProx = -1;
        if (v->getProxima() != nullptr) {
            for (size_t j = 0; j < viagens.size(); ++j) {
                if (viagens[j] == v->getProxima()) { idxProx = j; break; }
            }
        }
        fViagens << idxProx << ",";

        for (size_t k = 0; k < v->getPassageiros().size(); ++k) {
            fViagens << v->getPassageiros()[k]->getNome() << (k == v->getPassageiros().size() - 1 ? "" : ";");
        }
        fViagens << "\n";
    }
}
//CARREGAR DADOS
void GerenciadorCaminhos::carregarDados(const string& prefixo) {
    string linha;
    string pasta = "data/";
    ifstream fCidades(pasta + prefixo + "_cidades.csv");
    while (getline(fCidades, linha)) { if (!linha.empty()) cadastrarCidade(linha); }

    ifstream fTrajetos(pasta + prefixo + "_trajetos.csv");
    while (getline(fTrajetos, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        string o, d, t, dist;
        getline(ss, o, ','); getline(ss, d, ','); getline(ss, t, ','); getline(ss, dist, ',');
        cadastrarTrajeto(o, d, t[0], stoi(dist));
    }

    ifstream fPassageiros(pasta + prefixo + "_passageiros.csv");
    while (getline(fPassageiros, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        string n, cid, cpf;
        getline(ss, n, ','); getline(ss, cpf, ',');getline(ss, cid, ',');
        cadastrarPassageiro(n, cpf,cid);
    }

    ifstream fTransportes(pasta + prefixo + "_transportes.csv");
    while (getline(fTransportes, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        string n, t, cap, vel, distD, tempD,tempDAt,cid;
        getline(ss, n, ','); getline(ss, t, ','); getline(ss, cap, ','); getline(ss, vel, ',');
        getline(ss, distD, ','); getline(ss, tempD, ',');getline(ss, cid, ','); getline(ss, tempDAt, ',');

        cadastrarTransporte(n, t[0], stoi(cap), stoi(vel), stoi(distD), stoi(tempD),cid);
        for (Transporte* trans : transportes) {
            if (trans->getNome() == n) {
                trans->setTempoDescansoAtual(stoi(tempDAt));
                //if (cid == "EM_TRANSITO") trans->setLocalAtual(nullptr);
                break;
            }
        }
    }

    ifstream fViagens(pasta + prefixo + "_viagens.csv");
    vector<int> proximosIndices;

    while (getline(fViagens, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        string nT, o, d, hT, emAnd, distP, distT, idxProx, passs;
        getline(ss, nT, ','); getline(ss, o, ','); getline(ss, d, ',');
        getline(ss, hT, ','); getline(ss, emAnd, ','); getline(ss, distP, ',');
        getline(ss, distT, ','); getline(ss, idxProx, ','); getline(ss, passs, ',');

        Transporte* trans = nullptr;
        for (Transporte* tr : transportes) { if (tr->getNome() == nT) { trans = tr; break; } }

        vector<Passageiro*> pLista;
        stringstream ssP(passs);
        string singleNome;
        while (getline(ssP, singleNome, ';')) {
            for (Passageiro* pCand : passageirosCadastrados) {
                if (pCand->getNome() == singleNome) { pLista.push_back(pCand); break; }
            }
        }

        Cidade* cOrig = acharCidadePeloNome(o);
        Cidade* cDest = acharCidadePeloNome(d);

        if (trans && cOrig && cDest) {
            Viagem* v = new Viagem(trans, pLista, cOrig, cDest, stoi(distT));
            v->setHorasEmTransito(stoi(hT));
            v->setEmAndamento(stoi(emAnd) != 0);
            v->setDistanciaPercorrida(stoi(distP));
            viagens.push_back(v);
            proximosIndices.push_back(stoi(idxProx));

            if (!v->isEmAndamento() && stoi(idxProx) == -1) {
                visitasCidades[cDest->getNome()]++;
            }
        }
    }

    for (size_t i = 0; i < viagens.size(); ++i) {
        if (proximosIndices[i] != -1 && (size_t)proximosIndices[i] < viagens.size()) {
            viagens[i]->setProxima(viagens[proximosIndices[i]]);
        }
    }
}

int GerenciadorCaminhos::getVisitasCidades(const std::string& nomeCidade) const {
    auto it = visitasCidades.find(nomeCidade);
    if (it != visitasCidades.end()) {
        return it->second;
    }
    return 0; // Se não foi visitada ainda, o total é 0
}