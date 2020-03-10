#include "ventanatipopago.h"
#include "ui_ventanatipopago.h"
#include <QMessageBox>

ventanaTipoPago::ventanaTipoPago(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaTipoPago)
{
    ui->setupUi(this);
}

ventanaTipoPago::~ventanaTipoPago()
{
    delete ui;
}

void ventanaTipoPago::on_buttonBox_rejected()
{
    reject();
}

void ventanaTipoPago::on_buttonBox_accepted()
{
    switch(ui->comboBox->currentIndex())
    {
    case 0:{
        QMessageBox::critical(this, "Error", "Seleccione un tipo de pago");
        return;
    }
    case 1: tipodepago = Tarjeta;
        break;
    case 2: tipodepago = Efectivo;
        break;
    case 3: tipodepago = Cheques;
        break;
    default: reject(); /*Error*/
    }
    accept();
}
