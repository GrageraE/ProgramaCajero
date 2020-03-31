#ifndef JSON_H
#define JSON_H

#include <QWidget>
#include <QListWidgetItem>
#include <../single_include/nlohmann/json.hpp>

class Json
{

public:
    Json();
    int abrirJson(QString _nombreJson, QWidget* _parent);
    int guardarJson(QString _nombreJson);
    void cerrarJson();
    int anadirParametros(QWidget* _parent);
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
    QWidget* parent;
    QString nombreJson;
    int total;
    QString tarjeta;
    bool pagado;
    QList<QListWidgetItem*> listaArticulos;

    nlohmann::json j;

    //Declaracion de constantes:
    const std::string TOTAL = "Total";
    const std::string PAGADO = "Pagado";
    const std::string TIPOPAGO = "Tipo de pago";
    const std::string NUMERO_TARJETA = "Numero de tarjeta";
    const std::string ARTICULOS = "Articulos:";
    //------------------------------

};

#endif // JSON_H
