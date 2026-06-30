#ifndef TRAJETOS_H
#define TRAJETOS_H
#include "Cidade.h"
using namespace std;

class Trajeto {
private:
    Cidade* localOrigem;
    Cidade* localDestino;
    char modalTipo;
    int quilometragem;

public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);
    
    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    char getTipo() const;
    int getDistancia() const;
};

#endif