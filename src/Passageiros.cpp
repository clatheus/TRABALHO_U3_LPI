#include "Passageiros.h"
#include <string>
using namespace std;

//inicializa os atributos
Passageiro::Passageiro(string nomePassageiro, string cpfPassageiro, Cidade* localAtualPassageiro)
    : nome(nomePassageiro), localAtual(localAtualPassageiro), cpf(cpfPassageiro) {}

string Passageiro::getNome() const{
    return nome;
}

string Passageiro::getCpf() const{
    return cpf;
}

Cidade* Passageiro::getLocalAtual() const{ //pega o local atual do passageiro
    return localAtual;
}

void Passageiro::setLocalAtual(Cidade* local){ //muda o local atual do passageiro
    localAtual = local;
}

