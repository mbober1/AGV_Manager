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

    connect(scene, &Scene::test, this, &MainWindow::test);

    add_list_item("Task #1", "AGV Red");
    add_list_item("Task #2", "AGV Green");
    add_list_item("Task #3", "AGV Blue");
    add_list_item("Task #4", "Not assigned");
    add_list_item("Task #5", "Not assigned");
    add_list_item("Task #6", "Not assigned");

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

    this->list_items.append(theWidgetItem);
}

void MainWindow::test(int progress)
{
    list_items.at(0)->update_progress(progress);
}
