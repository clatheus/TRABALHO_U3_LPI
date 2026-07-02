#ifndef GERENCIADOR_H
#define GERENCIADOR_H
#include <vector>
#include <string>
#include "Cidades.h"
#include "Trajetos.h"
#include "Passageiros.h"

class GerenciadorCaminhos {
protected:
    std::vector<Cidade*> cadastroCidades;
    std::vector<Trajeto*> rotasDisponiveis;
    std::vector<Passageiro*> passageirosCadastrados;

    Cidade* acharCidadePeloNome(const std::string& nomeAlvo) const;

public:
    virtual ~GerenciadorCaminhos();

    bool cadastrarCidade(const std::string& nome);
    void cadastrarTrajeto(const std::string& nomeOrigem, const std::string& nomeDestino, char tipo, int distancia);

    bool cadastrarPassageiro(std::string nome, std::string cpf);
    Passageiro* procuraPassageiro(std::string cpf);
    
    bool existeTrajetoDireto(const std::string& nomeOrigem, const std::string& nomeDestino) const;
    
    
    std::vector<Trajeto*> buscarMelhorCaminho(const std::string& nomeOrigem, const std::string& nomeDestino) const;

    const std::vector<Cidade*>& getCidades() const;
    const std::vector<Trajeto*>& getTrajetos() const;
    const std::vector<Passageiro*>& getPassageiros() const;
};

#endif