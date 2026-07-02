#ifndef VIAGEM_H
#define VIAGEM_H

#include <vector>
#include <string>
#include "Transporte.h"
#include "Passageiros.h"
#include "Cidades.h"

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino; 
    Viagem* proxima; // ponteiro pra proxima perna da conexao
    int horasEmTransito;
    bool emAndamento;

    // variaveis pra ajudar a controlar os km rodados dentro de cada trecho
    int distanciaTotal;
    int distanciaPercorrida;

public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distancia);

    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado();
    bool isEmAndamento();

    // getters e setters pro controlador e pra salvar/carregar os arquivos
    Viagem* getProxima() const;
    void setProxima(Viagem* prox);
    Transporte* getTransporte() const;
    const std::vector<Passageiro*>& getPassageiros() const;
    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    int getHorasEmTransito() const;
    void setHorasEmTransito(int horas);
    void setEmAndamento(bool status);
    void setDistanciaPercorrida(int status);
    int getDistanciaPercorrida() const;
    int getDistanciaTotal() const;
};

#endif
