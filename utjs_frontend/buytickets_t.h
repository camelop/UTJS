#ifndef BUYTICKETS_T_H
#define BUYTICKETS_T_H

#include <QWidget>

namespace Ui {
class BuyTickets_T;
}

class BuyTickets_T : public QWidget
{
    Q_OBJECT

public:
    explicit BuyTickets_T(QWidget *parent = 0);
    ~BuyTickets_T();

private slots:
    void on_BackButton_clicked();

    void receiveshow();

signals:
    void menu_user_show();

private:
    Ui::BuyTickets_T *ui;
};

#endif // BUYTICKETS_T_H
