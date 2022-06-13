#ifndef SCENE_HPP
#define SCENE_HPP

#include <QWidget>
#include <QTimer>
#include "inc/robot.hpp"
#include "inc/Stage.hpp"

#define LINE_SIZE 6
#define LAST_POINT_SIZE 6
#define ROBOT_POINT_SIZE 7

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
    QVector<QPoint> warehouse_points;

    void animation_update();
    const QVector<QPoint> create_grid(size_t width, size_t height);
    void animate(Robot &agv, const QPoint &next_point, const QPoint &current_position);
    void refresh_task_list();

signals:
    void update_task_percents(const std::vector<float> &data);

public slots:
    void set_simulation_speed(int speed);
    void timer_state(bool state);
    
};

#endif // SCENE_HPP
