#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ventanatipopago.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cuenta->setReadOnly(true); //Evitar que el usuario introduzca caracteres no validos
    ui->total->setText("0");
    //Para que el usuario pueda seleccionar varios articulos al mismo tiempo:
    ui->listaArticulos->setSelectionMode(QAbstractItemView::ExtendedSelection);
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
    ui->total->clear();
    ui->listaArticulos->clear();
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
    QString txtCuenta = ui->cuenta->text();
    if(txtCuenta.isEmpty()) return;
    ui->total->setText(QString::number(ui->total->text().toInt() + txtCuenta.toInt()));
    new QListWidgetItem(txtCuenta+"€", ui->listaArticulos);
    ui->cuenta->clear();
}

void MainWindow::on_pushButton_2_clicked() //Eliminar articulo
{
    QList<QListWidgetItem*> lista = ui->listaArticulos->selectedItems();
    for(int i = 0; i < lista.size(); ++i)
    {
        /*
         * Como takeItem() requere de la columna, la obtenemos con row(),
         * que pide un QListWidgetItem*, los cueles se encuentran en nuestra lista
         */
        ui->listaArticulos->takeItem(ui->listaArticulos->row(lista.at(i)));
    }
}

void MainWindow::on_cambiarTipoPago_clicked()
{
    ventanaTipoPago ventana;
    ventana.setModal(true);
    if(ventana.exec() == QDialog::DialogCode::Rejected) return;
    switch(ventana.tipodepago)
    {
    case ventanaTipoPago::Tarjeta: ui->tipoPago->setText("Con Tarjeta");
        break;
    case ventanaTipoPago::Efectivo: ui->tipoPago->setText("En Efectivo");
        break;
    case ventanaTipoPago::Cheques: ui->tipoPago->setText("Con Cheques");
        break;
    }
}
