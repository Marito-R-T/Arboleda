#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <wait.h>
#include <programa.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //void setPrograma(Programa *programa);
    ~MainWindow();
    void handleC(int sig);
    int getPIDP();
    void setPIDP(int pid_p);
    Ui::MainWindow *getUI();
private slots:
    void on_buttonOK_clicked();

private:
    int pid_p;
    Ui::MainWindow *ui;
    //Programa *programa;
};
#endif // MAINWINDOW_H
