#include <QtWidgets>

class ChatWindow : public QWidget {
  Q_OBJECT

public:
  ChatWindow(QWidget *parent = nullptr) :
    QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;

    chatWidget = new QWidget;
    chatLayout = new QVBoxLayout;
    chatLayout->setAlignment(Qt::AlignTop); // 设置对齐方式为顶部对齐
    chatLayout->setContentsMargins(0, 0, 0,  0);

    chatWidget->setLayout(chatLayout);

    scrollArea = new QScrollArea;
    scrollArea->setWidget(chatWidget);
    scrollArea->setWidgetResizable(true);

    messageInput = new QLineEdit;
    sendButton = new QPushButton("发送");

    layout->addWidget(scrollArea);
    layout->addWidget(messageInput);
    layout->addWidget(sendButton);

    setLayout(layout);

    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
  }

public slots:
  void sendMessage() {
    QString messageText = messageInput->text();
    QLabel *messageLabel = new QLabel(messageText);
    // messageLabel->setMaximumWidth(300); // 设置最大宽度

    chatLayout->addWidget(messageLabel);
    messageLabel->setWordWrap(true);

    // 清除输入框
    messageInput->clear();

    // 滚动到最后一条消息
    scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
  }

private:
  QWidget *chatWidget;
  QVBoxLayout *chatLayout;
  QScrollArea *scrollArea;
  QLineEdit *messageInput;
  QPushButton *sendButton;
};
