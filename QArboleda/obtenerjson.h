#ifndef OBTENERJSON_H
#define OBTENERJSON_H

#include <QJsonObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ObtenerJson
{
public:
    ObtenerJson();
    static QJsonObject getObjeto();
    static QJsonObject getTallo(int tallo);
    static QJsonObject getRama(int tallo, int rama);
    static QJsonObject getHoja(int tallo, int rama, int hoja);
    static void modificarObjeto(QJsonObject objeto);
    static void modificarTallo(QJsonObject Qtallo, int tallo);
    static void modificarRama(QJsonObject Qrama, int tallo, int rama);
    static void modificarHoja(QJsonObject Qhoja, int tallo, int rama, int hoja);
    static QString leerComando();
};

#endif // OBTENERJSON_H
