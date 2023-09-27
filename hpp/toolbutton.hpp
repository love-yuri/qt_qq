#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>
#include <qevent.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qwidget.h>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <qwindowdefs.h>
#include <QTimer>

class ToolButton : public QToolButton {
  Q_OBJECT
private:
  
public:
  ToolButton(QWidget *parent = nullptr) :
    QToolButton(parent) {
    setEnabled(false);
  }

  virtual ~ToolButton() {
  }

protected:
  virtual void enterEvent(QEnterEvent *event) override {
    QToolButton::enterEvent(event);
    setEnabled(true);
  }

  virtual void leaveEvent(QEvent *event) override {
    QToolButton::leaveEvent(event);
    setEnabled(false);
  }
};

#endif