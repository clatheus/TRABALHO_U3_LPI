# -------------------- TRABALHO_U3_LPI --------------------

# -------------- CONTROLADOR DE VIAGENS --------------

Esse é o projeto final da disciplina Linguagem de Programação I. Nosso trabalho consiste em um sistema que gerencia o tráfego entre cidades, considerando diferentes tipos de trajeto e meios de transporte. O sistema permite o cadastro de cidades, trajetos, transportes e passageiros, além de calcular e simular viagens entre as cidades.

# Linguagens
Nosso código foi feito majoritariamente usando C++, que é o foco da disciplina, mas usamos também a linguagem CMake para automatizar o processo de compilação.

# Principais Funcionalidades
Algoritmo de Dijkstra: Calcula a rota de menor quilometragem entre duas cidades.

Viagens com Conexão: Suporte nativo para encadeamento de múltiplos trajetos em uma única jornada.

Controle de Fadiga: Bloqueio temporário de veículos para cumprimento de descanso obrigatório baseado na quilometragem rodada.

Passagem de Tempo Simulado: Atualização simultânea da posição física de todas as viagens ativas na malha hora a hora.

Banco de Dados em CSV: Exportação e importação completa do estado atual da simulação em arquivos .csv.

Interface Qt GUI: Telas dinâmicas, caixas de diálogo e formulários validados.

# Author(s)
```
┌─[ Kevin Tietz Loughney ]────────────────┐
│ (Turma 02)                              │
│ (20250027064)                           │
│ penfootbinario@gmail.com                │
└─────────────────────────────────────────┘
```
```
┌─[ Lyan Kelvin Benicio Silva ]───────────┐
│ (Turma 01)                              │
│ (20250031871)                           │
│ lyankelin94@gmail.com                   │
└─────────────────────────────────────────┘
```
```
┌─[ Matheus Lucheze Lopes ]───────────────┐
│ (Turma 01)                              │
│ (20250034149)                           │
│ matheus.lucheze.125@ufrn.edu.br         │
└─────────────────────────────────────────┘
```
```
┌─[ Rafaela Thais de Abreu Lucio Maia ]───┐
│ (Turma 01)                              │
│ (20250025927)                           │
│ rafaelathaisabreu28@gmail.com           │
└─────────────────────────────────────────┘
```

# Compiling and Running
##  Como Rodar o Projeto
Se você deseja apenas testar a aplicação sem precisar compilar o código:
1. Vá na aba *Releases* no lado direito desta página.
2. Baixe o arquivo .zip da versão mais recente.
3. Extraia os arquivos e execute o TRABALHO_U3_LPI.exe

## Como Compilar o Código Fonte

Se você deseja compilar o projeto na sua máquina, siga os passos abaixo:

### Pré-requisitos
* Compilador C++
* Qt Creator

### Passo a Passo (Via Qt Creator)
1. Clone este repositório: git clone <link-do-seu-repositorio>
2. Abra o *Qt Creator*.
3. Vá em Arquivo > Abrir Arquivo ou Projeto e selecione o arquivo CMakeLists.txt dentro da pasta TRABALHO_U3_LPI.
4. Configure o Kit de compilação (MinGW ou MSVC)
5. Clique em *Executar (Build & Run)* ou use o atalho Ctrl + R