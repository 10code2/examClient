#include "teacheroperate.h"
#include "ui_teacheroperate.h"
#include "Enroll.h"
#include "CommunicationProtocol.h"

TeacherOperate::TeacherOperate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherOperate)
{
    ui->setupUi(this);
    qDebug() << "a new TeacherOperate";

    examWidget = new ExamTeacher;
    scoreWidget = new Score;
    ui->stackedWidget->addWidget(examWidget);
    ui->stackedWidget->addWidget(scoreWidget);
    ui->stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(ui->listWidget, SIGNAL(currentRowChanged(int))
            , ui->stackedWidget, SLOT(setCurrentIndex(int)));
}

TeacherOperate::~TeacherOperate()
{
    delete ui;
}

TeacherOperate &TeacherOperate::getInstance()
{
    static TeacherOperate instance;
    return instance;
}

void TeacherOperate::handleGetExams(const QJsonObject &jsonObj)
{
    CommunicationProtocol::GetExamsResponse response = CommunicationProtocol::GetExamsResponse::fromJson(jsonObj);
    qDebug() << "get exams = " << response.exams;
    if(response.exams.size() > 0){
        examWidget->setExams(response.exams);
    }
}

void TeacherOperate::handleGetScores(const QJsonObject &jsonObj)
{
    CommunicationProtocol::GetScoresResponse response = CommunicationProtocol::GetScoresResponse::fromJson(jsonObj);
    qDebug() << "get exams = " << response.scores.size();
    if(response.scores.size() > 0){
        scoreWidget->setScores(response.scores);
    }
}

void TeacherOperate::closeEvent(QCloseEvent *event)
{
    Enroll::getInstance().show();
    QWidget::closeEvent(event); // 调用基类的关闭事件处理
}
