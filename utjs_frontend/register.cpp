#include "register.h"
#include "ui_register.h"
#include "utjs_classes.hpp"
#include <QMessageBox>
#include <QtDebug>
#include "communication.h"
#include "basic_binary_class.hpp"

Register::Register(QWidget *parent) : QWidget(parent), ui(new Ui::Register),com(communication_code)
{
    ui->setupUi(this);
    QObject::connect(&com,SIGNAL(finishDownload()),this,SLOT(download_finished()));
    Register::setTabOrder(ui->id,ui->name);
    Register::setTabOrder(ui->name,ui->setpswd);
    Register::setTabOrder(ui->setpswd,ui->repswd);
    Register::setTabOrder(ui->repswd,ui->id);

}

Register::~Register()
{
    delete ui;
}

void Register::download_finished(){
    qDebug() << "get!!!!!";
    std::stringstream sss;
    for (int i = 0; i < com.o.size(); ++i)
        sss << (com.o.data())[i];
    bool flag;
    sss >> flag;
    qDebug() << flag;
    if (!flag){
        emit regi_f();
    } else emit back_log();
    this->hide();
}

void Register::on_BackButton_clicked()
{
    id=ui->id->text();
    name=ui->name->text();
    newpswd=ui->setpswd->text();
    repswd=ui->repswd->text();
    QRegExp rxid("[a-zA-Z0-9_]{1,16}");
    QRegExp rxpd("[a-zA-Z0-9!@#%&*_-=+]{6,20}");
    if (!rxid.exactMatch(id)){
        QMessageBox message(QMessageBox::NoIcon, "警告", "ID格式错误");
        message.exec();
        return;
    }
    if (!rxpd.exactMatch(newpswd)){
        QMessageBox message(QMessageBox::NoIcon, "警告", "密码格式错误");
        message.exec();
        return;
    }
    QRegExp rx(".{1,8}");
    if (!rx.exactMatch(name)){
        QMessageBox message(QMessageBox::NoIcon, "警告", "姓名格式错误");
        message.exec();
        return;
    }
    qDebug()<<newpswd;
    qDebug()<<repswd;
    if (newpswd!=repswd){
        QMessageBox message(QMessageBox::NoIcon, "警告", "密码不一致");
        message.exec();
        return;
    }
    _id=id,_name=name;

    User _user;
    QByteArray tmp=id.toLatin1(); strcpy(_user.id,tmp.data());
    tmp=newpswd.toLatin1(); strcpy(_user.passWord,tmp.data());
    tmp=name.toUtf8(); strcpy(_user.name,tmp.data());
    //识别码_1
    qDebug() << "ready";
    std::stringstream sss;
    com.i.resize(0);
    sss<< Bint(1) << _user;
    com.i.append(QByteArray(sss.str().c_str(),sss.str().length()));
    com.communicate();
    qDebug() << "not lxy's guo";
}

void Register::on_BackLogButton_clicked()
{
    emit back_log();
    this->hide();
}

void Register::receiveshow()
{
    ui->id->clear();
    ui->name->clear();
    ui->repswd->clear();
    ui->setpswd->clear();
    this->show();
}
