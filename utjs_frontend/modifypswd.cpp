#include "modifypswd.h"
#include "ui_modifypswd.h"
#include <QMessageBox>
#include <QRegExp>
#include <QString>
#include "utjs_classes.hpp"
#include "communication.h"
#include "basic_binary_class.hpp"

ModifyPswd::ModifyPswd(QWidget *parent) : QWidget(parent), ui(new Ui::ModifyPswd),com(communication_code)
{
    ui->setupUi(this);
    QObject::connect(&com,SIGNAL(finishDownload()),this,SLOT(download_finished()));
}

ModifyPswd::~ModifyPswd()
{
    delete ui;
}

void ModifyPswd::download_finished(){
    qDebug() << "get!!!!!";
    std::stringstream sss;
    for (int i = 0; i < com.o.size(); ++i)
        sss << (com.o.data())[i];
    bool flag;
    sss >> flag;
    qDebug() << flag;
    if (!flag){
        QMessageBox message(QMessageBox::NoIcon,"警告","修改失败");
        message.exec();
        return;
    }
    emit menu_user_show();
    this->hide();
}


void ModifyPswd::on_BackButton_clicked()
{
    oldpswd=ui->lineEdit->text();
    newpswd=ui->lineEdit_2->text();
    repswd=ui->lineEdit_3->text();
    QRegExp rx("[a-zA-Z0-9!@#%&*_-=+]{6,20}");
    if (!rx.exactMatch(newpswd)){
        QMessageBox message(QMessageBox::NoIcon, "警告", "密码格式错误");
        message.exec();
        return;
    }
    if (newpswd!=repswd){
        QMessageBox message(QMessageBox::NoIcon, "警告", "两次密码不一致");
        message.exec();
        return;
    }

    User _user;
    QByteArray tmp=_id.toLatin1(); strcpy(_user.id,tmp.data());
    tmp=oldpswd.toLatin1(); strcpy(_user.passWord,tmp.data());
    tmp=newpswd.toLatin1(); strcpy(_user.hashSalt,tmp.data());
    //识别码_3

    std::stringstream sss;
    com.i.resize(0);
    sss<< Bint(3) << _user;
    com.i.append(QByteArray(sss.str().c_str(),sss.str().length()));
    com.communicate();

}

void ModifyPswd::on_CancelButton_clicked()
{
    emit menu_user_show();
    this->hide();
}

void ModifyPswd::receiveshow()
{
    this->show();
}
