#ifndef GERENCIADOR_H
#define GERENCIADOR_H
#include <vector>
#include <string>
#include "Cidades.h"
#include "Trajeto.h"
using namespace std;

class GerenciadorCaminhos {
protected:
    vector<Cidade*> cadastroCidades;
    vector<Trajeto*> rotasDisponiveis;

    Cidade* acharCidadePeloNome(const string& nomeAlvo) const;

public:
    virtual ~GerenciadorCaminhos();

    void cadastrarCidade(const string& nome);
    void cadastrarTrajeto(const string& nomeOrigem, const string& nomeDestino, char tipo, int distancia);
    
    bool existeTrajetoDireto(const string& nomeOrigem, const string& nomeDestino) const;
    
    vector<Trajeto*> buscarMelhorCaminho(const string& nomeOrigem, const string& nomeDestino) const;

    const vector<Cidade*>& getCidades() const;
    const vector<Trajeto*>& getTrajetos() const;
};

#endif