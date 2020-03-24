#include "json.h"
#include <QMessageBox>
#include <QDebug>
#include <QWidget>
#include <QListWidgetItem>
//Libreria JSON
//TODO: Cambiar la ubicación del single_include
#include <../../vcpkg/JSON/single_include/nlohmann/json.hpp>
//Manejo de archivos
#include <iomanip> //std::setw
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::ios;

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
    //Abrimos el archivo
    leerArchivo.open(nombreJson.toStdString(), ios::in);
    if(leerArchivo.fail()){
        //TODO: Manejo de errores
        return;
    }
    j = nlohmann::json::parse(leerArchivo);
    leerArchivo.close();
    return; //TODO: Manejar esto
}

/*
 * Esta funcion rellena una estructura "Sesion", con los datos del Json
 * Antes de invocarla, hay que llamar a abrirJson(QString, QWidget*)
 * En caso de fallar, retorna conjunto vacio({})
*/
Json::Sesion Json::interpretarJson()
{
    if(parent == nullptr)
    {
        qDebug() <<"No se ha configurado un QWidget*. Abortar";
        return {};
    }
    Sesion sesion;
    //Obtenemos el total:
    sesion.total = j.at("Total");
    //Obtenemos el valor de si esta pagado o no:
    sesion.pagado = j.at("Pagado");
    //Obtenemos el tipo de pago
    if(j.at("Tipo de pago") == "No seleccionado")
    {
        sesion.tipopago = Nulo;
    }
    else if(j.at("Tipo de pago") == "Con tarjeta")
    {
        sesion.tipopago = Tarjeta;
        sesion.tarjeta = QString::fromStdString(j.at("Numero de tarjeta"));
    }
    else if(j.at("Tipo de pago") == "En efectivo")
    {
        sesion.tipopago = Efectivo;
    }
    else if(j.at("Tipo de pago") == "Con cheques")
    {
        sesion.tipopago = Cheques;
    }
    //Y obtenemos la lista de articulos
    int cantidadArticulos = j.at("Articulos:").at("Cantidad: ");
    for(int i = 0; i < cantidadArticulos; ++i)
    {
        sesion.listaArticulos.push_back(QString::fromStdString(j.at("Articulos:").at("Articulo " + std::to_string(i+1))));
    }
    //Hemos terminado
    return sesion;
}

/*
 * Esta funcion guarda el JSON previamente construido con la funcion
 * Json::anadirParametros(QWidget*)
*/
void Json::guardarJson(QString _nombreJson)
{
    nombreJson = _nombreJson;
    //Guardamos en el archivo
    crearArchivo.open(nombreJson.toStdString(), ios::out);
    if(crearArchivo.fail())
    {
        //TODO: manejar esto
        return;
    }
    crearArchivo <<std::setw(4) <<j <<"\n";
    crearArchivo.close();
    //TODO: manejar esto:
    return;
}

/*
 * Esta funcion cierra el Json ya abierto previamente.
 * Se ejecuta con el destructor (funcion privada).
*/
void Json::cerrarJson()
{
    if(leerArchivo.is_open()) leerArchivo.close();
    if(crearArchivo.is_open()) crearArchivo.close();
    j.clear();
}

/*
 * Esta funcion realiza un chequeo y despues guarda los parametros ya
 * dados con los setters en el Json. Requiere un QWidget* opcional
*/
void Json::anadirParametros(QWidget* _parent) /*=nullptr*/
{
    //Comprobar el QWidget*
    if(_parent == nullptr && parent == nullptr)
    {
        qDebug() <<"Error: no se ha configurado un QWidget*. Abortar";
        return;
    }
    parent = _parent;
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
    //----------------------
    //Guardamos el total
    j["Total"] = total;
    //Guardamos el tipo de pago
    switch(tipopago){
    case Nulo:{
        j["Tipo de pago"] = "No seleccionado";
    }
        break;
    case Tarjeta:{
        j["Tipo de pago"] = "Con tarjeta";
        j["Numero de tarjeta"] = tarjeta.toInt();
    }
        break;
    case Efectivo:{
        j["Tipo de pago"] = "En efectivo";
    }
        break;
    case Cheques:{
        j["Tipo de pago"] = "Con cheques";
    }
        break;
    }
    //Guardamos si esta pagado o no
    j["Pagado"] = pagado;
    //Guardamos la lista de articulos
    j["Articulos:"]["Cantidad: "] = listaArticulos.size();
    for(int i = 0; i < listaArticulos.size(); ++i)
    {
        j["Articulos:"]["Articulo " + std::to_string(i+1)] = listaArticulos.at(i)->text().toStdString();
    }
    return; //TODO: manejar esto
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
