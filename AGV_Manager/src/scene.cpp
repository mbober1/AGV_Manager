#include "inc/scene.hpp"
#include <QPainter>
#include <QPainterPath>
#include <QBrush>

#define ROBOT_RED_FIRST_COLOR       QColor(0xB7, 0x1C, 0x1C)
#define ROBOT_RED_SECOND_COLOR      QColor(0xEF, 0x53, 0x50, 0xAA)
#define ROBOT_RED_HOME              QPoint(50,50)

#define ROBOT_GREEN_FIRST_COLOR     QColor(0x1B, 0x5E, 0x20)
#define ROBOT_GREEN_SECOND_COLOR    QColor(0x66, 0xBB, 0x6A, 0xAA)
#define ROBOT_GREEN_HOME            QPoint(50,150)

#define ROBOT_BLUE_FIRST_COLOR      QColor(0x01, 0x57, 0x9B)
#define ROBOT_BLUE_SECOND_COLOR     QColor(0x29, 0xB6, 0xF6, 0xAA)
#define ROBOT_BLUE_HOME             QPoint(50,270)

#define WAREHOUSE_WIDTH             1000
#define WAREHOUSE_HEIGTH            700
#define WAREHOUSE_BLOCK             50
#define get_block_center(block)     (block * WAREHOUSE_BLOCK + WAREHOUSE_BLOCK/ 2)
#define WAREHOUSE_POINT_COLOR       QColor(0x00, 0x00, 0x00)

#define WAREHOUSE_DATA ("../resources/data/warehouse.data")
#define TASK_DATA ("../resources/data/task.data")

/*!
 * \brief Constructor Scene Class
 */
Scene::Scene(QWidget *parent)
    : QWidget{parent},
      backend(new Stage(WAREHOUSE_DATA, TASK_DATA, option_3)),
      animation_timer(new QTimer(this))
{

    this->setGeometry(0, 0 , WAREHOUSE_WIDTH, WAREHOUSE_HEIGTH);
    this->setAutoFillBackground(true);

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":/image/resources/images/Warehouse.png").scaled(this->size(),
                     Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation)));

    this->setPalette(palette);
    this->show();


    this->robots.append(Robot(ROBOT_RED_HOME, ROBOT_RED_FIRST_COLOR, ROBOT_RED_SECOND_COLOR, 0));
    this->robots.append(Robot(ROBOT_GREEN_HOME, ROBOT_GREEN_FIRST_COLOR, ROBOT_GREEN_SECOND_COLOR, 1));
    this->robots.append(Robot(ROBOT_BLUE_HOME, ROBOT_BLUE_FIRST_COLOR, ROBOT_BLUE_SECOND_COLOR, 2));

    this->warehouse_points = create_grid(backend->columns_num(), backend->rows_num());

    connect(animation_timer, &QTimer::timeout, this, &Scene::animation_update);
    animation_timer->start(1000 / 60); // about 60 FPS

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
                path.lineTo(point);
            }

            painter.setPen(QPen(agv.SecondColor, this->line_size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawPath(path);


            // drawing last point
            painter.setBrush(QBrush(agv.SecondColor));
            painter.drawEllipse(agv.get_path().back(), this->point_size, this->point_size);
        }

        // drawing actuall position
        painter.setPen(QPen(agv.MainColor, this->line_size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.setBrush(QBrush(agv.MainColor));
        painter.drawEllipse(agv.get_position(), this->point_size, this->point_size);

        // debug
        for (auto &point : warehouse_points)
        {
            painter.setBrush(QBrush(WAREHOUSE_POINT_COLOR));
            painter.drawEllipse(point, 5, 5);
        }
    }

}

void Scene::set_new_positions(const std::vector<int> &position_list) 
{
    for (size_t i = 0; i < position_list.size(); i++)
    {
        int point_idx =  position_list[i];
        this->robots[i].set_position(warehouse_points[point_idx]);
    }
}


/*!
 * \brief This function run when timer overflow.
 */
void Scene::animation_update()
{
    for (Robot &agv : this->robots)
    {
        if (agv.is_ready() == true)
        {
            agv.clear_path();
            int id = agv.get_id();
            auto path_idx = backend->return_path(id);
            agv.set_path(path_idx, warehouse_points);
            backend->make_moves();
        }
        else
        {
            animate(agv);

            if (agv.is_arrived() == true)
            {
                agv.set_not_ready();
            }
            
        }
    }

    repaint();

}

void Scene::animate(Robot &agv) 
{
    auto position = agv.get_position();
    auto next_point = agv.get_next_point();

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


QVector<QPoint> Scene::create_grid(size_t width, size_t height) 
{
    QVector<QPoint> results;

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            results.push_back(QPoint(get_block_center(j), get_block_center(i)));
        }
    }
    
    return results;
}
