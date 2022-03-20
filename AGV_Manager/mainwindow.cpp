#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QListWidget>
#include <QPalette>
#include <listitem.hpp>


#define BACKGROUND_COLOR QColor(42, 42, 42)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new Scene(this))
{
    ui->setupUi(this);

    add_list_item("Task #1", "AGV Red");
    add_list_item("Task #2", "AGV Green");
    add_list_item("Task #3", "AGV Blue");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_list_item(QString title, QString robot)
{
    QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(listWidgetItem);
    ListItem *theWidgetItem = new ListItem(title, robot, this);
    listWidgetItem->setSizeHint(theWidgetItem->sizeHint ());
    ui->listWidget->setItemWidget(listWidgetItem, theWidgetItem);
}
