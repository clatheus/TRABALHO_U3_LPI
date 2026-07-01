#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H
#include "Cidades.h"
#include <string>

// Classe Passageiro
class Passageiro {
private:
    std::string nome;
    Cidade* localAtual;
public:
    Passageiro(std::string nome, Cidade* localAtual);
    std::string getNome();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
};

#endif 