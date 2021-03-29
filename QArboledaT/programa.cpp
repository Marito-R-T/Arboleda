#include "programa.h"

Programa::Programa()
{

}

void Programa::leerTexto(QString nombre) {
    nombre += "n";
}

void Programa::setSeguir(bool seguir) {
    this->seguir = seguir;
}

void Programa::setPID(int pid) {
    this->pid = pid;
}

int Programa::getPID() {
    return this->pid;
}

void Programa::setEliminar(bool eliminar) {
    this->eliminar = eliminar;
}

int Programa::getCTallos() {
    return this->cantidad_tallos;
}

void Programa::setPosTallo(int pos_tallo) {
    this->pos_tallo = pos_tallo;
}

void Programa::producirHojas(int n_tallo, int n_ramas, int n_hojas) {
    if (n_tallo < this->cantidad_tallos) {
        this->cambiarTallo(n_ramas, n_hojas);
    } else {
        this->crearTallo(n_tallo, n_ramas, n_hojas);
    }
}

void Programa::producirRamas(int n_tallos, int n_ramas) {
    this->producirHojas(n_tallos, n_ramas, 0);
}

void Programa::producirTallos(int n_tallos) {
    this->producirHojas(n_tallos, 0, 0);
}

void Programa::crearTallo(int n_tallo, int n_ramas, int n_hojas) {
    /*if(n_tallo == tallos.size() + 1) {
        Tallo tallo = Tallo();
        int pid_p;
        if (pipe(tallo.getP()) < 0) {
            exit(1);
        }
        pid_p = fork();
        if(pid_p == -1){
            printf("Error al crear proceso hijo\n");
        } else if (pid_p == 0) {
            tallo.setPID(getpid());
            tallo.setID(n_tallo);
            tallos.push_back(tallo);
            tallo.esperar();
            return;
        }
        this->cantidad_tallos = tallos.size();
        this->cambiarTallo(n_tallo, n_ramas, n_hojas);
    }*/
}

void Programa::crearTallo(int n_tallo, int n_ramas) {
    this->crearTallo(n_tallo, n_ramas, 0);
}

void Programa::crearTallo(int n_tallo) {
    this->crearTallo(n_tallo, 0, 0);
}

void Programa::cambiarTallo(int tallo, int n_ramas, int n_hojas) {
        /*QString ram = QString(n_ramas);
        QString hoj = QString(n_hojas);
        write(this->tallos.at(tallo).getP1(), ram.toStdString().c_str(), 4);
        write(this->tallos.at(tallo).getP1(), hoj.toStdString().c_str(), 4);*/
}

void Programa::cambiarTallo(int tallo, int n_ramas) {
    this->cambiarTallo(tallo, n_ramas, 0);
}

void Programa::proceso() {
}

void Programa::aumentarCTallos() {
    this->cantidad_tallos++;
}

int Programa::getR() {
    return rand() % 256;
}

int Programa::getG() {
    return rand() % 256;
}

int Programa::getB() {
    return rand() % 256;
}

void Programa::cambiarCTallo(int n_tallo) {
    int ra = rand() % 2;
    if(ra == 0) {
        this->tallos[n_tallo].setRGB(155, 155, 155);
    } else {
        this->tallos[n_tallo].setRGB(255, 255, 255);
    }
}

void Programa::cambiarCRama(int n_tallo, int n_rama) {
    int r = this->getR();
    int g = this->getG();
    int b = this->getB();
    this->tallos[n_tallo].ramas[n_rama].setRGB(r,g,b);
}

void Programa::cambiarCHoja(int n_tallo, int n_rama, int n_hoja) {
    int ra = rand() % 2;
    if(ra == 0) {
        this->tallos[n_tallo].ramas[n_rama].hojas[n_hoja].setRGB(0, 187, 45);
    } else {
        this->tallos[n_tallo].ramas[n_rama].hojas[n_hoja].setRGB(128, 64, 0);
    }
}
