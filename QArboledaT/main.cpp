#include <QCoreApplication>

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
#include <stdlib.h>
#include <time.h>
#include <tallo.h>
#include <rama.h>
#include <hoja.h>
#include <programa.h>

using namespace std;

typedef struct
{
  Programa programa;
  int x;
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
string comando;

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
    QCoreApplication a(argc, argv);

    initialise_shared();
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
        while(true) {
            string str;
            cin >> str;
            comando = str;
            pause();
        }
    } else if (pid == 0){
        sleep(2);
        pthread_mutex_lock(&data->mutex);
        data->programa.setPID(getpid());
        pthread_mutex_unlock(&data->mutex);
        signal(SIGCONT, signalCont);
        for (;;);
    } else {
        printf("error");
    }
    return a.exec();
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
    QString str = QString(comando.c_str());
    QStringList arr = str.split(",");
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
        Tallo Qtallo;
        Rama *ramas = new Rama[5];
        for (int i = 0; i < n_ramas; ++i) {
            int pidr = fork();
            if(pidr == 0) {
                Rama rama;
                Hoja *hojas = new Hoja[10];
                for (int j = 0; j < n_hojas; ++j) {
                    int pidh = fork();
                    if(pidh == 0) {
                        Hoja hoja;
                        hojas[j] = hoja;
                        bucleHoja(n_tallo, i, j);
                        break;
                    } else if(pidh < 0){

                    }
                }
                rama.hojas = hojas;
                ramas[i] = rama;
                bucleRama(n_tallo, i);
                break;
            } else if(pidr < 0){

            }
        }
        Qtallo.ramas = ramas;
        pthread_mutex_lock(&data->mutex);
        data->programa.tallos[n_tallo] = Qtallo;
        pthread_mutex_unlock(&data->mutex);
        bucleTallo(n_tallo);
    } else if (pid > 0) {

    } else if (pid <0) {

    }
}

void bucleTallo(int n_tallo) {
    while(true) {
        int num = rand() % 2;
        printf("colorTallo: %d\n", num);
        sleep(1);
    }
}

void bucleRama(int n_tallo, int n_rama) {
    while(true) {
        int num = rand() % 2;
        printf("colorRama: %d\n", num);
        sleep(1);
    }
}

void bucleHoja(int n_tallo, int rama, int n_hoja) {
    while(true) {
        int num = rand() % 2;
        printf("colorHoja: %d\n", num);
        sleep(1);
    }
}
