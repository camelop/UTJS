#include "mytickets.h"
#include "ui_mytickets.h"
#include "communication.h"
#include "basic_binary_class.hpp"
#include "utjs_classes.hpp"
#include <QMessageBox>
#include <QtDebug>

MyTickets::MyTickets(QWidget *parent) : QWidget(parent), ui(new Ui::MyTickets),com(communication_code)
{
    ui->setupUi(this);
    QObject::connect(&com,SIGNAL(finishDownload()),this,SLOT(download_finished()));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"日期"<<"车次"<<"出发地点"<<"目的地点"<<"张数"<<"座席类别"<<"票价"<<"订单类型");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

MyTickets::~MyTickets()
{
    delete ui;
}

void MyTickets::download_finished(){
    qDebug() << "get!!!!!";
    std::stringstream sss;
    for (int i = 0; i < com.o.size(); ++i)
        sss << (com.o.data())[i];
    bool flag=false;
    sss >> flag;
    qDebug() << flag;
    if (!flag){
        emit refund_f();
        return;
    }
    emit refund_t();
    this->hide();
}

void MyTickets::receiveshow(sjtu::vector<Ticket> tl)
{
    ui->name->setText("用户姓名: "+_name);
    ui->id->setText("用户id "+_id);

    ticket_list=tl;

    int row=ui->tableWidget->rowCount();
    for(int i=0;i<row;++i)
        for(int j=0;j<8;++j)
            if (ui->tableWidget->item(i,j)!=NULL) delete ui->tableWidget->item(i,j);

    ui->tableWidget->setRowCount(ticket_list.size());
    for(int i=0;i<ticket_list.size();++i){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(ticket_list[i].date.toQString()));
        QByteArray t(ticket_list[i].trainId,13);
        QString tmp=t;
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(tmp));
        t=QByteArray(ticket_list[i].fromStationId,21);
        tmp=t;
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(tmp));
        t=QByteArray(ticket_list[i].toStationId,21);
        tmp=t;
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(tmp));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number((int)ticket_list[i].num)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(translate2[ticket_list[i].seatType]));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString("%1").arg(ticket_list[i].price)));
        if (ticket_list[i].canceled) ui->tableWidget->setItem(i,7,new QTableWidgetItem("已退订"));
        else ui->tableWidget->setItem(i,7,new QTableWidgetItem("已购买"));
    }
    this->show();
}

void MyTickets::on_RefundButton_clicked()
{
    QList<QTableWidgetItem*> ret=ui->tableWidget->selectedItems();
    int row=ui->tableWidget->rowCount()? ui->tableWidget->row(ret.at(0)):-1;
    if (row==-1) return;
    if (ticket_list[row].canceled==true) return;
    std::stringstream sss;
    qDebug() << ticket_list[row].index;
    com.i.resize(0);
    sss<< Bint(7) << ticket_list[row];
    com.i.append(QByteArray(sss.str().c_str(),sss.str().length()));
    com.communicate();
}

void MyTickets::on_BackButton_clicked()
{
    emit menu_user_show();
    this->hide();
}
