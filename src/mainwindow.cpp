#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox> //import para as caixas de mensagens
#include<vector>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gerenciador.carregarDados("dados_sistema"); //carrega os dados salvos
    atualizarTelas();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_6_clicked()//botão de sair da janela
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Sair");
    msgBox.setText("Voce deseja sair do programa?");
    msgBox.setIcon(QMessageBox::Question);

    // configura os botões padrão
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    //altera o texto
    msgBox.setButtonText(QMessageBox::Yes, "Sim");
    msgBox.setButtonText(QMessageBox::No, "Nao");

    //executa e guarda a resposta
    int resposta = msgBox.exec();

    if (resposta == QMessageBox::Yes) {
        QApplication::quit();// se for igual a sim fecha o programa
    } else {
        qDebug() << "usuario nao saiu";
    }
}
//atualiza tabela com os dados
void MainWindow::atualizarTelas() {

    // =========================================================================
    // 1. CIDADES (Nome das cidades e as mais visitadas)
    // =========================================================================
    ui->tabelaCidades->setColumnCount(2); // Garante as colunas
    ui->tabelaCidades->setHorizontalHeaderLabels({"Cidade", "Visitas"}); // Títulos das colunas
    ui->tabelaCidades->setRowCount(0);
    const auto& listaCidades = gerenciador.getCidades();

        for (size_t i = 0; i < listaCidades.size(); ++i) {
        Cidade* c = listaCidades[i];
        int linha = ui->tabelaCidades->rowCount();
        ui->tabelaCidades->insertRow(linha);

        // Coluna 0: Nome da Cidade
        ui->tabelaCidades->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(c->getNome())));

        // Coluna 1: Visitas (Buscando o valor correto associado a ela no mapa do gerenciador!)
        int visitas = gerenciador.getVisitasCidades(c->getNome());
        ui->tabelaCidades->setItem(linha, 1, new QTableWidgetItem(QString::number(visitas)));
    }

    // Ordena a tabela automaticamente pela coluna 1 (Visitas) de forma decrescente
    ui->tabelaCidades->sortItems(1, Qt::DescendingOrder);


    // =========================================================================
    // 2. TRANSPORTES (Nome do transporte e local atual)
    // =========================================================================
    ui->tabelaTransportes->setColumnCount(2); // Garante as colunas
    ui->tabelaTransportes->setHorizontalHeaderLabels({"Nome do Transporte", "Local Atual"});
    ui->tabelaTransportes->setRowCount(0);
    const auto& listaTransportes = gerenciador.getTransportes();

        for (size_t i = 0; i < listaTransportes.size(); ++i) {
        Transporte* t = listaTransportes[i];
        int linha = ui->tabelaTransportes->rowCount();
        ui->tabelaTransportes->insertRow(linha);

        // Coluna 0: Nome do Transporte
        ui->tabelaTransportes->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(t->getNome())));

        // Coluna 1: Local do Transporte (Cidade atual ou "EM TRÂNSITO")
        QString local = (t->getLocalAtual() ? QString::fromStdString(t->getLocalAtual()->getNome()) : "EM TRANSITO");
        ui->tabelaTransportes->setItem(linha, 1, new QTableWidgetItem(local));
    }


    // =========================================================================
    // 3. PASSAGEIROS (Nome, CPF e Local Atual)
    // =========================================================================
    ui->tabelaPassageiros->setColumnCount(3); // Garante as colunas
    ui->tabelaPassageiros->setHorizontalHeaderLabels({"Nome", "CPF", "Local Atual"});
    ui->tabelaPassageiros->setRowCount(0);
    const auto& listaPassageiros = gerenciador.getPassageiros();

        for (size_t i = 0; i < listaPassageiros.size(); ++i) {
        Passageiro* p = listaPassageiros[i];
        int linha = ui->tabelaPassageiros->rowCount();
        ui->tabelaPassageiros->insertRow(linha);

        // Coluna 0: Nome
        ui->tabelaPassageiros->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(p->getNome())));

        // Coluna 1: CPF
        ui->tabelaPassageiros->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(p->getCpf())));

        // Coluna 2: Local Atual (Cidade atual ou "EM TRÂNSITO")
        QString local = (p->getLocalAtual() ? QString::fromStdString(p->getLocalAtual()->getNome()) : "EM TRANSITO");
        ui->tabelaPassageiros->setItem(linha, 2, new QTableWidgetItem(local));
    }


    // =========================================================================
    // 4. VIAGENS (Apenas as que estão em andamento!)
    // =========================================================================
    ui->tabelaViagens->setColumnCount(4); // Garante as colunas
    ui->tabelaViagens->setHorizontalHeaderLabels({"Transporte", "Origem", "Destino", "Status"});
    ui->tabelaViagens->setRowCount(0);
    const auto& listaViagens = gerenciador.getViagens();

        for (size_t i = 0; i < listaViagens.size(); ++i) {
        Viagem* v = listaViagens[i];

        // FILTRO: Só adiciona na tabela se a viagem estiver em andamento!
        if (v->isEmAndamento()) {
            int linha = ui->tabelaViagens->rowCount();
            ui->tabelaViagens->insertRow(linha);

            // Coluna 0: Nome do Transporte
            QString nomeTransp = (v->getTransporte() ? QString::fromStdString(v->getTransporte()->getNome()) : "Desconhecido");
            ui->tabelaViagens->setItem(linha, 0, new QTableWidgetItem(nomeTransp));

            // Coluna 1: Origem
            QString orig = (v->getOrigem() ? QString::fromStdString(v->getOrigem()->getNome()) : "-");
            ui->tabelaViagens->setItem(linha, 1, new QTableWidgetItem(orig));

            // Coluna 2: Destino
            QString dest = (v->getDestino() ? QString::fromStdString(v->getDestino()->getNome()) : "-");
            ui->tabelaViagens->setItem(linha, 2, new QTableWidgetItem(dest));

            // Coluna 3: Status fixo
            ui->tabelaViagens->setItem(linha, 3, new QTableWidgetItem("EM ANDAMENTO"));
        }
    }
}
//BOTOES NAVEGACAO-------------------------------------------------------
void MainWindow::on_pushButton_2_clicked() //botao menu cidades
{
    ui->stackedWidget->setCurrentIndex(1); //vai para pagina cidades
}


