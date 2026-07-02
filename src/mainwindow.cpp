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

//BOTOES CONFIRMACAO-------------------------------------------
void MainWindow::on_pushButton_9_clicked()//cadstra cidade
{
    //pega o texto dos campos da interface
    QString nome = ui->lineEditNomeCidade->text();

    bool sucesso = gerenciador.cadastrarCidade(nome.toStdString());

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

