#ifndef LOGIN_T_H
#define LOGIN_T_H

#include <QWidget>

namespace Ui {
    class Login_T;
}

class Login_T : public QWidget
{
    Q_OBJECT

public:
    explicit Login_T(QWidget *parent = 0);
    ~Login_T();

private slots:
    void on_BackButton_clicked();

    void receiveshow();

signals:
    void login_show();
private:
    Ui::Login_T *ui;
};

#endif // LOGIN_T_H
