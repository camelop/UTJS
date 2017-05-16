#include "buytickets_t.h"
#include "ui_buytickets_t.h"

BuyTickets_T::BuyTickets_T(QWidget *parent) : QWidget(parent), ui(new Ui::BuyTickets_T)
{
    ui->setupUi(this);
}

BuyTickets_T::~BuyTickets_T()
{
    delete ui;
}

void BuyTickets_T::on_BackButton_clicked()
{
    emit menu_user_show();
    this->hide();
}

void BuyTickets_T::receiveshow()
{
    this->show();
}
