#include "refund_f.h"
#include "ui_refund_f.h"

Refund_F::Refund_F(QWidget *parent) : QWidget(parent), ui(new Ui::Refund_F)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

Refund_F::~Refund_F()
{
    delete ui;
}

void Refund_F::on_BackButton_clicked()
{
    emit menu_user_show();
    this->hide();
}

void Refund_F::receiveshow()
{
    this->show();
}
