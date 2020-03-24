#ifndef VENTANAPAGOTARJETA_H
#define VENTANAPAGOTARJETA_H

#include <QDialog>

namespace Ui {
class ventanaPagoTarjeta;
}

class ventanaPagoTarjeta : public QDialog
{
    Q_OBJECT

public:
    explicit ventanaPagoTarjeta(int _total, QWidget *parent = nullptr);
    ~ventanaPagoTarjeta();
    QString nTarjeta;

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::ventanaPagoTarjeta *ui;
    int total;
};

#endif // VENTANAPAGOTARJETA_H
