#include "hoja.h"

Hoja::Hoja()
{

}

int Hoja::getPID() {
    return this->pid;
}

void Hoja::setPID(int pid) {
    this->pid = pid;
}

int Hoja::getPPID() {
    return this->ppid;
}

void Hoja::setPPID(int ppid) {
    this->ppid = ppid;
}

int Hoja::getID() {
    return this->id;
}

void Hoja::setID(int id) {
    this->id = id;
}

void Hoja::setSeguir(bool seguir) {
    this->seguir = seguir;
}

void Hoja::setEliminar(bool eliminar) {
    this->eliminar = eliminar;
}

int Hoja::getP0() {
    return p[0];
}

int Hoja::getP1() {
    return p[1];
}

int* Hoja::getP() {
    return p;
}

void Hoja::proceso() {
    while(seguir) {
        usleep(1000000);
    }
    if(eliminar) {
        return;
    } else {
        proceso();
    }
}

/* Esperar, donde este esta atento a la escritura del proceso principal, con el read
 esto lee si es el 1ero el tallo, el 2do es la rama, el 3ro es la hoja*/
void Hoja::esperar() {
    //while(true) {
        int nbytes;
        char inbuf[2];
        int i = 0;
        int n_h=-1;
        while((nbytes = read(p[0],inbuf, 2)) > 0){
            QString str = QString(inbuf);
            if (i == 0) {
                n_h = str.toInt();
                if(n_h == -1) {
                    exit(0);
                }
            }
            i++;
        }
        exit(0);
    //}
}

int Hoja::getR() {
    this->r;
}

int Hoja::getG() {
    this->g;
}

int Hoja::getB() {
    this->b;
}

void Hoja::setRGB(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}
