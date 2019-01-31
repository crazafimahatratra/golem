#ifndef DIALOGOPTIONS_H
#define DIALOGOPTIONS_H

#include <QDialog>
#include "models/goption.h"

namespace Ui {
class DialogOptions;
}

/**
 * @brief Ui for Options
 */
class DialogOptions : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent : parent widget
     */
    explicit DialogOptions(QWidget *parent = 0);
    ~DialogOptions();

private slots:
    void on_checkBoxUpdate_stateChanged();

    void on_checkBoxBackup_stateChanged();

    void on_pushButtonBrowse_clicked();

    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

    void on_lineEditBackupPath_textChanged(const QString &arg1);

private:
    Ui::DialogOptions *ui;
    Goption *m_option;
    void setCurrentUpdateSchedule(Goption::UpdateSchedule value);
    void setCurrentBackupSchedule(Goption::BackupSchedule value);
    void setCurrentBackupFileNaming(Goption::BackupFileNaming value);
    void load();
    void save();
};

#endif // DIALOGOPTIONS_H
