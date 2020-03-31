#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ventanatipopago.h"
#include "impresion.h"
//ventanaPago*
#include "ventanapagotarjeta.h"
#include "ventanapagocheques.h"
//No se incluye implementacion de ventana para Efectivo por causas obvias
//--------------
//Json
#include "json.h"
#include <QFileDialog>
//--------------
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cuenta->setReadOnly(true); //Evitar que el usuario introduzca caracteres no validos
    ui->total->setText("0€");
    total = 0;
    ui->nombreSesion->setText("-----------------------");
    numeroTarjeta = "";
    pagado = false;
    //Para que el usuario pueda seleccionar varios articulos al mismo tiempo:
    ui->listaArticulos->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //El tipo de pago, por defecto, no esta seleccionado
    tipopago = Nulo;
    //Por defecto, esta sesion se considera nueva
    nuevoJson = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSalir_triggered()
{
    exit(0);
}

void MainWindow::on_actionCerrar_triggered()
{
    ui->cuenta->clear();
    ui->tipoPago->clear();
    ui->total->setText("0€");
    ui->listaArticulos->clear();
    total = 0;
    tipopago = Nulo;
    if(!nuevoJson){
        json.cerrarJson();
        ui->nombreSesion->setText("-----------------------");
        nuevoJson = true;
    }
}

void MainWindow::on_boton1_clicked()
{
    ui->cuenta->setText(ui->cuenta->text()+"1");
}

void MainWindow::on_boton2_clicked()
{
    ui->cuenta->setText(ui->cuenta->text()+"2");
}

void MainWindow::on_boton3_clicked()
{
    ui->cuenta->setText(ui->cuenta->text()+"3");
}

void MainWindow::on_boton4_clicked()
{
    ui->cuenta->setText(ui->cuenta->text()+"4");
}

void MainWindow::on_boton5_clicked()
{
    ui->cuenta->setText(ui->cuenta->text()+"5");
}

void MainWindow::on_boton6_clicked()
{
    ui->cuenta->setText(ui->cuenta->text()+"6");
}

void MainWindow::on_boton7_clicked()
{
    ui->cuenta->setText(ui->cuenta->text()+"7");
}

void MainWindow::on_boton8_clicked()
{
    ui->cuenta->setText(ui->cuenta->text()+"8");
}

void MainWindow::on_boton9_clicked()
{
    ui->cuenta->setText(ui->cuenta->text()+"9");
}

void MainWindow::on_boton0_clicked()
{
    ui->cuenta->setText(ui->cuenta->text()+"0");
}

void MainWindow::on_botonSiguiente_clicked()
{
    //Modificar el total
    QString txtCuenta = ui->cuenta->text();
    if(txtCuenta.isEmpty()) return;
    total += txtCuenta.toInt();
    ui->total->setText(QString::number(total) + "€");
    //Añadir el objeto a la lista
    new QListWidgetItem(txtCuenta+"€", ui->listaArticulos);
    ui->cuenta->clear();
}

void MainWindow::on_pushButton_2_clicked() //Eliminar articulos
{
    QList<QListWidgetItem*> lista = ui->listaArticulos->selectedItems();
    for(int i = 0; i < lista.size(); ++i)
    {
        QString txt = lista.at(i)->text();
        txt.truncate(txt.size()-1); //Quitamos el €
        //Restamos del total la cantidad de los elementos seleccionados
        int cantidadAQuitar = txt.toInt();
        total -= cantidadAQuitar;
        /*
        * Como takeItem() requere de la columna, la obtenemos con row(),
        * que pide un QListWidgetItem*, los cueles se encuentran en nuestra lista
        */
        ui->listaArticulos->takeItem(ui->listaArticulos->row(lista.at(i)));
    }
    ui->total->setText(QString::number(total) + "€"); //Mostramos el nuevo total
}

void MainWindow::on_cambiarTipoPago_clicked()
{
    ventanaTipoPago ventana;
    ventana.setModal(true);
    if(ventana.exec() == QDialog::DialogCode::Rejected) return;
    switch(ventana.tipodepago)
    {
    case ventanaTipoPago::Tarjeta: {
        ui->tipoPago->setText("Con Tarjeta");
        tipopago = Tarjeta;
    }
        break;
    case ventanaTipoPago::Efectivo: {
        ui->tipoPago->setText("En Efectivo");
        tipopago = Efectivo;
    }
        break;
    case ventanaTipoPago::Cheques: {
        ui->tipoPago->setText("Con Cheques");
        tipopago = Cheque;
    }
        break;
    }
}

