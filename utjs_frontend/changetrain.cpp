#include "changetrain.h"
#include "ui_changetrain.h"

ChangeTrain::ChangeTrain(QWidget *parent) : QWidget(parent), ui(new Ui::ChangeTrain)
{
    ui->setupUi(this);
}

ChangeTrain::~ChangeTrain()
{
    delete ui;
}

void ChangeTrain::on_AddTrainButton_clicked()
{
    emit addtrain_show();
    this->hide();
}

void ChangeTrain::on_ModifyTrainButton_clicked()
{
    emit modifytrain_show();
    this->hide();
}

void ChangeTrain::on_DeleteTrainButton_clicked()
{
    emit deletetrain_show();
    this->hide();
}

void ChangeTrain::on_BackButton_clicked()
{
    emit menu_admin_show();
    this->hide();
}

void ChangeTrain::receiveshow()
{
    this->show();
}
