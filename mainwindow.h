#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "json.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSalir_triggered();

    void on_actionCerrar_triggered();

    void on_boton1_clicked();

    void on_boton2_clicked();

    void on_boton3_clicked();

    void on_boton4_clicked();

    void on_boton5_clicked();

    void on_boton6_clicked();

    void on_boton7_clicked();

    void on_boton8_clicked();

    void on_boton9_clicked();

    void on_boton0_clicked();

    void on_botonSiguiente_clicked();

    void on_pushButton_2_clicked();

    void on_cambiarTipoPago_clicked();

    void on_pagar_clicked();

    void on_actionAbrir_triggered();

    void on_actionGuardar_triggered();

    void on_actionGuardar_como_triggered();

private:
    Ui::MainWindow *ui;
    enum TipoPago{
        Nulo = -1, //Tipo de pago no seleccionado
        Tarjeta,
        Efectivo,
        Cheque
    }tipopago;
    int total;
    QString numeroTarjeta;
    bool pagado;

    Json json;
    bool nuevoJson;
};
#endif // MAINWINDOW_H
