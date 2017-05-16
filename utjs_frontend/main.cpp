#include <QApplication>
#include <QStyleFactory>
#include <QString>
#include <QtNetwork>
#include <QMovie>
#include <QLabel>
#include <QDate>
#include <QFile>
#include <QtDebug>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <QTextCodec>

QString _id,_name;
int communication_code;

#include "utjs_classes.hpp"
#include "utjs_stl.hpp"
#include "basic_binary_class.hpp"

//enum SeatType {None, TeDengZuo, YiDengZuo, ErDengZuo, YingZuo, RuanZuo, ShangWuZuo, WuZuo, YingWoXia, RuanWoXia, GaoJiRuanWo}; // to be developed, constant maxSeatType
sjtu::map<SeatType,QString> translate2;
sjtu::map<QString,SeatType> translate;
sjtu::map<char,TrainType> toTrainType;


#include "mainwindow.h"
#include "login.h"
#include "menu_admin.h"
#include "menu_user.h"
#include "register.h"
#include "addtrain.h"
#include "buytickets_f.h"
#include "buytickets_t.h"
#include "changetrain.h"
#include "deletetrain.h"
#include "login_f.h"
#include "login_t.h"
#include "modifypswd.h"
#include "modifysell.h"
#include "modifytrain.h"
#include "mytickets.h"
#include "refund_f.h"
#include "refund_t.h"
#include "saletickets.h"
#include "ticketslist.h"
#include "viewuser.h"
#include "register_f.h"
#include "buyticket.h"
#include "user_info.h"
#include "log.h"

