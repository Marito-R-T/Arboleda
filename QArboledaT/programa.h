#ifndef PROGRAMA_H
#define PROGRAMA_H

#include <tallo.h>
#include <QString>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <QStringList>
#include <obtenerjson.h>
#include <string>

class Programa
{
private:
    int pid;
    int cantidad_tallos = 0;
    Tallo elegido;
    int pos_tallo;
    void proceso();
    bool seguir = true;
    bool eliminar = false;
public:
    Programa();
    Tallo tallos[10];
    int getPID();
    void setPID(int pid);
    int getCTallos();
    void aumentarCTallos();
    int p[2];
    void setPosTallo(int pos_tallo);
    void setSeguir(bool seguir);
    void setEliminar(bool eliminar);
    void leerTexto(QString nombre);
    void crearTallo(int n_tallo, int n_ramas, int n_hojas);
    void crearTallo(int n_tallo, int n_ramas);
    void crearTallo(int n_tallo);
    void cambiarTallo(int tallo, int n_ramas, int n_hojas);
    void cambiarTallo(int tallo, int n_ramas);
    void producirTallos(int n_tallos);
    void producirRamas(int n_tallos, int n_ramas);
    void producirHojas(int n_tallos, int n_ramas, int n_hojas);
};

#endif // PROGRAMA_H
