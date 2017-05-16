#ifndef TICKETSLIST_H
#define TICKETSLIST_H

#include <QMainWindow>
#include <QDate>
#include "utjs_classes.hpp"

namespace Ui {
    class TicketsList;
}

extern sjtu::map<SeatType,QString> translate2;

class TicketsList : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicketsList(QWidget *parent = 0);
    QDate date;
    QString start_station,to_station,train_id;
    sjtu::vector<Train> train_list;
    float price;
    ~TicketsList();
private slots:
    void receiveshow(QDate,QString,QString,sjtu::vector<Train>);

    void on_BuyButton_clicked();

signals:
    //void buyticket_show(QDate,QString,QString,QString,float);
    void buyticket_show(Train);
private:
    Ui::TicketsList *ui;
};

#endif // TICKETSLIST_H
