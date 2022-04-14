#include "inc/mainwindow.hpp"
#include "build/ui_mainwindow.h"

#include <QListWidget>
#include <QPalette>


#define BACKGROUND_COLOR QColor(42, 42, 42)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new Scene(this))
{
    ui->setupUi(this);

    connect(scene, &Scene::test, this, &MainWindow::test);

    add_list_item("AGV Red");
    add_list_item("AGV Green");
    add_list_item("AGV Blue");
    add_list_item("Not assigned");
    add_list_item("Not assigned");
    add_list_item("Not assigned");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_list_item(QString robot)
{
    QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(listWidgetItem);

    TaskItem *theWidgetItem = new TaskItem(robot, this);
    listWidgetItem->setSizeHint(theWidgetItem->sizeHint ());
    ui->listWidget->setItemWidget(listWidgetItem, theWidgetItem);

    this->list_items.append(theWidgetItem);
}

void MainWindow::test(int progress)
{
    list_items.at(0)->update_progress(progress);
}
