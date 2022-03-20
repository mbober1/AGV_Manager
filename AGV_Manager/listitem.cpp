#include "listitem.hpp"
#include "ui_listitem.h"

  
/*!
 * \brief Constructor ListItem Class
 */
ListItem::ListItem(QString title, QString robot, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItem)
{
    ui->setupUi(this);
    ui->title_label->setText(title);
    ui->robot_label->setText(robot);
}


/*!
 * \brief Destructor ListItem Class
 */
ListItem::~ListItem()
{
    delete ui;
}

  
/*!
 * \brief Update progressbar
 * \param[in] progress - Value to be set
 */
void ListItem::update_progress(int progress)
{
    ui->progressBar->setValue(progress);
}
