#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QtDebug>
#include <QRegExp>
#include <QMovie>
#include "utjs_classes.hpp"
#include "communication.h"
#include "basic_binary_class.hpp"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login),com(communication_code)
{
    ui->setupUi(this);
    ui->UserID->setText("");
    ui->UserID->setFont(QFont( "Timers" , 8 ,  QFont::Bold) );
    ui->UserID->setStyleSheet("color:black");
    QObject::connect(&com,SIGNAL(finishDownload()),this,SLOT(download_finished()));

    timer = new QTimer(this);
    setWindowFlags(Qt::FramelessWindowHint);
    movie = new QMovie("C:/Users/lxy98/Documents/qtTraining/kehuduan/sjtu/gif.gif");
    ui->label_4->setAlignment(Qt::AlignCenter);
    ui->label_4->setMovie(movie);
    movie->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(4000);
}

void Login::onTimeout(){
    ui->label_4->hide();
}

Login::~Login()
{
    movie->stop();
    delete movie;
    delete ui;
}

void Login::download_finished(){
    qDebug() << "get!!!!!";
    std::stringstream sss;
    for (int i = 0; i < com.o.size(); ++i)
        sss << (com.o.data())[i];
    Bint key;
    sss >> key;
    communication_code = (int)key;
    qDebug()<<"key:" << (int)key;
    User get_user;
    sss >> get_user;
    QByteArray t(get_user.hashSalt,65);
    QString qd=t;
    qDebug() << qd;
    if (strcmp(get_user.hashSalt,"failed")==0){
        emit log_f_show();
        return;
    }
    _id=get_user.id;
    qDebug() << _id;
    if (_id=="0"){
        emit menu_admin_show();
    }else{
        qDebug() << get_user.name;
        QByteArray tmp(get_user.name);
        _name=tmp;
        qDebug() << _name;
        emit menu_user_show();
    }
    this->hide();
}

void Login::on_BackButton_clicked()
{
    id=ui->UserID->text(),pswd=ui->Passward->text();
    QRegExp rxid("[a-zA-Z0-9_]{1,16}");
    QRegExp rxnm("[a-zA-Z0-9!@#%&*_-=+]{6,20}");
    if (!rxid.exactMatch(id)){
            QMessageBox message(QMessageBox::NoIcon, "警告", "ID格式错误");
            message.exec();
            return;
    }
    if (!rxnm.exactMatch(pswd)){
            QMessageBox message(QMessageBox::NoIcon, "警告", "密码格式错误");
            message.exec();
            return;
    }
    User _user;
    QByteArray tmp=id.toLatin1(); strcpy(_user.id,tmp.data());
    tmp=pswd.toLatin1(); strcpy(_user.passWord,tmp.data());
    //识别码_2
    std::stringstream sss;
    com.i.resize(0);
    sss<< Bint(2) << _user;
    com.i.append(QByteArray(sss.str().c_str(),sss.str().length()));
    com.communicate();

}

void Login::on_CancelButton_clicked()
{
    this->hide();
}

void Login::on_RegisterButton_clicked()
{
    emit register_show();
    this->hide();
}

void Login::receiveshow()
{
    communication_code=-2;
    ui->UserID->setText("");
    ui->Passward->clear();
    this->show();
}

void Login::mousePressEvent(QMouseEvent *e)
{
    last = e->globalPos();
}
void Login::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x()+dx, y()+dy);
}
void Login::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}
