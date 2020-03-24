#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ventanatipopago.h"
//ventanaPago*
#include "ventanapagotarjeta.h"
#include "ventanapagocheques.h"
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
    if(!nuevoJson) json.~Json();
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
        numeroTarjeta = ventana.nTarjeta;
    }
        break;
    case MainWindow::Efectivo:{

    }
        break;
    case MainWindow::Cheque:{
        ventanaPagoCheques ventana(total);
        ventana.setModal(true);
        if(ventana.exec() == QDialog::DialogCode::Rejected) return;
    }
        break;
    }
    pagado = true;
    on_actionCerrar_triggered(); //Cierra la sesión
}

//JSON:
void MainWindow::on_actionAbrir_triggered()
{
    QString nombreArchivoJson =
            QFileDialog::getOpenFileName(this, "Abrir Sesión...", QDir::currentPath(),
                                         "Archivos JSON (*.json)");
    if(nombreArchivoJson.isEmpty()) return;
    json.abrirJson(nombreArchivoJson, this);
    nuevoJson = false;

}

void MainWindow::on_actionGuardar_triggered()
{
    QString nombreArchivoJson;
    if(nuevoJson)
    {
        nombreArchivoJson = QFileDialog::getSaveFileName(this, "Guardar sesión...", QDir::currentPath(),
                                     "Archivos JSON (*.json)");

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
    json.guardarJson(nombreArchivoJson);
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
    json.guardarJson(nombreArchivoJson);
}
