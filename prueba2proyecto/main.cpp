#include "mainwindow.h"

#include <QApplication>
#include <programa.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <vector>
#include <iostream>
#include <signal.h>
#include <sys/types.h>

using namespace std;

Programa programa;
//void senal(int numero);

int main(int argc, char *argv[])
{

    programa = Programa();
    int pid;
    if (pipe(programa.p) < 0) {
        exit(1);
    }
    if((pid = fork()) > 0) {
        QApplication a(argc, argv);
        MainWindow w;
        w.setPrograma(&programa);
        w.show();
        return a.exec();
    } else if (pid == 0){
        programa.setPID(getpid());
        programa.esperar();
    } else {
        printf("error");
    }
    return 1;
}

/*void senal(int numero) {
    cout<<"señal\n";
}*/

