#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QWidget>
#include <QDateTime>
#include <QTreeWidgetItem>

namespace Ui {
class SearchResult;
}

class SearchResult : public QWidget
{
    Q_OBJECT

public:
    enum class SearchType
    {
        All = 0,
        Tasks = 1,
        Events = 2,
    };
    class Result
    {
    public:
        SearchType type;
        int id;
        QDateTime date;
        QString column1;
        QString column2;
        Result(SearchType type, int id, QDateTime date, QString column1, QString column2)
        {
            this->id = id;
            this->type = type;
            this->date = date;
            this->column1 = column1;
            this->column2 = column2;
        }
    };
    explicit SearchResult(QWidget *parent = 0);
    ~SearchResult();
    void search(QString pattern);
    void _search();

signals:
    void resultRowDoubleClicked(SearchType type, int object_id);

private slots:
    void on_pushButtonClear_clicked();

    void on_comboBoxWhere_currentIndexChanged(int);

    void on_lineEditPattern_returnPressed();

    void on_lineEditPattern_textChanged(const QString &arg1);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int);

private:
    Ui::SearchResult *ui;
    QList<Result> searchInTasks();
    QList<Result> searchInEvents();
    QString htmlToText(QString html);
    void addResultsToTree(QList<Result> results);
};

#endif // SEARCHRESULT_H
