#ifndef TALLO_H
#define TALLO_H

#include <rama.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <QString>
#include <random>

class Tallo
{
private:
    int pid, id;
    void proceso();
    int cantidad_ramas;
    int cantidad_hojas;
    bool seguir = true;
    bool eliminar = false;
    int r, g, b;
    int p[2];
public:
    Rama ramas[5];
    Tallo();
    int getPID();
    void setPID(int pid);
    int getID();
    void setID(int id);
    int getCRamas();
    void setCRamas(int cantidad_ramas);
    int getCHojas();
    int getP0();
    int getP1();
    int* getP();
    void setCHojas(int cantidad_hojas);
    void setSeguir(bool seguir);
    void setEliminar(bool eliminar);
    void producirRamas(int n_ramas);
    void producirHojas(int n_ramas, int n_hojas);
    void generarRamas();
    void crearRamas(int n_ramas, int n_hojas);
    void crearRamas(int n_ramas);
    void eliminarRamas(int n_ramas);
    void eliminarHojas(int n_hojas);
    void cambiarRamas(int n_hojas);
    void esperar();
    int getR();
    int getG();
    int getB();
    void setRGB(int r, int g, int b);
};

#endif // TALLO_H
