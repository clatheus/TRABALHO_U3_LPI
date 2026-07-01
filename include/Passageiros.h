#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H
#include "Cidades.h"
#include <string>

// Classe Passageiro
class Passageiro {
private:
    std::string nome;
    std::string cpf;
    Cidade* localAtual;
public:
    Passageiro(std::string nomePassageiro, std::string cpfPassageiro, Cidade* localAtualPassageiro);
    std::string getNome() const;
    std::string getCpf() const;
    Cidade* getLocalAtual() const;
    void setLocalAtual(Cidade* local);
};

#endif 