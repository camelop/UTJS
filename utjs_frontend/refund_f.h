#ifndef REFUND_F_H
#define REFUND_F_H

#include <QWidget>

namespace Ui {
    class Refund_F;
}

class Refund_F : public QWidget
{
    Q_OBJECT

public:
    explicit Refund_F(QWidget *parent = 0);
    ~Refund_F();


private slots:
    void on_BackButton_clicked();

    void receiveshow();
signals:
    void menu_user_show();
private:
    Ui::Refund_F *ui;
};


#endif // REFUND_F_H
