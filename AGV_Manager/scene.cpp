#include "scene.hpp"
#include <QPainter>
#include <QPainterPath>
#include <QBrush>

#define BACKGROUND_COLOR QColor(42, 42, 42)

#define ROBOT_RED_FIRST_COLOR QColor(0xB7, 0x1C, 0x1C)
#define ROBOT_RED_SECOND_COLOR QColor(0xEF, 0x53, 0x50)
#define ROBOT_RED_HOME QPoint(50,150)

#define ROBOT_GREEN_FIRST_COLOR QColor(0x1B, 0x5E, 0x20)
#define ROBOT_GREEN_SECOND_COLOR QColor(0x66, 0xBB, 0x6A)
#define ROBOT_GREEN_HOME QPoint(50,50)

#define ROBOT_BLUE_FIRST_COLOR QColor(0x01, 0x57, 0x9B)
#define ROBOT_BLUE_SECOND_COLOR QColor(0x29, 0xB6, 0xF6)
#define ROBOT_BLUE_HOME QPoint(50,250)

Scene::Scene(QWidget *parent)
    : QWidget{parent}
{
    this->setGeometry(0, 0 , 1000, 720);
    this->setAutoFillBackground(true);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, BACKGROUND_COLOR);
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/image/resources/images/Warehouse.png").scaled(this->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));//Use smooth zoom
    this->setPalette(palette);
    this->show();

    this->robots.append(Robot(ROBOT_RED_HOME, QPoint(0,0), ROBOT_RED_FIRST_COLOR, ROBOT_RED_SECOND_COLOR));
    this->robots.append(Robot(ROBOT_GREEN_HOME, QPoint(4,4), ROBOT_GREEN_FIRST_COLOR, ROBOT_GREEN_SECOND_COLOR));
    this->robots.append(Robot(ROBOT_BLUE_HOME, QPoint(8,8), ROBOT_BLUE_FIRST_COLOR, ROBOT_BLUE_SECOND_COLOR));

}

void Scene::paintEvent(QPaintEvent *event)
{
    for (Robot agv : this->robots)
    {
        QPainter painter(this);

        if (agv.path_points.size() != 0)
        {
            // drawing paths
            QPainterPath path;
            path.moveTo(agv.path_points.front());

            for (auto point : agv.path_points)
            {
                path.lineTo(point + agv.drawing_offset);
            }

            painter.setPen(QPen(agv.SecondColor, this->line_size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawPath(path);


            // drawing first and last point
            painter.setBrush(QBrush(agv.SecondColor));
            painter.drawEllipse(agv.path_points.front() + agv.drawing_offset, this->point_size, this->point_size);
            painter.drawEllipse(agv.path_points.back() + agv.drawing_offset, this->point_size, this->point_size);
        }


        // drawing actuall position
        painter.setPen(QPen(agv.MainColor, this->line_size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.setBrush(QBrush(agv.MainColor));
        painter.drawEllipse(agv.position + agv.drawing_offset, this->point_size, this->point_size);

    }


}