void MainWindow::on_pagar_clicked()
{
    if(ui->listaArticulos->count() == 0){
        QMessageBox::critical(this, "Error", "No hay artículos a pagar");
        return;
    }

    switch(tipopago)
    {
    case MainWindow::Nulo:{
        QMessageBox::critical(this, "Error", "No se ha seleccionado un tipo de pago");
        return;
    }
    case MainWindow::Tarjeta:{
        ventanaPagoTarjeta ventana(total);
        ventana.setModal(true);
        if(ventana.exec() == QDialog::DialogCode::Rejected) return;
        numeroTarjeta = ventana.numeroTarjeta;
    }
        break;
    case MainWindow::Efectivo:{
        QMessageBox::information(this, "Pagado", "Pagado correctamente");
    }
        break;
    case MainWindow::Cheque:{
        ventanaPagoCheques ventana(total);
        ventana.setModal(true);
        if(ventana.exec() == QDialog::DialogCode::Rejected) return;
    }
        break;
    }
    pagado = true; //Ya esta pagado
    if(QMessageBox::question(this, "Recibo", "¿Quiere imprimir un recibo ahora?")
            == QMessageBox::Yes)
    {
        on_recibo_clicked(); //Imprimir
    }
    if(QMessageBox::question(this, "Terminar", "¿Quiere terminar la sesión ahora? No podrás"
                             " imprimir un recibo después de esta acción")
            == QMessageBox::Yes)
    {
        on_actionCerrar_triggered(); //Cerrar
    }
}

void MainWindow::on_recibo_clicked()
{
    //Obtenemos la lista de articulos
    if(ui->listaArticulos->count() == 0)
    {
        QMessageBox::critical(this, "Error", "No hay artículos a pagar");
        return;
    }
    QList<QListWidgetItem*> lista;
    for(int i = 0; i < ui->listaArticulos->count(); ++i)
    {
        lista.push_back(ui->listaArticulos->item(i));
    }
    //Comprobamos el total y el estado de pago
    if(!pagado)
    {
        QMessageBox::critical(this, "Error", "No se ha completado el pago");
        return;
    }
    if(total == 0)
    {
        QMessageBox::critical(this, "Error", "El total es 0");
        return;
    }
    Impresion impresion(this, lista, total);
    //Seleccionamos el tipo de pago
    switch(tipopago)
    {
    case Nulo:{
        QMessageBox::critical(this, "Error", "No se ha seleccionado tipo de pago");
        return;
    }
    case Tarjeta:{
        impresion.setTipoPago(Impresion::TipoPago::Tarjeta);
        impresion.setNumeroTarjeta(numeroTarjeta);
    }
        break;
    case Efectivo:{
        impresion.setTipoPago(Impresion::TipoPago::Efectivo);
    }
        break;
    case Cheque:{
        impresion.setTipoPago(Impresion::TipoPago::Cheques);
    }
        break;
    }
    impresion.imprimir();
    QMessageBox::information(this, "Información", "Pdf creado correctamente");
}

void MainWindow::on_borrar_clicked()
{
    QString txt = ui->cuenta->text();
    txt.truncate(txt.size()-1);
    ui->cuenta->setText(txt);
}

//JSON:
QString MainWindow::obtenerNombreSesion(QString path)
{
    QFileInfo f(path);
    if(!f.isFile())
        return QString();
    return f.baseName();
}

void MainWindow::on_actionAbrir_triggered()
{
    if(QMessageBox::question(this, "Atención", "¿Seguro que quieres abrir una nueva sesión? "
                             "Esta sesión se cerrará.") == QMessageBox::No)
        return;

    QString nombreArchivoJson =
            QFileDialog::getOpenFileName(this, "Abrir Sesión...", QDir::currentPath(),
                                         "Archivos JSON (*.json)");
    if(nombreArchivoJson.isEmpty()) return;
    if(json.abrirJson(nombreArchivoJson, this) == -1)
    {
        QMessageBox::critical(this, "Error", "Ha ocurrido un error al abrir el archivo proporcionado. "
                                             "Revise el sistema de ficheros.");
        return;
    }
    nuevoJson = false;

    Json::Sesion sesion = json.interpretarJson();
    //Primero, cerramos la sesion: ------------
    //No usamos la funcion dedicada porque destruye la clase JSON, lo que provocará crash
    ui->total->setText("0€");
    ui->tipoPago->clear();
    ui->listaArticulos->clear();
    ui->cuenta->clear();
    //Importamos los cambios -------------
    //Primero el total:
    total = sesion.total;
    ui->total->setText(QString::number(total));
    //Despues si esta pagado o no:
    pagado = sesion.pagado;
    //Ahora el tipo de pago (y el numero de tarjeta):
    switch(sesion.tipopago)
    {
    case Json::TipoPago::Nulo:{
        tipopago = MainWindow::Nulo;
    }
        break;
    case Json::TipoPago::Tarjeta:{
        tipopago = MainWindow::Tarjeta;
        ui->tipoPago->setText("Con Tarjeta");
        numeroTarjeta = sesion.tarjeta;
    }
        break;
    case Json::TipoPago::Efectivo:{
        tipopago = MainWindow::Efectivo;
        ui->tipoPago->setText("En Efectivo");
    }
        break;
    case Json::TipoPago::Cheques:{
        tipopago = MainWindow::Cheque;
        ui->tipoPago->setText("Con Cheques");
    }
        break;
    }
    //Ahora importamos la lista de articulos:
    for(int i = 0; i < sesion.listaArticulos.size(); ++i)
    {
        new QListWidgetItem(sesion.listaArticulos.at(i), ui->listaArticulos);
    }
    //Por ultimo, indicamos el nombre de la sesion:
    ui->nombreSesion->setText(obtenerNombreSesion(nombreArchivoJson));
}

