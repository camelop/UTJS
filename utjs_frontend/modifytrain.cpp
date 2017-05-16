﻿#include "modifytrain.h"
#include "ui_modifytrain.h"
#include <QRegExp>
#include <QMessageBox>
#include "communication.h"
#include "basic_binary_class.hpp"
#include <exception>
#include <QDate>

ModifyTrain::ModifyTrain(QWidget *parent) : QWidget(parent), ui(new Ui::ModifyTrain),com(communication_code)
{
    ui->setupUi(this);
    QObject::connect(&com,SIGNAL(finishDownload()),this,SLOT(download_finished()));
}

ModifyTrain::~ModifyTrain()
{
    delete ui;
}

void ModifyTrain::download_finished(){
    qDebug() << "get!!!!!";
    std::stringstream sss;
    for (int i = 0; i < com.o.size(); ++i)
        sss << (com.o.data())[i];
    bool flag;
    sss >> flag;
    if (!flag){
        QMessageBox message(QMessageBox::NoIcon, "警告", "修改失败");
        message.exec();
        return;
    }
    QMessageBox message(QMessageBox::NoIcon, "新消息", "删除成功");
    message.exec();
}

void strcpyFromQString(char* x,QString &ori){
    QByteArray temp=ori.toUtf8();
    strcpy(x,temp.data());
}

void ModifyTrain::on_BackButton_clicked()
{
    train_msg=ui->textEdit->toPlainText();

    Train _Train;
    QDate date=ui->dateEdit->date();
    QStringList all=train_msg.split('\n');

        int cnt=0;
        QString line;
        if (all.size()==0) {
            QMessageBox::warning(NULL, "Sorry...", "Wrong data format!");
            return;
        }
        line=all[cnt++];
        if (line=="请在填写好输入后删除该行"){
            QMessageBox::warning(NULL, "Sorry...", "请在填写好输入后删除第一行！");
            return;
        }
        cnt--;
        try{
            if (cnt>all.size()) throw -1;
            line = all[cnt++];
            if (line.size()<2) throw -2;
            Train nw;
            QByteArray tmp=line.toLatin1();
            strcpy(nw.id,tmp.data());
            nw.type=toTrainType[nw.id[0]];
            if (cnt>all.size()) throw -3;
            line = all[cnt++];
            QStringList parts = line.split(",");
            qDebug() << parts[5];
            qDebug() << parts[6];
            qDebug() << parts[7];
            if(parts.size()>5) nw.seatType[0]=translate[parts[5]];
                else nw.seatType[0]=None;
            if(parts.size()>6) nw.seatType[1]=translate[parts[6]];
                else nw.seatType[1]=None;
            if(parts.size()>7) nw.seatType[2]=translate[parts[7]];
                else nw.seatType[2]=None;
            for(int i=0;i<3;++i) qDebug() << nw.seatType[i];
            nw.sale=true; nw.sold=false;
            nw.stationNumber=0;
            nw.date=Date(2000,1,1);

            if (cnt>all.size()) throw -4;
            line = all[cnt++];
                while(cnt<=all.size()){
                    QStringList parts = line.split(",");
                    TrainStation nws;
                    QByteArray tmp=parts[0].toUtf8();
                    strcpy(nws.id,tmp.data());
                    if (parts[2]==QString(QStringLiteral("起点站"))){
                        nws.type=FirstStation;
                    } else {
                        if (parts[3]==QString("终到站")){
                            nws.type=LastStation;
                        } else
                            nws.type=MiddleStation;
                    }
                    if(parts.size()>5) {
                        nws.price[0]=(parts[5].right(parts[5].length ()-1)).toFloat();
                        if (parts[5]=='-') nws.price[0]=0;
                    }
                    if(parts.size()>6) {
                        nws.price[1]=(parts[6].right(parts[6].length ()-1)).toFloat();
                        if (parts[6]=='-') nws.price[1]=0;
                    }
                    if(parts.size()>7) {
                        nws.price[2]=(parts[7].right(parts[7].length ()-1)).toFloat();
                        if (parts[7]=='-') nws.price[2]=0;
                    }
                    if (nws.type!=FirstStation) nws.arriveTime=Time(parts[2]);
                    if (nws.type!=LastStation) nws.departureTime=Time(parts[3]);
                    nws.distance=(parts[4].left(parts[4].length ()-2)).toShort();
                    nw.ticketNumber[0].push_back(2000);
                    nw.ticketNumber[1].push_back(2000);
                    nw.ticketNumber[2].push_back(2000);
                    nw.stations.push_back(nws);

                    if (nws.type==LastStation) break;
                    if (cnt>all.size()) throw -5;
                    line = all[cnt++];
                }
                //to be decided
                nw.stationNumber=nw.stations.size();
                //end to be
                _Train=nw;
        } catch(int x){
            QMessageBox::warning(NULL, "Sorry...", "Wrong data format!");
            return;
        }
    _Train.date.year=date.year();
    _Train.date.month=date.month();
    _Train.date.day=date.day();
        //send nw


    //识别码_9
    std::stringstream sss;
        com.i.resize(0);
        sss<< Bint(9) << _Train;
        com.i.append(QByteArray(sss.str().c_str(),sss.str().length()));
        com.communicate();

}

void ModifyTrain::on_CancelButton_clicked()
{
    emit menu_admin_show();
    this->hide();
}

void ModifyTrain::receiveshow()
{
    ui->dateEdit->setDate(QDate(2017,4,8));
    this->show();
}
