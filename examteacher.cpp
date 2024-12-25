#include "examteacher.h"
#include "ui_examteacher.h"
#include "Enroll.h"
#include "CommunicationProtocol.h"

ExamTeacher::ExamTeacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamTeacher)
{
    ui->setupUi(this);

    connect(ui->examsTable, &QTableWidget::cellDoubleClicked, this, &ExamTeacher::onCellDoubleClicked);

    initializeSampleData();
    // ui->examsTable->setCellWidget(1,0,pushBt);
}

ExamTeacher::~ExamTeacher()
{
    delete ui;
}

void ExamTeacher::setExams(const QList<QJsonObject> &exams)
{
    ui->examsTable->clearContents(); // 清空现有内容
    ui->examsTable->setRowCount(0);   // 清除所有行
    ui->examsTable->setRowCount(exams.size()); // 设置行数
    qDebug() << "exams num = " << exams.size();

    for (int row = 0; row < exams.size(); ++row) {
        const QJsonObject& exam = exams[row];

        QTableWidgetItem* itemRow = new QTableWidgetItem(QString::number(row + 1));
        QTableWidgetItem* itemAcademicYear = new QTableWidgetItem(exam["AcademicYear"].toString());
        QTableWidgetItem* itemSemester = new QTableWidgetItem(exam["Term"].toString());
        QTableWidgetItem* itemCourse = new QTableWidgetItem(exam["CourseName"].toString());
        QTableWidgetItem* itemTeacher = new QTableWidgetItem(exam["Examiner"].toString());
        QTableWidgetItem* itemData = new QTableWidgetItem(exam["ExamDate"].toString());
        QTableWidgetItem* itemTime = new QTableWidgetItem(exam["EndTime"].toString());

        ui->examsTable->setItem(row, 0, itemRow);
        ui->examsTable->setItem(row, 1, itemAcademicYear);
        ui->examsTable->setItem(row, 2, itemSemester);
        ui->examsTable->setItem(row, 3, itemCourse);
        ui->examsTable->setItem(row, 4, itemTeacher);
        ui->examsTable->setItem(row, 5, itemData);
        ui->examsTable->setItem(row, 6, itemTime);
    }
}

void ExamTeacher::onCellDoubleClicked(int row, int column)
{
   Q_UNUSED(column);

   ui->academicYearLineEdit->setText(ui->examsTable->item(row, 1)->text());
   ui->semesterLineEdit->setText(ui->examsTable->item(row, 2)->text());
   ui->courseLineEdit->setText(ui->examsTable->item(row, 3)->text());
   ui->teacherLineEdit->setText(ui->examsTable->item(row, 4)->text());
   ui->dataLineEdit->setText(ui->examsTable->item(row, 5)->text());
   ui->endLineEdit->setText(ui->examsTable->item(row, 6)->text());
}

void ExamTeacher::initializeSampleData()
{
    ui->examsTable->setRowCount(3);

    ui->examsTable->setItem(0, 0, new QTableWidgetItem("1"));
    ui->examsTable->setItem(0, 1, new QTableWidgetItem("2023-2024"));
    ui->examsTable->setItem(0, 2, new QTableWidgetItem("Fall"));
    ui->examsTable->setItem(0, 3, new QTableWidgetItem("Mathematics"));
    ui->examsTable->setItem(0, 4, new QTableWidgetItem("Dr. Smith"));
    ui->examsTable->setItem(0, 5, new QTableWidgetItem("2023-07-25"));
    ui->examsTable->setItem(0, 6, new QTableWidgetItem("11:30"));

    ui->examsTable->setItem(1, 0, new QTableWidgetItem("2"));
    ui->examsTable->setItem(1, 1, new QTableWidgetItem("2023-2024"));
    ui->examsTable->setItem(1, 2, new QTableWidgetItem("Spring"));
    ui->examsTable->setItem(1, 3, new QTableWidgetItem("python"));
    ui->examsTable->setItem(1, 4, new QTableWidgetItem("Prof. Johnson"));
    ui->examsTable->setItem(1, 5, new QTableWidgetItem("2023-05-25"));
    ui->examsTable->setItem(1, 6, new QTableWidgetItem("14:30"));

    ui->examsTable->setItem(2, 0, new QTableWidgetItem("3"));
    ui->examsTable->setItem(2, 1, new QTableWidgetItem("2023-2024"));
    ui->examsTable->setItem(2, 2, new QTableWidgetItem("Spring"));
    ui->examsTable->setItem(2, 3, new QTableWidgetItem("C++"));
    ui->examsTable->setItem(2, 4, new QTableWidgetItem("Dr. Smith"));
    ui->examsTable->setItem(2, 5, new QTableWidgetItem("2023-05-25"));
    ui->examsTable->setItem(2, 6, new QTableWidgetItem("14:30"));


}

