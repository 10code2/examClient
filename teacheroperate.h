#ifndef TEACHEROPERATE_H
#define TEACHEROPERATE_H

#include <QWidget>
#include<QDebug>
#include<QJsonObject>
#include "examteacher.h"
#include "score.h"


namespace Ui {
class TeacherOperate;
}

class TeacherOperate : public QWidget
{
    Q_OBJECT

public:

    ~TeacherOperate();

    static TeacherOperate &getInstance();

    void handleGetExams(const QJsonObject &jsonObj);
    void handleGetScores(const QJsonObject &jsonObj);

private:
    explicit TeacherOperate(QWidget *parent = nullptr);
    Ui::TeacherOperate *ui;
    ExamTeacher *examWidget;
    Score *scoreWidget;

protected:
    void closeEvent(QCloseEvent *) override; // 重写关闭事件
};

#endif // TEACHEROPERATE_H
