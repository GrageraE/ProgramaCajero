#ifndef IMPRESION_H
#define IMPRESION_H
#include <QListWidgetItem>
#include <QPrinter>

class Impresion
{
public:
    enum TipoPago{
        Nulo = -1,
        Tarjeta,
        Efectivo,
        Cheques
    }tipopago;

    Impresion(QList<QListWidgetItem*> _lista, int _total);
    void imprimir();
    void setNumeroTarjeta(int _numero);
    void setTipoPago(TipoPago _tipopago);
private:
    QPrinter printer;
    const QString nombre = "recibo.pdf";
    QList<QListWidgetItem*> lista;
    int total;
    int numeroTarjeta;
    void escribirPdf();
};

#endif // IMPRESION_H
