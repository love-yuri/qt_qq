#ifndef MSG_INFO_H
#define MSG_INFO_H

#include <QWidget>
#include "../ui/ui_msg_info.h"
class MsgInfo : public QWidget {
  
private:
  Ui::MsgInfo *ui;

public:
  MsgInfo(QWidget *parent = nullptr) :
    QWidget(parent), ui(new Ui::MsgInfo) {
    ui->setupUi(this);
    setFixedHeight(112);
  }

};

#endif