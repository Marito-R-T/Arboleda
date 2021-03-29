#include "rama.h"

Rama::Rama()
{
}

int Rama::getPID() {
    return this->pid;
}

void Rama::setPID(int pid) {
    this->pid = pid;
}

int Rama::getPPID() {
    return this->ppid;
}

void Rama::setPPID(int ppid) {
    this->ppid = ppid;
}

int Rama::getID() {
    return this->id;
}

void Rama::setID(int id) {
    this->id = id;
}

int Rama::getCHojas() {
    return this->cantidad_hojas;
}

void Rama::setCHojas(int cantidad_hojas) {
    this->cantidad_hojas = cantidad_hojas;
}

void Rama::setSeguir(bool seguir) {
    this->seguir = seguir;
}

void Rama::setEliminar(bool eliminar) {
    this->eliminar = eliminar;
}

int Rama::getP0() {
    return p[0];
}

int Rama::getP1() {
    return p[1];
}

int* Rama::getP() {
    return p;
}

void Rama::eliminarHojas(int n_hojas) {
    /*for (int i = hojas.size() - 1; i > hojas.size() - n_hojas - 1; i--) {
        QString str = QString(-1);
        write(this->hojas.at(i).getP1(), str.toStdString().c_str(), 4);
        hojas.pop_back();
    }*/
}

void Rama::eliminarTHojas() {
    for (int i = 0; i < this->cantidad_hojas; ++i) {
        kill(this->hojas[i].getPID(), SIGKILL);
    }
}

void Rama::crearHojas(int n_hojas) {
    /*for (int i=0;i < n_hojas; i++) {
        Hoja hoja = Hoja();
        int pid_p;
        if (pipe(hoja.getP()) < 0) {
            exit(1);
        }
        pid_p = fork();
        if(pid_p == -1){
            printf("Error al crear proceso hijo\n");
            break;
        } else if (pid_p == 0) {
            hoja.setPID(getpid());
            hoja.setPPID(this->pid);
            hoja.setID(i + this->hojas.size());
            hojas.push_back(hoja);
            hoja.esperar();
            return;
        }
    }
    this->cantidad_hojas = hojas.size();*/
}

void Rama::producirHojas(int n_hojas) {
    if (n_hojas < this->cantidad_hojas) {
        this->eliminarHojas(cantidad_hojas-n_hojas);
    } else if (n_hojas > this->cantidad_hojas) {
        this->crearHojas(n_hojas - this->cantidad_hojas);
    }
}

/* Esperar, donde este esta atento a la escritura del proceso principal, con el read
 esto lee si es el 1ero el tallo, el 2do es la rama, el 3ro es la hoja*/
void Rama::esperar() {
    //while(true) {
        /*int nbytes;
        char inbuf[2];
        int i = 0;
        int n_h=-1;
        while((nbytes = read(p[0],inbuf, 2)) > 0){
            QString str = QString(inbuf);
            if (i == 0) {
                n_h = str.toInt();
            }
            i++;
        }
        if(n_h != -1) {
            producirHojas(n_h);
        } else {
            eliminarHojas(this->hojas.size());
            exit(0);
        }
        exit(0);*/
    //}
}

void Rama::proceso() {
    while(seguir) {
        usleep(1000000);
    }
    if(eliminar) {
        return;
    } else {
        proceso();
    }
}

int Rama::getR() {
    this->r;
}

int Rama::getG() {
    this->g;
}

int Rama::getB() {
    this->b;
}

void Rama::setRGB(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}
