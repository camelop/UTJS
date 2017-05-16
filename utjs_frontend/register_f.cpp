#include "register_f.h"
#include "ui_register_f.h"

Register_F::Register_F(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register_F)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

Register_F::~Register_F()
{
    delete ui;
}

void Register_F::receiveshow()
{
    this->show();
}


void Register_F::on_BackLogButton_clicked()
{
    emit login_show();
    this->hide();
}
