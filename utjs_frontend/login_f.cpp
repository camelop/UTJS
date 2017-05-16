#include "login_f.h"
#include "ui_login_f.h"

Login_F::Login_F(QWidget *parent) : QWidget(parent), ui(new Ui::Login_F)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

Login_F::~Login_F()
{
    delete ui;
}

void Login_F::on_BackLogButton_clicked()
{
    emit login_show();
    this->hide();
}

void Login_F::receiveshow()
{
    this->show();
}
