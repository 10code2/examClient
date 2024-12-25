#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QFile>
#include<QMessageBox>
#include<QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>


QT_BEGIN_NAMESPACE
namespace Ui { class Enroll; }
QT_END_NAMESPACE

class Enroll : public QWidget
{
    Q_OBJECT

public:
    ~Enroll();

    static Enroll &getInstance();
    void sendRequest(const QJsonObject &request);

private slots:
    void showConnect();

    void on_pushButton_teacher_clicked();

    void on_pushButton_master_clicked();

    void recvMsg();  // 接收回复消息


private:
    Ui::Enroll *ui;
    QString m_strIp;
    quint16 m_usPort;
    QTcpSocket *m_socket;
    static Enroll instance; // 全局静态变量

private:
    Enroll(QWidget *parent = nullptr);
    void loadConfig();
    void handleLogin(const QJsonObject &jsonObj);
    void handleAddTeacher(const QJsonObject &jsonObj);
    void handleMessage(const QJsonObject &jsonObj);
    void handleInformation(const QJsonObject &jsonObj);

};
#endif // WIDGET_H
