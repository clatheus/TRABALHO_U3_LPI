#include "ControladorDeTransito.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

ControladorDeTransito::~ControladorDeTransito() {
    for (Transporte* t : transportes) delete t;
    for (Viagem* v : viagens) delete v;
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, int distDescanso, int tempoDescanso, std::string localAtual) {
    Cidade* cidade = acharCidadePeloNome(localAtual);
    transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distDescanso, tempoDescanso, cidade));
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual) {
    Cidade* cidade = acharCidadePeloNome(localAtual);
    if (cidade) {
        // o construtor pede cpf, entao passamos o nome nos dois campos pra rodar
        passageirosCadastrados.push_back(new Passageiro(nome, nome, cidade));
    }
}

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino) {
    Transporte* t = nullptr;
    for (Transporte* trans : transportes) {
        if (trans->getNome() == nomeTransporte) { t = trans; break; }
    }

    if (!t) { std::cout << "Erro: Transporte nao encontrado.\n"; return; }
    Cidade* orig = acharCidadePeloNome(nomeOrigem);
    Cidade* dest = acharCidadePeloNome(nomeDestino);
    if (!orig || !dest) { std::cout << "Erro: Cidades invalidas.\n"; return; }
    if (t->getLocalAtual() != orig) { std::cout << "Erro: Transporte nao esta na origem.\n"; return; }
    if (nomesPassageiros.size() > (size_t)t->getCapacidade()) { std::cout << "Erro: Capacidade excedida.\n"; return; }

    std::vector<Passageiro*> passSelecionados;
    for (const auto& nome : nomesPassageiros) {
        Passageiro* p = nullptr;
        for (Passageiro* cand : passageirosCadastrados) {
            if (cand->getNome() == nome) { p = cand; break; }
        }
        if (!p || p->getLocalAtual() != orig) {
            std::cout << "Erro: Passageiro '" << nome << "' invalido ou fora da origem.\n";
            return;
        }
        passSelecionados.push_back(p);
    }

    // puxa a rota calculada pela busca
    std::vector<Trajeto*> rota = buscarMelhorCaminho(nomeOrigem, nomeDestino);
    if (rota.empty()) { std::cout << "Erro: Caminho inviavel.\n"; return; }

    for (Trajeto* tr : rota) {
        if (tr->getTipo() != t->getTipo()) {
            std::cout << "Erro: Modal de transporte incompativel com o trajeto.\n";
            return;
        }
    }

    // vai criando as viagens e linkando os ponteiros
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
}

void ControladorDeTransito::avancarHoras(int horas) {
    for (int h = 0; h < horas; ++h) {
        // o set impede de mover o mesmo transporte duas vezes na mesma hora em pernas diferentes
        std::set<Transporte*> transportesMovidosNestaHora;
        for (Viagem* v : viagens) {
            if (v->isEmAndamento() && transportesMovidosNestaHora.find(v->getTransporte()) == transportesMovidosNestaHora.end()) {
                transportesMovidosNestaHora.insert(v->getTransporte());
                v->avancarHoras(1);

                // se terminou a ultima conexao da viagem, joga no contador de visitas
                if (!v->isEmAndamento() && v->getProxima() == nullptr) {
                    visitasCidades[v->getDestino()->getNome()];
                }
            }
        }
    }
}

void ControladorDeTransito::relatarEstado() {
    std::cout << "\n---------- RELATORIOS OBRIGATORIOS ----------\n";

    // onde esta cada pessoa do sistema
    std::cout << "\n[1] LOCALIZACAO DE CADA PASSAGEIRO:\n";
    for (Passageiro* p : passageirosCadastrados) {
        std::cout << " - " << p->getNome() << ": ";
        if (p->getLocalAtual() != nullptr) {
            std::cout << "Na cidade de " << p->getLocalAtual()->getNome() << "\n";
        } else {
            // se ta nulo, varre as viagens ativas pra achar onde a pessoa ta presa
            for (Viagem* v : viagens) {
                if (v->isEmAndamento()) {
                    for (Passageiro* vp : v->getPassageiros()) {
                        if (vp->getNome() == p->getNome()) {
                            std::cout << "EM TRANSITO (" << v->getOrigem()->getNome() << " -> " 
                                      << v->getDestino()->getNome() << ") no transporte: " 
                                      << v->getTransporte()->getNome() << "\n";
                        }
                    }
                }
            }
        }
    }

    // onde estao os transportes
    std::cout << "\n[2] LOCALIZACAO DE CADA TRANSPORTE:\n";
    for (Transporte* t : transportes) {
        std::cout << " - " << t->getNome() << " [" << t->getTipo() << "]: ";
        if (t->getLocalAtual() != nullptr) {
            std::cout << "Estacionado em " << t->getLocalAtual()->getNome() << "\n";
        } else {
            for (Viagem* v : viagens) {
                if (v->isEmAndamento() && v->getTransporte() == t) {
                    std::cout << "EM TRANSITO de " << v->getOrigem()->getNome() << " para " << v->getDestino()->getNome();
                    if (t->estaEmDescanso()) std::cout << " [PARADO EM DESCANSO]";
                    std::cout << "\n";
                }
            }
        }
    }

    // listar o que ta rodando na hora
    std::cout << "\n[3] VIAGENS EM ANDAMENTO:\n";
    bool nenhumaAtiva = true;
    for (Viagem* v : viagens) {
        if (v->isEmAndamento()) {
            v->relatarEstado();
            nenhumaAtiva = false;
        }
    }
    if (nenhumaAtiva) std::cout << " Nenhuma viagem ativa no momento.\n";

    // ranking de visitas das cidades
    std::cout << "\n[4] CIDADES MAIS VISITADAS (RANKING DE CHEGADAS FINAIS):\n";
    if (visitasCidades.empty()) {
        std::cout << " Nenhuma chegada registrada ainda.\n";
    } else {
        for (const auto& par : visitasCidades) {
            std::cout << " - " << par.first << ": " << par.second << " visitas\n";
        }
    }
    std::cout << "---------------------------------------------\n\n";
}

