#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include <qevent.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <qwindowdefs.h>
#include <QTimer>

class PushButton : public QPushButton {
  Q_OBJECT
public:
  PushButton(QWidget *parent = nullptr) :
    QPushButton(parent), timer(new QTimer()) {
    setGeometry(200, 200, 200, 200);
    radius = 15;
    setEnabled(false);
    max_radius = qSqrt(width() * width() + height() * height());
    qDebug() << max_radius;
    timer->setInterval(max_radius / 28);
}

virtual ~PushButton() {
    
}

private:
QPointF mouse_point;
QTimer *timer;
int radius;
int max_radius;

protected:
virtual void paintEvent(QPaintEvent *event) override {
  QPushButton::paintEvent(event);
  QPainter painter(this);
  if (!mouse_point.isNull()) {
    painter.setBrush(QBrush(QColor(88, 146, 44, 166)));
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(rect(), 0, 0);
    painter.setClipPath(path);
    painter.drawEllipse(mouse_point, radius, radius);
  }
}

virtual void enterEvent(QEnterEvent *event) override {
  setEnabled(true);
  QPushButton::enterEvent(event);
  mouse_point = event->position();
  timer->disconnect();
  connect(timer, &QTimer::timeout, [this]() {
    radius += 2;
    if (radius > max_radius) {
      timer->stop();
      return;
    }
    update();
  });
  timer->start();
}

virtual void leaveEvent(QEvent *event) override {
  timer->disconnect();
  setEnabled(false);
  connect(timer, &QTimer::timeout, [this]() {
    radius -= 2;
    if (radius < 0) {
      radius = 0;
      update();
      timer->stop();
      return;
    }
    update();
  });
  timer->start();
}
}
;

#endif