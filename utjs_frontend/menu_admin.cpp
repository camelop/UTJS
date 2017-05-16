#include "menu_admin.h"
#include "ui_menu_admin.h"

Menu_Admin::Menu_Admin(QWidget *parent) : QWidget(parent), ui(new Ui::Menu_Admin)
{
    ui->setupUi(this);
}

Menu_Admin::~Menu_Admin()
{
    delete ui;
}

void Menu_Admin::on_ChangeTrain_clicked()
{
    emit changetrain_show();
    this->hide();
}

void Menu_Admin::on_ModifySell_clicked()
{
    emit modifysell_show();
    this->hide();
}

void Menu_Admin::on_ModifyUser_clicked()
{
    emit viewuser_show();
    this->hide();
}

void Menu_Admin::on_ViewLog_clicked()
{
    emit log_show();
    this->hide();
}

void Menu_Admin::on_BackLogButton_clicked()
{
    emit login_show();
    this->hide();
}

void Menu_Admin::receiveshow()
{
    this->show();
}
