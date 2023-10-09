/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-09-27 13:29:54
 * @LastEditTime: 2023-10-09 21:59:26
 * @Description: 抄QQ界面
 */
#include <QApplication>
#include <qlayout.h>
#include "include/mainwindow.h"
#include "hpp/drawer.hpp"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  MainWindow window;
//   Drawer d;
//   d.show();
  return app.exec();
}
