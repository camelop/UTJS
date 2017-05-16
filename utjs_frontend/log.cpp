#include "log.h"
#include "ui_log.h"

Log::Log(QWidget *parent) : QWidget(parent), ui(new Ui::Log)
{
    ui->setupUi(this);
}

Log::~Log()
{
    delete ui;
}

void Log::on_BackButton_clicked()
{
    emit menu_admin_show();
    this->hide();
}

void Log::receiveshow()
{
    ui->textBrowser->setText(log);
    this->show();
}
