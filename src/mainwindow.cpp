#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox> //import para as caixas de mensagens


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_6_clicked()//botão de sair da janela
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Sair");
    msgBox.setText("Você deseja sair do programa?");
    msgBox.setIcon(QMessageBox::Question);

    // configura os botões padrão
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    //altera o texto
    msgBox.setButtonText(QMessageBox::Yes, "Sim");
    msgBox.setButtonText(QMessageBox::No, "Não");

    //executa e guarda a resposta
    int resposta = msgBox.exec();

    if (resposta == QMessageBox::Yes) {
        QApplication::quit();// se for igual a sim fecha o programa
    } else {
        qDebug() << "usuario nao saiu";
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
        QMessageBox::information(this, "Sucesso", "Cidade cadastrada!");
        ui->lineEditNomeCidade->clear(); // limpa os campos
    } else {
        QMessageBox::critical(this, "Erro", "Cidade já está cadastrada!");
    }
}


void MainWindow::on_pushButton_17_clicked()//cadstra passageiro
{
    std::string nome = ui->lineNomePassageiro->text().toStdString();
    std::string cpf = ui->linePassageiroCpf->text().toStdString();

    bool sucesso = gerenciador.cadastrarPassageiro(nome, cpf);

    if (sucesso) {
        QMessageBox::information(this, "Sucesso", "Passageiro cadastrado!");
        ui->lineNomePassageiro->clear(); // limpa os campos
        ui->linePassageiroCpf->clear();
    } else {
        QMessageBox::critical(this, "Erro", "CPF já existente");
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
        QMessageBox::information(this, "Sucesso", "Trajeto cadastrado!");
        ui->lineOrigemTrajeto->clear(); // limpa os campos
        ui->lineDestinoTrajeto->clear();
        ui->lineDistanciaTrajeto->clear();
        ui->comboBox->clear();
    } else {
        QMessageBox::critical(this, "Erro", "Não é possível linkar o trajeto: Origem/Destino não existem ou Distância inválida.");
    }
}



