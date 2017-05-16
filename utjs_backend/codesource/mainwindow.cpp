#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCryptographicHash>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

char HashCharSet(int k) {
    if (k < 26) return 'a' + k;
    else if (k < 52) return 'A' + k - 26;
    else return '0' + k - 52;
}

void GenerateHashSalt(char *s) {
    srand(time(NULL));
    for (int i = 0; i < 64; ++i)
        s[i] = HashCharSet(rand() % 36);
    s[64] = 0;
}

const char* HashPassWord(const char *passWord, const char *hashSalt) {
    QCryptographicHash hash(QCryptographicHash::Sha256);
    QByteArray byteArray;
    byteArray.append(hashSalt);
    byteArray.append(passWord);
    hash.addData(byteArray);
    QByteArray resultByteArray = hash.result();
    QString resultQString = resultByteArray.toHex();
    QByteArray trByteArray = resultQString.toLatin1();
    return trByteArray.data();
}

bool MainWindow::RegisterUser(const User &userToReg) {
    User newUser(userToReg);
    if (users.count(newUser) != 0) return false;
    char newHashSalt[65];
    GenerateHashSalt(newHashSalt);
    strcpy(newUser.hashSalt, newHashSalt);
    strcpy(newUser.passWord, HashPassWord(userToReg.passWord, newUser.hashSalt));
    users.insert(newUser);
    return true;
}

//return "failed" or "success" in loginUser.hashSalt
User MainWindow::Login(const User &userLogin) {
    User loginUser(userLogin);
    strcpy(loginUser.hashSalt, "failed");
    if (users.count(loginUser) == 0) return loginUser;
    auto it = users.find(loginUser);
    strcpy(loginUser.passWord, HashPassWord(loginUser.passWord, it->hashSalt));
    if (strcmp(loginUser.passWord, it->passWord) != 0) return loginUser;
    strcpy(loginUser.name, it->name);
    strcpy(loginUser.hashSalt, "success");
    return loginUser;
}

//frontend send new password in userToChg.hashSalt
bool MainWindow::ChangePassWord(const User &userToChg) {
    User updateUser(userToChg);
    if (users.count(updateUser) == 0) return false;
    sjtu::set<User>::iterator it = users.find(updateUser);
    strcpy(updateUser.passWord, HashPassWord(userToChg.passWord, it->hashSalt));
    if (strcmp(updateUser.passWord, it->passWord) != 0) return false;
    char newHashSalt[65];
    GenerateHashSalt(newHashSalt);
    strcpy(it->hashSalt, newHashSalt);
    strcpy(it->passWord, HashPassWord(userToChg.hashSalt, it->hashSalt));
    return true;
}

bool MainWindow::DeleteUser(const char *id) {
    User userToDel;
    strcpy(userToDel.id, id);
    if (users.count(userToDel) == 0) return false;
    users.erase(users.find(userToDel));
    return true;
}

sjtu::vector<Ticket> MainWindow::GetTicketByUserId(const char *id) {
    sjtu::vector<Ticket> ret;
    sjtu::set<Ticket>::iterator it;
    Ticket ticketToQuery;
    strcpy(ticketToQuery.userId, id);
    ticketToQuery.date = Date(0, 0, 0); // a minimum date
    it = tickets.lower_bound(ticketToQuery);
    for (; it != tickets.end(); ++it) {
        if (strcmp((*it).userId, id) != 0) break;
        ret.push_back(*it);
    }
    return ret;
}

bool MainWindow::CancelTicket(const Ticket &ticketToCan) {
    auto it = tickets.find(ticketToCan);
    if (it == tickets.end()) return false;
    if (it->canceled) return false;
    (*it).canceled = true;
    Train trainToCan;
    trainToCan.date = ticketToCan.date;
    strcpy(trainToCan.id, ticketToCan.trainId);
    auto trainIt = trains.find(trainToCan);
    if (trainIt == trains.end()) return false;
    Ticket ticketToCan2(ticketToCan);
    ticketToCan2.num = -(ticketToCan.num);
    trainIt->buy(ticketToCan2);
    return true;
}

