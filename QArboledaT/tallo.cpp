#include "tallo.h"

Tallo::Tallo()
{
}

int Tallo::getPID() {
    return this->pid;
}

void Tallo::setPID(int pid) {
    this->pid = pid;
}

int Tallo::getID() {
    return this->id;
}

void Tallo::setID(int id) {
    this->id = id;
}

int Tallo::getCHojas() {
    return this->cantidad_hojas;
}

void Tallo::setCHojas(int cantidad_hojas) {
    this->cantidad_hojas = cantidad_hojas;
}

int Tallo::getCRamas() {
    return this->cantidad_ramas;
}

void Tallo::setCRamas(int cantidad_ramas) {
    this->cantidad_ramas = cantidad_ramas;
}

void Tallo::setSeguir(bool seguir) {
    this->seguir = seguir;
}

void Tallo::setEliminar(bool eliminar) {
    this->eliminar = eliminar;
}

int Tallo::getP0() {
    return p[0];
}

int Tallo::getP1() {
    return p[1];
}

int* Tallo::getP() {
    return p;
}

void Tallo::crearRamas(int n_ramas, int n_hojas) {
    /*for (int i=0;i < n_ramas; i++) {
        Rama rama = Rama();
        int pid_p;
        if (pipe(rama.getP()) < 0) {
            exit(1);
        }
        pid_p = fork();
        if(pid_p == -1){
            printf("Error al crear proceso hijo\n");
            break;
        } else if (pid_p == 0) {
            rama.setPID(getpid());
            rama.setPPID(this->pid);
            rama.setID(i);
            this->ramas.push_back(rama);
            rama.esperar();
            return;
        }
    }
    this->cantidad_ramas=ramas.size();
    this->cantidad_hojas=n_hojas;
    this->cambiarRamas(n_hojas);*/
}

void Tallo::crearRamas(int n_ramas) {
    this->crearRamas(n_ramas, 0);
}

void Tallo::producirHojas(int n_ramas, int n_hojas) {
    if (n_ramas < this->cantidad_ramas) {
        this->eliminarRamas(cantidad_ramas-n_ramas);
    } else if (n_ramas > this->cantidad_ramas) {
        this->crearRamas(n_ramas - this->cantidad_ramas, n_hojas);
    } else {
        this->cambiarRamas(n_hojas);
    }
}

void Tallo::eliminarRamas(int n_ramas) {
    /*for (int i = ramas.size() - 1; i > ramas.size() - n_ramas - 1; i--) {
        QString str = QString(-1);
        write(this->ramas.at(i).getP1(), str.toStdString().c_str(), 4);
        ramas.pop_back();
    }*/
}

void Tallo::cambiarRamas(int n_hojas) {
    /*for (int i = 0; i < this->ramas.size(); i++) {
        QString ram = QString(n_hojas);
        write(this->ramas.at(i).getP1(), ram.toStdString().c_str(), 4);
    }*/
}

void Tallo::producirRamas(int n_ramas) {
    this->producirHojas(n_ramas, 0);
}

/* Esperar, donde este esta atento a la escritura del proceso principal, con el read
 esto lee si es el 1ero el tallo, el 2do es la rama, el 3ro es la hoja*/
void Tallo::esperar() {
    //while(true) {
        /*int nbytes;
        char inbuf[2];
        int i = 0;
        int n_r=-1, n_h=-1;
        while((nbytes = read(p[0],inbuf, 2)) > 0){
            QString str = QString(inbuf);
            if (i == 0) {
                n_r = str.toInt();
            } else if (i == 1) {
                n_h = str.toInt();
            }
            i++;
        }
        if(n_h != -1) {
            producirHojas(n_r, n_h);
        } else if(n_r != -1) {
            producirRamas(n_r);
        } else if(n_r == -1) {
            eliminarRamas(this->ramas.size());
            exit(0);
        }
        exit(0);*/
    //}
}

void Tallo::proceso() {
    while(seguir) {
        usleep(1000000);
    }
    if(eliminar) {
        return;
    } else {
        proceso();
    }
}
