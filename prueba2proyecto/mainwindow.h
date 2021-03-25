#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <programa.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setPrograma(Programa *programa);
    ~MainWindow();

private slots:
    void on_buttonOK_clicked();

private:
    Ui::MainWindow *ui;
    Programa *programa;
};
#endif // MAINWINDOW_H
