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
 * "nombreJson". Ademas, requiere de QWidget* para lanzar QMessageBox's
 * @Retorna 0 en caso de exito y -1 en caso de fallo
*/
int Json::abrirJson(QString _nombreJson, QWidget* _parent)
{
    nombreJson = _nombreJson;
    parent = _parent;
    //Abrimos el archivo
    leerArchivo.open(nombreJson.toStdString(), ios::in);
    if(leerArchivo.fail()){
        return -1;
    }
    j = nlohmann::json::parse(leerArchivo);
    leerArchivo.close();
    return 0;
}

/*
 * Esta funcion rellena una estructura "Sesion", con los datos del Json
 * Antes de invocarla, hay que llamar a abrirJson(QString, QWidget*)
 * En caso de fallar, retorna conjunto vacio({})
*/
Json::Sesion Json::interpretarJson()
{
    //Declaracion de constantes:
    const std::string TOTAL = "Total";
    const std::string PAGADO = "Pagado";
    const std::string TIPOPAGO = "Tipo de pago";
    const std::string NUMERO_TARJETA = "Numero de tarjeta";
    const std::string ARTICULOS = "Articulos:";
    //------------------------------

    if(parent == nullptr)
    {
        qDebug() <<"No se ha configurado un QWidget*. Abortar";
        return {};
    }
    Sesion sesion;
    //Obtenemos el total:
    sesion.total = j.at(TOTAL);
    //Obtenemos el valor de si esta pagado o no:
    sesion.pagado = j.at(PAGADO);
    //Obtenemos el tipo de pago
    if(j.at(TIPOPAGO) == "No seleccionado")
    {
        sesion.tipopago = Nulo;
    }
    else if(j.at(TIPOPAGO) == "Con tarjeta")
    {
        sesion.tipopago = Tarjeta;
        sesion.tarjeta = QString::fromStdString(j.at(NUMERO_TARJETA));
    }
    else if(j.at(TIPOPAGO) == "En efectivo")
    {
        sesion.tipopago = Efectivo;
    }
    else if(j.at(TIPOPAGO) == "Con cheques")
    {
        sesion.tipopago = Cheques;
    }
    //Y obtenemos la lista de articulos
    int cantidadArticulos = j.at(ARTICULOS).at("Cantidad: ");
    for(int i = 0; i < cantidadArticulos; ++i)
    {
        sesion.listaArticulos.push_back(QString::fromStdString(j.at(ARTICULOS).at("Articulo " + std::to_string(i+1))));
    }
    //Hemos terminado
    return sesion;
}

/*
 * Esta funcion guarda el JSON previamente construido con la funcion
 * Json::anadirParametros(QWidget*)
 * @☺Retorna 0 en caso de exito y -1 en caso de fallo
*/
int Json::guardarJson(QString _nombreJson)
{
    nombreJson = _nombreJson;
    //Guardamos en el archivo
    crearArchivo.open(nombreJson.toStdString(), ios::out);
    if(crearArchivo.fail())
    {
        return -1;
    }
    crearArchivo <<std::setw(4) <<j <<"\n";
    crearArchivo.close();
    return 0;
}

/*
 * Esta funcion cierra el Json ya abierto previamente.
 * Se ejecuta con el destructor. Esta funcion es privada
*/
void Json::cerrarJson()
{
    if(leerArchivo.is_open()) leerArchivo.close();
    if(crearArchivo.is_open()) crearArchivo.close();
    j.clear();
}

/*
 * Esta funcion realiza un chequeo y despues guarda los parametros ya
 * dados con los setters en el Json. Requiere un QWidget*
 * @Retorna 0 en caso de exito y -1 en caso de cualquier tipo de fallo
 * @Fallos: si la comprobacion de QWidget* sale incorrecta, ademas de retornar 0
 * tambien muestra un mensaje en la consola. En el resto de fallos, lanza un QMessageBox::critical
*/
int Json::anadirParametros(QWidget* _parent)
{
    //Comprobar el QWidget*
    if(_parent == nullptr && parent == nullptr)
    {
        qDebug() <<"Error: no se ha configurado un QWidget*. Abortar";
        return -1;
    }
    parent = _parent;
    //Comprobacion del total
    if(total <= 0)
    {
        QMessageBox::critical(parent, "Error", "El total es 0. Empieza una sesión de compra para"
                                               " guardarla.");
        return -1;
    }
    //Comprobar la lista de articulos
    if(listaArticulos.isEmpty())
    {
        QMessageBox::critical(parent, "Error", "No hay artículos añadidos");
        return -1;
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
    return 0;
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
}

void Json::setArticulos(QList<QListWidgetItem *> _lista)
{
    listaArticulos = _lista;
}
//-------------------------------
