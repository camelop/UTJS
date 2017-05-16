#include "menu_user.h"
#include "ui_menu_user.h"
#include "communication.h"
#include "basic_binary_class.hpp"
#include "utjs_classes.hpp"

Menu_User::Menu_User(QWidget *parent) : QWidget(parent), ui(new Ui::Menu_User),com(communication_code)
{
    ui->setupUi(this);
    QObject::connect(&com,SIGNAL(finishDownload()),this,SLOT(download_finished()));
}

Menu_User::~Menu_User()
{
    delete ui;
}

void Menu_User::download_finished(){
    qDebug() << "get!!!!!";
    std::stringstream sss;
    for (int i = 0; i < com.o.size(); ++i)
        sss << (com.o.data())[i];
    sjtu::vector<Ticket> ret;
    sss >> ret;
    emit ticketslist_show(ret);
    this->hide();
}

void Menu_User::on_MyTicketsButton_clicked()
{
    char ret[17];
    QByteArray tmp=_id.toLatin1(); strcpy(ret,tmp.data());
    //识别码_4
    std::stringstream sss;
    com.i.resize(0);
    sss << Bint(4) << Bchar<17>(ret);
    com.i.append(QByteArray(sss.str().c_str(),sss.str().length()));
    com.communicate();

}

void Menu_User::on_MoreTicketsButton_clicked()
{
    emit saletickets_show();
    this->hide();
}

void Menu_User::on_MyInfoButton_clicked()
{
    emit modifypswd_show();
    this->hide();
}

void Menu_User::on_BackLogButton_clicked()
{
    emit back_log();
    this->hide();
}

void Menu_User::receiveshow()
{
    ui->id->setText("<html><head/><body><p>ID: " + _id + "</p></body></html>");
    ui->name->setText("<html><head/><body><p>姓名: " + _name + "</p></body></html>");
    this->show();
}
