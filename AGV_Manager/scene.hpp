#ifndef SCENE_HPP
#define SCENE_HPP

#include <QWidget>
#include "robot.hpp"

class Scene : public QWidget
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);

private:
    QVector<Robot> robots;
    int point_size = 8;
    int line_size = 7;

signals:

};

#endif // SCENE_HPP
