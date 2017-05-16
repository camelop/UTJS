#ifndef REGISTER_F_H
#define REGISTER_F_H

#include <QWidget>

namespace Ui {
class Register_F;
}


class Register_F : public QWidget
{
    Q_OBJECT

public:
    explicit Register_F(QWidget *parent = 0);
    ~Register_F();

private slots:

    void receiveshow();

    void on_BackLogButton_clicked();

signals:
    void login_show();

private:
    Ui::Register_F *ui;
};


#endif // REGISTER_F_H
