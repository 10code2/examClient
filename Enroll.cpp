#include "Enroll.h"
#include "ui_Enroll.h"
#include "masteroperate.h"
#include "teacheroperate.h"
#include "CommunicationProtocol.h"


Enroll::Enroll(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Enroll)
{
    ui->setupUi(this);
    qDebug() << "a new Enroll";
    m_socket = new QTcpSocket;
    loadConfig();
    // 连接服务器
    connect(m_socket, SIGNAL(connected()), this, SLOT(showConnect()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
    m_socket->connectToHost(QHostAddress(m_strIp), m_usPort);
}

Enroll::~Enroll()
{
    qDebug() << "Enroll 中断";
    delete m_socket;
    delete ui;
}

Enroll& Enroll::getInstance()
{
    static Enroll instance;
    return instance;
}

void Enroll::loadConfig()
{
    QFile file("://client.config");
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray Ba = file.readAll();
        file.close();
        QString Str = Ba.toStdString().c_str();
        Str.replace("\r\n", " ");
        QStringList SL = Str.split(' ');

        m_strIp = SL.at(0);
        m_usPort = SL.at(1).toUShort();
//        qDebug() << m_strIp;
//        qDebug() << m_usPort;
    }
    else
    {
        QMessageBox::critical(this, "open config", "open failed");
    }
}

void Enroll::sendRequest(const QJsonObject &request)
{
    // 2 转化为文档、字节流
    QJsonDocument jsonDoc(request);
    QByteArray jsonData = jsonDoc.toJson();

    // 3 发送请求
    m_socket->write(jsonData);
    m_socket->flush();
    qDebug() << "Enroll 发送";
}

// 1 处理教师登录响应
void Enroll::handleLogin(const QJsonObject &jsonObj)
{
    CommunicationProtocol::LoginResponse response = CommunicationProtocol::LoginResponse::fromJson(jsonObj);
    if (response.success) {
        // 处理登录成功的逻辑
        this->hide();
        qDebug() << "User logged in successfully with ID:" << response.userId;

        if(response.userType == "teachers") TeacherOperate::getInstance().show();
        else MasterOperate::getInstance().show();

    } else {
        // 处理登录失败的逻辑
        qDebug() << "Login failed:" << response.errorMessage;
    }
}

void Enroll::handleAddTeacher(const QJsonObject &jsonObj)
{
    CommunicationProtocol::AddTeacherResponse response = CommunicationProtocol::AddTeacherResponse::fromJson(jsonObj);
    if (response.success) {
        // 处理添加教师成功的逻辑
        qDebug() << "Teacher added successfully.";
    } else {
        // 处理添加教师失败的逻辑
        qDebug() << "Adding teacher failed:" << response.errorMessage;
    }
}

void Enroll::handleMessage(const QJsonObject &jsonObj)
{
    CommunicationProtocol::ErrorResponse message = CommunicationProtocol::ErrorResponse::fromJson(jsonObj);
    QMessageBox::information(this, "错误消息", message.errorMessage);
}

void Enroll::handleInformation(const QJsonObject &jsonObj)
{
    CommunicationProtocol::SuccessResponse message = CommunicationProtocol::SuccessResponse::fromJson(jsonObj);
    QMessageBox::information(this, "成功消息", message.successMessage);
}


// 处理回复信息
void Enroll::recvMsg()
{
    QByteArray data = m_socket->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    if (jsonDoc.isNull()) {
        qWarning() << "Failed to parse JSON data:" << data;
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    // 提取 action 字段
    int action = jsonObj.value("action").toInt(-1); // 默认值设为 -1 表示未知动作

    switch(action){
    case CommunicationProtocol::LOGIN: {
        handleLogin(jsonObj);
        break;
    }
    case CommunicationProtocol::ADD_TEACHER: {
        handleAddTeacher(jsonObj);
        break;
    }
    case CommunicationProtocol::GET_EXAMS: {
        // qDebug() << "response of GET_EXAMS : " << jsonObj.size();
        TeacherOperate::getInstance().handleGetExams(jsonObj);
        break;
    }
    case CommunicationProtocol::CREATE_EXAM: {
        handleInformation(jsonObj);
        break;
    }
    case CommunicationProtocol::DELETE_EXAM: {
        handleInformation(jsonObj);
        break;
    }
    case CommunicationProtocol::ERROR: {
        handleMessage(jsonObj);
        break;
    }
    case CommunicationProtocol::GET_SCORES: {
        TeacherOperate::getInstance().handleGetScores(jsonObj);
        break;
    }
    // 添加其他动作的处理分支
    default:
        qWarning() << "Unhandled action:" << action;
        break;
    }
}






void Enroll::showConnect()
{
    QMessageBox::information(this, "连接服务器","连接成功");
}


void Enroll::on_pushButton_teacher_clicked()
{
    // 1 先拿到登录信息
    CommunicationProtocol::LoginRequest request;
    request.username = ui->usernameEdit->text();
    request.password = ui->passwordEdit->text();
    request.userType = "teachers";
    // qDebug() << "LoginRequest Data:" << request.username << "," << request.password;

    // 2 转化为字节流
    sendRequest(request.toJson());
}

void Enroll::on_pushButton_master_clicked()
{
    // 1 先拿到登录信息
    CommunicationProtocol::LoginRequest request;
    request.username = ui->usernameEdit->text();
    request.password = ui->passwordEdit->text();
    request.userType = "masters";
    //qDebug() << "LoginRequest Data:" << request.username << "," << request.password;

    // 2 转化为字节流
    sendRequest(request.toJson());
}
