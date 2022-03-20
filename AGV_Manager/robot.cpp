#include "robot.hpp"
#include <QtMath>

Robot::Robot(const QPoint &home_position, const QPoint &drawing_offset, const QColor &MainColor, const QColor &SecondColor) :
    drawing_offset(drawing_offset),
    MainColor(MainColor),
    SecondColor(SecondColor),
    position(home_position)
{
    QPoint p1(250, 50);
    QPoint p2(940, 50);
    QPoint p3(940, 270);
    QPoint p4(250, 270);
    QPoint p5(250, 600);
    QPoint p6(750, 600);
    QPoint p7(750, 630);

    this->add_point(p1);
    this->add_point(p2);
    this->add_point(p3);
    this->add_point(p4);
    this->add_point(p5);
    this->add_point(p6);
    this->add_point(p7);
}

const QVector<QPoint> &Robot::get_path()
{
    return this->path_points_show;
}

void Robot::clear_path()
{
    this->path_points_show.clear();
}

int Robot::get_len(const QPoint &point1, const QPoint &point2)
{
    auto tmp = point1 - point2;
    return sqrt( pow(tmp.x(), 2) + pow(tmp.y(), 2) );
}

int Robot::get_path_len()
{
    int lenght = 0;
    int point_count = this->path_points_show.size();

    if (point_count > 1)
    {
        for(int i = 0; i < point_count - 1; i++)
        {
            lenght += get_len(this->path_points_show[i], this->path_points_show[i + 1]);
        }
    }

    return lenght;
}

void Robot::add_point(const QPoint &point)
{
    this->path_points_show.append(point);
}

const QPoint &Robot::get_position()
{
    return this->position;
}

void Robot::move(const QPoint &vector)
{
    this->position += vector;
}

void Robot::checkpoint()
{
    this->path_points_show.pop_front();
}
