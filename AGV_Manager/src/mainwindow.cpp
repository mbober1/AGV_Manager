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
    connect(ui->speed_box, QOverload<int>::of(&QSpinBox::valueChanged), scene, &Scene::set_simulation_speed);

    connect(ui->start_button, &QPushButton::clicked, [this]()
    {
        static bool state = true;

        state = !state;
        scene->timer_state(state);
    });

    add_list_item("AGV Red");
    add_list_item("AGV Green");
    add_list_item("AGV Blue");

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
