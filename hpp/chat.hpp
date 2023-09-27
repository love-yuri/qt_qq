#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QResizeEvent>
#include <qboxlayout.h>
#include <qfontmetrics.h>
#include <qlabel.h>
#include <qlayoutitem.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpicture.h>
#include <qpixmap.h>
#include <qsizepolicy.h>
#include <qtextdocument.h>
#include <qtypes.h>
#include <qwidget.h>
#include <QTextBlock>
#include <QTextDocument>
#include "../ui/ui_chat.h"

class Chat : public QWidget {
  Q_OBJECT

private:
  Ui::Chat *ui;
  bool is_me;

public:
  Chat(QWidget *parent = nullptr) :
    QWidget(parent), ui(new Ui::Chat) {
    ui->setupUi(this);
  }

  Chat(const QTextDocument *document, bool is_me = false) :
    ui(new Ui::Chat), is_me(is_me) {
    ui->setupUi(this);
    init(document);
  }

  virtual ~Chat() {
    delete ui;
  }

  void setAvatar(const QString &file_name) {
    QPixmap pixmap(file_name);
    qreal w_real = static_cast<qreal>(60.0 / pixmap.width());
    qreal h_real = static_cast<qreal>(60.0 / pixmap.height());
    QPixmap n_pixmap = pixmap.scaled(
      pixmap.width() * w_real,
      pixmap.height() * h_real,
      Qt::KeepAspectRatio,
      Qt::SmoothTransformation);
    QPixmap a_pixmap(n_pixmap.size());
    a_pixmap.fill(Qt::transparent);
    QPainter painter(&a_pixmap);
    QPainterPath path;
    path.addEllipse(a_pixmap.rect());
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, n_pixmap);
    ui->label_2->setPixmap(a_pixmap);
  }

protected:
  virtual void resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
  }

private:
  void init(const QTextDocument *document) {
    QTextBlock block = document->begin();
    QString message = document->toPlainText();
    int count = 0, h = QFontMetrics(ui->label->font()).height();
    while (block.isValid() && block.layout()) {
      count += block.layout()->lineCount();
      block = block.next();
    }
    int max_height = count * (3 + h) + 16;
    if (max_height < 60) {
      max_height = 60;
    }
    ui->label->setMaximumHeight(max_height);
    setFixedHeight(max_height);
    ui->label->setText(message);
    if (is_me) {
      ui->horizontalLayout->removeWidget(ui->widget);
      ui->horizontalLayout->addWidget(ui->widget);
    }
    int w = QFontMetrics(ui->label->font()).boundingRect(message).width();
    if (count == 1 && w < 600) {
      
      ui->label->setFixedWidth(w + 20);
      QSpacerItem *space = is_me ? ui->horizontalSpacer_3 : ui->horizontalSpacer;
      space->changeSize(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
  }
};

#endif