/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-10-09 20:21:09
 * @LastEditTime: 2023-10-09 21:58:18
 * @Description: 抽屉模式
 */

#include "../ui/ui_drawer.h"
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qwidget.h>

class Drawer : public QWidget {
public:
  Drawer() :
    ui(new Ui::Drawer) {
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->layout()->setAlignment(Qt::AlignTop);
    auto layout = ui->scrollAreaWidgetContents->layout();
    QListWidget *w = new QListWidget;
    
    for(int i = 0; i < 7; i++)
    {
      QPushButton *button = new QPushButton(QString("%1 +++ %2").arg(i).arg(i));
      button->setFixedHeight(60);
      button->setContentsMargins(0,0,0,0);
      QListWidgetItem *it = new QListWidgetItem();
      it->setSizeHint(QSize(200, 60));
      w->setContentsMargins(0,0,0,0);
      w->addItem(it);
      w->setItemWidget(it, button);
    }
    layout->addWidget(w);
    
    w->setFixedHeight(422);
    {
      QListWidget *w = new QListWidget;
      
      for(int i = 0; i < 7; i++)
      {
        QPushButton *button = new QPushButton(QString("%1 --- %2").arg(i).arg(i));
        button->setFixedHeight(60);
        button->setContentsMargins(0,0,0,0);
        QListWidgetItem *it = new QListWidgetItem();
        it->setSizeHint(QSize(200, 60));
        w->setContentsMargins(0,0,0,0);
        w->addItem(it);
        w->setItemWidget(it, button);
      }
      layout->addWidget(w);
      w->setFixedHeight(422);
    }
    connect(ui->toolButton, &QToolButton::clicked, [this, w]() {
      static bool iv = false;
      w->setVisible(iv);
      iv = !iv;
    });
  }

private:
  Ui::Drawer *ui;
};


