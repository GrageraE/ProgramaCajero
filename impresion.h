#ifndef IMPRESION_H
#define IMPRESION_H
#include <QListWidgetItem>
#include <QPrinter>

class Impresion
{
    //private:
    enum TipoPago{
        Tarjeta,
        Efectivo,
        Cheques
    }tipopago;

public:
    Impresion(QList<QListWidgetItem*> _lista, int _total, Impresion::TipoPago _tipoPago);
    void escribirPdf();
    void imprimir();
    void setNumeroTarjeta(int _numero);
private:
    QPrinter printer;
    const QString nombre = "recibo.pdf";
    QList<QListWidgetItem*> lista;
    int total;
    int numeroTarjeta;
};

#endif // IMPRESION_H
