#ifndef REFUND_T_H
#define REFUND_T_H

#include <QWidget>

namespace Ui {
    class Refund_T;
}

class Refund_T : public QWidget
{
    Q_OBJECT

public:
    explicit Refund_T(QWidget *parent = 0);
    ~Refund_T();



private slots:
    void on_BackButton_clicked();

    void receiveshow();
signals:
    void menu_user_show();
private:
    Ui::Refund_T *ui;
};

#endif // REFUND_T_H
