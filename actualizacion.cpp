#include "actualizacion.h"
#include <QMessageBox>
//Cabeceras para realizar requests a GitHub:
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
//Libreria para manejar las respuestas de GitHub, es decir, JSON:
#include <../single_include/nlohmann/json.hpp>

Actualizacion::Actualizacion(QWidget* _parent)
{
    parent = _parent;
}

Actualizacion::Respuesta Actualizacion::comprobarActualizaciones()
{
    //Realizamos la consulta
    QNetworkAccessManager* manager = new QNetworkAccessManager(parent);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                     SLOT(recogerRespuesta(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("https://api.github.com/repos/GrageraE/ProgramaCajero/releases/latest")));

    delete manager;
    return respuesta;
}

void Actualizacion::recogerRespuesta(QNetworkReply* reply)
{
    if(reply->error())
    {
        //Error
        respuesta.estado = Actualizacion::Error;
        return;
    }
    //Interpretar el JSON
    nlohmann::json j;
    j = nlohmann::json::parse(reply->readAll().toStdString());
    respuesta.version = QString::fromStdString(j.at("tag_name"));
    if(respuesta.version == VERSION){
        respuesta.estado = Actualizacion::Actualizado;
    }
    else{
        respuesta.estado = Actualizacion::Desactualizado;
        respuesta.url = QString::fromStdString(j.at("html_url"));
        respuesta.novedades = QString::fromStdString(j.at("body"));
    }
}
