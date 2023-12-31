#include "include/mainwindow.h"
#include "../ui/ui_mainwindow.h"
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
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qtextdocument.h>
#include <qtextobject.h>
#include <qtoolbutton.h>
#include <qwidget.h>
#include <QFontMetrics>
#include "hpp/toolbutton.hpp"
#include "hpp/tools.hpp"
#include "hpp/chat.hpp"
#include <QSplitter>
#include <QTextBlock>
#include <QMessageLogger>
#include <QScrollBar>
#include "hpp/msg_info.hpp"
#include "include/message.h"
#include "include/tcp_client.h"

MainWindow::MainWindow(QMainWindow *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  window(new QWidget(this)),
  client(new TcpClient(this)) {
  ui->setupUi(this);

  /* 初始化工作 */
  yuri::Tools::init();
  yuri::Tools::loadQss(":qss/index.qss", this);
  yuri::Tools::loadQss(":qss/left_wid.qss", ui->left_wid);
  yuri::Tools::loadQss(":qss/message_w.qss", ui->message_w);

  /* 添加长选框 */
  addScrollArea();

  ui->msg_main_sp->setSizes({ 700, 500});
  
  client->start("127.0.0.1", 2078);
  if (client->login("yuri", "miku2078")) {
    client->startToRead();
  }
  if (client->isLogin()) {
    ui->msg_scroll->layout()->setAlignment(Qt::AlignTop);
    QListWidget *w = new QListWidget();
    QString ret = client->sendCommand(C_USERS_SIZE);
    int size = 0;
    for (QString fd : ret.split(",")) {
      MsgInfo *info = new MsgInfo;
      size++;
      info->setTitle(fd);
      ui->msg_scroll->layout()->addWidget(info);
    }
  }

  

  connect(ui->contack_person_b, &ToolButton::clicked, [this]() {
    ui->stackedWidget->setCurrentIndex(1);
  });

  connect(ui->message_b, &ToolButton::clicked, [this]() {
    ui->stackedWidget->setCurrentIndex(0);
  });

  auto layout = ui->scrollAreaWidgetContents->layout();
  layout->setAlignment(Qt::AlignTop);

  for (int j = 0; j < 1; j++) {
    QListWidget *w = new QListWidget();
    for(int i = 0; i < 7; i++)
    {
      QPushButton *button = new QPushButton(QString("%1").arg(i,5));
      button->setFixedHeight(60);
      button->setContentsMargins(0,0,0,0);
      QListWidgetItem *it = new QListWidgetItem();
      it->setSizeHint(QSize(200, 60));
      w->setContentsMargins(0,0,0,0);
      w->addItem(it);
      w->setItemWidget(it, button);
    }
    w->setFixedHeight(422);
    layout->addWidget(w);
  }

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
}

// private function

void MainWindow::addScrollArea() {
  {
    QVBoxLayout *layout = new QVBoxLayout(ui->msg_scroll);
    layout->setAlignment(Qt::AlignTop);
    connect(ui->search_but, &QPushButton::clicked, [this, layout]() {
      MsgInfo *info = new MsgInfo;
      layout->addWidget(info);
    });
  }
  {
    QVBoxLayout *layout = new QVBoxLayout(ui->chat_scroll);
    layout->setAlignment(Qt::AlignTop);
    connect(ui->send_msg_b, &QPushButton::clicked, [this, layout]() {
      auto chat = new Chat(ui->send_msg_edit->document());
      // client->write(send_ui->textEdit->toPlainText().toUtf8());
      chat->setAvatar(":/picture/avatar.jpg");
      layout->addWidget(chat);
    });
  }

  // connect(send_ui->pushButton, &QPushButton::clicked, [area, this, parent, pLayout]() {
  //   auto chat = new Chat(send_ui->textEdit->document());
  //   client->write(send_ui->textEdit->toPlainText().toUtf8());
  //   chat->setAvatar(":/picture/avatar.jpg");
  //   pLayout->addWidget(chat);
  //   QScrollBar *bar = area->verticalScrollBar();
  //   bar->setValue(bar->maximum());
  // });

  // connect(client, &TcpClient::getData, [this, pLayout, area](const TcpClient::Message msg) {
  //   QTextDocument docu = QTextDocument(msg.byte);
  //   auto chat = new Chat(&docu, false);
  //   chat->setAvatar(":/picture/avatar.jpg");
  //   pLayout->addWidget(chat);
  //   QScrollBar *bar = area->verticalScrollBar();
  //   bar->setValue(bar->maximum());
  //   // qdebug << msg.byte;
  // });
}