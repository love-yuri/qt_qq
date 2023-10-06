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
}
QT_END_NAMESPACE


class MainWindow : QMainWindow {
  Q_OBJECT
public:
  MainWindow(QMainWindow *parent = nullptr);
  virtual ~MainWindow();

  void resizeEvent(QResizeEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

private:
  Ui::MainWindow *ui;
  Ui::Send *send_ui;
  Ui::MsgList *msg_list_ui;
  QWidget *window;
  TcpClient *client;

  void addScrollArea(QWidget *parent);
};


#endif 