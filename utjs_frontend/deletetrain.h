#ifndef DELETETRAIN_H
#define DELETETRAIN_H

#include <QWidget>
#include <QMessageBox>
#include <QDate>
#include "communication.h"

namespace Ui {
    class DeleteTrain;
}

extern int communication_code;

class DeleteTrain : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteTrain(QWidget *parent = 0);
    QString  train_id;
    QDate date;
    Communication com;
    char ret[13];
    ~DeleteTrain();

private slots:
    void on_BackButton_clicked();

    void on_CancelButton_clicked();

    void receiveshow();

    void download_finished();

signals:
    void menu_admin_show();

private:
    Ui::DeleteTrain *ui;
};

#endif // DELETETRAIN_H
