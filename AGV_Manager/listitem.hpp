#ifndef LISTITEM_HPP
#define LISTITEM_HPP

#include <QWidget>

namespace Ui {
class ListItem;
}

class ListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ListItem(QString title, QString robot, QWidget *parent = nullptr);
    ~ListItem();

private:
    Ui::ListItem *ui;
};

#endif // LISTITEM_HPP
