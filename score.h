#ifndef SCORE_H
#define SCORE_H

#include <QWidget>

namespace Ui {
class Score;
}

class Score : public QWidget
{
    Q_OBJECT

public:
    explicit Score(QWidget *parent = nullptr);
    ~Score();

    void setScores(const QList<QJsonObject> &exams);

private slots:
    void on_pushButton_search_clicked();

private:
    Ui::Score *ui;
    void fetchStudents(const QString &major, const QString &course, const QString &name, const QString &number, const QString &className);
};

#endif // SCORE_H
