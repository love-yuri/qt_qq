/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-09-27 13:29:54
 * @LastEditTime: 2023-10-07 13:52:20
 * @Description: 抄QQ界面
 */
#include <QApplication>
#include "include/mainwindow.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  MainWindow window;
  return app.exec();
}
