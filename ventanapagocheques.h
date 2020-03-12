#ifndef VENTANAPAGOCHEQUES_H
#define VENTANAPAGOCHEQUES_H

#include <QDialog>

namespace Ui {
class ventanaPagoCheques;
}

class ventanaPagoCheques : public QDialog
{
    Q_OBJECT

public:
    explicit ventanaPagoCheques(int _total, QWidget *parent = nullptr);
    ~ventanaPagoCheques();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::ventanaPagoCheques *ui;
    int total;
    enum ValorCheque{
        Nulo = -1, //Cheque no valido
        Diez = 10,
        Veinte = 20,
        Cincuenta = 50
    }valorCheque;
    int dineroPagado;
    ValorCheque comprobarCheque(QString cheque);
};

#endif // VENTANAPAGOCHEQUES_H
