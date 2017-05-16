#ifndef LOGIN_F_H
#define LOGIN_F_H

#include <QWidget>

namespace Ui {
    class Login_F;
}

class Login_F : public QWidget
{
    Q_OBJECT

public:
    explicit Login_F(QWidget *parent = 0);
    ~Login_F();

private slots:
    void on_BackLogButton_clicked();

    void receiveshow();
signals:
    void login_show();

private:
    Ui::Login_F *ui;
};

#endif // LOGIN_F_H
