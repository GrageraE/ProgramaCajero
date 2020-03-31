#include "ventanapagotarjeta.h"
#include "ui_ventanapagotarjeta.h"
#include <QMessageBox>

ventanaPagoTarjeta::ventanaPagoTarjeta(int _total, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaPagoTarjeta)
{
    ui->setupUi(this);
    numeroTarjeta = "";
    ui->numeroTarjeta->setEchoMode(QLineEdit::Password);
    ui->codigoSeguridad->setEchoMode(QLineEdit::Password);
    total = _total;
    ui->total->setText(QString::number(total) + "€");
    nTarjeta = "";
}

ventanaPagoTarjeta::~ventanaPagoTarjeta()
{
    delete ui;
}

void ventanaPagoTarjeta::on_buttonBox_rejected()
{
    reject();
}

void ventanaPagoTarjeta::on_buttonBox_accepted()
{
    //Chequeo de la integridad de los QString's
    QString tarjeta = ui->numeroTarjeta->text();
    QString codigo = ui->codigoSeguridad->text();
    if(tarjeta.size() < 16 || tarjeta.size() > 19){
        QMessageBox::critical(this, "Error", "La longitud del número de la tajeta no es correcta");
        return;
    }
    if(codigo.size() != 4)
    {
        QMessageBox::critical(this, "Error", "La longitud el código de seguridad no es válida");
        return;
    }
    QRegExp exp("\\d*");
    if(!exp.exactMatch(tarjeta))
    {
        QMessageBox::critical(this, "Error", "El número de tarjeta proporcionado no es válido");
        return;
    }
    if(!exp.exactMatch(codigo))
    {
        QMessageBox::critical(this, "Error", "El código de seguridad no es válido");
        return;
    }
    /*
     * Aquí tendría que venir toda la chisma para
     * efectuarlo correctamente (usando APIs?)
     */

    nTarjeta = tarjeta;
    QMessageBox::information(this, "Información", "Pago efectuado correctamente");
    numeroTarjeta = tarjeta;
    accept();
}
