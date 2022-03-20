#include "scene.hpp"
#include <QPainter>
#include <QPainterPath>
#include <QBrush>

#define ROBOT_RED_FIRST_COLOR       QColor(0xB7, 0x1C, 0x1C)
#define ROBOT_RED_SECOND_COLOR      QColor(0xEF, 0x53, 0x50, 0xAA)
#define ROBOT_RED_HOME              QPoint(50,150)

#define ROBOT_GREEN_FIRST_COLOR     QColor(0x1B, 0x5E, 0x20)
#define ROBOT_GREEN_SECOND_COLOR    QColor(0x66, 0xBB, 0x6A, 0xAA)
#define ROBOT_GREEN_HOME            QPoint(50,50)

#define ROBOT_BLUE_FIRST_COLOR      QColor(0x01, 0x57, 0x9B)
#define ROBOT_BLUE_SECOND_COLOR     QColor(0x29, 0xB6, 0xF6, 0xAA)
#define ROBOT_BLUE_HOME             QPoint(50,250)

  
/*!
 * \brief Constructor Scene Class
 */
Scene::Scene(QWidget *parent)
    : QWidget{parent},
      animation_timer(new QTimer(this))
{

    this->setGeometry(0, 0 , 1000, 720);
    this->setAutoFillBackground(true);

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":/image/resources/images/Warehouse.png").scaled(this->size(),
                     Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation)));

    this->setPalette(palette);
    this->show();

    this->robots.append(Robot(ROBOT_RED_HOME, QPoint(0,0), ROBOT_RED_FIRST_COLOR, ROBOT_RED_SECOND_COLOR));
    this->robots.append(Robot(ROBOT_GREEN_HOME, QPoint(2,2), ROBOT_GREEN_FIRST_COLOR, ROBOT_GREEN_SECOND_COLOR));
    this->robots.append(Robot(ROBOT_BLUE_HOME, QPoint(4,4), ROBOT_BLUE_FIRST_COLOR, ROBOT_BLUE_SECOND_COLOR));


    connect(animation_timer, &QTimer::timeout, this, &Scene::animation_update);
    animation_timer->start(17); // about 60 FPS

}


/*!
 * \brief Overload of Virtual function. Its executed every time sth change on screen
 */
void Scene::paintEvent(QPaintEvent *event)
{
    for (Robot &agv : this->robots)
    {
        QPainter painter(this);

        if (agv.get_path().empty() == false)
        {
            // drawing paths
            QPainterPath path;
            path.moveTo(agv.get_position());

            for (auto &point : agv.get_path())
            {
                path.lineTo(point + agv.drawing_offset);
            }

            painter.setPen(QPen(agv.SecondColor, this->line_size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawPath(path);


            // drawing last point
            painter.setBrush(QBrush(agv.SecondColor));
            painter.drawEllipse(agv.get_path().back() + agv.drawing_offset, this->point_size, this->point_size);
        }


        // drawing actuall position
        painter.setPen(QPen(agv.MainColor, this->line_size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.setBrush(QBrush(agv.MainColor));
        painter.drawEllipse(agv.get_position() + agv.drawing_offset, this->point_size, this->point_size);

    }

}


/*!
 * \brief This function run when timer overflow.
 */
void Scene::animation_update()
{

    for (Robot &agv : this->robots)
    {
        if (agv.get_path().empty())
        {
            agv.clear_path();
            break;
        }

        auto position = agv.get_position();
        auto next_point = agv.get_path().first();

        // drop point you are in
        if (position == next_point)
        {
            agv.checkpoint();
        }

        // animate X axis
        if (position.x() > next_point.x())
        {
            agv.move(QPoint(-1, 0));
        }
        else if (position.x() < next_point.x())
        {
            agv.move(QPoint(1, 0));
        }

        // animate Y axis
        if (position.y() > next_point.y())
        {
            agv.move(QPoint(0, -1));
        }
        else if (position.y() < next_point.y())
        {
            agv.move(QPoint(0, 1));
        }

    }

    repaint();

    emit test(this->robots[0].get_progress()); // TO DO

}
