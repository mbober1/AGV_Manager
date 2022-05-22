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
    void set_new_positions(const std::vector<int> &position_list);

private:
    QVector<Robot> robots_list;
    Stage* backend;
    QTimer* animation_timer;
    int last_point_size = 6;
    int robot_point_size = 7;
    int line_size = 6;

    void animation_update();
    QVector<QPoint> create_grid(size_t width, size_t height);
    QVector<QPoint> warehouse_points;
    void animate(Robot &agv, QPoint next_point, QPoint current_position);

signals:
    void test(int progress);

};

#endif // SCENE_HPP
