/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-09-27 13:29:54
 * @LastEditTime: 2023-10-10 08:14:24
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
