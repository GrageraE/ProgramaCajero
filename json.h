#ifndef JSON_H
#define JSON_H

#include <QWidget>
#include <QListWidgetItem>
#include <../../vcpkg/JSON/single_include/nlohmann/json.hpp>

class Json
{
    enum TipoPago{
        Nulo = -1,
        Tarjeta,
        Efectivo,
        Cheques
    }tipopago;

public:
    Json();
    ~Json();
    void abrirJson(QString _nombreJson, QWidget* _parent);
    void anadirParametros();
    QString getNombreArchivo();

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

};

#endif // JSON_H
