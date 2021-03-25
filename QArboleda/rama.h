#ifndef RAMA_H
#define RAMA_H

#include <hoja.h>
#include <vector>

class Rama
{
private:
    std::vector<Hoja> hojas;
    int pid, ppid, id;
    void proceso();
    int cantidad_hojas;
    bool seguir = true;
    bool eliminar = false;
    int p[2];
public:
    Rama();
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
    void producirHojas(int n_hojas);
    void crearHojas(int n_hojas);
    void eliminarHojas(int n_hojas);
    void generarHojas();
    void esperar();
};

#endif // RAMA_H
