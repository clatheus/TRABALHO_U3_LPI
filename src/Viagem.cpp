#include "Viagem.h"
#include <iostream>

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distancia)
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino), 
      proxima(nullptr), horasEmTransito(0), emAndamento(false), 
      distanciaTotal(distancia), distanciaPercorrida(0) {}

void Viagem::iniciarViagem() {
    emAndamento = true;
    horasEmTransito = 0;
    distanciaPercorrida = 0;

    // tira todo mundo da cidade atual pq agora tao na estrada (viram nullptr)
    transporte->setLocalAtual(nullptr);
    for (Passageiro* p : passageiros) {
        p->setLocalAtual(nullptr);
    }
}

void Viagem::avancarHoras(int horas) {
    if (!emAndamento) return;

    for (int i = 0; i < horas; ++i) {
        if (!emAndamento) break;

        // se o transporte tiver descansando, so passa o tempo e nao sai do lugar
        if (transporte->estaEmDescanso()) {
            transporte->decrementarTempoDescanso(1);
            horasEmTransito++;
            continue;
        }

        horasEmTransito++;
        int velocidade = transporte->getVelocidade();
        int distanciaRestante = distanciaTotal - distanciaPercorrida;

        if (velocidade >= distanciaRestante) {
            // chegou no destino dessa perna da viagem
            transporte->incrementarDistanciaTrecho(distanciaRestante);
            distanciaPercorrida = distanciaTotal;
            emAndamento = false;

            // so bota na cidade se for a ultima conexao de verdade
            if (proxima == nullptr) {
                transporte->setLocalAtual(destino);
                for (Passageiro* p : passageiros) {
                    p->setLocalAtual(destino);
                }
            } else {
                // se tiver proxima conexao, ja starta ela direto
                proxima->iniciarViagem();
            }
        } else {
            // ainda nao chegou na cidade, so soma o que conseguiu andar na hora
            transporte->incrementarDistanciaTrecho(velocidade);
            distanciaPercorrida += velocidade;
        }
    }
}

void Viagem::relatarEstado() {
    std::cout << "  [Perna] " << origem->getNome() << " -> " << destino->getNome() 
              << " | Horas em Transito: " << horasEmTransito << "h\n";
}

bool Viagem::isEmAndamento() { return emAndamento; }
Viagem* Viagem::getProxima() const { return proxima; }
void Viagem::setProxima(Viagem* prox) { proxima = prox; }
Transporte* Viagem::getTransporte() const { return transporte; }
const std::vector<Passageiro*>& Viagem::getPassageiros() const { return passageiros; }
Cidade* Viagem::getOrigem() const { return origem; }
Cidade* Viagem::getDestino() const { return destino; }
int Viagem::getHorasEmTransito() const { return horasEmTransito; }
void Viagem::setHorasEmTransito(int horas) { horasEmTransito = horas; }
void Viagem::setEmAndamento(bool status) { emAndamento = status; }
void Viagem::setDistanciaPercorrida(bool status) { distanciaPercorrida = status;}
int Viagem::getDistanciaPercorrida() const { return distanciaPercorrida; }
int Viagem::getDistanciaTotal() const { return distanciaTotal; }