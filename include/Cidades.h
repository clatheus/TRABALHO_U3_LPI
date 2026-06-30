#ifndef CIDADES_H
#define CIDADES_H
#include <string>
using namespace std;

class Cidade {
private:
    string nomeId; 

public:
    Cidade(string nome);
    
    string getNome() const;
};

#endif