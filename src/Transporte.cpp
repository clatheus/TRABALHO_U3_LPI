#include "Transporte.h"

//construtor
Transporte::Transporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual)
    : nome(nome), tipo(tipo), capacidade(capacidade), velocidade(velocidade), distancia_entre_descansos(distancia_entre_descansos), tempo_de_descanso(tempo_de_descanso), localAtual(localAtual), distancia_percorrida_trecho(0), tempo_de_descanso_atual(0) {}

std::string Transporte::getNome() const { return nome; }
char Transporte::getTipo() const { return tipo; }
int Transporte::getCapacidade() const { return capacidade; }
int Transporte::getVelocidade() const { return velocidade; }
int Transporte::getDistanciaEntreDescansos() const { return distancia_entre_descansos; }
int Transporte::getTempoDescanso() const { return tempo_de_descanso; }
int Transporte::getTempoDescansoAtual() const { return tempo_de_descanso_atual; }
Cidade* Transporte::getLocalAtual() const { return localAtual; }

void Transporte::setLocalAtual(Cidade* local) { 
    localAtual = local; 
}

bool Transporte::estaEmDescanso() const {
    return tempo_de_descanso_atual > 0;
}

void Transporte::resetarDescanso() {
    distancia_percorrida_trecho = 0;
    tempo_de_descanso_atual = 0;
}

//caso atinja o limite de km, ativa o tempo de descanso necessario
void Transporte::incrementarDistanciaTrecho(int km) {
    distancia_percorrida_trecho += km;
    if (distancia_percorrida_trecho >= distancia_entre_descansos) {
        tempo_de_descanso_atual = tempo_de_descanso;
        distancia_percorrida_trecho = 0;
    }
}

//reduz o tempo restante de descanso a medida que a simulacao avanca as horas
void Transporte::decrementarTempoDescanso(int horas) {
    if (tempo_de_descanso_atual > 0) {
        tempo_de_descanso_atual -= horas;
        if (tempo_de_descanso_atual < 0) {
            tempo_de_descanso_atual = 0;
        }
    }
}

void Transporte::setTempoDescansoAtual(int horas) {
    tempo_de_descanso_atual = horas;
}