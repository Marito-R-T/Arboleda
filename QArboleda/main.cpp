#include "mainwindow.h"

#include <QApplication>
#include <programa.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <shared_mutex>
#include <semaphore.h>
#include <fstream>
#include <iostream>
#include <QJsonObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>
#include <string>
#include <sys/mman.h>
#include <pthread.h>
#include <wait.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <fcntl.h>
#include <QSharedMemory>

using namespace std;

typedef struct
{
  Programa programa;
  int x;
  MainWindow w;
  string comando;
  pthread_mutex_t mutex;
} shared_data;

static shared_data* data = NULL;

//void senal(int numero);
void crearProceso(int n_tallo, int n_ramas, int n_hojas);
void leerTexto();
void bucleTallo(int n_tallo);
void bucleRama(int n_tallo, int n_rama);
void bucleHoja(int n_tallo, int n_rama, int n_hoja);
void signalCont(int numero);
void signalContW(int numero);
int tallo_mostrado = 0;
int pid_w,  pid_p;

void initialise_shared() {
    // place our shared data in shared memory
    int prot = PROT_READ | PROT_WRITE;
    int flags = MAP_SHARED | MAP_ANONYMOUS;
    data = (shared_data*)mmap(NULL, sizeof(shared_data), prot, flags, -1, 0);
    assert(data);
    // compartir la ventana
    /*int prot1 = PROT_READ | PROT_WRITE;
    int flags1 = MAP_SHARED | MAP_ANONYMOUS;
    w = (MainWindow*)mmap(NULL, sizeof(MainWindow), prot1, flags1, -1, 0);
    assert(data);*/
    // initialise mutex so it works properly in shared memory
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&data->mutex, &attr);
}

int main(int argc, char *argv[])
{
    initialise_shared();
    QApplication a(argc, argv);
    MainWindow w;
    data->w = w;
    /*QJsonValue val = QJsonValue("{\"comando\": \"P\",\"tallos\" : []}");
    QJsonObject obj = val.toObject();
    QJsonDocument doc = QJsonDocument(obj);
    ofstream of("programa.json");
    of<<doc.toJson().toStdString();
    of.close();*/
    int pid;
    if((pid = fork()) > 0) {
        //w.setPrograma(&programa);
        /*pthread_mutex_lock(&data->mutex);
        pthread_mutex_unlock(&data->mutex);*/
        pid_w = getpid();
        signal(SIGCONT, signalContW);
        data->w.show();
        return a.exec();
    } else if (pid == 0){
        sleep(2);
        pthread_mutex_lock(&data->mutex);
        data->w.getUI()->buttonOK->setText(QString("hola que tal"));
        pid_p = getpid();
        data->programa.setPID(getpid());
        pthread_mutex_unlock(&data->mutex);
        signal(SIGCONT, signalCont);
        for (;;);
    } else {
        printf("error");
    }
    return 1;
}

void signalCont(int numero) {
    signal(SIGCONT, signalCont);
    leerTexto();
    kill(pid_w, SIGCONT);
}

void signalContW(int numero) {
    signal(SIGCONT, signalContW);
}

void leerTexto() {
    QJsonObject obj = ObtenerJson::getObjeto();
    QString comando = obj["comando"].toString();
    QStringList arr = comando.split(",");
    string accion;
    int n_tallo = 0, n_ramas = 0, n_hojas = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if(i==0) {
            accion = arr.at(i).toStdString();
        } else if(i == 1) {
            n_tallo = arr.at(i).toInt();
        } else if (i == 2) {
            n_ramas = arr.at(i).toInt();
        } else if (i == 3) {
            n_hojas = arr.at(i).toInt();
        }
    }
    if(accion == "P"){
        if(n_tallo < data->programa.getCTallos()) {
            tallo_mostrado = n_tallo;
        } else if(n_tallo == data->programa.getCTallos()+1) {
            crearProceso(n_tallo, n_ramas, n_hojas);
        }
    }
}

void crearProceso(int n_tallo, int n_ramas, int n_hojas) {
    int pid = fork();
    if(pid == 0) {
        for (int i = 0; i < n_ramas; ++i) {
            int pidr = fork();
            if(pidr == 0) {
                for (int j = 0; j < n_hojas; ++j) {
                    int pidh = fork();
                    if(pidh == 0) {
                        bucleHoja(n_tallo, i, j);
                        break;
                    } else if(pidh < 0){

                    }
                }
                break;
            } else if(pidr < 0){

            }
        }
    } else if (pid > 0) {

    } else if (pid <0) {

    }
}

void bucleTallo(int n_tallo) {
    while(true) {
        Tallo t = Tallo();

    }
}

void bucleRama(int n_tallo, int n_rama) {
    while(true) {

    }
}

void bucleHoja(int n_tallo, int rama, int n_hoja) {
    while(true) {

    }
}
