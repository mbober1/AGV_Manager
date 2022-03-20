#include "robot.hpp"

Robot::Robot(QPoint home_position, QPoint drawing_offset, QColor MainColor, QColor SecondColor) :
    position(home_position),
    drawing_offset(drawing_offset),
    MainColor(MainColor),
    SecondColor(SecondColor)
{
    QPoint p1(250, 50);
    QPoint p2(940, 50);
    QPoint p3(940, 270);
    QPoint p4(250, 270);
    QPoint p5(250, 600);
    QPoint p6(750, 600);
    QPoint p7(750, 630);

    this->path_points.append(this->position);
    this->path_points.append(p1);
    this->path_points.append(p2);
    this->path_points.append(p3);
    this->path_points.append(p4);
    this->path_points.append(p5);
    this->path_points.append(p6);
    this->path_points.append(p7);
}
