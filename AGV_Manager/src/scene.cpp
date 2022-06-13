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
#define WAREHOUSE_HEIGTH            720
#define WAREHOUSE_BLOCK             50
#define get_block_center(block)     (block * WAREHOUSE_BLOCK + WAREHOUSE_BLOCK/ 2)
#define WAREHOUSE_POINT_COLOR       QColor(0x00, 0x00, 0x00)

#define WAREHOUSE_DATA ("../resources/data/warehouse.data")
#define TASK_DATA ("../resources/data/task.data")
#define get_backend_position(agv_id)      (warehouse_points[backend->return_current_position(agv_id)])


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

    this->warehouse_points = create_grid(backend->columns_num(), backend->rows_num());


    this->robots_list.append(Robot(get_backend_position(0), ROBOT_RED_FIRST_COLOR, ROBOT_RED_SECOND_COLOR, 0));
    this->robots_list.append(Robot(get_backend_position(1), ROBOT_GREEN_FIRST_COLOR, ROBOT_GREEN_SECOND_COLOR, 1));
    this->robots_list.append(Robot(get_backend_position(2), ROBOT_BLUE_FIRST_COLOR, ROBOT_BLUE_SECOND_COLOR, 2));

    connect(animation_timer, &QTimer::timeout, this, &Scene::animation_update);
    animation_timer->start(1000 / 120); // about 60 FPS
}


/*!
 * \brief Overload of Virtual function. Its executed every time sth change on screen
 */
void Scene::paintEvent(QPaintEvent *event)
{
    for (Robot &agv : this->robots_list)
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

            painter.setPen(QPen(agv.SecondColor, LINE_SIZE, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawPath(path);


            // drawing last point
            painter.setBrush(QBrush(agv.SecondColor));
            painter.drawEllipse(agv.get_path().back(), LAST_POINT_SIZE, LAST_POINT_SIZE);
        }

        // drawing actuall position
        painter.setPen(QPen(agv.MainColor, LINE_SIZE, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.setBrush(QBrush(agv.MainColor));
        painter.drawEllipse(agv.get_position(), ROBOT_POINT_SIZE, ROBOT_POINT_SIZE);

        // debug
        // for (auto &point : warehouse_points)
        // {
        //     painter.setBrush(QBrush(WAREHOUSE_POINT_COLOR));
        //     painter.drawEllipse(point, 5, 5);
        // }
    }

}

void Scene::set_new_positions(const std::vector<int> &position_list)
{
    for (size_t i = 0; i < position_list.size(); i++)
    {
        int point_idx =  position_list[i];
        this->robots_list[i].set_position(warehouse_points[point_idx]);
    }
}


/*!
 * \brief This function run when timer overflow.
 */
void Scene::animation_update()
{
    bool make_move = true;

    for (Robot &agv : this->robots_list)
    {
        if (agv.state != Robot_State::ARRIVED)
        {
            make_move = false;
        }
    }

    if (make_move == true)
    {
        backend->make_moves();
        refresh_task_list();
    }

    for (Robot &agv : this->robots_list)
    {
        switch (agv.state)
        {
            case Robot_State::READY: // skończył zadanie
            {
                backend->add_task_to_vehicle(agv.get_id());

                auto new_path = backend->return_path(agv.get_id());
                agv.set_path(new_path, warehouse_points);

                agv.state = Robot_State::ARRIVED;
                break;
            }

            case Robot_State::DRIVING: // pomiędzy punktami
            {
                QPoint backend_position = get_backend_position(agv.get_id());
                QPoint current_position = agv.get_position();

                if (current_position == backend_position)
                {
                    agv.state = Robot_State::ARRIVED;
                    agv.next_point();
                }
                else
                {
                    animate(agv, backend_position, current_position);
                }

                break;
            }

            case Robot_State::ARRIVED: // dojechał do punktu
            {
                QPoint backend_position = get_backend_position(agv.get_id());
                QPoint current_position = agv.get_position();

                if (current_position == backend_position)
                {
                    agv.state = Robot_State::READY;
                }
                else
                {
                    agv.state = Robot_State::DRIVING;
                }
                
                break;
            }
        }
    }

    repaint();
}

void Scene::animate(Robot &agv, const QPoint &next_point, const QPoint &current_position)
{
    // animate X axis
    if (current_position.x() > next_point.x())
    {
        agv.move(QPoint(-1, 0));
    }
    else if (current_position.x() < next_point.x())
    {
        agv.move(QPoint(1, 0));
    }

    // animate Y axis
    if (current_position.y() > next_point.y())
    {
        agv.move(QPoint(0, -1));
    }
    else if (current_position.y() < next_point.y())
    {
        agv.move(QPoint(0, 1));
    }
}

void Scene::refresh_task_list()
{
    auto percents = backend->return_task_percents();
    auto ids = backend->return_task_ids();

    emit update_task_percents(percents);
    emit update_task_ids(ids);
    printf("%d, %d, %d\n", ids[0], ids[1],ids[2]);
}

void Scene::set_simulation_speed(int speed) 
{
    if(speed == 0)
    {
        animation_timer->stop();
    }
    else
    {
        animation_timer->setInterval(1000 / speed);
    }
}

void Scene::timer_state(bool state)
{
    if(state)
    {
        animation_timer->start();
    }
    else
    {
        animation_timer->stop();
    }
}


const QVector<QPoint> Scene::create_grid(size_t width, size_t height)
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
