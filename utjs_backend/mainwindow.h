#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "utjs_stl.hpp"
#include <QtDebug>
#include <QtNetwork>
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDialog>
#include <QMessageBox>
#include <QStringList>
#include <QCryptographicHash>
#include <QtDebug>
#include <QTime>
#include <QDateTime>
#include <sstream>
#include "utjs_classes.hpp"

#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <ctime>
#include "utjs_classes.hpp"
#include "utjs_stl.hpp"
#include "basic_binary_class.hpp"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void acceptConnection();
    void readMessage();
    void closeConnect();

    void sendData();
    void updateClientProgress(qint64 numBytes);
    void displayError(QAbstractSocket::SocketError socketError);
signals:
    void finishDownload();
    void updateProgressBar(int value);

private slots:
    bool ModifyTrain(const Train &trainToMod);
    void WriteLog(QString newLog);
    void on_pushButton_clicked();
    void myUpdatePB(int rate);
    void reply();


    void on_actionImport_trains_triggered();

    void on_actionExit_triggered();

    void on_actionImport_changes_triggered();

    void on_actionErase_cache_triggered();

    void on_pushButton_2_clicked();

    void on_actionRead_logs_triggered();

private:

    Ui::MainWindow *ui;

    sjtu::map<QString,SeatType> translate;
    sjtu::map<char,TrainType> toTrainType;

    bool isLoggingIn;
    bool state;
    int nwKey;
    sjtu::map<int,QDateTime> validKeys;
    //todo change it into map to record userid
    QByteArray ii,oo;
    QTcpServer *server;
    QTcpSocket *clientConnection;
    quint64 blockSize;
    QHostAddress hostAddress;
    qint16 tcpPort;
    int sendPointer;
    qint64 totalBytes, bytesReceived,
           bytesToReceive, dataSize;

    qint64 bytesWritten,
           bytesToWrite, loadSize;
    QByteArray inBlock, outBlock;
    QTime time, lastTime;

    //backend required
    sjtu::set<Train> trains;
    sjtu::set<User> users;
    sjtu::set<Ticket> tickets;
    bool RegisterUser(const User &userToReg);
    User Login(const User &userLogin);
    bool ChangePassWord(const User &userToChg);
    bool DeleteUser(const char *id);
    sjtu::vector<Ticket> GetTicketByUserId(const char *id);
    bool CancelTicket(const Ticket &ticketToCan);
    sjtu::vector<Train> QueryTicket(const TicketQuery &ticketToQue);
    bool BuyTicket(const Ticket &ticketToBuy);
    bool AddTrain(const Train &trainToAdd);
    bool DeleteTrain(const Train &trainToDel);
    bool StopTrainSale(const Train &trainToChange);
    bool StartTrainSale(const Train &trainToChange);
    bool CancelTicket2(const Ticket &ticketToCan);


};

#endif // MAINWINDOW_H
