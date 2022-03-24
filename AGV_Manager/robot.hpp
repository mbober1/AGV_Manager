#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <QPoint>
#include <QVector>
#include <QColor>

class Robot
{
public:
    Robot(const QPoint &home_position, const QPoint &drawing_offset, const QColor &MainColor, const QColor &SecondColor);
    const QVector<QPoint> &get_path();
    const QPoint &get_position();
    void add_point(const QPoint &point);
    void move(const QPoint &vector);
    void checkpoint();
    void clear_path();
    int get_path_len();
    int get_progress();

    QPoint drawing_offset;
    QColor MainColor;
    QColor SecondColor;

private:
    QPoint position;
    QVector<QPoint> path_points;
    int get_len(const QPoint &point1, const QPoint &point2);

};

#endif // ROBOT_HPP
