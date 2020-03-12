#include "ventanapagocheques.h"
#include "ui_ventanapagocheques.h"
#include <QMessageBox>

ventanaPagoCheques::ventanaPagoCheques(int _total, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaPagoCheques)
{
    ui->setupUi(this);
    total = _total;
    ui->total->setText(QString::number(total) + "€");
    dineroPagado = 0;
    ui->dineroPagado->setText("0€");
}

ventanaPagoCheques::~ventanaPagoCheques()
{
    delete ui;
}

void ventanaPagoCheques::on_buttonBox_rejected()
{
    reject();
}

void ventanaPagoCheques::on_buttonBox_accepted()
{
    //Recoger el dinero ya pagado con cheques
    QString txt = ui->dineroPagado->text();
    txt.truncate(txt.size()-1);
    int dineroPagado = txt.toInt();
    if(dineroPagado < total){
        QMessageBox::critical(this, "Insuficiente", "No se ha alcanzado el total. Introduzca más cheques o "
                                                    "seleccione otro tipo de pago");
        return;
    }
    QMessageBox::information(this, "Pagado", "Pago completado");
    accept();
}

void ventanaPagoCheques::on_pushButton_clicked() //Boton "Comprobar Cheque"
{
    QString cheque = ui->cheque->text();
    ui->cheque->clear();
    switch(comprobarCheque(cheque))
    {
    case Nulo:{
        QMessageBox::critical(this, "Error", "El cheque introducido no es válido");
        return;
    }
    case Diez:{
        dineroPagado += 10;
    }
        break;
    case Veinte:{
            dineroPagado += 20;
    }
        break;
    case Cincuenta:{
        dineroPagado += 50;
    }
        break;
    }
    ui->dineroPagado->setText(QString::number(dineroPagado) + "€");
}

ventanaPagoCheques::ValorCheque ventanaPagoCheques::comprobarCheque(QString cheque)
{
    //Comprobamos la suma ASCII para verificar que el cheque sea valido
    int suma = 0;
    for(int i = 0; i < cheque.size(); ++i)
    {
        suma += cheque.at(i).unicode();
    }
    if(suma != 1250){
        return Nulo;
    }
    /*
     * La longitud determina el valor:
     * 12 caracteres: 10€
     * 15 caracteres: 20€
     * 17 caracteres: 50€
    */
    switch(cheque.size())
    {
    case 12:{
        valorCheque = Diez;
    }
        break;
    case 15:{
        valorCheque = Veinte;
    }
        break;
    case 17:{
        valorCheque = Cincuenta;
    }
        break;
    default:{
        return Nulo; //Cheque no valido
    }
    }
    return valorCheque;
}
