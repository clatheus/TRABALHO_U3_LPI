#ifndef GERENCIADOR_H
#define GERENCIADOR_H
#include <vector>
#include <string>
#include "Cidades.h"
#include "Trajetos.h"
#include "Passageiros.h"
#include "Transporte.h"
#include "Viagem.h"
#include <map>

class GerenciadorCaminhos {
protected:
    std::vector<Cidade*> cadastroCidades;
    std::vector<Trajeto*> rotasDisponiveis;
    std::vector<Passageiro*> passageirosCadastrados;
    std::vector<Transporte*> transportes;
    std::vector<Viagem*> viagens;

    Cidade* acharCidadePeloNome(const std::string& nomeAlvo) const;

    // map pra guardar as estatisticas de visitas das cidades pro relatorio
    std::map<std::string, int> visitasCidades;

public:
    virtual ~GerenciadorCaminhos();

    bool cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual);
    bool cadastrarCidade(const std::string& nome);
    bool cadastrarTrajeto(const std::string& nomeOrigem, const std::string& nomeDestino, char tipo, int distancia);

    bool cadastrarPassageiro(std::string nome, std::string cpf);
    Passageiro* procuraPassageiro(std::string cpf);
    
    bool existeTrajetoDireto(const std::string& nomeOrigem, const std::string& nomeDestino) const;
    
    
    std::vector<Trajeto*> buscarMelhorCaminho(const std::string& nomeOrigem, const std::string& nomeDestino) const;

     // getters pra passar os dados pra interface
    const std::vector<Cidade*>& getCidades() const;
    const std::vector<Trajeto*>& getTrajetos() const;
    const std::vector<Passageiro*>& getPassageiros() const;
    const std::vector<Transporte*>& getTransportes() const;
    const std::vector<Viagem*>& getViagens() const;

    //vaigens
    void iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);
    void relatarEstado();

    // salvamento em arquivos csv
    void salvarDados(const std::string& prefixo) const;
    void carregarDados(const std::string& prefixo);
};

#endif