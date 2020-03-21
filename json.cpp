#include "json.h"
#include <QMessageBox>
#include <QDebug>
#include <QWidget>
#include <QListWidgetItem>
//Libreria JSON
//TODO: Cambiar la ubicación del single_include
#include <../../vcpkg/JSON/single_include/nlohmann/json.hpp>

Json::Json()
{
    //Inicializacion de datos
    parent = nullptr;
    tarjeta = "";
    total = 0;
    pagado = false;
    tipopago = Nulo;
    listaArticulos.clear();
}

Json::~Json()
{
    cerrarJson();
}

/*
 * Esta funcion abre un archivo Json con el argumento
 * "nombreJson". Ademas, requiere de QWidget* para lanzar
 * en un futuro QMessageBox's
*/
void Json::abrirJson(QString _nombreJson, QWidget* _parent)
{
    nombreJson = _nombreJson;
    parent = _parent;
    //TODO: Usar la libreria
}

/*
 * Esta funcion cierra el Json ya abierto previamente.
 * Se ejecuta con el destructor.
*/
void Json::cerrarJson()
{
    //TODO: Usar la libreria
}

/*
 * Esta funcion realiza un chequeo y despues guarda los parametros ya
 * dados con los setters en el Json
*/
void Json::anadirParametros()
{
    //Comprobar el QWidget*
    if(parent == nullptr)
    {
        qDebug() <<"Error: no se ha inicializado el parametro QWidget*. Abortar";
        return;
    }
    //Comprobacion del total
    if(total <= 0)
    {
        QMessageBox::critical(parent, "Error", "El total es 0. Empieza una sesión de compra para"
                                               " guardarla.");
        return;
    }
    //Comprobar la lista de articulos
    if(listaArticulos.isEmpty())
    {
        QMessageBox::critical(parent, "Error", "No hay artículos añadidos");
        return;
    }
    //Comprobar el tipo de pago
    switch (tipopago) {
    case Nulo:{
        QMessageBox::critical(parent, "Error", "No se ha seleccionado un tipo de pago");
        return;
    }
    default: break;
    }
    //TODO: Usar la libreria
    //----------------------
}

QString Json::getNombreArchivo()
{
    return nombreJson;
}

//Setters: -------------------
void Json::setTotal(int _total)
{
    total = _total;
}

void Json::setPagado(bool _pagado)
{
    pagado = _pagado;
}

void Json::setTipoPago(TipoPago _tipopago)
{
    tipopago = _tipopago;
}

void Json::setnumeroTarjeta(QString _numeroTarjeta)
{
    tarjeta = _numeroTarjeta;
    setPagado(true); //De por si esta pagado
}

void Json::setArticulos(QList<QListWidgetItem *> _lista)
{
    listaArticulos = _lista;
}
//-------------------------------