void MainWindow::on_pushButton_3_clicked() //botao menu trajetos
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_5_clicked() //botao menu transportes
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_4_clicked() //botao passageiros
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_clicked() //botao viagens
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_8_clicked() //botao meunu cadstrar cidades
{
    ui->stackedWidget_2->setCurrentIndex(1);
}


void MainWindow::on_pushButton_7_clicked()//BOTAO CONSULTAR CIDADES MAIS Vizitadas
{
    ui->stackedWidget_2->setCurrentIndex(2);
}


void MainWindow::on_pushButton_10_clicked()//botao cadastrar trajeto menu
{
    ui->stackedWidget_3->setCurrentIndex(1);
}


void MainWindow::on_pushButton_12_clicked()  //botao cadastrar tranporte menu
{
     ui->stackedWidget_4->setCurrentIndex(1);
}


void MainWindow::on_pushButton_13_clicked() //botao menu consulyat local transporte
{
    ui->stackedWidget_4->setCurrentIndex(2);
}


void MainWindow::on_pushButton_15_clicked()//botao cadartar passageiro
{
  ui->stackedWidget_5->setCurrentIndex(2);
}


void MainWindow::on_pushButton_16_clicked()//botao consultar local passageiro
{
    ui->stackedWidget_5->setCurrentIndex(1);
}


void MainWindow::on_pushButton_18_clicked()//botao iniciar viagem  menu
{
    ui->stackedWidget_6->setCurrentIndex(1);
}


void MainWindow::on_pushButton_19_clicked()//boato mneu consultar viagens em andamento
{
    ui->stackedWidget_6->setCurrentIndex(2);
}
void MainWindow::on_pushButton_21_clicked() //botão de voltar
{
        //verifica se estamos em alguma subtela de cidades
        if (ui->stackedWidget_2->currentIndex() > 0) {
            ui->stackedWidget_2->setCurrentIndex(ui->stackedWidget_2->currentIndex() - 1);
        }
        //verifica se estamos em alguma subtela de trajetos
        else if (ui->stackedWidget_3->currentIndex() > 0) {
            ui->stackedWidget_3->setCurrentIndex(ui->stackedWidget_3->currentIndex() - 1);
        }
        //verifica se estamos em alguma subtela de transportes
        else if (ui->stackedWidget_4->currentIndex() > 0) {
            ui->stackedWidget_4->setCurrentIndex(ui->stackedWidget_4->currentIndex() - 1);

        }else if(ui->stackedWidget_5->currentIndex() > 0){ //passageiros
            ui->stackedWidget_5->setCurrentIndex(ui->stackedWidget_5->currentIndex() - 1);

        }else if(ui->stackedWidget_6->currentIndex() > 0){ //viagens
            ui->stackedWidget_6->setCurrentIndex(ui->stackedWidget_6->currentIndex() - 1);
}
        // se não estiver em nenhuma subtela então volta para o menu principal
        else {
            ui->stackedWidget->setCurrentIndex(0);
        }
}

//BOTOES CONFIRMACAO-------------------------------------------
void MainWindow::on_pushButton_9_clicked()//cadstra cidade
{
    //pega o texto dos campos da interface
    std::string nome = ui->lineEditNomeCidade->text().toStdString();

    bool sucesso = gerenciador.cadastrarCidade(nome);

    //feedback para o usuário
    if (sucesso) {
        gerenciador.salvarDados("dados_sistema");//autosave
        atualizarTelas();
        QMessageBox::information(this, "Sucesso", "Cidade cadastrada!");
        ui->lineEditNomeCidade->clear(); // limpa os campos
    } else {
        QMessageBox::critical(this, "Erro", "Cidade ja esta cadastrada!");
    }
}


