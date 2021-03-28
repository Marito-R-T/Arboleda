#include "obtenerjson.h"

ObtenerJson::ObtenerJson()
{

}

QJsonObject ObtenerJson::getObjeto() {
    ifstream in("prueba.json");
    string linea, frase;
    while(!in.eof()){
        getline(in, linea);
        frase.append(linea.append("\n"));
    }
    QJsonObject objeto = QJsonValue(QString(frase.c_str())).toObject();
    in.close();
    return objeto;
}

QJsonObject ObtenerJson::getTallo(int tallo) {
    ifstream in("prueba.json");
    string linea, frase;
    while(!in.eof()){
        getline(in, linea);
        frase.append(linea.append("\n"));
    }
    QJsonObject objeto = QJsonValue(QString(frase.c_str())).toObject();
    QJsonArray tallos = objeto["tallos"].toArray();
    in.close();
    if(tallos.size() > tallo) {
        return tallos[tallo].toObject();
    }
    return QJsonObject();
}

QJsonObject ObtenerJson::getRama(int tallo, int rama) {
    ifstream in("prueba.json");
    string linea, frase;
    while(!in.eof()){
        getline(in, linea);
        frase.append(linea.append("\n"));
    }
    in.close();
    QJsonObject objeto = QJsonValue(QString(frase.c_str())).toObject();
    QJsonArray tallos = objeto["tallos"].toArray();
    if(tallos.size() > tallo) {
        QJsonArray ramas = tallos[tallo].toObject()["ramas"].toArray();
        if(ramas.size() > rama) {
            return ramas[rama].toObject();
        }
    }
    return QJsonObject();
}

QJsonObject ObtenerJson::getHoja(int tallo, int rama, int hoja) {
    ifstream in("prueba.json");
    string linea, frase;
    while(!in.eof()){
        getline(in, linea);
        frase.append(linea.append("\n"));
    }
    in.close();
    QJsonObject objeto = QJsonValue(QString(frase.c_str())).toObject();
    QJsonArray tallos = objeto["tallos"].toArray();
    if(tallos.size() > tallo) {
        QJsonArray ramas = tallos[tallo].toObject()["ramas"].toArray();
        if(ramas.size() > rama) {
            QJsonArray hojas = ramas[rama].toObject()["ramas"].toArray();
            if(hojas.size() > hoja) {
                return hojas[hoja].toObject();
            }
        }
    }
    return QJsonObject();
}

void ObtenerJson::modificarObjeto(QJsonObject objeto) {
    QJsonDocument documento = QJsonDocument(objeto);
    ofstream of("prueba.json");
    of << documento.toJson().toStdString();
    of.close();
}

void ObtenerJson::modificarTallo(QJsonObject objeto, int tallo) {
    QJsonObject programa = ObtenerJson::getObjeto();
    QJsonArray Qtallos = programa["tallos"].toArray();
    if(Qtallos.size() > tallo) {
        Qtallos.replace(tallo, objeto);
    }
    programa["tallos"] = Qtallos;
    QJsonDocument documento = QJsonDocument(programa);
    ofstream of("prueba.json");
    of << documento.toJson().toStdString();
    of.close();
}

void ObtenerJson::modificarRama(QJsonObject objeto, int tallo, int rama) {
    QJsonObject programa = ObtenerJson::getObjeto();
    QJsonObject Qtallo = ObtenerJson::getTallo(tallo);
    if(!Qtallo.isEmpty()){
        QJsonArray Qramas = Qtallo["ramas"].toArray();
        if(Qramas.size() > rama) {
            Qramas.replace(rama, objeto);
        }
        Qtallo["ramas"] = Qramas;
        QJsonArray Qtallos = programa["tallos"].toArray();
        Qtallos.replace(tallo, Qtallo);
        programa["tallos"] = Qtallos;
        QJsonDocument documento = QJsonDocument(programa);
        ofstream of("prueba.json");
        of << documento.toJson().toStdString();
        of.close();
    }
}

void ObtenerJson::modificarHoja(QJsonObject objeto, int tallo, int rama, int hoja) {
    QJsonObject programa = ObtenerJson::getObjeto();
    QJsonObject QTallo = ObtenerJson::getTallo(tallo);
    QJsonObject QRama = ObtenerJson::getRama(tallo, rama);
    if(!QTallo.isEmpty() && !QRama.isEmpty()){
        QJsonArray QHojas = QRama["hojas"].toArray();
        if(QHojas.size() > hoja) {
            QHojas.replace(hoja, objeto);
        }
        QRama["hojas"] = QHojas;
        QJsonArray QRamas = QTallo["ramas"].toArray();
        QRamas.replace(rama, QRama);
        QTallo["ramas"] = QRamas;
        QJsonArray QTallos = programa["tallos"].toArray();
        QTallos.replace(tallo, QTallo);
        programa["tallos"] = QTallos;
        QJsonDocument documento = QJsonDocument(programa);
        ofstream of("prueba.json");
        of << documento.toJson().toStdString();
        of.close();
    }
}

QString ObtenerJson::leerComando() {
    QJsonObject obj = ObtenerJson::getObjeto();
    return obj["comando"].toString();
}
