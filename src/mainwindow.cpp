#include "include/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include "../ui/ui_send.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QToolButton>
#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QScrollArea>
#include <QLineEdit>
#include <qabstractscrollarea.h>
#include <qboxlayout.h>
#include <qfontmetrics.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qtextdocument.h>
#include <qtextobject.h>
#include <qtoolbutton.h>
#include <qwidget.h>
#include <QFontMetrics>
#include "hpp/tools.hpp"
#include "hpp/chat.hpp"
#include <QSplitter>
#include <QTextBlock>
#include <QMessageLogger>
#include <QScrollBar>
#include "../ui/ui_msg_list.h"
#include "hpp/msg_info.hpp"

MainWindow::MainWindow(QMainWindow *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  send_ui(new Ui::Send),
  msg_list_ui(new Ui::MsgList),
  window(new QWidget(this)) {
  ui->setupUi(this);
  yuri::Tools::init();
  yuri::Tools::loadQss(":qss/left_wid.qss", ui->left_wid);
  yuri::Tools::loadQss(":qss/main_wid.qss", ui->main_wid);

  QHBoxLayout *layout = new QHBoxLayout(ui->main_wid);
  QSplitter *splitter = new QSplitter(Qt::Horizontal, ui->main_wid);
  QWidget *leftLabel = new QWidget(splitter); // 左边消息列表
  leftLabel->setMinimumWidth(450);
  msg_list_ui->setupUi(leftLabel);
  QVBoxLayout *pLayout = new QVBoxLayout();
  pLayout->setAlignment(Qt::AlignTop);
  msg_list_ui->scrollAreaWidgetContents->setLayout(pLayout);
  connect(msg_list_ui->pushButton, &QPushButton::clicked, [this, pLayout]() {
    MsgInfo *info = new MsgInfo;
    pLayout->addWidget(info);
  });

  QSplitter *r_splitter = new QSplitter(Qt::Vertical, splitter);
  QWidget *r_top = new QWidget(r_splitter); // 右上对话列表
  QWidget *r_but = new QWidget(r_splitter); // 右下聊天输入框
  send_ui->setupUi(r_but);
  r_but->setMinimumHeight(300);
  r_but->setMaximumHeight(500);
  layout->addWidget(splitter);
  layout->setContentsMargins(0, 0, 0, 0);
  splitter->setSizes({400, 1000});
  r_splitter->setSizes({600, 300});
  ui->main_wid->setLayout(layout);

  addScrollArea(r_top);
  show();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
}

void MainWindow::paintEvent(QPaintEvent *event) {
  QMainWindow::paintEvent(event);
}

MainWindow::~MainWindow() {
  delete ui;
  delete send_ui;
}


// private function

void MainWindow::addScrollArea(QWidget *parent) {
  QHBoxLayout *layout = new QHBoxLayout;
  QScrollArea *area = new QScrollArea();
  area->setWidgetResizable(true);
  area->setWidget(new QWidget(area));
  QVBoxLayout *pLayout = new QVBoxLayout(); 
  pLayout->setAlignment(Qt::AlignTop);
  area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  connect(send_ui->pushButton, &QPushButton::clicked, [area, this, parent, pLayout]() {
    static bool is_me = false;
    auto chat = new Chat(send_ui->textEdit->document(), is_me);
    chat->setAvatar(":/picture/avatar.jpg");
    pLayout->addWidget(chat);
    QScrollBar *bar = area->verticalScrollBar();
    bar->setValue(bar->maximum());
    is_me = !is_me;
  });

  area->widget()->setLayout(pLayout); // 把布局放置到QScrollArea的内部QWidget中
  layout->addWidget(area);
  parent->setLayout(layout);
}