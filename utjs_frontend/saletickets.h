#ifndef SALETICKETS_H
#define SALETICKETS_H

#include <QMainWindow>
#include <QDate>
#include "communication.h"
#include "utjs_classes.hpp"

extern QString _id,_name;
extern int communication_code;

namespace Ui {
    class SaleTickets;
}

class SaleTickets : public QMainWindow
{
    Q_OBJECT

public:
    explicit SaleTickets(QWidget *parent = 0);
    QDate date;
    QString start_station,to_station;
    Communication com;
    bool C,D,G,K,T,Z;
    bool train_type[6];
    ~SaleTickets();

private slots:
    void on_AskListButton_clicked();

    void on_BackButton_clicked();

    void receiveshow();

    void on_swap_clicked();

    void on_all_stateChanged(int arg1);

    void download_finished();
signals:
    void menu_user_show();

    void ticketslist_show(QDate,QString,QString,sjtu::vector<Train>);
private:
    Ui::SaleTickets *ui;
};

#endif // SALETICKETS_H
