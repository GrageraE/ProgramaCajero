#ifndef VENTANAACTUALIZAR_H
#define VENTANAACTUALIZAR_H

#include <QDialog>
#include "actualizacion.h"

namespace Ui {
class ventanaActualizar;
}

class ventanaActualizar : public QDialog
{
    Q_OBJECT

public:
    explicit ventanaActualizar(Actualizacion::Respuesta _respuesta, QString _Version, QWidget *parent = nullptr);
    ~ventanaActualizar();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::ventanaActualizar *ui;
    Actualizacion::Respuesta r;
    QString VERSION;
};

#endif // VENTANAACTUALIZAR_H
