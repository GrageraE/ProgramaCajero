#include "impresion.h"
#include <QListWidgetItem>
#include <QMessageBox>
//QtPrint
#include <QPrinter>
#include <QPrinterInfo>
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
    //Configuracion inicial:
    printer.setOutputFormat(QPrinter::OutputFormat::NativeFormat); //Esta implementacion usara Pdf's;
                                                                   //pero en Windows no se permite impresion
                                                                   //no nativa
    printer.setOutputFileName(nombre); //"recibo.xps"
    printer.setPaperSize(QPrinter::A4); //Formato estandar: A4
    printer.setOrientation(QPrinter::Orientation::Portrait);
    printer.setCopyCount(1);
}

void Impresion::escribirPdf()
{
    //Creamos el dibujador, que construye el pdf
    QPainter painter;
    painter.begin(&printer);
    painter.setPen(Qt::black);
    //Cabecera:
    QFont cabecera("Times", 20, QFont::Bold); //Fuente de la cabecera
    cabecera.setUnderline(true);
    painter.setFont(cabecera);
    /*
     * Funcionamiento del constructor de QRect (https://doc.qt.io/qt-5/qrect.html#QRect-3):
     * El primer argumento es la coordenada x, y el segundo es la coordenada y.
     * Basicamente, los dos primeros argumentos son la posicion donde
     * se escribira el rectangulo.
     * 1000 es la longitud de la base, y 300 es la altura.
     * Basicamente, estos dos ultimos argumentos son la longitud del rectangulo.
     * Informacion: https://doc.qt.io/qt-5/qrect.html
    */
    QRect rect(-100, -30, 1000, 300);
    painter.drawText(rect, Qt::AlignTop | Qt::AlignCenter, "Recibo");

    painter.setFont(QFont("Times", 12));
    int linea = 170;
    for(int i = 0; i < lista.size(); ++i)
    {
        painter.drawText(100, linea, "Articulo " + QString::number(i+1) + ": ");
        painter.drawText(200, linea, lista.at(i)->text());
        linea += 20;
    }
    QFont fuenteTotal("Times", 15); //Fuente del espacio del total
    fuenteTotal.setUnderline(true);
    painter.setFont(fuenteTotal);
    linea += 5; //Para dar espacio a la fuente
    painter.drawText(100, linea, "Total: " + QString::number(total) + "€");
    painter.setFont(QFont("Times", 12));
    linea += 20;
    painter.drawText(100, linea, "Tipo de pago usado: ");
    painter.setFont(QFont("Times", 15));
    switch(tipopago)
    {
    case Tarjeta:{
        painter.drawText(230, linea, "Con tarjeta");
        linea += 20;
        painter.setFont(QFont("Times", 12));
        painter.drawText(100, linea, "Numero de tarjeta: " + numeroTarjeta);
    }
        break;
    case Efectivo:{
        painter.drawText(230, linea, "Efectivo");
    }
        break;
    case Cheques:{
        painter.drawText(230, linea, "Con cheques");
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
    //Llamamos al SO para darnos una impresora
    QPrintDialog dialog(&printer, parent);
    dialog.setWindowTitle("Imprimir recibo...");
    if(dialog.exec() == QDialog::Rejected) return;
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
