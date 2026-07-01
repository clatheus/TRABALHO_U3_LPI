#include "Cidades.h"
using namespace std;

Cidade::Cidade(string nome) : nomeId(nome) {}

string Cidade::getNome() const {
    return nomeId;
}