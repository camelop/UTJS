#ifndef VIEWUSER_H
#define VIEWUSER_H

#include <QWidget>
#include "communication.h"
#include "utjs_classes.hpp"

namespace Ui {
    class ViewUser;
}

extern int communication_code;
extern QString _name,_id;

class ViewUser : public QWidget
{
    Q_OBJECT

public:
    explicit ViewUser(QWidget *parent = 0);
    QString id;
    Communication com;
    char ret[17];
    ~ViewUser();

private slots:
    void on_AskUserButton_clicked();

    void on_BackButton_clicked();

    void receiveshow();

    void download_finished();
signals:
    void menu_admin_show();
    void user_info_show(sjtu::vector<Ticket>);
private:
    Ui::ViewUser *ui;
};

#endif // VIEWUSER_H
