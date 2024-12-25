#include "masteroperate.h"
#include "ui_masteroperate.h"
#include "Enroll.h"
#include "examteacher.h"
#include "score.h"

MasterOperate::MasterOperate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MasterOperate)
{
    ui->setupUi(this);
    examWidget = new ExamTeacher;
    scoreWidget = new Score;
    ui->stackedWidget->addWidget(examWidget);
    ui->stackedWidget->addWidget(scoreWidget);
    ui->stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(ui->listWidget, SIGNAL(currentRowChanged(int))
            , ui->stackedWidget, SLOT(setCurrentIndex(int)));
}

MasterOperate::~MasterOperate()
{
    delete ui;
}

MasterOperate &MasterOperate::getInstance()
{
    static MasterOperate instance;
    return instance;
}

void MasterOperate::closeEvent(QCloseEvent *event)
{
    Enroll::getInstance().show();
    QWidget::closeEvent(event); // 调用基类的关闭事件处理
}
