#ifndef TOOLS_H
#define TOOLS_H

#include <QMessageLogContext>
#include <QFileInfo>
#include <QDateTime>
#include <QWidget>
#include <QFile>
#include <qmutex.h>
#include <qtextobject.h>

namespace yuri {

class Tools {
public:
  static bool loadQss(const QString &file_name, QWidget *widget) {
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly)) {
      qDebug() << file_name << " 打开失败!";
      return false;
    }
    widget->setStyleSheet(widget->styleSheet() + file.readAll());
    file.close();
    return true;
  }

  static void init(bool file = false) {
    if (file) {
      qInstallMessageHandler(logFile);
    } else {
      qInstallMessageHandler(log);
    }
  }

  static int getRowCount(QTextBlock block) {
    int c = 0;
    while (block.isValid() && block.layout()) {
      c += block.layout()->lineCount();
      block = block.next();
    }
    return c;
  }

private:
  static void log(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    // 23:22:22 test.c:5 ->
    QString message = QString("%1 %2:%3 -> %4")
                        .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                        .arg(QFileInfo(context.file).fileName())
                        .arg(context.line)
                        .arg(msg);
    switch (type) {
    
    case QtDebugMsg:
      qDebug() << message;
      break;
    case QtInfoMsg:
      qInfo() << message;
      break;
    case QtWarningMsg:
      qWarning() << message;
      break;
    case QtCriticalMsg:
      qCritical() << message;
      break;
    case QtFatalMsg:
      qFatal() << message;
      break;
    default:
      break;
    }
  }

  static void logFile(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    // 23:22:22 test.c:5 ->
    QString message = QString("%1 %2:%3 -> %4\r\n")
                        .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                        .arg(QFileInfo(context.file).fileName())
                        .arg(context.line)
                        .arg(msg);
    QString msg_head;
    switch (type) {
    case QtDebugMsg:
      msg_head = QString("Debug ");
      break;
    case QtInfoMsg:
      msg_head = QString("Info ");
      break;
    case QtWarningMsg:
      msg_head = QString("Warning ");
      break;
    case QtCriticalMsg:
      msg_head = QString("Critical ");
      break;
    case QtFatalMsg:
      msg_head = QString("Fatal ");
      break;
    default:
      msg_head = QString("Err");
      break;
    }
    static QMutex mutex;
    mutex.lock();
    QFile file("D:/qt_test/yuri.txt");
    if (file.open(QFile::WriteOnly | QFile::Append)) {
      file.write(QString(msg_head + message).toUtf8());
      file.flush();
      file.close();
    }
    mutex.unlock();
  }
};



} // namespace yuri
#ifndef qinfo
#define qinfo QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).info()
#endif

#ifndef qdebug
#define qdebug QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).debug()
#endif

#ifndef qerror
#define qerror QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).warning()
#endif


#endif