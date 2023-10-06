/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-10-03 12:35:35
 * @LastEditTime: 2023-10-06 21:04:08
 * @Description: 消息类型头文件
 */
#ifndef MESSAGE_H
#define MESSAGE_H

#define USERNAME_SIZE 20
#define PASSWORD_SIZE 20

/* 消息状态 */

#define LOGIN_SUCCESS 0x01      // 登陆成功
#define DUPLICATE_USERNAME 0x02 // 用户名重复
#define WRONG_PASSWORD 0x03     // 密码错误
#define TIME_OUT 0x04           // 超时错误
#define MSG_ERROR 0x05          // 获取错误
#define REQUEST_TO_SEND 0x06    // 请求发送
#define OK 0x07                 // 确认码

/* 指令部分 */
#define COMMAND_OK 0x10 // 指令确认码
#define C_USERS_SIZE 0x11 // 获取用户数量


/* 用户信息 */
struct UserInfo {
  char username[USERNAME_SIZE + 1]{};
  char password[PASSWORD_SIZE + 1]{};
};

/* 定义消息类型 */
using MsgState = char;

/* 定义消息头 */
struct MsgHead {
  unsigned long int msg_size{};
  MsgState state{};
  int receiver_fd{};

  const char *data() {
    return reinterpret_cast<char *>(this);
  }  

  MsgHead() = default;

  MsgHead(const MsgHead &head) {
    msg_size = head.msg_size;
    state = head.state;
    receiver_fd = head.receiver_fd;
  }
};

#endif