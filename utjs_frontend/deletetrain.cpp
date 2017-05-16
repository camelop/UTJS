#include "deletetrain.h"
#include "ui_deletetrain.h"
#include <QMessageBox>
#include <QRegExp>
#include "utjs_classes.hpp"
#include "communication.h"
#include "basic_binary_class.hpp"
#include <QDate>

DeleteTrain::DeleteTrain(QWidget *parent) : QWidget(parent), ui(new Ui::DeleteTrain),com(communication_code)
{
    ui->setupUi(this);
    QObject::connect(&com,SIGNAL(finishDownload()),this,SLOT(download_finished()));
}

DeleteTrain::~DeleteTrain()
{
    delete ui;
}

void DeleteTrain::download_finished(){
    qDebug() << "get!!!!!";
    std::stringstream sss;
    for (int i = 0; i < com.o.size(); ++i)
        sss << (com.o.data())[i];
    bool flag;
    sss >> flag;
    if (!flag){
        QMessageBox message(QMessageBox::NoIcon, "警告", "删除失败");
        message.exec();
        return;
    }
    QMessageBox message(QMessageBox::NoIcon, "新消息", "删除成功");
    message.exec();
}

void DeleteTrain::on_BackButton_clicked()
{
    date=ui->dateEdit->date();
    train_id=ui->lineEdit->text();
    QRegExp rx("[A-Z0-9//]{1,16}");
    if (!rx.exactMatch(train_id)){
        QMessageBox message(QMessageBox::NoIcon, "警告", "车次格式错误");
        message.exec();
        return;
    }

    Train _Train;
    QByteArray tmp=train_id.toLatin1(); strcpy(_Train.id,tmp.data());
    _Train.date.year=date.year();
    _Train.date.month=date.month();
    _Train.date.day=date.day();
    //识别码_10

    std::stringstream sss;
        com.i.resize(0);
        sss << Bint(10) << _Train;
        com.i.append(QByteArray(sss.str().c_str(),sss.str().length()));
        com.communicate();

}

void DeleteTrain::on_CancelButton_clicked()
{
    emit menu_admin_show();
    this->hide();
}

void DeleteTrain::receiveshow()
{
    ui->lineEdit->clear();

    ui->dateEdit->setDate(QDate(2017,4,8));
    this->show();
}
