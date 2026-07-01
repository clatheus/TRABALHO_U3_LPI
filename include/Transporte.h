#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include <string>

class Cidade;

class Transporte {
private:
    std::string nome;
    char tipo;                         //'A' para aquatico e 'T' para Terrestre
    int capacidade;                    //capacidade maxima
    int velocidade                    
    int distancia_entre_descansos;
    int tempo_de_descanso;

    int distancia_percorrida_trecho;   //km rodados desde o ultimo descanso
    int tempo_de_descanso_atual;       //horas que ainda faltam cumprir de descanso
    Cidade* localAtual;                //ponteiro para a cidade onde o transporte esta (ou nullptr se em transito)

public:
    Transporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual);

    std::string getNome() const;
    char getTipo() const;
    int getCapacidade() const;
    int getVelocidade() const;
    int getDistanciaEntreDescansos() const;
    int getTempoDescanso() const;
    int getTempoDescansoAtual() const;
    Cidade* getLocalAtual() const;

    void setLocalAtual(Cidade* local);
    bool estaEmDescanso() const;

    void resetarDescanso();
    void incrementarDistanciaTrecho(int km);
    void decrementarTempoDescanso(int horas);
    void setTempoDescansoAtual(int horas);
};

#endif