const std::vector<Transporte*>& ControladorDeTransito::getTransportes() const { return transportes; }
const std::vector<Viagem*>& ControladorDeTransito::getViagens() const { return viagens; }

void ControladorDeTransito::salvarDados(const std::string& prefixo) const {
    ofstream fCidades(prefixo + "_cidades.csv");
    for (Cidade* c : cadastroCidades) fCidades << c->getNome() << "\n";

    ofstream fTrajetos(prefixo + "_trajetos.csv");
    for (Trajeto* t : rotasDisponiveis) fTrajetos << t->getOrigem()->getNome() << "," << t->getDestino()->getNome() << "," << t->getTipo() << "," << t->getDistancia() << "\n";

    ofstream fPassageiros(prefixo + "_passageiros.csv");
    for (Passageiro* p : passageirosCadastrados) fPassageiros << p->getNome() << "," << (p->getLocalAtual() ? p->getLocalAtual()->getNome() : "EM_TRANSITO") << "\n";

    ofstream fTransportes(prefixo + "_transportes.csv");
    for (Transporte* t : transportes) fTransportes << t->getNome() << "," << t->getTipo() << "," << t->getCapacidade() << "," << t->getVelocidade() << "," << t->getDistanciaEntreDescansos() << "," << t->getTempoDescanso() << "," << (t->getLocalAtual() ? t->getLocalAtual()->getNome() : "EM_TRANSITO") << "," << t->getTempoDescansoAtual() << "\n";

    ofstream fViagens(prefixo + "_viagens.csv");
    for (size_t i = 0; i < viagens.size(); ++i) {
        Viagem* v = viagens[i];
        fViagens << v->getTransporte()->getNome() << "," << v->getOrigem()->getNome() << "," << v->getDestino()->getNome() << "," << v->getHorasEmTransito() << "," << v->isEmAndamento() << "," << v->getDistanciaPercorrida() << "," << v->getDistanciaTotal() << ",";
        
        // salva o index do proximo no arquivo pra poder reconstruir os ponteiros da lista quando recarregar
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

void ControladorDeTransito::carregarDados(const std::string& prefixo) {
    std::string linha;

    ifstream fCidades(prefixo + "_cidades.csv");
    while (getline(fCidades, linha)) { if (!linha.empty()) cadastrarCidade(linha); }

    ifstream fTrajetos(prefixo + "_trajetos.csv");
    while (getline(fTrajetos, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        string o, d, t, dist;
        getline(ss, o, ','); getline(ss, d, ','); getline(ss, t, ','); getline(ss, dist, ',');
        cadastrarTrajeto(o, d, t[0], stoi(dist));
    }

    ifstream fPassageiros(prefixo + "_passageiros.csv");
    while (getline(fPassageiros, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        string n, cid;
        getline(ss, n, ','); getline(ss, cid, ',');
        cadastrarPassageiro(n, cid);
    }

    ifstream fTransportes(prefixo + "_transportes.csv");
    while (getline(fTransportes, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        string n, t, cap, vel, distD, tempD, cid, tempDAt;
        getline(ss, n, ','); getline(ss, t, ','); getline(ss, cap, ','); getline(ss, vel, ',');
        getline(ss, distD, ','); getline(ss, tempD, ','); getline(ss, cid, ','); getline(ss, tempDAt, ',');
        
        cadastrarTransporte(n, t[0], stoi(cap), stoi(vel), stoi(distD), stoi(tempD), cid == "EM_TRANSITO" ? "" : cid);
        for (Transporte* trans : transportes) {
            if (trans->getNome() == n) {
                trans->setTempoDescansoAtual(stoi(tempDAt));
                if (cid == "EM_TRANSITO") trans->setLocalAtual(nullptr);
                break;
            }
        }
    }

    ifstream fViagens(prefixo + "_viagens.csv");
    std::vector<int> proximosIndices;

    while (getline(fViagens, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        string nT, o, d, hT, emAnd, distP, distT, idxProx, passs;
        getline(ss, nT, ','); getline(ss, o, ','); getline(ss, d, ','); 
        getline(ss, hT, ','); getline(ss, emAnd, ','); getline(ss, distP, ',');
        getline(ss, distT, ','); getline(ss, idxProx, ','); getline(ss, passs, ',');

        Transporte* trans = nullptr;
        for (Transporte* tr : transportes) { if (tr->getNome() == nT) { trans = tr; break; } }

        std::vector<Passageiro*> pLista;
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