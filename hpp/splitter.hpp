#ifndef SPLITTER_H
#define SPLITTER_H

#include <QSplitter>
#include <qevent.h>
#include <qnamespace.h>
#include <qsplitter.h>
#include <qwidget.h>

class Splitter : public QSplitter {
public:
  Splitter(QWidget *parent = nullptr) :
    QSplitter(parent) {
    setContentsMargins(0, 0, 0, 0);
  }

  Splitter(Qt::Orientation orient, QWidget *parent = nullptr) :
    QSplitter(orient, parent) {
  }

  virtual ~Splitter() {
  }

public:
  void addWidget(QWidget *widget) {
    if (widget->minimumWidth() || widget->minimumHeight()) {
      connect(this, &QSplitter::splitterMoved, [this](int pos, int index) {
        if (pos == 0) {
          moveSplitter(old_pos, index);
          return;
        }
        old_pos = pos;
      });
    }
    QSplitter::addWidget(widget);
  }

private:
  int old_pos;
};

#endif