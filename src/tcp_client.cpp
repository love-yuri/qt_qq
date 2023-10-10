#include "include/tcp_client.h"
#include <qabstractsocket.h>
#include <qcoreapplication.h>
#include <qtcpsocket.h>
#include "hpp/tools.hpp"
#include "include/message.h"

TcpClient::TcpClient(QObject *parent) :
  QTcpSocket(parent) {
  is_login = false;
  connect(this, &TcpClient::recv, [this](const QByteArray &msg) {
    write(msg);
  });
}

// 析构默认调用end函数
TcpClient::~TcpClient() {
}

// 开启连接，默认等待 30000ms
bool TcpClient::start(const QString &hostname, quint16 port, int msecs) {
  connectToHost(hostname, port); // 连接host
  bool is_start = waitForConnected(msecs);
  if (is_start) {
    // 如果能够读取就读取数据并存如last_msg
    qdebug << "连接 " + hostname + ": " + QString::number(port) + " 成功!";
  }
  return is_start;
}

// 向服务器发送数据，返回发送成功数据大小，否则返回 0
quint16 TcpClient::write(const QByteArray data) {
  if (state() == TcpClient::ConnectedState && TcpClient::isWritable()) {
    mutex.lock();
    // qdebug << "获取的锁";
    setMsgState(REQUEST_TO_SEND);
    MsgHead head;
    head.msg_size = data.size();
    // qdebug << "size -> " << head.msg_size;
    head.state = REQUEST_TO_SEND;
    write(head.data(), sizeof(MsgHead));
    flush();
    MsgState state(getMsgState());
    // qdebug << (int)state;
    if (state != OK) {
      return 0;
    }
    int ret = QTcpSocket::write(data);
    mutex.unlock();
    return ret;
  }
  return 0;
}

quint16 TcpClient::write(const char *data, quint16 size) {
  if (state() == TcpClient::ConnectedState && TcpClient::isWritable()) {
    return QTcpSocket::write(data, size);
  }
  return 0;
}

bool TcpClient::login(const QString &username, const QString &password) {
  if (username.size() > USERNAME_SIZE || password.size() > PASSWORD_SIZE) {
    qerror << "用户名或密码长度过长!";
    return false;
  }
  UserInfo user;
  qstrcpy(user.username, username.toUtf8());
  qstrcpy(user.password, password.toUtf8());
  int ret = write(reinterpret_cast<char *>(&user), sizeof(UserInfo));
  if (ret > 0 && getMsgState() == LOGIN_SUCCESS) {
    qdebug << "登陆成功!";
    is_login = true;
    return true;
  } else {
    return false;
  }
}

MsgState TcpClient::getMsgState(unsigned int time_out) {
  MsgState state(0);
  if (bytesAvailable() < 1 && !waitForReadyRead(time_out)) {
    return TIME_OUT;
  }

  if (read(&state, 1) != 1) {
    return MSG_ERROR;
  }
  return state;
}

bool TcpClient::setMsgState(MsgState state, unsigned int time_out) {
  MsgState c(state);
  int ret = QTcpSocket::write(QByteArray(&c, 1));
  return ret == 1 && waitForBytesWritten(time_out);
}

bool TcpClient::isLogin() const {
  return is_login;
}

void TcpClient::startToRead() {
  auto msgHead = [this]() {
    static int head_size = sizeof(MsgHead);
    if (bytesAvailable() < head_size) {
      // qdebug << "正在获得头!";
      waitForReadyRead(-1);
    }
    char head[head_size];
    read(head, head_size);
    return *reinterpret_cast<MsgHead *>(head);
  };

  connect(this, &TcpClient::readyRead, [this, msgHead]() {
    if (!mutex.try_lock()) {
      qinfo << "获取失败!";
      return;
    }
    if (state() == QAbstractSocket::ConnectedState) {
      MsgState state(getMsgState());
      // qinfo << (int)state;
      if (state == TIME_OUT) {
        mutex.unlock();
        return;
      }

      if (state > COMMAND_OK) {
        Message message;
        message.msg_head.state = state;
        emit getData(message);
        mutex.unlock();
        return;
      }

      if (state == COMMAND_OK) {
        if (bytesAvailable() < 1) {
          waitForReadyRead();
        }
        buffer = readAll();
        mutex.unlock();
        return;
      }

      MsgHead head(msgHead());
      if (head.state != state) {
        setMsgState(MSG_ERROR);
        mutex.unlock();
        return;
      }
      setMsgState(OK);
      if (bytesAvailable() < head.msg_size) {
        waitForReadyRead();
      }
      Message message;
      message.msg_head = head;
      message.byte = readAll();
      mutex.unlock();
    
      emit getData(message);
      QCoreApplication::processEvents();
    }
  });
}

QString TcpClient::sendCommand(MsgState com) {
  // disconnect(this, &TcpClient::readyRead, nullptr, nullptr);
  setMsgState(com);
  waitForReadyRead(500);
  return buffer;
}
