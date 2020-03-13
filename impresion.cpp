#include "impresion.h"
#include <QListWidgetItem>
//QtPrint
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QPrintDialog>

Impresion::Impresion(QList<QListWidgetItem*> _lista, int _total, Impresion::TipoPago _tipoPago)
{
    lista = _lista;
    total = _total;
    tipopago = _tipoPago;
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
    painter.setFont(QFont("Times"));

    QRect rect(painter.viewport());
    painter.drawText(rect, Qt::AlignCenter, "Recibo");
    int linea = 200;
    for(int i = 0; i < lista.size(); ++i)
    {
        painter.drawText(100, linea, "Articulo " + QString::number(i) + lista.at(i)->text());
        linea += 200;
    }
    painter.drawText(100, linea, "Total: " + QString::number(total) + "€");
    linea += 200;
    switch(tipopago)
    {
    case Tarjeta:{
        painter.drawText(100, linea, "Tipo de pago usado: con tarjeta");
        linea += 200;
        painter.drawText(100, linea, "Numero de tarjeta: ");
    }
        break;
    case Efectivo:{
        painter.drawText(100, linea, "Tipo de pago usado: efectivo");
    }
        break;
    case Cheques:{
        painter.drawText(100, linea, "Tipo de pago usado: con cheques");
    }
        break;
    }
    painter.end();
}

void Impresion::imprimir()
{
}

void Impresion::setNumeroTarjeta(int _numero)
{
    numeroTarjeta = _numero;
}
