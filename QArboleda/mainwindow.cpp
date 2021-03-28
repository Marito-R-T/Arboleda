#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    //kill(this->programa->getPID(), SIGCONT);
    printf("Se preciono el boton\n");
    QString str = ui->txtEntrada->text();
    str = str.remove("(");
    str = str.remove(")");
    kill(pid_p, SIGCONT);
    pause();
}

/*void MainWindow::setPrograma(Programa *programa){
    this->programa = programa;
    this->programa->setPID(18);
}
*/
Ui::MainWindow *MainWindow::getUI(){
    return this->ui;
}

void MainWindow::setPIDP(int pid_p) {
    this->pid_p = pid_p;
}

int MainWindow::getPIDP() {
    return this->pid_p;
}
