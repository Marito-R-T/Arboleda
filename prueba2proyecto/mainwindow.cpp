#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "programa.h"
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <wait.h>

using namespace std;

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


void MainWindow::on_buttonOK_clicked()
{
    /*Programa* programa = new Programa();
    QString str = ui->txtEntrada->text();
    //string str2 = str.toStdString();
    ui->txt_prueba->setText("");
    str = str.remove("(");
    str = str.remove(")");
    QStringList list = str.split(",");
    for (int i=0; i<list.size(); i++) {
        ui->txt_prueba->append(list[i]+"\n");
    }
    programa->leerTexto("");*/
    printf("Se preciono el boton\n");
    QString str = ui->txtEntrada->text();
    str = str.remove("(");
    str = str.remove(")");
    write(this->programa->p[1], str.toStdString().c_str(), 10);
}

void MainWindow::setPrograma(Programa *programa){
    this->programa = programa;
    this->programa->setPID(18);
}
