#include "ventanaactualizar.h"
#include "ui_ventanaactualizar.h"
#include <QDesktopServices> //Usado para lanzar URLs

ventanaActualizar::ventanaActualizar(Actualizacion::Respuesta _respuesta, QString _Version, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaActualizar)
{
    ui->setupUi(this);
    //Inicializar valores
    r = _respuesta;
    VERSION = _Version;
    //Configurar el dialog
    ui->versionInstalada->setText(VERSION);
    ui->versionDisponible->setText(r.version);
    ui->cuadroNovedades->setReadOnly(true);

    //Esto está comentado porque usa features de Qt 5.14, y tengo Qt 5.13 :(
    //QTextDocument* doc = new QTextDocument();
    //doc->setMarkdown
    //ui->cuadroNovedades->setMarkdown();
    ui->cuadroNovedades->setPlainText(r.novedades); //TODO: Quitar esto
}

ventanaActualizar::~ventanaActualizar()
{
    delete ui;
}

void ventanaActualizar::on_buttonBox_rejected()
{
    reject();
}

void ventanaActualizar::on_buttonBox_accepted()
{
    QDesktopServices::openUrl(QUrl(r.url));
}
