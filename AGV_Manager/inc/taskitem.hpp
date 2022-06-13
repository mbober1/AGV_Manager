#ifndef TASKITEM_HPP
#define TASKITEM_HPP

#include <QWidget>

namespace Ui
{
    class TaskItem;
}

class TaskItem : public QWidget
{
    Q_OBJECT


public:
    explicit TaskItem(QString robot, QWidget *parent = nullptr);
    ~TaskItem();

public slots:
    void update_progress(int progress);
    void update_id(int id);

private:
    Ui::TaskItem *ui;
    QString assigned_to;
};

#endif // TASKITEM_HPP
