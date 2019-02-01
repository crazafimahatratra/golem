#include "searchresult.h"
#include "ui_searchresult.h"
#include <QDebug>
#include "models/event.h"
#include "models/task.h"
#include "constants.h"
#include "qtkit/WidgetUtils/treewidget.h"

SearchResult::SearchResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchResult)
{
    ui->setupUi(this);
}

SearchResult::~SearchResult()
{
    delete ui;
}

void SearchResult::search(QString pattern)
{
    ui->lineEditPattern->setText(pattern);
    _search();
}

void SearchResult::_search()
{
    SearchType type = static_cast<SearchType>(ui->comboBoxWhere->currentIndex());
    QList<Result> results;
    QString pattern = ui->lineEditPattern->text();
    if(!pattern.isEmpty())
    {
        if(type == SearchType::All || type == SearchType::Events)
            results.append(searchInEvents());
        if(type == SearchType::All || type == SearchType::Tasks)
            results.append(searchInTasks());
    }
    addResultsToTree(results);
}

QList<SearchResult::Result> SearchResult::searchInTasks()
{
    QString pattern = ui->lineEditPattern->text();
    Task *model = new Task();
    model->select("task.*, project.name as project_name");
    model->where("title LIKE", QString("%%%1%%").arg(pattern));
    model->where("content LIKE", QString("%%1%%").arg(pattern), "OR");
    model->join("project", "project.id = project_id");
    QList<Task *> rows = model->get<Task>();
    QList<Result> results;
    for(int i = 0; i < rows.length(); i++)
    {
        results.append(Result(SearchType::Tasks, rows[i]->dueDate, rows[i]->project_name, rows[i]->title));
        delete rows[i];
    }
    delete model;
    return results;
}

QList<SearchResult::Result> SearchResult::searchInEvents()
{
    QString pattern = ui->lineEditPattern->text();
    Event *model = new Event();
    model->select("event.*, project.name as project_name");
    model->where("title LIKE", QString("%%%1%%").arg(pattern));
    model->where("content LIKE", QString("%%1%%").arg(pattern), "OR");
    model->join("project", "project.id = project_id");
    QList<Event *> rows = model->get<Event>();
    QList<Result> results;
    for(int i = 0; i < rows.length(); i++)
    {
        results.append(Result(SearchType::Events, rows[i]->evedate, rows[i]->project_name, rows[i]->title));
        delete rows[i];
    }
    delete model;
    return results;
}

void SearchResult::addResultsToTree(QList<SearchResult::Result> results)
{
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        ui->treeWidget->topLevelItem(i)->takeChildren();
    }
    for(int i = 0; i < results.length(); i++)
    {
        int index = 0;
        if(results[i].type == SearchType::Events)
            index = 1;
        QTreeWidgetItem *root = ui->treeWidget->topLevelItem(index);
        if(root)
        {
            QTreeWidgetItem *child = new QTreeWidgetItem(static_cast<int>(results[i].type));
            child->setText(0, results[i].date.toString(DATETIME_FORMAT));
            child->setText(1, results[i].column1);
            child->setText(2, results[i].column2);
            root->addChild(child);
        }
    }
    ui->treeWidget->expandAll();
    WidgetUtils::TreeWidget::hideEmptyTopTree(ui->treeWidget);
    WidgetUtils::TreeWidget::resizeColumns(ui->treeWidget);
}

void SearchResult::on_pushButtonClear_clicked()
{
    ui->lineEditPattern->clear();
    _search();
}

void SearchResult::on_comboBoxWhere_currentIndexChanged(int)
{
    _search();
}

void SearchResult::on_lineEditPattern_returnPressed()
{
    _search();
}

void SearchResult::on_lineEditPattern_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        _search();
}
