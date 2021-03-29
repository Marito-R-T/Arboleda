#ifndef RAMA_H
#define RAMA_H

#include <hoja.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <QString>
#include <random>

class Rama
{
private:
    int pid, ppid, id;
    void proceso();
    int cantidad_hojas;
    bool seguir = true;
    bool eliminar = false;
    int r, g, b;
    int p[2];
public:
    Rama();
    Hoja hojas[10];
    int getPID();
    void setPID(int pid);
    int getPPID();
    void setPPID(int ppid);
    int getID();
    void setID(int id);
    int getP0();
    int getP1();
    int* getP();
    int getCHojas();
    void setCHojas(int cantidad_hojas);
    void setSeguir(bool seguir);
    void setEliminar(bool eliminar);
    void eliminarTHojas();
    void producirHojas(int n_hojas);
    void crearHojas(int n_hojas);
    void eliminarHojas(int n_hojas);
    void generarHojas();
    void esperar();
    int getR();
    int getG();
    int getB();
    void setRGB(int r, int g, int b);
};

#endif // RAMA_H
