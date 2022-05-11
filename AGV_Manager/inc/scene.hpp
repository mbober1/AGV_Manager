#ifndef SCENE_HPP
#define SCENE_HPP

#include <QWidget>
#include <QTimer>
#include "inc/robot.hpp"
#include "inc/Stage.hpp"

class Scene : public QWidget
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);

private:
    QVector<Robot> robots;
    Stage* backend;
    QTimer* animation_timer;
    int point_size = 8;
    int line_size = 6;

    void animation_update();
    QVector<QPoint> create_grid(size_t width, size_t height);
    QVector<QPoint> warehouse_points;

signals:
    void test(int progress);

};

#endif // SCENE_HPP
