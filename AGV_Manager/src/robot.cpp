#include "inc/robot.hpp"
#include <QtMath>

  
/*!
 * \brief Constructor Robot Class
 */
Robot::Robot() {}

  
/*!
 * \brief Constructor Robot Class
 */
Robot::Robot(const QPoint &home_position, const QColor &MainColor, const QColor &SecondColor, int id) :
    MainColor(MainColor),
    SecondColor(SecondColor),
    state(Robot_State::READY),
    position(home_position),
    id(id)
{}


/*!
 * \brief Get path (point)
 * \return Vector of points
 */
const QVector<QPoint> &Robot::get_path()
{
    return this->path_points;
}


/*!
 * \brief Clear path - remove all points
 */
void Robot::clear_path()
{
   this->path_points.clear();
}


void Robot::set_path(std::list<int> &path, const QVector<QPoint> &warehouse_points) 
{
    clear_path();
    while (path.empty() == false)
    {
        int point_idx = path.front();
        path.pop_front();

        this->add_point(warehouse_points[point_idx]);
    }
}


/*!
 * \brief Get length between two points
 * \param[in] point1 - First point
 * \param[in] point2 - Second point
 * \return Length
 */
int Robot::get_len(const QPoint &point1, const QPoint &point2)
{
    auto tmp = point1 - point2;
    return sqrt( pow(tmp.x(), 2) + pow(tmp.y(), 2) );
}


/*!
 * \brief Get length of all path
 * \return Length of path
 */
int Robot::get_path_len()
{
    int lenght = 0;
    int point_count = this->path_points.size();

    if (point_count > 1)
    {
        lenght += get_len(this->get_position(), this->path_points[0]);

        for(int i = 0; i < point_count - 1; i++)
        {
            lenght += get_len(this->path_points[i], this->path_points[i + 1]);
        }

    }

    return lenght;
}


/*!
 * \brief Get progress of path
 * \return Value from 0 to 100
 */
int Robot::get_progress()
{
    static int start = get_path_len();

    if ( start == 0 )
    {
        return 100;
    }
    else
    {
        return 100 - (get_path_len() * 100 / start);
    }
}


void Robot::set_position(const QPoint &new_position) 
{
    this->position = new_position;
}

void Robot::next_point() 
{
    if (path_points.empty())
    {
        return;
    }
    else
    {
        path_points.pop_front();
    }
}

/*!
 * \brief Add point to path
 * \param[in] point - Point to be added
 */
void Robot::add_point(const QPoint &point)
{
    this->path_points.append(point);
}

/*!
 * \brief Get actual position of robot
 * \return QPoint with actual position
 */
const QPoint &Robot::get_position()
{
    return this->position;
}

int Robot::get_id() 
{
    return id;
}

const QPoint &Robot::get_next_point() 
{
    return path_points.first();
}

/*!
 * \brief Move robot by vector
 * \param[in] vector - vector to move
 */
void Robot::move(const QPoint &vector)
{
    this->position += vector;
}


// /*!
//  * \brief 
//  */
// void Robot::set_ready()
// {
//     this->ready = true;
// }

// void Robot::set_not_ready()
// {
//     this->ready = false;   
// }

// bool Robot::is_ready() 
// {
//     return ready;
// }

bool Robot::is_arrived() 
{
    if (position == path_points.first())
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
