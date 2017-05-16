#ifndef ADDTRAIN_H
#define ADDTRAIN_H

#include <QWidget>
#include "communication.h"
#include "utjs_classes.hpp"

namespace Ui {
class AddTrain;
}

extern int communication_code;
extern sjtu::map<QString,SeatType> translate;
extern sjtu::map<char,TrainType> toTrainType;

class AddTrain : public QWidget
{
    Q_OBJECT

public:
    QString train_id,train_msg;
    explicit AddTrain(QWidget *parent = 0);
    Communication com;
    ~AddTrain();

private slots:
    void on_BackButton_clicked();

    void on_CancelButton_clicked();

    void receiveshow();

    void download_finished();
signals:
    void menu_admin_show();
private:
    Ui::AddTrain *ui;
};

#endif // ADDTRAIN_H
