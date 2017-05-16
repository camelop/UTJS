#include "saletickets.h"
#include "ui_saletickets.h"
#include <QtDebug>
#include <QString>
#include "utjs_classes.hpp"
#include "communication.h"
#include "basic_binary_class.hpp"

SaleTickets::SaleTickets(QWidget *parent) : QMainWindow(parent), ui(new Ui::SaleTickets),com(communication_code)
{
    ui->setupUi(this);
    QObject::connect(&com,SIGNAL(finishDownload()),this,SLOT(download_finished()));
}

SaleTickets::~SaleTickets()
{
    delete ui;
}

void SaleTickets::download_finished(){
    qDebug() << "get!!!!!";
    std::stringstream sss;
    for (int i = 0; i < com.o.size(); ++i)
        sss << (com.o.data())[i];
    sjtu::vector<Train> tmp;
    sss >> tmp;
    for(int i=0;i<tmp.size();++i){
        qDebug() << i << " : " << tmp[i].id << '\n'
                 << tmp[i].stations[0].price[0] << tmp[i].stations[1].price[0] << '\n'
                 << tmp[i].stations[0].price[1] << tmp[i].stations[1].price[1] << '\n'
                 << tmp[i].stations[0].price[2] << tmp[i].stations[1].price[2] << '\n';
    }
    emit ticketslist_show(date,start_station,to_station,tmp);
}

void SaleTickets::on_AskListButton_clicked()
{
    date=ui->dateEdit->date();
    qDebug() << date;
    start_station=ui->_start->text();
    to_station=ui->_to->text();
    qDebug() << start_station << to_station;
    train_type[0]=ui->c->isChecked();
    train_type[3]=ui->d->isChecked();
    train_type[4]=ui->g->isChecked();
    train_type[1]=ui->k->isChecked();
    train_type[2]=ui->t->isChecked();
    train_type[5]=ui->z->isChecked();
    TicketQuery _TicketQuery;
    _TicketQuery.date.year=date.year();
    _TicketQuery.date.month=date.month();
    _TicketQuery.date.day=date.day();
    QByteArray tmp=start_station.toUtf8(); strcpy(_TicketQuery.fromStationId,tmp.data());
    tmp=to_station.toUtf8(); strcpy(_TicketQuery.toStationId,tmp.data());
    for(int i=0;i<6;++i) _TicketQuery.trainType[i]=train_type[i];
    //识别码_5

    std::stringstream sss;
    com.i.resize(0);
    sss<< Bint(5) << _TicketQuery;
    com.i.append(QByteArray(sss.str().c_str(),sss.str().length()));
    com.communicate();

}

void SaleTickets::on_BackButton_clicked()
{
    emit menu_user_show();
    this->hide();
}

void SaleTickets::receiveshow()
{
    ui->id->setText(" "+_id);
    this->show();
}

void SaleTickets::on_swap_clicked()
{
    QString tmp=ui->_start->text();
    ui->_start->setText(ui->_to->text());
    ui->_to->setText(tmp);
}


void SaleTickets::on_all_stateChanged(int arg1)
{
    if (ui->all->isChecked()){
        ui->c->setChecked(true);
        ui->d->setChecked(true);
        ui->g->setChecked(true);
        ui->k->setChecked(true);
        ui->t->setChecked(true);
        ui->z->setChecked(true);
    }else{
        ui->c->setChecked(false);
        ui->d->setChecked(false);
        ui->g->setChecked(false);
        ui->k->setChecked(false);
        ui->t->setChecked(false);
        ui->z->setChecked(false);
    }
}
