#include "impresion.h"
#include <QListWidgetItem>
#include <QMessageBox>
//QtPrint
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QPrintDialog>

Impresion::Impresion(QWidget* _parent, QList<QListWidgetItem*> _lista, int _total)
{
    parent = _parent; //Para lanzar QMessageBox's
    lista = _lista;
    tipopago = Nulo;
    total = _total;
    numeroTarjeta = "";
    /* TODO - Decidir los pasos
    //Configuracion inicial:
    printer.setOutputFormat(QPrinter::PdfFormat); //Esta implementacion usara Pdf's
    printer.setOutputFileName(nombre); "recibo.pdf"
    printer.setPaperSize(QPrinter::A4); //Formato estandar: A4
    */
}

void Impresion::escribirPdf()
{
    //Creamos los ajustes del pdf
    QPdfWriter writer(nombre); /*"recibo.pdf"*/
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setPageMargins(QMargins(30, 30, 30, 30));
    //Creamos el dibujador, que construye el pdf
    QPainter painter(&writer);
    painter.setPen(Qt::black);
    //Cabecera:
    QFont cabecera("Times", 20, QFont::Bold); //Fuente de la cabecera
    cabecera.setUnderline(true);
    painter.setFont(cabecera);
    /*
     * Funcionamiento del constructor de QRect (https://doc.qt.io/qt-5/qrect.html#QRect-3):
     * 4000 es la coordenada x, y 70 es la coordenada y.
     * Basicamente, los dos primeros argumentos son la posicion donde
     * se escribira el rectangulo.
     * 1000 es la longitud de la base, y 300 es la altura.
     * Basicamente, estos dos ultimos argumentos son la longitud del rectangulo.
     * Informacion: https://doc.qt.io/qt-5/qrect.html
    */
    QRect rect(4000, 70, 1000, 300);
    painter.drawText(rect, Qt::AlignTop | Qt::AlignCenter, "Recibo");

    painter.setFont(QFont("Times", 10));
    int linea = 500;
    for(int i = 0; i < lista.size(); ++i)
    {
        painter.drawText(100, linea, "Articulo " + QString::number(i+1) + ": ");
        painter.drawText(1095, linea, lista.at(i)->text());
        linea += 200;
    }
    painter.setFont(QFont("Times", 15)); //Aumento del tamaño de la letra
    linea += 100; //Para dar espacio por el aumento de letra
    painter.drawText(100, linea, "Total: " + QString::number(total) + "€");
    painter.setFont(QFont("Times", 10));
    linea += 200;
    painter.drawText(100, linea, "Tipo de pago usado: ");
    painter.setFont(QFont("Times", 15));
    switch(tipopago)
    {
    case Tarjeta:{
        painter.drawText(1500, linea, "Con tarjeta");
        linea += 200;
        painter.setFont(QFont("Times", 10));
        painter.drawText(100, linea, "Numero de tarjeta: " + numeroTarjeta);
    }
        break;
    case Efectivo:{
        painter.drawText(1500, linea, "Efectivo");
    }
        break;
    case Cheques:{
        painter.drawText(1500, linea, "Con cheques");
    }
        break;
    default: return;
    }
    painter.end();
}

void Impresion::imprimir()
{
    if(tipopago == Nulo)
    {
        return;
    }
    escribirPdf();
}

void Impresion::setNumeroTarjeta(QString _numero)
{
    numeroTarjeta = _numero;
}

void Impresion::setTipoPago(TipoPago _tipopago)
{
    tipopago = _tipopago;
}
