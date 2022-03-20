#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "listitem.hpp"
#include "scene.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void add_list_item(QString title, QString robot);

public slots:
    void test(int progress);

private:
    Ui::MainWindow *ui;
    Scene* scene;
    QVector<ListItem*> list_items;

};
#endif // MAINWINDOW_HPP
