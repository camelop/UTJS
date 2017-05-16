#include "viewuser.h"
#include "ui_viewuser.h"
#include <QMessageBox>
#include "communication.h"
#include "basic_binary_class.hpp"
#include "utjs_classes.hpp"

ViewUser::ViewUser(QWidget *parent) : QWidget(parent), ui(new Ui::ViewUser),com(communication_code)
{
    ui->setupUi(this);
    QObject::connect(&com,SIGNAL(finishDownload()),this,SLOT(download_finished()));
}

ViewUser::~ViewUser()
{
    delete ui;
}

void ViewUser::download_finished(){
    qDebug() << "get!!!!!";
    std::stringstream sss;
    for (int i = 0; i < com.o.size(); ++i)
        sss << (com.o.data())[i];
    User _user;
    sjtu::vector<Ticket> ret;
    sss >> _user >> ret;
    QByteArray tmp(_user.name,33);
    _name=tmp;
    tmp=QByteArray(_user.id,17);
    _id=tmp;
    qDebug() << _id;
    qDebug() << _name;
    qDebug() << ret.size();
    emit user_info_show(ret);
}

void ViewUser::on_AskUserButton_clicked()
{
    id=ui->lineEdit->text();
    QRegExp rxid("[a-zA-Z0-9_]{1,16}");
        if (!rxid.exactMatch(id)){
            QMessageBox message(QMessageBox::NoIcon, "警告", "ID格式错误");
            message.exec();
            return;
        }

    QByteArray tmp=id.toLatin1(); strcpy(ret,tmp.data());
    //识别码_13

    std::stringstream sss;
    com.i.resize(0);
    sss<< Bint(13) << Bchar<17>(ret);
    com.i.append(QByteArray(sss.str().c_str(),sss.str().length()));
    com.communicate();

}

void ViewUser::on_BackButton_clicked()
{
    emit menu_admin_show();
    this->hide();
}

void ViewUser::receiveshow()
{
    this->show();
}
