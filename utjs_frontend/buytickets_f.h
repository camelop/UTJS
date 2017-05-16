#ifndef BUYTICKETS_F_H
#define BUYTICKETS_F_H

#include <QWidget>

namespace Ui {
class BuyTickets_F;
}

class BuyTickets_F : public QWidget
{
    Q_OBJECT

public:
    explicit BuyTickets_F(QWidget *parent = 0);
    ~BuyTickets_F();

private slots:
    void on_BackButton_clicked();

    void receiveshow();

signals:
    void menu_user_show();

private:
    Ui::BuyTickets_F *ui;
};

#endif // BUYTICKETS_F_H
