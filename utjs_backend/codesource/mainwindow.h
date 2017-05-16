#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
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
    bool DelteTrain(const Train &trainToDel);
    bool StopTrainSale(const Train &trainToChange);
    bool StartTrainSale(const Train &trainToChange);
    bool CancelTicket2(const Ticket &ticketToCan);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
