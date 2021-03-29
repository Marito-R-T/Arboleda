#ifndef HOJA_H
#define HOJA_H

#include <unistd.h>
#include <stdio.h>
#include <QString>
#include <wait.h>

class Hoja
{
private:
    int pid, ppid, id;
    bool seguir = true;
    bool eliminar = false;
    int p[2];
    int r, g, b;
public:
    Hoja();
    int getPID();
    void setPID(int pid);
    int getPPID();
    void setPPID(int ppid);
    int getID();
    int getP0();
    int getP1();
    int* getP();
    void setID(int id);
    void setSeguir(bool seguir);
    void setEliminar(bool eliminar);
    void proceso();
    void esperar();
    int getR();
    int getG();
    int getB();
    void setRGB(int r, int g, int b);
};

#endif // HOJA_H
