#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <QPoint>
#include <QVector>
#include <QColor>

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

    void set_ready();
    void set_not_ready();
    bool is_ready();
    bool is_arrived();

    void set_path(std::list<int> &path, const QVector<QPoint> &warehouse_points);
    void clear_path();

    int get_path_len();
    int get_progress();
    void set_position(const QPoint &new_position);

    int get_id();

    QColor MainColor;
    QColor SecondColor;

private:
    QPoint position;
    QVector<QPoint> path_points;
    int get_len(const QPoint &point1, const QPoint &point2);
    bool ready;
    int id;

};

#endif // ROBOT_HPP


// set_path  -> return_paths
// set_position
// aminacja 
// set_ready

// jeżeli wszystkie ready
//     clear_path
//     make_moves