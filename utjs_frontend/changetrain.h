#ifndef CHANGETRAIN_H
#define CHANGETRAIN_H

#include <QWidget>

namespace Ui {
    class ChangeTrain;
}

class ChangeTrain : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeTrain(QWidget *parent = 0);
    ~ChangeTrain();

private slots:
    void on_AddTrainButton_clicked();

    void on_ModifyTrainButton_clicked();

    void on_DeleteTrainButton_clicked();

    void on_BackButton_clicked();

    void receiveshow();

signals:
    void addtrain_show();

    void modifytrain_show();

    void deletetrain_show();

    void menu_admin_show();

private:
    Ui::ChangeTrain *ui;
};

#endif // CHANGETRAIN_H