void MainWindow::on_pushButton_17_clicked()//cadstra passageiro
{
    std::string nome = ui->lineNomePassageiro->text().toStdString();
    std::string cpf = ui->linePassageiroCpf->text().toStdString();
    std::string cidade = ui->lineCidadePassageiro->text().toStdString();

    bool sucesso = gerenciador.cadastrarPassageiro(nome, cpf,cidade);

    if (sucesso) {
        gerenciador.salvarDados("dados_sistema");
        atualizarTelas();
        QMessageBox::information(this, "Sucesso", "Passageiro cadastrado!");
        ui->lineNomePassageiro->clear(); // limpa os campos
        ui->linePassageiroCpf->clear();
        ui->lineCidadePassageiro->clear();
    } else {
        QMessageBox::critical(this, "Erro", "CPF ja existente ou Cidade invalida");
    }

}

void MainWindow::on_pushButton_11_clicked() //cadastra trajeto
{
    std::string origem = ui->lineOrigemTrajeto->text().toStdString();
    std::string destino = ui->lineDestinoTrajeto->text().toStdString();
    int distancia = ui->lineDistanciaTrajeto->text().toInt();

    char tipo;
    if(ui->comboBox->currentText()=="Terrestre"){
        tipo = 'T';
    }else{
        tipo = 'A';
    }
    bool sucesso = gerenciador.cadastrarTrajeto(origem, destino, tipo, distancia);


    if (sucesso) {
        gerenciador.salvarDados("dados_sistema");
        atualizarTelas();
        QMessageBox::information(this, "Sucesso", "Trajeto cadastrado!");
        ui->lineOrigemTrajeto->clear(); // limpa os campos
        ui->lineDestinoTrajeto->clear();
        ui->lineDistanciaTrajeto->clear();
    } else {
        QMessageBox::critical(this, "Erro", "Nao e possivel linkar o trajeto: Origem/Destino nao existem ou Distancia invalida.");
    }
}

void MainWindow::on_pushButton_14_clicked()//cadastra transporte
{
    std::string nome = ui->lineNomeTransporte->text().toStdString();
    char tipo;
    if(ui->comboBox_2->currentText()=="Terrestre"){
        tipo = 'T';
    }else{
        tipo = 'A';
    }
    int velocidade = ui->lineVelocidade->text().toInt();
    std::string cidade = ui->lineCidadeTransporte->text().toStdString();
    int capacidade = ui->lineCapacidade->text().toInt();
    int distdescanco = ui->lineDistanciaDescanso->text().toInt();
    int descanso = ui->lineDescanso->text().toInt();

    bool sucesso = gerenciador.cadastrarTransporte(nome, tipo, capacidade, velocidade,distdescanco,descanso,cidade);

    if(sucesso){
    gerenciador.salvarDados("dados_sistema");
        atualizarTelas();
    QMessageBox::information(this, "Sucesso", "Transporte cadastrado!");
    ui->lineVelocidade->clear(); // limpa os campos
    ui->lineNomeTransporte->clear();
    ui->lineCidadeTransporte->clear();
    ui->lineCapacidade->clear();
    ui->lineDistanciaDescanso->clear();
    ui->lineDescanso->clear();
    } else {
        QMessageBox::critical(this, "Erro", "Transporte ja existe ou Cidade invalida");
    }
}


void MainWindow::on_pushButton_20_clicked()
{//iniciar vuagem
    std::string nome = ui->lineTransporteViagem->text().toStdString();
    std::string origem = ui->lineOrigemViagem->text().toStdString();
    std::string destino = ui->lineDestinoViagem->text().toStdString();

    //pega o texto
    QString textoPassageiros = ui->linePassageiroViagem->toPlainText();

    QStringList listaNomesQt = textoPassageiros.split(",");

    vector<string> nomesPassageiros;

    for (const QString& nomeQt : listaNomesQt) {
        // remove espaços em branco extras que o usuário digita
        QString nomeLimpo = nomeQt.trimmed();

        // só adiciona se o campo não estiver vazio
        if (!nomeLimpo.isEmpty()) {
            nomesPassageiros.push_back(nomeLimpo.toStdString());
        }
    }

    if (nomesPassageiros.empty()) {
        QMessageBox::warning(this, "Aviso", "Digite e separe por virgula ao menos um passageiro!");
        return;
    }
    if (origem == destino) {
        QMessageBox::warning(this, "Aviso", "A origem e o destino nao podem ser iguais!");
        return;
    }

    bool sucesso = gerenciador.iniciarViagem(nome, nomesPassageiros, origem, destino);

    if(!sucesso){
        QMessageBox::warning(this, "Erro", "Verifique se os componentes são validos!");
        return;
    }

    QMessageBox::information(this, "Sucesso", "Viagem iniciada! Avance as horas para se movimentar.");
    gerenciador.salvarDados("dados_sistema");
    atualizarTelas();
    ui->lineTransporteViagem->clear();
    ui->lineOrigemViagem->clear();
    ui->lineDestinoViagem->clear();
    ui->linePassageiroViagem->clear();
}


void MainWindow::on_pushButton_22_clicked()//avançar horaass
{
    int horas = ui->spinBox->value();

    gerenciador.avancarHoras(horas);
    QMessageBox::information(this, "Tempo", "O tempo avançou " + QString::number(horas) + " horas!");
    atualizarTelas();

}