bool MainWindow::CancelTicket2(const Ticket &ticketToCan) {
    auto it = tickets.lower_bound(ticketToCan);
    for (; it != tickets.end(); ++it) {
        if (it->canceled) continue;
        if (!(it->same(ticketToCan))) return false;
        Train trainToCan;
        trainToCan.date = ticketToCan.date;
        strcpy(trainToCan.id, ticketToCan.trainId);
        auto trainIt = trains.find(trainToCan);
        if (trainIt == trains.end()) return false;
        Ticket ticketToCan2(ticketToCan);
        ticketToCan2.num = -(ticketToCan.num);
        trainIt->buy(ticketToCan2);
        if (ticketToCan.num == it->num) it->canceled = true;
        else it->num -= ticketToCan.num;
    }
    return false;
}

sjtu::vector<Train> MainWindow::QueryTicket(const TicketQuery &ticketToQue) {
    sjtu::vector<Train> ret;
    Train trainToQue;
    trainToQue.date = ticketToQue.date;
    strcpy(trainToQue.id, ""); // a minimum id
    auto it = trains.lower_bound(trainToQue);
    for (; it != trains.end(); ++it) {
        if (!ticketToQue.trainType[(*it).type]) continue;
        if (!(*it).link(ticketToQue.fromStationId, ticketToQue.toStationId)) continue;
        ret.push_back((*it).trans(ticketToQue.fromStationId, ticketToQue.toStationId));
    }
    return ret;
}

bool MainWindow::BuyTicket(const Ticket &ticketToBuy) {
    Train trainToBuy;
    trainToBuy.date = ticketToBuy.date;
    strcpy(trainToBuy.id, ticketToBuy.trainId);
    auto trainIt = trains.find(trainToBuy);
    if (trainIt == trains.end()) return false;
    Ticket newTicket = trainIt->buy(ticketToBuy);
    if (newTicket.num == 0) return false;
    auto ticketIt = tickets.lower_bound(newTicket);
    if (ticketIt != tickets.end() && newTicket.same(*ticketIt))
        newTicket.index = ticketIt->index + 1;
    else newTicket.index = 1;
    tickets.insert(newTicket);
    return true;
}

bool MainWindow::AddTrain(const Train &trainToAdd) {
    Train newTrain(trainToAdd);
    auto it = trains.find(newTrain);
    if (it != trains.end()) return false;
    newTrain.sold = false;
    newTrain.sale = true;
    trains.insert(newTrain);
    return true;
}

bool MainWindow::DelteTrain(const Train &trainToDel) {
    auto it = trains.find(trainToDel);
    if (it == trains.end()) return false;
    if (it->sold) return false;
    trains.erase(it);
    return true;
}

bool MainWindow::StopTrainSale(const Train &trainToChange) {
    auto it = trains.find(trainToChange);
    if (it == trains.end()) return false;
    if (it->sold) return false;
    it->sale = false;
    return true;
}

bool MainWindow::StartTrainSale(const Train &trainToChange) {
    auto it = trains.find(trainToChange);
    if (it == trains.end()) return false;
    it->sale = true;
    return true;
}
/*
// Fake Reply
void AVeryGoodFunction() {
    std::stringstream ss;
    ii.resize(0);
    Bint mode;
    sstream >> mode;
    switch (mode) {
    case 1: //Register
        User userToReg;
        sstream >> userToReg;
        bool boolRet = RegisterUser(userToReg);
        ss << boolRet;
        break;
    case 2: //Login
        User userLogin, userReturn;
        userReturn = Login(userLogin);
        ss << userReturn;
        break;
    case 3: //Change Password
        User userToChg;
        sstream >> userToChg;
        bool boolRet = ChangePassWord(userToChg);
        ss << boolRet;
        break;
    case 4: //Query Own Tickets
        Bchar<17> id;
        sstream >> id;
        sjtu::vector<Ticket> ret = GetTicketByUserId(id);
        ss << ret;
        break;
    case 5: //Query Trains
        TicketQuery ticketToQue;
        sstream >> ticketToQue;
        sjtu::vector<Train> ret = QueryTicket(ticketToQue);
        ss << ret;
        break;
    case 6: //Buy Ticket
        Ticket ticketToBuy;
        sstream >> ticketToBuy;
        bool boolRet = BuyTicket(ticketToBuy);
        ss << boolRet;
        break;
    case 7: //Cancel Ticket
        Ticket ticketToCan;
        sstream >> ticketToCan;
        bool boolRet = CancelTicket(ticketToCan);
        ss << boolRet;
        break;
    case 8: //
    }
    ii.append(QByteArray(ss.str().c_str(),ss.str().length()));
}
*/
