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
#include<cstring>
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
  char comando[9];
  int tallo_mostrado = 0;
  Rama rmanipulada[5];
  Hoja hmanipulada[10];
  int rama_cambiar = -1;
  int pid_w,  pid_p;
  pthread_mutex_t mutex;
} shared_data;

static shared_data* data = NULL;

//void senal(int numero);
void crearProceso(int n_tallo, int n_ramas, int n_hojas);
void modificarAspectos(int n_tallo, int n_ramas, int n_hojas);
void crearRamasNuevas(int numero);
void crearHojasNuevas(int numero);
void leerTexto();
void bucleTallo(int n_tallo);
void bucleRama(int n_tallo, int n_rama);
void bucleHoja(int n_tallo, int n_rama, int n_hoja);
void signalCont(int numero);
void signalContW(int numero);
void signalHup(int numero);
void pintarTallo();
/*Rama *regresarRamas(int n_ramas, int n_hojas);
Hoja *regresarHojas(int n_rama, int n_hojas);*/
void regresarRamas(int n_ramas, int n_hojas);
void regresarHojas(int n_rama, int n_hojas);

void initialise_shared() {
    // place our shared data in shared memory
    int prot = PROT_READ | PROT_WRITE;
    int flags = MAP_SHARED | MAP_ANONYMOUS;
    data = (shared_data*)mmap(NULL, sizeof(shared_data), prot, flags, -1, 0);
    assert(data);
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
        data->pid_w = getpid();
        signal(SIGCONT, signalContW);
        while(true) {
            char str[9];
            printf("Ingrese un comando\n");
            scanf("%s", &str);
            for (int i = 0; i < 9; ++i) {
                data->comando[i] = str[i];
            }
            kill(data->pid_p, SIGCONT);
            pause();
        }
    } else if (pid == 0){
        //pthread_mutex_lock(&data->mutex);
        sleep(1);
        printf("hola\n");
        data->pid_p = getpid();
        data->programa.setPID(getpid());
        //pthread_mutex_unlock(&data->mutex);
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
    kill(data->pid_w, SIGCONT);
}

void signalContW(int numero) {
    signal(SIGCONT, signalContW);
}

void signalHup(int numero) {
}

void crearRamasNuevas(int numero){
    signal(SIGINT, crearRamasNuevas);
    QString str = QString(data->comando);
    printf("El comando es: %s\n", data->comando);
    QStringList arr = str.split(",");
    string accion;
    int n_tallo = 0, n_ramas = 0, n_hojas = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if(i==0) {
            accion = arr.at(i).toStdString();
        } else if(i == 1) {
            n_tallo = arr.at(i).toInt() - 1;
        } else if (i == 2) {
            n_ramas = arr.at(i).toInt();
        } else if (i == 3) {
            n_hojas = arr.at(i).toInt();
        }
    }
    int CRamas = data->programa.tallos[n_tallo].getCRamas();
    printf("Se crearan %d de ramas, cada una con %d hijos\n", n_ramas - CRamas, data->programa.tallos[n_tallo].getCHojas());
    regresarRamas(n_ramas - CRamas, data->programa.tallos[n_tallo].getCHojas());
    for (int i = 0; i < n_ramas-CRamas; i++) {
        printf("Se colocará en la posición %d la rama creada\n", CRamas + i);
        data->programa.tallos[n_tallo].ramas[CRamas+i] = data->rmanipulada[i];
        data->programa.tallos[n_tallo].ramas[CRamas+i].setCHojas(data->programa.tallos[n_tallo].getCHojas());
    }
    kill(data->pid_p, SIGHUP);
}

void crearHojasNuevas(int numero) {
    signal(SIGINT, crearHojasNuevas);
    QString str = QString(data->comando);
    printf("El comando es: %s\n", data->comando);
    QStringList arr = str.split(",");
    string accion;
    int n_tallo = 0, n_ramas = 0, n_hojas = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if(i==0) {
            accion = arr.at(i).toStdString();
        } else if(i == 1) {
            n_tallo = arr.at(i).toInt() - 1;
        } else if (i == 2) {
            n_ramas = arr.at(i).toInt();
        } else if (i == 3) {
            n_hojas = arr.at(i).toInt();
        }
    }
    Rama rama;
    rama = data->programa.tallos[n_tallo].ramas[data->rama_cambiar];
    int cHojas = data->programa.tallos[n_tallo].getCHojas();
    printf("crear la cantidad de %d\n", n_hojas - cHojas);
    printf("Se crearan %d hijos, para cada rama\n", n_hojas - cHojas);
    regresarHojas(data->rama_cambiar, n_hojas - cHojas);
    for (int j = 0; j < n_hojas - cHojas; ++j) {
        rama.hojas[cHojas+j] = data->hmanipulada[j];
    }
    rama.setCHojas(n_hojas);
    data->programa.tallos[n_tallo].ramas[data->rama_cambiar] = rama;
    printf("SALIR DE CREAR HOJAS");
    kill(data->pid_p, SIGHUP);
}

void leerTexto() {
    QString str = QString(data->comando);
    printf("El comando es: %s\n", data->comando);
    QStringList arr = str.split(",");
    string accion;
    int n_tallo = 0, n_ramas = 0, n_hojas = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if(i==0) {
            accion = arr.at(i).toStdString();
        } else if(i == 1) {
            n_tallo = arr.at(i).toInt() - 1;
        } else if (i == 2) {
            n_ramas = arr.at(i).toInt();
        } else if (i == 3) {
            n_hojas = arr.at(i).toInt();
        }
    }
    data->tallo_mostrado = n_tallo;
    if(accion == "P"){
        if(n_tallo < data->programa.getCTallos()) {
            modificarAspectos(n_tallo, n_ramas, n_hojas);
        } else if(n_tallo == data->programa.getCTallos()) {
            printf("Tallo: %d, NRamas: %d, NHojas: %d\n", n_tallo, n_ramas, n_hojas);
            crearProceso(n_tallo, n_ramas, n_hojas);
        }
    }
}

