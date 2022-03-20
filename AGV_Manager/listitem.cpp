#include "listitem.hpp"
#include "ui_listitem.h"

ListItem::ListItem(QString title, QString robot, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItem)
{
    ui->setupUi(this);
    ui->title_label->setText(title);
    ui->robot_label->setText(robot);
}

ListItem::~ListItem()
{
    delete ui;
}
