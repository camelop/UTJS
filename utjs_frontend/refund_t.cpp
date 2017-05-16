#include "refund_t.h"
#include "ui_refund_t.h"

Refund_T::Refund_T(QWidget *parent) : QWidget(parent), ui(new Ui::Refund_T)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

Refund_T::~Refund_T()
{
    delete ui;
}

void Refund_T::on_BackButton_clicked()
{
    emit menu_user_show();
    this->hide();
}

void Refund_T::receiveshow()
{
    this->show();
}
