#include "impresion.h"
#include <QListWidgetItem>
//QtPrint
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QPrintDialog>

Impresion::Impresion(QList<QListWidgetItem*> _lista, int _total)
{
    lista = _lista;
    tipopago = Nulo;
    total = _total;
    numeroTarjeta = 0;
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
    painter.setFont(QFont("Times", 10));

    QRect rect(painter.viewport()); //TODO: El rectángulo se crea en el medio; no en el principio
    painter.drawText(rect, Qt::AlignCenter | Qt::AlignTop, "Recibo");
    int linea = 200;
    for(int i = 0; i < lista.size(); ++i)
    {
        painter.drawText(100, linea, "Articulo " + QString::number(i+1) + ": ");
        painter.drawText(1080, linea, lista.at(i)->text());
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
        painter.drawText(100, linea, "Numero de tarjeta: " + QString::number(numeroTarjeta));
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

void Impresion::setNumeroTarjeta(int _numero)
{
    numeroTarjeta = _numero;
}

void Impresion::setTipoPago(TipoPago _tipopago)
{
    tipopago = _tipopago;
}
