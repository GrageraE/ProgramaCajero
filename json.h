#ifndef JSON_H
#define JSON_H

#include <QWidget>
#include <QListWidgetItem>
#include <../../vcpkg/JSON/single_include/nlohmann/json.hpp>
#include <fstream>
using std::ifstream;
using std::ofstream;

class Json
{

public:
    Json();
    ~Json();
    void abrirJson(QString _nombreJson, QWidget* _parent);
    void guardarJson(QString _nombreJson);
    void anadirParametros(QWidget* _parent = nullptr);
    QString getNombreArchivo();

    //Tipo de pago:
    enum TipoPago{
        Nulo = -1,
        Tarjeta,
        Efectivo,
        Cheques
    }tipopago;

    //Sesion:
    struct Sesion{
        int total;
        TipoPago tipopago;
        QString tarjeta;
        QList<QString> listaArticulos;
        bool pagado;
    };
    Sesion interpretarJson();

    //Setters
    void setTipoPago(TipoPago _tipopago);
    void setTotal(int _total);
    void setnumeroTarjeta(QString _numeroTarjeta);
    void setPagado(bool _pagado);
    void setArticulos(QList<QListWidgetItem*> _lista);

private:
    void cerrarJson();
    QWidget* parent;
    QString nombreJson;
    int total;
    QString tarjeta;
    bool pagado;
    QList<QListWidgetItem*> listaArticulos;

    nlohmann::json j;
    ifstream leerArchivo;
    ofstream crearArchivo;

};

#endif // JSON_H
