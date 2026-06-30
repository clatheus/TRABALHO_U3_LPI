#include "Trajeto.h"
using namespace std;

Trajeto::Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia)
    : localOrigem(origem), localDestino(destino), modalTipo(tipo), quilometragem(distancia) {}

Cidade* Trajeto::getOrigem() const { 
    return localOrigem; 
}

Cidade* Trajeto::getDestino() const { 
    return localDestino; 
}

char Trajeto::getTipo() const { 
    return modalTipo; 
}

int Trajeto::getDistancia() const { 
    return quilometragem; 
}