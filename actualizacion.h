#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H
#include <QString>
#include <QWidget>
#include <QNetworkReply>

class Actualizacion : public QObject
{

    Q_OBJECT

    //Esta es la version del programa
    //DEBE DE ESTAR ACTUALIZADA EN TODO MOMENTO
    const QString VERSION = "1.1.0";
    //--------------------------------
public:
    Actualizacion(QWidget* _parent);

    enum EstadoActualiacion{
        Error = -1,
        Actualizado,
        Desactualizado
    };

    struct Respuesta{
        EstadoActualiacion estado = Error;
        QString version = "-1";
        QString url = "";
        QString novedades = "";
    }respuesta;

    void comprobarActualizaciones();

private slots:
    void recogerRespuesta(QString reply);
private:
    QWidget* parent;
};

#endif // ACTUALIZACION_H
