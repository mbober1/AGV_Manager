#include "scene.hpp"
#include <QPainter>
#include <QBrush>

Scene::Scene(QWidget *parent)
    : QWidget{parent}
{
    this->setGeometry(0,0,1000,720);
    this->setAutoFillBackground(true);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(42, 42, 42));
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/image/resources/images/Warehouse.png").scaled(this->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));//Use smooth zoom
    this->setPalette(palette);
    this->show();

    QPoint p1(50, 50);
    QPoint p2(940, 50);
    QPoint p3(940, 270);
    QPoint p4(250, 270);
    QPoint p5(250, 600);
    QPoint p6(750, 600);
    QPoint p7(750, 650);

    this->lines.append(QLine(p1, p2));
    this->lines.append(QLine(p2, p3));
    this->lines.append(QLine(p3, p4));
    this->lines.append(QLine(p4, p5));
    this->lines.append(QLine(p5, p6));
    this->lines.append(QLine(p6, p7));

}

void Scene::paintEvent(QPaintEvent *event)
{
    QPen linePen(QColor(0x1e, 0xb9, 0x80)); // green
    linePen.setWidth(5);

    QPainter myline(this);
    myline.setPen(linePen);


    for (auto line : this->lines)
    {
        myline.drawLine(line);
    }

    myline.drawPoint(500, 500);
}