void MainWindow::on_actionGuardar_triggered()
{
    QString nombreArchivoJson;
    if(nuevoJson)
    {
        nombreArchivoJson = QFileDialog::getSaveFileName(this, "Guardar sesión...", QDir::currentPath(),
                                     "Archivos JSON (*.json)");
        if(nombreArchivoJson.isEmpty()) return;

    }
    else
        nombreArchivoJson = json.getNombreArchivo();

    nuevoJson = false;
    //Configuramos el total
    json.setTotal(total);
    //Configuramos la lista
    if(ui->listaArticulos->count() == 0)
    {
        QMessageBox::critical(this, "Error", "La lista de artículos está vacía.");
        return;
    }
    QList<QListWidgetItem*> lista;
    for(int i = 0; i < ui->listaArticulos->count(); ++i)
    {
        lista.push_back(ui->listaArticulos->item(i));
    }
    json.setArticulos(lista);
    //Configuramos el tipo de pago
    switch(tipopago)
    {
    case Nulo:{
        json.setTipoPago(Json::TipoPago::Nulo);
    }
        break;
    case Tarjeta:{
        json.setTipoPago(Json::TipoPago::Tarjeta);
        json.setnumeroTarjeta(numeroTarjeta);
    }
        break;
    case Efectivo:{
        json.setTipoPago(Json::TipoPago::Efectivo);
    }
        break;
    case Cheque:{
        json.setTipoPago(Json::TipoPago::Cheques);
    }
        break;
    }
    //Mandamos el estado de la compra
    json.setPagado(pagado);
    //Lo guardamos
    json.anadirParametros(this);
    if(json.guardarJson(nombreArchivoJson) == -1)
    {
        QMessageBox::critical(this, "Error", "Ha habido un error al salvar la sesión. "
                                             "Revise el sistema de archivos.");
        return;
    }
    //Indicamos el nombre de la sesion:
    ui->nombreSesion->setText(obtenerNombreSesion(nombreArchivoJson));
}

void MainWindow::on_actionGuardar_como_triggered()
{
    QString nombreArchivoJson = QFileDialog::getSaveFileName(this, "Guardar sesión como...",
                                                             QDir::currentPath(),
                                                             "Archivos JSON (*.json)");
    if(nombreArchivoJson.isEmpty()) return;
    //Comprobaciones:
    if(total <= 0)
    {
        QMessageBox::critical(this, "Error", "Inicie la sesión de compra para guardar esta sesión");
        return;
    }
    if(ui->listaArticulos->count() == 0) return;
    //Creamos el JSON
    json.setTotal(total);
    json.setPagado(pagado);
    //Obtenemos los articulos
    QList<QListWidgetItem*> lista;
    for(int i = 0; i < ui->listaArticulos->count(); ++i)
    {
        lista.push_back(ui->listaArticulos->item(i));
    }
    json.setArticulos(lista);
    //Obtenemos el tipo de pago
    switch(tipopago){
    case Nulo:{
        json.setTipoPago(Json::TipoPago::Nulo);
    }
        break;
    case Tarjeta:{
        json.setTipoPago(Json::TipoPago::Tarjeta);
        json.setnumeroTarjeta(numeroTarjeta);
    }
        break;
    case Efectivo:{
        json.setTipoPago(Json::TipoPago::Efectivo);
    }
        break;
    case Cheque:{
        json.setTipoPago(Json::TipoPago::Cheques);
    }
        break;
    }
    //Creamos el Json
    json.anadirParametros(this);
    if(json.guardarJson(nombreArchivoJson) == -1)
    {
        QMessageBox::critical(this, "Error", "Ha habido un error al salvar la sesión. "
                                             "Revise el sistema de archivos");
        return;
    }
    //Indicamos el nombre de la sesion:
    ui->nombreSesion->setText(obtenerNombreSesion(nombreArchivoJson));
}
