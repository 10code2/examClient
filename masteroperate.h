#ifndef MASTEROPERATE_H
#define MASTEROPERATE_H

#include <QWidget>

namespace Ui {
class MasterOperate;
}

class MasterOperate : public QWidget
{
    Q_OBJECT

public:

    ~MasterOperate();
    static MasterOperate &getInstance();

private:
    explicit MasterOperate(QWidget *parent = nullptr);
    Ui::MasterOperate *ui;
    QWidget *examWidget;
    QWidget *scoreWidget;

protected:
    void closeEvent(QCloseEvent *) override; // 重写关闭事件
};


#endif // MASTEROPERATE_H
