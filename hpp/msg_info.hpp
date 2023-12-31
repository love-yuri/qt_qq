/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-09-27 13:29:54
 * @LastEditTime: 2023-10-22 18:01:44
 * @Description: 左侧消息对话
 */
#ifndef MSG_INFO_H
#define MSG_INFO_H

#include <QWidget>
#include "../ui/ui_msg_info.h"
#include "hpp/tools.hpp"
class MsgInfo : public QWidget {
private:
  Ui::MsgInfo *ui;

public:
  MsgInfo(QWidget *parent = nullptr) :
    QWidget(parent), ui(new Ui::MsgInfo) {
    ui->setupUi(this);
    setFixedHeight(112);  
    setStyleSheet("#widget { \
      background-color: aquamarine;\
    }");                                                                                                                                                                                                                                                                                                                                                                                                                                     
  }

  void setTitle(const QString &title) {
    ui->name->setText(title);
  }
};

#endif