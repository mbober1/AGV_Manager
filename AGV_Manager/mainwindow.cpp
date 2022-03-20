#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new Scene(this))
{
    ui->setupUi(this);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(scene, 0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
