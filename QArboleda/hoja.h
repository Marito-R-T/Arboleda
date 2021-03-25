#ifndef HOJA_H
#define HOJA_H


class Hoja
{
private:
    int pid, ppid, id;
    bool seguir = true;
    bool eliminar = false;
    int p[2];
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
};

#endif // HOJA_H
