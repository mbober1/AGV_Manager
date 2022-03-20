#ifndef SCENE_HPP
#define SCENE_HPP

#include <QWidget>

class Scene : public QWidget
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *event);

private:
    QVector<QLine> lines;
signals:

};

#endif // SCENE_HPP
