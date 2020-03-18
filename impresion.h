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

    Impresion(QWidget* _parent, QList<QListWidgetItem*> _lista, int _total);
    void imprimir();
    void setNumeroTarjeta(QString _numero);
    void setTipoPago(TipoPago _tipopago);
private:
    QPrinter printer;
    const QString nombre = "recibo.xps";
    QList<QListWidgetItem*> lista;
    int total;
    QString numeroTarjeta;
    void escribirPdf();
    QWidget* parent;
};

#endif // IMPRESION_H
