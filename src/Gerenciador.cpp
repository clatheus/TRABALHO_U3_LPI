#include "Gerenciador.h"
#include <iostream>
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
}

Cidade* GerenciadorCaminhos::acharCidadePeloNome(const string& nomeAlvo) const {
    for (Cidade* c : cadastroCidades) {
        if (c->getNome() == nomeAlvo) return c;
    }
    return nullptr;
}

void GerenciadorCaminhos::cadastrarCidade(const string& nome) {
    if (acharCidadePeloNome(nome) != nullptr) {
        cout << "[AVISO] Ignorado: '" << nome << "' ja possui cadastro ativo.\n";
        return;
    }
    cadastroCidades.push_back(new Cidade(nome));
}

void GerenciadorCaminhos::cadastrarTrajeto(const string& nomeOrigem, const string& nomeDestino, char tipo, int distancia) {
    Cidade* destinoPt = acharCidadePeloNome(nomeDestino);

    if (origemPt == nullptr || destinoPt == nullptr) {
        cout << "[ERRO] Inpossivel linkar trajeto: Origem ou Destino inexistentes.\n";
        return;
    }
    rotasDisponiveis.push_back(new Trajeto(origemPt, destinoPt, tipo, distancia));
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

const vector<Cidade*>& GerenciadorCaminhos::getCidades() const { 
    return cadastroCidades; 
}

const vector<Trajeto*>& GerenciadorCaminhos::getTrajetos() const { 
    return rotasDisponiveis; 
}