#include "buytickets_f.h"
#include "ui_buytickets_f.h"

BuyTickets_F::BuyTickets_F(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuyTickets_F)
{
    ui->setupUi(this);
}

BuyTickets_F::~BuyTickets_F()
{
    delete ui;
}

void BuyTickets_F::on_BackButton_clicked()
{
    emit menu_user_show();
    this->hide();
}

void BuyTickets_F::receiveshow()
{
    this->show();
}