int main(int argc, char *argv[])
{
//    QApplication::setStyle("plastique");
    QApplication::setStyle(QStyleFactory::create("Fusion"));
 //   QFile qss("C:/Users/lxy98/Documents/qtTraining/kehuduan/sjtu/black.qss");
 //   qss.open(QFile::ReadOnly);
 //   qApp->setStyleSheet(qss.readAll());
 //   qss.close();

    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb18030"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    translate["-"]=None;
    translate["特等座"]=TeDengZuo;
    translate["一等座"]=YiDengZuo;
    translate["二等座"]=ErDengZuo;
    translate["硬座"]=YingZuo;
    translate["软座"]=RuanZuo;
    translate["商务座"]=ShangWuZuo;
    translate["无座"]=WuZuo;
    translate["硬卧下"]=YingWoXia;
    translate["软卧下"]=RuanWoXia;
    translate["高级软卧"]=GaoJiRuanWo;

    translate2[None] = "";
    translate2[TeDengZuo] = "特等座";
    translate2[YiDengZuo] = "一等座";
    translate2[ErDengZuo] ="二等座";
    translate2[YingZuo] = "硬座";
    translate2[RuanZuo] = "软座";
    translate2[ShangWuZuo] = "商务座";
    translate2[WuZuo] = "无座";
    translate2[YingWoXia] = "硬卧下";
    translate2[RuanWoXia] = "软卧下";
    translate2[GaoJiRuanWo] = "高级软卧";

    //enum TrainType {C, K, T, D, G};
        toTrainType['C']=C;
        toTrainType['K']=K;
        toTrainType['T']=T;
        toTrainType['D']=D;
        toTrainType['G']=G;
        toTrainType['Z']=Z;


    communication_code=-2;
    QApplication a(argc, argv);
    Login _Login;
    Menu_Admin _Menu_Admin;
    Menu_User _Menu_User;
    Register _Register;
    Register_F _Register_F;
    AddTrain _AddTrain;
    BuyTicket  _BuyTicket;
    BuyTickets_F _BuyTickets_F;
    BuyTickets_T _BuyTickets_T;
    ChangeTrain _ChangeTrain;
    DeleteTrain _DeleteTrain;
    Login_F _Login_F;
    Login_T _Login_T;
    ModifyPswd _ModifyPswd;
    ModifySell _ModifySell;
    ModifyTrain _ModifyTrain;
    MyTickets _MyTickets;
    MainWindow _m;
    Refund_T _Refund_T;
    Refund_F _Refund_F;
    SaleTickets _SaleTickets;
    TicketsList _TicketsList;
    User_Info _User_Info;
    ViewUser _ViewUser;

    QObject::connect(&_Login,SIGNAL(menu_admin_show()),&_Menu_Admin,SLOT(receiveshow()));
    QObject::connect(&_Login,SIGNAL(menu_user_show()),&_Menu_User,SLOT(receiveshow()));
    QObject::connect(&_Login,SIGNAL(register_show()),&_Register,SLOT(receiveshow()));
    QObject::connect(&_Login,SIGNAL(log_f_show()),&_Login_F,SLOT(receiveshow()));
    QObject::connect(&_Menu_User,SIGNAL(back_log()),&_Login,SLOT(receiveshow()));
    QObject::connect(&_Register,SIGNAL(back_log()),&_Login,SLOT(receiveshow()));
    QObject::connect(&_Register,SIGNAL(regi_f()),&_Register_F,SLOT(receiveshow()));
    QObject::connect(&_Register_F,SIGNAL(login_show()),&_Login,SLOT(receiveshow()));
    QObject::connect(&_AddTrain,SIGNAL(menu_admin_show()),&_Menu_Admin,SLOT(receiveshow()));
    QObject::connect(&_BuyTicket,SIGNAL(menu_user_show()),&_Menu_User,SLOT(receiveshow()));
    QObject::connect(&_BuyTicket,SIGNAL(buy_t()),&_BuyTickets_T,SLOT(receiveshow()));
    QObject::connect(&_BuyTicket,SIGNAL(buy_f()),&_BuyTickets_F,SLOT(receiveshow()));
    QObject::connect(&_BuyTickets_F,SIGNAL(menu_user_show()),&_Menu_User,SLOT(receiveshow()));
    QObject::connect(&_BuyTickets_T,SIGNAL(menu_user_show()),&_Menu_User,SLOT(receiveshow()));
    QObject::connect(&_ChangeTrain,SIGNAL(addtrain_show()),&_AddTrain,SLOT(receiveshow()));
    QObject::connect(&_ChangeTrain,SIGNAL(modifytrain_show()),&_ModifyTrain,SLOT(receiveshow()));
    QObject::connect(&_ChangeTrain,SIGNAL(deletetrain_show()),&_DeleteTrain,SLOT(receiveshow()));
    QObject::connect(&_ChangeTrain,SIGNAL(menu_admin_show()),&_Menu_Admin,SLOT(receiveshow()));
    QObject::connect(&_DeleteTrain,SIGNAL(menu_admin_show()),&_Menu_Admin,SLOT(receiveshow()));
    QObject::connect(&_Login_F,SIGNAL(login_show()),&_Login,SLOT(receiveshow()));
    QObject::connect(&_Login_T,SIGNAL(login_show()),&_Login,SLOT(receiveshow()));
    QObject::connect(&_Menu_Admin,SIGNAL(changetrain_show()),&_ChangeTrain,SLOT(receiveshow()));
    QObject::connect(&_Menu_Admin,SIGNAL(modifysell_show()),&_ModifySell,SLOT(receiveshow()));
    QObject::connect(&_Menu_Admin,SIGNAL(viewuser_show()),&_ViewUser,SLOT(receiveshow()));
    QObject::connect(&_Menu_Admin,SIGNAL(login_show()),&_Login,SLOT(receiveshow()));
    QObject::connect(&_Menu_User,SIGNAL(ticketslist_show(sjtu::vector<Ticket>)),&_MyTickets,SLOT(receiveshow(sjtu::vector<Ticket>)));
    QObject::connect(&_Menu_User,SIGNAL(saletickets_show()),&_SaleTickets,SLOT(receiveshow()));
    QObject::connect(&_Menu_User,SIGNAL(modifypswd_show()),&_ModifyPswd,SLOT(receiveshow()));
    QObject::connect(&_ModifyPswd,SIGNAL(menu_user_show()),&_Menu_User,SLOT(receiveshow()));
    QObject::connect(&_ModifySell,SIGNAL(menu_admin_show()),&_Menu_Admin,SLOT(receiveshow()));
    QObject::connect(&_ModifyTrain,SIGNAL(menu_admin_show()),&_Menu_Admin,SLOT(receiveshow()));
    QObject::connect(&_MyTickets,SIGNAL(refund_t()),&_Refund_T,SLOT(receiveshow()));
    QObject::connect(&_MyTickets,SIGNAL(refund_f()),&_Refund_F,SLOT(receiveshow()));
    QObject::connect(&_MyTickets,SIGNAL(menu_user_show()),&_Menu_User,SLOT(receiveshow()));
    QObject::connect(&_Refund_T,SIGNAL(menu_user_show()),&_Menu_User,SLOT(receiveshow()));
    QObject::connect(&_Refund_F,SIGNAL(menu_user_show()),&_Menu_User,SLOT(receiveshow()));
    QObject::connect(&_SaleTickets,SIGNAL(menu_user_show()),&_Menu_User,SLOT(receiveshow()));
    QObject::connect(&_SaleTickets,SIGNAL(ticketslist_show(QDate,QString,QString,sjtu::vector<Train>)),&_TicketsList,SLOT(receiveshow(QDate,QString,QString,sjtu::vector<Train>)));
    QObject::connect(&_TicketsList,SIGNAL(buyticket_show(Train)),&_BuyTicket,SLOT(receiveshow(Train)));
    QObject::connect(&_User_Info,SIGNAL(menu_admin_show()),&_Menu_Admin,SLOT(receiveshow()));
    QObject::connect(&_ViewUser,SIGNAL(menu_admin_show()),&_Menu_Admin,SLOT(receiveshow()));
    QObject::connect(&_ViewUser,SIGNAL(user_info_show(sjtu::vector<Ticket>)),&_User_Info,SLOT(receiveshow(sjtu::vector<Ticket>)));



    _Login.show();
    //_MyTickets.show();

    return a.exec();
}
