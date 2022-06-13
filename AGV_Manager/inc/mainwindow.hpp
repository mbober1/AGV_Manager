#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "taskitem.hpp"
#include "inc/scene.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void add_list_item(QString robot);

public slots:
    void update_task_percent(const std::vector<float> &data);
    void update_task_id(const std::vector<int> &data);

private:
    Ui::MainWindow *ui;
    Scene* scene;
    QVector<TaskItem*> list_items;

};
#endif // MAINWINDOW_HPP
