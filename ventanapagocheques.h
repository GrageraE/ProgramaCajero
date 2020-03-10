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
    int dineroPagado;
};

#endif // VENTANAPAGOCHEQUES_H
