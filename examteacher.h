#ifndef EXAMTEACHER_H
#define EXAMTEACHER_H

#include <QWidget>
#include<QPushButton>
#include<QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>

namespace Ui {
class ExamTeacher;
}

class ExamTeacher : public QWidget
{
    Q_OBJECT

public:
    explicit ExamTeacher(QWidget *parent = nullptr);
    ~ExamTeacher();

    void setExams(const QList<QJsonObject> &exams);

public slots:
    void onCellDoubleClicked(int row, int column);

private slots:
    void on_searchButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::ExamTeacher *ui;
    QPushButton *pushBt;

    void initializeSampleData(); // 测试函数
    // 1 搜索考试
    void fetchExams(const QString &academicYear, const QString &semester, const QString &course, const QString &teacher, const QString &data, const QString &end);
    // 2 发布考试
    void CreateExam(const QString &academicYear, const QString &semester, const QString &course, const QString &teacher, const QString &data, const QString &end);
    // 3 删除考试
    void deleteExam(const QString &academicYear, const QString &semester, const QString &course, const QString &teacher, const QString &data, const QString &end);

};

#endif // EXAMTEACHER_H
