#include "buyticket.h"
#include "ui_buyticket.h"
#include "utjs_classes.hpp"
#include <QDate>
#include "communication.h"
#include "basic_binary_class.hpp"
#include <QtDebug>

BuyTicket::BuyTicket(QWidget *parent) : QWidget(parent), ui(new Ui::BuyTicket),com(communication_code)
{
    ui->setupUi(this);
    QObject::connect(&com,SIGNAL(finishDownload()),this,SLOT(download_finished()));
}

BuyTicket::~BuyTicket()
{
    delete ui;
}

void BuyTicket::download_finished(){
    qDebug() << "get!!!!!";
    std::stringstream sss;
    for (int i = 0; i < com.o.size(); ++i)
        sss << (com.o.data())[i];
    bool flag;
    sss >> flag;
    qDebug() << flag;
    if (flag){
        emit buy_t();
    }else emit buy_f();
    this->hide();
}

void BuyTicket::on_BackButton_clicked()
{
    Ticket _Ticket;

    ticket_cnt=ui->spinBox->value();
    int k=ui->comboBox->currentIndex();
    _Ticket.seatType=_Train.seatType[k];
    _Ticket.date=_Train.date;
    strcpy(_Ticket.fromStationId,_Train.stations[0].id);
    strcpy(_Ticket.toStationId,_Train.stations[1].id);
    strcpy(_Ticket.trainId,_Train.id);
    QByteArray tmp=_id.toLatin1(); strcpy(_Ticket.userId,tmp.data());
    _Ticket.num=ticket_cnt;
    int row=ui->comboBox->currentIndex();
    _Ticket.price=(int(_Train.stations[1].price[row]-_Train.stations[0].price[row]))*ticket_cnt;

    qDebug() <<_Ticket.trainId;
    qDebug() <<_Ticket.fromStationId;
    qDebug() <<_Ticket.toStationId;
    qDebug() <<_Ticket.seatType;
    qDebug() << ticket_cnt;
    qDebug() << _Ticket.price;
    //座位类型
    //识别码_6
    std::stringstream sss;
    com.i.resize(0);
    Bint temp(6);
    sss<< temp << _Ticket;
    com.i.append(QByteArray(sss.str().c_str(),sss.str().length()));
    com.communicate();
}

void BuyTicket::on_CancelButton_clicked()
{
    this->hide();
}

void BuyTicket::receiveshow(Train t)
{
    ui->comboBox->setEditable(false);
    int cnt=ui->comboBox->count();
    ui->comboBox->clear();
    _Train=t;
    QByteArray tmp(t.id,13);
    train_id=tmp;
    ui->id->setText("用户ID: "+_id);
    ui->train->setText("车次: "+train_id);
    ui->name->setText("用户姓名: "+_name);
    ui->spinBox->setValue(0);
    for(int i=0;i<3;++i){
        if (t.seatType[i]==None) break;
        if ((t.stations[1].price-t.stations[0].price)<0.01) break;
        ui->comboBox->addItem(translate2[t.seatType[i]]);
    }
    this->show();
}

/*void BuyTicket::receiveshow(QDate _d,QString _f,QString _t,QString _ti,float _p)
{
    date=_d,start_station=_f,to_station=_t,train_id=_ti,price=_p;
    ui->id->setText("用户ID: "+_id);
    ui->train->setText("车次: "+train_id);
    ui->name->setText("用户姓名: "+_name);
    this->show();
}*/
