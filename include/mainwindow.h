/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-10-06 13:22:42
 * @LastEditTime: 2023-10-07 14:51:43
 * @Description: 主窗口头
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include/tcp_client.h"
#include <qmainwindow.h>
#include <qtconfigmacros.h>
#include <qwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class Send;
class MsgList;
} // namespace Ui

QT_END_NAMESPACE

class MainWindow : QMainWindow {
  Q_OBJECT
public:
  MainWindow(QMainWindow *parent = nullptr);
  virtual ~MainWindow();

  void resizeEvent(QResizeEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

private:
  /* 各种ui合集 */
  Ui::MainWindow *ui;
  Ui::Send *send_ui;
  Ui::MsgList *msg_list_ui;
  QWidget *window;
  TcpClient *client;

  void addScrollArea();
};

#endif