#include "taskitem.hpp"
#include "ui_taskitem.h"

  
/*!
 * \brief Constructor TaskItem Class
 */
TaskItem::TaskItem(QString robot, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskItem),
    assigned_to(robot)
{
    ui->setupUi(this);

    TaskItem::number++;
    ui->title_label->setText("Task #" + QString::number(TaskItem::number));
    ui->robot_label->setText(this->assigned_to);
}


/*!
 * \brief Destructor TaskItem Class
 */
TaskItem::~TaskItem()
{
    delete ui;
}

  
/*!
 * \brief Update progressbar
 * \param[in] progress - Value to be set
 */
void TaskItem::update_progress(int progress)
{
    ui->progressBar->setValue(progress);
}


int TaskItem::number = 0;
