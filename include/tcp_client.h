/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-09-28 16:55:58
 * @LastEditTime: 2023-10-06 19:47:02
 * @Description: tcp客户端
 */
#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "message.h"
#include <QTcpSocket>
#include <qmutex.h>

#define WRITE_TIMEOUT_MS 500000
#define READ_TIMEOUT_MS 500000

class TcpClient : public QTcpSocket {
  Q_OBJECT
  using State = char;

public:
  
  struct Message {
    MsgHead msg_head;
    QByteArray byte;
  };

  TcpClient(QObject *parent = nullptr);
  virtual ~TcpClient();

  /* 开始连接到 hostname 的 port端口 */
  bool start(const QString &hostname, quint16 port, int msecs = 30000);
  quint16 write(const QByteArray data);
  quint16 write(const char *data, quint16 size);

  /* 登陆函数 */
  bool login(const QString &username, const QString &password);

  /* 获取对方的消息状态 超时直接返回*/
  MsgState getMsgState(unsigned int = READ_TIMEOUT_MS);

  /* 向对方写入消息状态 超时直接返回 */
  bool setMsgState(MsgState state, unsigned int = WRITE_TIMEOUT_MS);

  /* 开启监听读取内容 */
  void startToRead();

  /* 发送指令 */
  QString sendCommand(MsgState com);

signals:
  /* 关联写入信息 */
  void recv(const QByteArray &);

  /* 获得消息 */
  void getData(const Message);

  /* 获得具体信息 */
  void getMsg(const QByteArray);
  
private:
  bool is_login;
  QMutex mutex;
  QByteArray buffer;
};

#endif
