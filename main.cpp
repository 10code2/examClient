#include "Enroll.h"
#include "examteacher.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Enroll:: getInstance().show();
//    ExamTeacher t;
//    t.show();
    return a.exec();
}
