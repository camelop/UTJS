#include "login_t.h"
#include "ui_login_t.h"

Login_T::Login_T(QWidget *parent) : QWidget(parent), ui(new Ui::Login_T)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

Login_T::~Login_T()
{
    delete ui;
}

void Login_T::on_BackButton_clicked()
{
    emit login_show();
    this->hide();
}

void Login_T::receiveshow()
{
    this->show();
}
