#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>

namespace Ui {
class DialogAbout;
}

/**
 * @brief This is about the **about dialog**
 */
class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent widget
     */
    explicit DialogAbout(QWidget *parent = 0);
    ~DialogAbout();

private:
    Ui::DialogAbout *ui;
    QString readlicense(QString filename);
};

#endif // DIALOGABOUT_H
