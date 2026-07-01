#include "Trajetos.h"
using namespace std;

Trajeto::Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia)
    : Origem(origem), Destino(destino), Tipo(tipo), Distancia(distancia) {}

Cidade* Trajeto::getOrigem() const { 
    return Origem; 
}

Cidade* Trajeto::getDestino() const { 
    return Destino; 
}

char Trajeto::getTipo() const { 
    return Tipo; 
}

int Trajeto::getDistancia() const { 
    return Distancia; 
}