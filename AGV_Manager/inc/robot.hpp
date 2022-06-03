#pragma once

#include <QPoint>
#include <QVector>
#include <QColor>

enum class Robot_State
{
    READY,
    DRIVING,
    ARRIVED
};

class Robot
{
public:
    Robot();
    Robot(const QPoint &home_position, const QColor &MainColor, const QColor &SecondColor, int id);
    const QVector<QPoint> &get_path();
    const QPoint &get_position();
    const QPoint &get_next_point();

    void add_point(const QPoint &point);
    void move(const QPoint &vector);

    // void set_ready();
    // void set_not_ready();
    // bool is_ready();
    bool is_arrived();

    void set_path(std::list<int> &path, const QVector<QPoint> &warehouse_points);
    void clear_path();
    void next_point();

    int get_path_len();
    int get_progress();
    void set_position(const QPoint &new_position);

    int get_id();

    QColor MainColor;
    QColor SecondColor;
    Robot_State state;

private:
    QPoint position;
    QVector<QPoint> path_points;
    int get_len(const QPoint &point1, const QPoint &point2);
    int id;

};