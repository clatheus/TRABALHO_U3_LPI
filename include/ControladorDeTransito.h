#ifndef CONTROLADOR_DE_TRANSITO_H
#define CONTROLADOR_DE_TRANSITO_H

#include "Gerenciador.h"
#include "Transporte.h"
#include "Viagem.h"
#include <vector>
#include <string>
#include <map>

// herda as funcoes do gerenciador do colega pra nao precisar refazer cidades e trajetos
class ControladorDeTransito : public GerenciadorCaminhos {
private:
    std::vector<Transporte*> transportes;
    std::vector<Viagem*> viagens;
    
    // map pra guardar as estatisticas de visitas das cidades pro relatorio
    std::map<std::string, int> visitasCidades;

public:
    ~ControladorDeTransito();

    // metodos exatamente com os nomes que o professor colocou no pdf
    void cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual);
    void cadastrarPassageiro(std::string nome, std::string localAtual);
    void iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);
    void relatarEstado();

    // getters pra passar os dados pra interface
    const std::vector<Transporte*>& getTransportes() const;
    const std::vector<Viagem*>& getViagens() const;

    // salvamento em arquivos csv
    void salvarDados(const std::string& prefixo) const;
    void carregarDados(const std::string& prefixo);
};

#endif