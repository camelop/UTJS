#include "user_info.h"
#include "ui_user_info.h"
#include "communication.h"
#include "basic_binary_class.hpp"
#include "utjs_classes.hpp"
#include <QMessageBox>
#include <QtDebug>

User_Info::User_Info(QWidget *parent) : QWidget(parent), ui(new Ui::User_Info),com(communication_code)
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

User_Info::~User_Info()
{
    delete ui;
}

void User_Info::on_BackButton_clicked()
{
    emit menu_admin_show();
    _id="0";
    this->hide();
}

void User_Info::receiveshow(sjtu::vector<Ticket> tl)
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
