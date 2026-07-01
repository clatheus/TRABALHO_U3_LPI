#ifndef TRAJETOS_H
#define TRAJETOS_H
#include "Cidades.h"
using namespace std;

class Trajeto {
private:
    Cidade* Origem;
    Cidade* Destino;
    char Tipo;
    int Distancia;

public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);
    
    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    char getTipo() const;
    int getDistancia() const;
};

#endif