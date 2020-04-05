#include "actualizacion.h"
#include <QMessageBox>
#include <QEventLoop>
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

void Actualizacion::comprobarActualizaciones()
{
    //Realizamos la consulta
    QNetworkAccessManager* manager = new QNetworkAccessManager(parent);
    QNetworkReply* r =
            manager->get(QNetworkRequest(QUrl("https://api.github.com/repos/GrageraE/ProgramaCajero/releases/latest")));
    /*
     * La razón por la que está este loop aquí es porque esta API es asíncrona. Esto significa que
     * debemos esperar a que Qt reciba los datos, y esta espera debe de ser realizada manualmente.
     * Para ello, usaremos la clase QEventLoop, que proporciona un bucle que se ejecutará hasta que
     * reciba una cierta señal. Esta señal será QNetworkReply::finished() (no sé si la clase está bien).
     * Al recibir esta señal, se ejecutará QEventLoop::quit(), que parará el bucle. Para ese entonces,
     * QNetworkAccessManager ya habrá obtenido todos los datos del request.
    */
    QEventLoop loop;
    QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit())); //Significa que cuando termine, pare el bucle
    loop.exec(); //Aquí empieza el bucle
    //Interpretamos la respuesta
    if(r->error())
    {
        QMessageBox::critical(parent, "Error", "Error de red: " + r->errorString());
        return;
    }
    recogerRespuesta(QString(r->readAll()));
}

void Actualizacion::recogerRespuesta(QString reply)
{
    //Interpretar el JSON
    nlohmann::json j;
    j = nlohmann::json::parse(reply.toStdString());
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
