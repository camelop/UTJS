#ifndef MENU_ADMIN_H
#define MENU_ADMIN_H

#include <QWidget>

extern int communication_code;

namespace Ui {
    class Menu_Admin;
}

class Menu_Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Menu_Admin(QWidget *parent = 0);
    ~Menu_Admin();

private slots:
    void on_ChangeTrain_clicked();

    void on_ModifySell_clicked();

    void on_ModifyUser_clicked();

    void on_ViewLog_clicked();

    void on_BackLogButton_clicked();

    void receiveshow();

signals:
    void changetrain_show();

    void modifysell_show();

    void viewuser_show();

    void log_show();

    void login_show();
private:
    Ui::Menu_Admin *ui;
};

#endif // MENU_ADMIN_H
