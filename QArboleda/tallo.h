#ifndef TALLO_H
#define TALLO_H

#include <rama.h>
#include <vector>

class Tallo
{
private:
    std::vector<Rama> ramas;
    int pid, id;
    void proceso();
    int cantidad_ramas;
    int cantidad_hojas;
    bool seguir = true;
    bool eliminar = false;
    int p[2];
public:
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
    void cambiarRamas(int n_hojas);
    void esperar();
};

#endif // TALLO_H
