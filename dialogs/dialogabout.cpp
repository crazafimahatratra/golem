#include "dialogabout.h"
#include "ui_dialogabout.h"
#include "appversion.h"
#include <QFile>
#include <QTextStream>

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    ui->labelAppName->setText(APP_NAME);
    ui->labelAppVersion->setText(QString("Version %1").arg(APP_VERSION));
    QString lic_qt = readlicense(":/others/license_qt.txt");
    ui->textBrowser->setHtml(QString("<center><h1>Qt</h1></center><pre>%2</pre>"
                                         "<center><h1>SQLite</h1></center>"
                                         "<p style='font-family:monospace'>SQLite is a small C library that implements a self-contained, "
                                        "embeddable, zero-configuration SQL database engine. -- quoted from www.sqlite.org."
                                         "According to the comments in the source files, the code is in the public domain. "
                                     "See the SQLite Copyright page on the SQLite web site for further information.</p>").arg(lic_qt));

}

DialogAbout::~DialogAbout()
{
    delete ui;
}

QString DialogAbout::readlicense(QString filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        return "ERROR";
    }
    QTextStream in(&file);
    QString res = in.readAll();
    file.close();
    return res;
}
