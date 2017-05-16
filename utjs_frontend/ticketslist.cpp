#include "ticketslist.h"
#include "ui_ticketslist.h"
#include <QDate>
#include <QtDebug>

TicketsList::TicketsList(QWidget *parent) : QMainWindow(parent), ui(new Ui::TicketsList)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->resizeColumnToContents(0);
    ui->tableWidget->setColumnCount(12);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"车次"<<"出发时间"<<"到达时间"<<"座席类别"<<"票价"<<"剩余票数"<<"座席类别"<<"票价"<<"剩余票数"<<"座席类别"<<"票价"<<"剩余票数");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

TicketsList::~TicketsList()
{
    delete ui;
}

void TicketsList::receiveshow(QDate _d,QString _f,QString _t,sjtu::vector<Train> tl)
{
    train_list=tl;

    int row=ui->tableWidget->rowCount();
    for(int i=0;i<row;++i)
        for(int j=0;j<12;++j)
            if (ui->tableWidget->item(i,j)!=NULL) delete ui->tableWidget->item(i,j);

    ui->tableWidget->clearContents();
    date=_d,start_station=_f,to_station=_t;
    ui->date->setText(_d.toString());
    ui->_start->setText(_f);
    ui->_to->setText(_t);
    ui->tableWidget->setRowCount(train_list.size());
    for(int i=0;i<train_list.size();++i){
        QByteArray t(train_list[i].id,13);
        train_id=t;
        qDebug() << i << ":" << train_id;
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(train_id));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(train_list[i].stations[0].departureTime.toQString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(train_list[i].stations[1].arriveTime.toQString()));
        for(int j=0;j<3;++j){
            qDebug() << train_list[i].seatType[j];
            float price=train_list[i].stations[1].price[j]-train_list[i].stations[0].price[j];
            if (price<0.01) break;
            if (train_list[i].seatType[j]==None) break;
            ui->tableWidget->setItem(i,3+3*j,new QTableWidgetItem(translate2[train_list[i].seatType[j]]));
            ui->tableWidget->setItem(i,5+3*j,new QTableWidgetItem(QString::number((int)train_list[i].ticketNumber[j][0])));
            ui->tableWidget->setItem(i,4+3*j,new QTableWidgetItem(QString("%1").arg(price)));
        }
        qDebug() << '\n';
    }
    this->show();
}

void TicketsList::on_BuyButton_clicked()
{
    QList<QTableWidgetItem*> ret=ui->tableWidget->selectedItems();
    int row=ui->tableWidget->rowCount()? ui->tableWidget->row(ret.at(0)):-1;
    if (row==-1) return;
    emit buyticket_show(train_list[row]);
    this->hide();
}
