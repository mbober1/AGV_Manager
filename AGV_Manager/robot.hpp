#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <QPoint>
#include <QVector>
#include <QColor>

class Robot
{
public:
    Robot(QPoint home_position, QPoint drawing_offset, QColor MainColor, QColor SecondColor);

    QPoint position;
    QPoint drawing_offset;
    QVector<QPoint> path_points;
    QColor MainColor;
    QColor SecondColor;
};

#endif // ROBOT_HPP
