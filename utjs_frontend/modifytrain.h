#ifndef MODIFYTRAIN_H
#define MODIFYTRAIN_H

#include <QWidget>
#include "communication.h"

namespace Ui {
    class ModifyTrain;
}

extern int communication_code;
extern sjtu::map<QString,SeatType> translate;
extern sjtu::map<char,TrainType> toTrainType;

class ModifyTrain : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyTrain(QWidget *parent = 0);
    QString train_id,train_msg;
    Communication com;
    ~ModifyTrain();

private slots:
    void on_BackButton_clicked();

    void on_CancelButton_clicked();

    void receiveshow();

    void download_finished();
signals:
    void menu_admin_show();
private:
    Ui::ModifyTrain *ui;
};

#endif // MODIFYTRAIN_H