void regresarRamas(int n_ramas, int n_hojas) {
    printf("incializando ramas!!\n");
    for (int i = 0; i < n_ramas; i++) {
        int pidr = fork();
        if(pidr == 0) {
            signal(SIGINT, crearHojasNuevas);
            Rama rama;
            rama.setCHojas(n_hojas);
            rama.setPID(getpid());
            regresarHojas(i, n_hojas);
            for (int j = 0; j < n_hojas; ++j) {
                rama.hojas[j] = data->hmanipulada[j];
            }
            //rama.hojas = hojas;
            data->rmanipulada[i] = rama;
            printf("finalizando hojas!! %d\n", rama.getPID());
            bucleRama(data->tallo_mostrado, i);
            break;
        } else if(pidr < 0){

        } else if(pidr > 0) {
            signal(SIGHUP, signalHup);
            pause();
        }
    }
}

void regresarHojas(int n_rama, int n_hojas) {
    printf("incializando hojas!!\n");
    for (int j = 0; j < n_hojas; j++) {
        int pidh = fork();
        if(pidh == 0) {
            Hoja hoja;
            hoja.setPID(getpid());
            data->hmanipulada[j] = hoja;
            printf("Hoja:  %d\n", data->hmanipulada[j].getPID());
            kill(getppid(), SIGHUP);
            bucleHoja(data->tallo_mostrado, n_rama, j);
            break;
        } else if(pidh < 0){

        } else if (pidh > 0){
            signal(SIGHUP, signalHup);
            //printf("padre y mi pid es: %d\n", getpid());
            pause();
            //printf("padre y mi pid es: %d\n", getpid());
        }
    }
}

void pintarTallo() {
    Tallo tallo = data->programa.tallos[data->tallo_mostrado];
    printf("*****%d\n", tallo.getPID());
    for (int i = 0; i < tallo.getCRamas(); ++i) {
        Rama rama = tallo.ramas[i];
        printf("********%d\n", rama.getPID());
        for (int j = 0; j < tallo.getCHojas(); ++j) {
            printf("***********%d\n", rama.hojas[j]);
        }
    }
}

void crearProceso(int n_tallo, int n_ramas, int n_hojas) {
    printf("incializado!!\n");
    int pid = fork();
    if(pid == 0) {
        Tallo Qtallo;
        Qtallo.setPID(getpid());
        Qtallo.setCHojas(n_hojas);
        Qtallo.setCRamas(n_ramas);
        regresarRamas(n_ramas, n_hojas);
        for (int i = 0; i < n_ramas; ++i) {
            Qtallo.ramas[i] = data->rmanipulada[i];
        }
        data->programa.tallos[n_tallo] = Qtallo;
        printf("finalizando ramas!! %d\n", data->programa.tallos[n_tallo].getPID());
        data->programa.aumentarCTallos();
        printf("finalizado!\n");
        data->tallo_mostrado = n_tallo;
        pintarTallo();
        bucleTallo(n_tallo);
    } else if (pid > 0) {
        signal(SIGHUP, signalHup);
        pause();
    } else if (pid <0) {

    }
}

void modificarAspectos(int n_tallo, int n_ramas, int n_hojas) {
    int cRamas = data->programa.tallos[n_tallo].getCRamas();
    if(cRamas > n_ramas) {
        data->programa.tallos[n_tallo].eliminarRamas(n_ramas);
    } else if (cRamas < n_ramas) {
        kill(data->programa.tallos[n_tallo].getPID(), SIGINT);
        signal(SIGHUP, signalHup);
        pause();
    }
    data->programa.tallos[n_tallo].setCRamas(n_ramas);
    int cHojas = data->programa.tallos[n_tallo].getCHojas();
    cRamas = data->programa.tallos[n_tallo].getCRamas();
    if(cHojas > n_hojas) {
        data->programa.tallos[n_tallo].eliminarHojas(n_hojas);
    } else if (cHojas < n_hojas) {
        for (int i = 0; i < cRamas; i++) {
            signal(SIGHUP, signalHup);
            printf("%d) hasta donde llega el cambiar? %d\n", i,data->programa.tallos[n_tallo].ramas[i].getPID());
            data->rama_cambiar = i;
            kill(data->programa.tallos[n_tallo].ramas[i].getPID(), SIGINT);
            pause();
        }
    }
    data->programa.tallos[n_tallo].setCHojas(n_hojas);
}

void bucleTallo(int n_tallo) {
    signal(SIGINT, crearRamasNuevas);
    kill(getppid(), SIGHUP);
    while(true) {
        if(n_tallo == data->tallo_mostrado){
            int num = rand() % 2;
            //printf("colorTallo: %d\n", num);
        }
        sleep(1);
    }
}

void bucleRama(int n_tallo, int n_rama) {
    kill(getppid(), SIGHUP);
    while(true) {
        if(n_tallo == data->tallo_mostrado){
            int num = rand() % 2;
            //printf("colorTallo: %d\n", num);
        }
        //printf("colorRama: %d\n", num);
        sleep(1);
    }
}

void bucleHoja(int n_tallo, int rama, int n_hoja) {
    while(true) {
        if(n_tallo == data->tallo_mostrado){
            int num = rand() % 2;
            //printf("colorTallo: %d\n", num);
        }
        //printf("colorHoja: %d\n", num);
        sleep(1);
    }
}
