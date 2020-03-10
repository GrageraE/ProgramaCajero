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

void ventanaPagoCheques::on_pushButton_clicked()
{
    QString cheque = ui->cheque->text();

}
