#include "dialogoptions.h"
#include "ui_dialogoptions.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

DialogOptions::DialogOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOptions)
{
    m_option = Goption::getRow<Goption>();
    if(!m_option)
        m_option = new Goption();
    ui->setupUi(this);
    ui->comboBoxUpdateSchedule->addItem("Application starts", static_cast<int>(Goption::UpdateSchedule::appStart));
    ui->comboBoxUpdateSchedule->addItem("Daily", static_cast<int>(Goption::UpdateSchedule::daily));
    ui->comboBoxUpdateSchedule->addItem("Weekly", static_cast<int>(Goption::UpdateSchedule::weekly));
    ui->comboBoxUpdateSchedule->addItem("Monthly", static_cast<int>(Goption::UpdateSchedule::monthly));

    ui->comboBoxBackupSchedule->addItem("Application starts", static_cast<int>(Goption::BackupSchedule::appStart));
    ui->comboBoxBackupSchedule->addItem("Application closes", static_cast<int>(Goption::BackupSchedule::appClose));

    ui->comboBoxBackupFilepattern->addItem("Per minute", static_cast<int>(Goption::BackupFileNaming::perMinute));
    ui->comboBoxBackupFilepattern->addItem("Hourly", static_cast<int>(Goption::BackupFileNaming::hourly));
    ui->comboBoxBackupFilepattern->addItem("Daily", static_cast<int>(Goption::BackupFileNaming::daily));
    ui->comboBoxBackupFilepattern->addItem("Weekly", static_cast<int>(Goption::BackupFileNaming::weekly));
    ui->comboBoxBackupFilepattern->addItem("Monthly", static_cast<int>(Goption::BackupFileNaming::monthly));
    load();
}

DialogOptions::~DialogOptions()
{
    delete m_option;
    delete ui;
}

void DialogOptions::on_checkBoxUpdate_stateChanged()
{
    int arg1 = ui->checkBoxUpdate->checkState();
    ui->comboBoxUpdateSchedule->setEnabled(arg1 == Qt::Checked);
}

void DialogOptions::on_checkBoxBackup_stateChanged()
{
    int arg1 = ui->checkBoxBackup->checkState();
    ui->comboBoxBackupSchedule->setEnabled(arg1 == Qt::Checked);
    ui->comboBoxBackupFilepattern->setEnabled(arg1 == Qt::Checked);
    ui->lineEditBackupPath->setEnabled(arg1 == Qt::Checked);
    ui->pushButtonBrowse->setEnabled(arg1 == Qt::Checked);
}

void DialogOptions::on_pushButtonBrowse_clicked()
{

    QString initialPath = ui->lineEditBackupPath->text();
    QDir dir(initialPath);
    if(initialPath.isEmpty() || !dir.exists())
        initialPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString path = QFileDialog::getExistingDirectory(this, "Choosez a destination", initialPath);
    if(path.isEmpty())
        return;
    ui->lineEditBackupPath->setText(path);
}

void DialogOptions::on_pushButtonOK_clicked()
{
    save();
}

void DialogOptions::on_pushButtonCancel_clicked()
{
    this->reject();
}

void DialogOptions::on_lineEditBackupPath_textChanged(const QString &arg1)
{
    QDir qdir(arg1);
    if(!qdir.exists())
    {
        ui->lineEditBackupPath->setStyleSheet("color: red");
    } else {
        ui->lineEditBackupPath->setStyleSheet("color: black");
    }
}

void DialogOptions::setCurrentUpdateSchedule(Goption::UpdateSchedule value)
{
    for(int i = 0; i < ui->comboBoxUpdateSchedule->count(); i++)
    {
        if(ui->comboBoxUpdateSchedule->itemData(i).toInt() == static_cast<int>(value))
        {
            ui->comboBoxUpdateSchedule->setCurrentIndex(i);
            break;
        }
    }
}

void DialogOptions::setCurrentBackupSchedule(Goption::BackupSchedule value)
{
    for(int i = 0; i < ui->comboBoxBackupSchedule->count(); i++)
    {
        if(ui->comboBoxBackupSchedule->itemData(i).toInt() == static_cast<int>(value))
        {
            ui->comboBoxBackupSchedule->setCurrentIndex(i);
            break;
        }
    }
}

void DialogOptions::setCurrentBackupFileNaming(Goption::BackupFileNaming value)
{
    for(int i = 0; i < ui->comboBoxBackupFilepattern->count(); i++)
    {
        if(ui->comboBoxBackupFilepattern->itemData(i).toInt() == static_cast<int>(value))
        {
            ui->comboBoxBackupFilepattern->setCurrentIndex(i);
            break;
        }
    }
}

void DialogOptions::load()
{
    setCurrentUpdateSchedule(m_option->updateSchedule);
    setCurrentBackupSchedule(m_option->backupSchedule);
    setCurrentBackupFileNaming(m_option->backupFileNaming);
    ui->lineEditBackupPath->setText(m_option->backupPath);
    ui->checkBoxUpdate->setChecked(m_option->checkUpdate);
    ui->checkBoxBackup->setChecked(m_option->backup);
    on_checkBoxBackup_stateChanged();
    on_checkBoxUpdate_stateChanged();
}

void DialogOptions::save()
{
    m_option->updateSchedule = static_cast<Goption::UpdateSchedule>(ui->comboBoxUpdateSchedule->currentData().toInt());
    m_option->backupSchedule = static_cast<Goption::BackupSchedule>(ui->comboBoxBackupSchedule->currentData().toInt());
    m_option->backupFileNaming = static_cast<Goption::BackupFileNaming>(ui->comboBoxBackupFilepattern->currentData().toInt());
    m_option->backupPath = ui->lineEditBackupPath->text();
    m_option->checkUpdate = ui->checkBoxUpdate->isChecked();
    m_option->backup = ui->checkBoxBackup->isChecked();
    qDebug() << m_option->id;
    if(m_option->id)
    {
        m_option->update();
    }
    else
    {
        m_option->insert();
    }
    accept();
}
