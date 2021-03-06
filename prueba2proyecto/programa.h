#ifndef PROGRAMA_H
#define PROGRAMA_H

#include <tallo.h>
#include <QString>
#include <vector>

class Programa
{
private:
    std::vector<Tallo> tallos;
    int pid;
    int cantidad_tallos;
    int cantidad_ramas;
    int cantidad_hojas;
    int pos_tallo;
    void proceso();
    bool seguir = true;
    bool eliminar = false;
public:
    Programa();
    int getPID();
    void setPID(int pid);
    int getCTallos();
    void setCTallos(int cantidad_tallos);
    int p[2];
    void setCRamas(int cantidad_ramas);
    void setCHojas(int cantidad_hojas);
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
    void esperar();
};

#endif // PROGRAMA_H