void ExamTeacher::fetchExams(const QString &academicYear, const QString &semester, const QString &course, const QString &teacher, const QString &data, const QString &end)
{
    CommunicationProtocol::GetExamsRequest request;
    request.academicYear = academicYear;
    request.semester = semester;
    request.course = course;
    request.teacher = teacher;
    request.data = data;
    request.end = end;

    qDebug() << request.academicYear << request.course << request.data;

    Enroll::getInstance().sendRequest(request.toJson());
}

void ExamTeacher::CreateExam(const QString &academicYear, const QString &semester, const QString &course, const QString &teacher, const QString &data, const QString &end)
{
    CommunicationProtocol::CreateExamRequest request;
    request.academicYear = academicYear;
    request.semester = semester;
    request.course = course;
    request.teacher = teacher;
    request.data = data;
    request.end = end;

    Enroll::getInstance().sendRequest(request.toJson());
}

void ExamTeacher::deleteExam(const QString &academicYear, const QString &semester, const QString &course, const QString &teacher, const QString &data, const QString &end)
{
    CommunicationProtocol::DeleteExamRequest request;
    request.academicYear = academicYear;
    request.semester = semester;
    request.course = course;
    request.teacher = teacher;
    request.data = data;
    request.end = end;

    Enroll::getInstance().sendRequest(request.toJson());
}

void ExamTeacher::on_searchButton_clicked()
{
    QString academicYear = ui->academicYearLineEdit->text();
    QString semester = ui->semesterLineEdit->text();
    QString course = ui->courseLineEdit->text();
    QString teacher = ui->teacherLineEdit->text();
    QString data = ui->dataLineEdit->text();
    QString end = ui->endLineEdit->text();

    fetchExams(academicYear, semester, course, teacher, data, end);
}

void ExamTeacher::on_pushButton_clicked()
{
    QString academicYear = ui->academicYearLineEdit->text();
    QString semester = ui->semesterLineEdit->text();
    QString course = ui->courseLineEdit->text();
    QString teacher = ui->teacherLineEdit->text();
    QString data = ui->dataLineEdit->text();
    QString end = ui->endLineEdit->text();

    if(academicYear.isEmpty() || semester.isEmpty() || course.isEmpty() ||
            teacher.isEmpty() ||data.isEmpty() ||end.isEmpty()){
        qDebug() << "考试信息不全";
        return;
    }

    CreateExam(academicYear, semester, course, teacher, data, end);
}

void ExamTeacher::on_pushButton_delete_clicked()
{
    QString academicYear = ui->academicYearLineEdit->text();
    QString semester = ui->semesterLineEdit->text();
    QString course = ui->courseLineEdit->text();
    QString teacher = ui->teacherLineEdit->text();
    QString data = ui->dataLineEdit->text();
    QString end = ui->endLineEdit->text();

    if(academicYear.isEmpty() || semester.isEmpty() || course.isEmpty() ||
            teacher.isEmpty() ||data.isEmpty() ||end.isEmpty()){
        qDebug() << "考试信息不全";
        return;
    }

    deleteExam(academicYear, semester, course, teacher, data, end);
}

void ExamTeacher::on_pushButton_clear_clicked()
{
    ui->academicYearLineEdit->clear();
    ui->semesterLineEdit->clear();
    ui->courseLineEdit->clear();
    ui->teacherLineEdit->clear();
    ui->dataLineEdit->clear();
    ui->endLineEdit->clear();
}
