#include "score.h"
#include "ui_score.h"
#include "CommunicationProtocol.h"
#include "Enroll.h"

Score::Score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Score)
{
    ui->setupUi(this);
}

Score::~Score()
{
    delete ui;
}

void Score::on_pushButton_search_clicked()
{
    QString major = ui->lineEdit_major->text();
    QString className = ui->lineEdit_class->text();
    QString name = ui->lineEdit_name->text();
    QString number = ui->lineEdit_number->text();
    QString course = ui->lineEdit_course->text();

    fetchStudents(major, course, name, number, className);
}

void Score::fetchStudents(const QString &major, const QString &course, const QString &name, const QString &number, const QString &className)
{
    CommunicationProtocol::GetScoresRequest request;
    request.name = name;
    request.major = major;
    request.number = number;
    request.className = className;
    request.course = course;

    Enroll::getInstance().sendRequest(request.toJson());
    qDebug() << "发送学生搜索请求";
}


void Score::setScores(const QList<QJsonObject> &scores)
{
    ui->tableWidget->clearContents(); // 清空现有内容
    ui->tableWidget->setRowCount(0);   // 清除所有行
    ui->tableWidget->setRowCount(scores.size()); // 设置行数
    qDebug() << "scores num = " << scores.size();

    for (int row = 0; row < scores.size(); ++row) {
        const QJsonObject& score = scores[row];

        // QTableWidgetItem* itemRow = new QTableWidgetItem(QString::number(row + 1));
        QTableWidgetItem* itname = new QTableWidgetItem(score["Name"].toString());
        QTableWidgetItem* itclassNmae = new QTableWidgetItem(score["ClassName"].toString());
        QTableWidgetItem* itemCourse = new QTableWidgetItem(" ");//score["CourseName"].toString());
        QTableWidgetItem* itnumber = new QTableWidgetItem(score["StudentNumber"].toString());
        QTableWidgetItem* itscore = new QTableWidgetItem(QString::number(score["Score"].toDouble()));
        QTableWidgetItem* itmajor = new QTableWidgetItem(score["Major"].toString());

        ui->tableWidget->setItem(row, 0, itclassNmae);
        ui->tableWidget->setItem(row, 1, itmajor);
        ui->tableWidget->setItem(row, 2, itname);
        ui->tableWidget->setItem(row, 3, itnumber);
        ui->tableWidget->setItem(row, 4, itemCourse);
        ui->tableWidget->setItem(row, 5, itscore);
        // ui->examsTable->setItem(row, 6, itemTime);
        qDebug() << score["Score"];
    }
}
