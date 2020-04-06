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

    QTextDocument* doc = new QTextDocument(ui->cuadroNovedades);
    doc->setDocumentLayout(new QPlainTextDocumentLayout(doc));
    doc->setMarkdown(r.novedades);
    ui->cuadroNovedades->setDocument(doc);
    ui->cuadroNovedades->setReadOnly(true);
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
    accept();
}
