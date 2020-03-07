#ifndef VENTANATIPOPAGO_H
#define VENTANATIPOPAGO_H

#include <QDialog>

namespace Ui {
class ventanaTipoPago;
}

class ventanaTipoPago : public QDialog
{
    Q_OBJECT

public:
    explicit ventanaTipoPago(QWidget *parent = nullptr);
    ~ventanaTipoPago();

    enum TipoPago{
        Tarjeta,
        Efectivo,
        Cheques
    }tipodepago;

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::ventanaTipoPago *ui;
};

#endif // VENTANATIPOPAGO_H
