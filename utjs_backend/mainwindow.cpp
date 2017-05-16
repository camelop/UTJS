#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    state(0)
{
    //enum SeatType {None, TeDengZuo, YiDengZuo, ErDengZuo, YingZuo, RuanZuo, ShangWuZuo, WuZuo, YingWoXia, RuanWoXia, GaoJiRuanWo};
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
    //enum TrainType {C, K, T, D, G};
    toTrainType['C']=C;
    toTrainType['K']=K;
    toTrainType['T']=T;
    toTrainType['D']=D;
    toTrainType['G']=G;
    toTrainType['Z']=Z;
    ui->setupUi(this);
    connect(this,SIGNAL(finishDownload()),this,SLOT(reply()));
    validKeys[-2]=QDateTime::currentDateTime().addYears(1000);
    lastTime.setHMS(0,0,0);
    /*
     *
    sjtu::set<Train> trains;
    sjtu::set<User> users;
    sjtu::set<Ticket> tickets;
     */
    std::fstream fin;
    fin.open("data.bin",std::ios_base::binary|std::ios_base::in);
    if (fin.is_open()){
        fin>>trains;
        fin>>users;
        fin>>tickets;
        WriteLog("Server open: read from \"data.bin\" .");
        WriteLog("  found: train:"+QString::number(trains.size())+
                 "\n           users:"+QString::number(users.size())+"\n           tickets:"+QString::number(tickets.size()));
    } else
        WriteLog("Server open: \"data.bin\" not found.");
    fin.close();
}

MainWindow::~MainWindow()
{
    WriteLog("Server close: without saving.");
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (state==0){
        state=1;
        server = new QTcpServer();
        server->setMaxPendingConnections(1);
        server->listen(QHostAddress::Any, 10086);
        connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

        ui->frame->setStyleSheet("background: green");
        ui->pushButton->setText("Server started");
        WriteLog("Server started.");
    } else{
        state=0;

        server->close();
        delete server;

        ui->frame->setStyleSheet("background: red");
        ui->pushButton->setText("Server stopped");
        WriteLog("Server stopped.");
    }
}

void MainWindow::myUpdatePB(int rate){
    ui->progressBar->setValue(rate);
}



void MainWindow::acceptConnection()
{
    ii.clear();
    dataSize=-1;
    nwKey=-1;
    clientConnection = server->nextPendingConnection();
    ui->pushButton->setText(ui->pushButton->text().left(ui->pushButton->text().indexOf('\n'))+"\nfrom IP: "
                            +clientConnection->peerAddress().toString());
    WriteLog("connect -> "+clientConnection->peerAddress().toString());
    isLoggingIn=false;
//    clientConnection->setReadBufferSize(BLOCK_SIZE);
    connect(clientConnection,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(clientConnection,SIGNAL(disconnected()),this,SLOT(closeConnect()));
    connect(clientConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,
            SLOT(displayError(QAbstractSocket::SocketError)));
    totalBytes=0;
    bytesReceived=0;
    blockSize=0;
    time.start();
}

void MainWindow::readMessage(){
    float useTime = time.elapsed();
    bytesReceived+=clientConnection->bytesAvailable();
    isLoggingIn=false;
    if (nwKey==-1){
        QByteArray qtmp=clientConnection->read(sizeof(int));
        char tmpp[sizeof(int)];
        for (int j=0;j<sizeof(int);j++){
            tmpp[j]=(qtmp.data())[j];
        }
        nwKey=(int)(*(reinterpret_cast<int*>(tmpp)));

        if (nwKey==-2) isLoggingIn=true;
        if (validKeys.count(nwKey)==0){
            qDebug()<<"Key not found.";
            clientConnection->close();
            return;
        } else {
            if (validKeys[nwKey]<QDateTime::currentDateTime()){
                qDebug()<<validKeys[nwKey];
                qDebug()<<QDateTime::currentDateTime();
                qDebug()<<"Key too old.";
                validKeys.erase(validKeys.find(nwKey));
                clientConnection->close();
                return;
            }
        }
        bytesReceived-=sizeof(int);
    }
    if (dataSize==-1){
        QByteArray qtmp=clientConnection->read(sizeof(int));
        char tmpp[sizeof(int)];
        for (int j=0;j<sizeof(int);j++){
            tmpp[j]=(qtmp.data())[j];
        }
        dataSize=(int)(*(reinterpret_cast<int*>(tmpp)));
        bytesReceived-=sizeof(int);
    }
    inBlock = clientConnection->readAll();
    ii.append(inBlock);
    inBlock.resize(0);
    int r=((float)bytesReceived/dataSize)*50;
    emit myUpdatePB(r);
    qDebug()<<tr("receive %1B(%2\%) useTime：%3s").arg(bytesReceived)
                                                 .arg(r)
                                                 .arg((float)useTime/1000);
    if (bytesReceived==dataSize){
        qDebug()<<tr("Received.");
        qDebug()<<ii.size();
        emit finishDownload();
    }
    if (clientConnection->bytesAvailable()>0) readMessage();

}

void MainWindow::closeConnect(){
    qDebug()<<tr("Connection stopped");
    WriteLog("disconnected ->X");
    clientConnection->close();
}


void MainWindow::displayError(QAbstractSocket::SocketError socketError){
    switch(socketError){
        case QAbstractSocket::RemoteHostClosedError:
            qDebug()<<clientConnection->errorString();
            break;
    default: qDebug()<<clientConnection->errorString();
    }
}

int generateRandomNumber()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return ((qrand()%10007)*10007+420);

}

void MainWindow::reply(){
    qDebug()<<"Replying.";
    std::stringstream sstream;
    for (int i=0;i<ii.size();i++)
        sstream<<(ii.data())[i];

//reply begin
    std::stringstream ss;
    ii.resize(0);
    Bint mode;
    sstream >> mode;
    WriteLog("protocol ID: "+QString::number((int)mode));
    switch ((int)mode) {
    case 1: //Register{
    {
        if (!isLoggingIn){
            clientConnection->close();
            break;
        }
        User userToReg;
        sstream >> userToReg;
        bool boolRet = RegisterUser(userToReg);
        ss << boolRet;
        if (boolRet) WriteLog("RegisterUser " + QString::fromUtf8(userToReg.id));
        break;
    }
    case 2: //Login
    {
        if (!isLoggingIn){
            clientConnection->close();
            break;
        }
        User userLogin, userReturn;
        sstream >> userLogin;
        userReturn = Login(userLogin);
        if (strcmp(userReturn.hashSalt, "success") == 0) {
           int p=generateRandomNumber();
           validKeys[p]=QDateTime::currentDateTime().addSecs(600);
           Bint pp(p);
           qDebug()<<"key: "<<p;
           ss<< pp;
        } else {
           Bint p(-2);
           ss<< p;
        }
        ss << userReturn;
        if (strcmp(userReturn.hashSalt, "success") == 0)
            WriteLog("UserLogin " + QString::fromUtf8(userLogin.id));
        break;
    }
    case 3: //Change Password
    {
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        User userToChg;
        sstream >> userToChg;
        bool boolRet = ChangePassWord(userToChg);
        ss << boolRet;
        if (boolRet) WriteLog("UserChangePassword " + QString::fromUtf8(userToChg.id));
        break;
    }
    case 4: //Query Own Tickets
    {
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        Bchar<17> id;
        sstream >> id;
        sjtu::vector<Ticket> ret = GetTicketByUserId((char*)id);
        ss << ret;
        WriteLog("QueryUserTickets " + QString::fromUtf8((char*)id));
        break;
    }
    case 5: //Query Trains
    {
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        TicketQuery ticketToQue;
        sstream >> ticketToQue;
        sjtu::vector<Train> ret = QueryTicket(ticketToQue);
        ss << ret;
        for (auto i : ret)
            qDebug() << i.id;
        WriteLog("QueryTrain in " + ticketToQue.date.toQString() + \
                         " from " + QString::fromUtf8(ticketToQue.fromStationId) + \
                        " to " + QString::fromUtf8(ticketToQue.toStationId));
        break;
    }
    case 6: //Buy Ticket
    {
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        Ticket ticketToBuy;
        sstream >> ticketToBuy;
        bool boolRet = BuyTicket(ticketToBuy);
        ss << boolRet;
        if (boolRet) WriteLog("User " + QString::fromUtf8(ticketToBuy.userId) + \
                                      " buys " + QString::number(ticketToBuy.num) + " ticket(s) of " + \
                                      ticketToBuy.date.toQString() + " from " + \
                                      QString::fromUtf8(ticketToBuy.fromStationId) + " to " + \
                                        QString::fromUtf8(ticketToBuy.toStationId));
        break;
    }
    case 7: //Cancel Ticket
    {
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        Ticket ticketToCan;
        sstream >> ticketToCan;
        qDebug() << ticketToCan.userId;
        qDebug() << ticketToCan.date.toQString();
        qDebug() << ticketToCan.trainId;
        qDebug() << ticketToCan.fromStationId;
        qDebug() << ticketToCan.toStationId;
        qDebug() << ticketToCan.num;
        qDebug() << ticketToCan.index;
        bool boolRet = CancelTicket(ticketToCan);
        ss << boolRet;
        if (boolRet) WriteLog("User " + QString::fromUtf8(ticketToCan.userId) + \
                                      " cancels " + QString::number(ticketToCan.num) + " ticket(s) of " + \
                                      ticketToCan.date.toQString() + " from " + \
                                      QString::fromUtf8(ticketToCan.fromStationId) + " to " + \
                                    QString::fromUtf8(ticketToCan.toStationId));
        break;
    }
    case 8: {//Add Train
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        Train trainToAdd;
        sstream >> trainToAdd;
        for (int i = 0; i < trainToAdd.stationNumber; ++i)
            qDebug() << trainToAdd.stations[i].id;
        bool success=true;
        for (int cnt=28;cnt<32;cnt++) {
            trainToAdd.date=Date(2017,3,cnt);
            if (!AddTrain(trainToAdd)) {
                success=false;
                break;
            }
        }
        if (success) for (int cnt=1;cnt<28;cnt++) {
            trainToAdd.date=Date(2017,4,cnt);
            if (!AddTrain(trainToAdd)) {
                success=false;
                break;
            }
        }
        bool boolRet = success;
        ss << boolRet;
        if (boolRet) WriteLog("AddTrain " + QString::fromUtf8(trainToAdd.id) + " of " + \
                              trainToAdd.date.toQString());
        break;
    }
    case 9: {//Modify Train
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        Train trainToMod;
        sstream >> trainToMod;
        bool boolRet = ModifyTrain(trainToMod);
        ss << boolRet;
        if (boolRet) WriteLog("ModifyTrain " + QString::fromUtf8(trainToMod.id) + " of " + \
                              trainToMod.date.toQString());
        break;
    }
    case 10: {//Delete Train
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        Train trainToDel;
        sstream >> trainToDel;
        bool boolRet = DeleteTrain(trainToDel);
        ss << boolRet;
        if (boolRet) WriteLog("DeleteTrain " + QString::fromUtf8(trainToDel.id) + " of " + \
                              trainToDel.date.toQString());
        break;
    }
    case 11: {//Start Train Sale
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        Train trainToChg;
        sstream >> trainToChg;
        bool boolRet = StartTrainSale(trainToChg);
        ss << boolRet;
        if (boolRet) WriteLog("StartTrainSale " + QString::fromUtf8(trainToChg.id) + " of " + \
                              trainToChg.date.toQString());
        break;
    }
    case 12: {//Stop Train Sale
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        Train trainToChg;
        sstream >> trainToChg;
        bool boolRet = StopTrainSale(trainToChg);
        ss << boolRet;
        if (boolRet) WriteLog("StopTrainSale " + QString::fromUtf8(trainToChg.id) + " of " + \
                              trainToChg.date.toQString());
        break;
    }
    case 13: {//Get User Info
        if (isLoggingIn){
            clientConnection->close();
            break;
        }
        Bchar<17> userId;
        sstream >> userId;
        User userToQue;
        strcpy(userToQue.id, (char*)userId);
        auto it = users.find(userToQue);
        sjtu::vector<Ticket> vectorRet;
        if (it == users.end()) {
            strcpy(userToQue.hashSalt, "failed");
            ss << userToQue << vectorRet;
            break;
        }
        strcpy(userToQue.hashSalt, "success");
        strcpy(userToQue.name, it->name);
        vectorRet = GetTicketByUserId((char*)userId);
        ss << userToQue << vectorRet;
        WriteLog("GetUserInfo " + QString::fromUtf8((char*)userId));
        break;
    }
    }

    ii.append(QByteArray(ss.str().c_str(),ss.str().length()));
//reply end

    sendData();
}



void MainWindow::sendData(){
    bytesWritten=0;
    qDebug()<<tr("Send request");
    int* mysize= new int(ii.size());

    QByteArray lasti; lasti.resize(0);
    for (int j=0;j<sizeof(int);j++)
        lasti.append(char( *((reinterpret_cast<char*>(mysize))+j) ));

    lasti.append(ii);
    ii=lasti;
    //qDebug()<<ii;
    delete mysize;

    connect(clientConnection,SIGNAL(bytesWritten(qint64)),SLOT(updateClientProgress(qint64)));
    qDebug()<<" Sending";
    bytesToWrite=totalBytes=ii.size();
    for (qint64 j=bytesWritten;j<bytesWritten+qMin(bytesToWrite,loadSize);++j){
        outBlock.append(ii[(int)j]);
    }
    bytesToWrite=totalBytes-clientConnection->write(outBlock);
    bytesWritten+=outBlock.size();

    qDebug()<<"sent："<<bytesWritten<<" remain："<<bytesToWrite<<" total："<<totalBytes;
    int r=((float)bytesWritten/totalBytes)*50+50;
    myUpdatePB(r);
    outBlock.resize(0);
}

void MainWindow::updateClientProgress(qint64 numBytes){
    bytesWritten+=numBytes;;
    if (bytesToWrite>0){
        outBlock.resize(0);
        for (qint64 j=bytesWritten;j<bytesWritten+qMin(bytesToWrite,loadSize);++j){
            outBlock.append(ii[(int)j]);
        }
        bytesToWrite-=(int)clientConnection->write(outBlock);
        int r=((float)bytesWritten/totalBytes)*50;
        myUpdatePB(r);
        outBlock.resize(0);
        qDebug()<<"sent："<<bytesWritten<<" remain："<<bytesToWrite<<" total："<<totalBytes;
    } else {
        totalBytes=0;
        bytesWritten=0;
        bytesToWrite=0;
        qDebug()<<"Sended.";
    }
}

void strcpyFromQString(char* x, QString &ori){
    QByteArray temp=ori.toUtf8();
    strcpy(x,temp.data());
}

void MainWindow::on_actionRead_logs_triggered()
{
    std::fstream fout;
    fout.open("log.txt", std::ios_base::out|std::ios_base::trunc);

    lastTime=QTime::currentTime();
    fout << (QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss").toStdString()<<std::endl;

    fout<<"  "<< "logs been erased." << std::endl;
    fout.close();
}


void MainWindow::on_actionImport_trains_triggered()
{
    myUpdatePB(0);
    QString strSrcName = QFileDialog::getOpenFileName(this,
            tr("Import informations about trains"),tr("."),
            tr("Out files(*.out);;All files(*)"));
    qDebug()<<tr("Read from: ")<<strSrcName;
    WriteLog("Read trains from: "+strSrcName);
    QFile file(strSrcName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(NULL, "Sorry...", "Open failed!");
        return;
    }
    QTextStream qin(&file);
    qin.setCodec("UTF-8");
    QString line;
    sjtu::set<Train> tempTrains;
    tempTrains.clear();
    try{
        line = qin.readLine();
        while (!line.isNull()){
            if (line.size()<2) break;
            Train nw;
            strcpyFromQString(nw.id,line);
            nw.type=toTrainType[nw.id[0]];

            line = qin.readLine();
            QStringList parts = line.split(",");

            if(parts.size()>5) nw.seatType[0]=translate[parts[5]];
            else nw.seatType[0]=None;
            if(parts.size()>6) nw.seatType[1]=translate[parts[6]];
            else nw.seatType[1]=None;
            if(parts.size()>7) nw.seatType[2]=translate[parts[7]];
            else nw.seatType[2]=None;
            nw.sale=true; nw.sold=false;
            nw.stationNumber=0;
            nw.date=Date(2000,1,1);

            line = qin.readLine();
            while(!line.isNull()){
                QStringList parts = line.split(",");
                TrainStation nws;
                strcpyFromQString(nws.id,parts[0]);
                if (parts[2]==QString("起点站")){
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
                nws.distance=(parts[4].left(parts[4].length ()-2)).toShort(); //从右边截).toShort();
                nw.ticketNumber[0].push_back(2000);
                nw.ticketNumber[1].push_back(2000);
                nw.ticketNumber[2].push_back(2000);
                nw.stations.push_back(nws);

                line=qin.readLine();

                if (nws.type==LastStation) break;
            }
            //to be decided
            nw.stationNumber=nw.stations.size();
            //end to be
            if (tempTrains.count(nw)) {
                qDebug()<<"Train:"<<nw.id<<" has already appeared";
                WriteLog("NOTICE! Train:"+QByteArray(nw.id,strlen(nw.id))+" has already appeared.");
                //throw -1;
            } else
            tempTrains.insert(nw);
        }
        for (auto items: tempTrains){
            Train tp=items;
            for (int cnt=28;cnt<32;cnt++) {
                tp.date=Date(2017,3,cnt);
                if(!AddTrain(tp)) throw -1;
            }
            for (int cnt=1;cnt<28;cnt++) {
                tp.date=Date(2017,4,cnt);
                if(!AddTrain(tp)) throw -1;
            }
        }
    } catch(...){
        myUpdatePB(50);
        QMessageBox::warning(NULL, "Sorry...", "Wrong data format!");
        return;
    }
    myUpdatePB(100);
    QMessageBox::information(NULL, "Good news", "Import succeed.");
    return;
}

void MainWindow::on_actionExit_triggered()
{
    if (state==1){
        state=0;
        server->close();
        delete server;
    }

    std::fstream fout("data.bin");
    fout.open("data.bin",std::ios_base::out|std::ios_base::binary);
 //   std::ofstream ffout("data.txt");
    if (trains.size()!=0 || users.size()!=0 || tickets.size()!=0){
        fout<<trains;
        fout<<users;
        fout<<tickets;
        fout.flush();
        fout.close();
        WriteLog("Server close: changes saved.");
        QMessageBox::information(NULL, "Saving...", " finished");
    } else {
        fout.flush();
        fout.close();
        WriteLog("Server close: cannot save changes...");
        QMessageBox::information(NULL, "Something is empty..", "Save failed!");

    }
 //   fout.seekp(0,std::ios::beg);
/*    for (auto i:tickets){
        ffout<<i.userId<<' '<<i.trainId<<' '<<i.fromStationId<<' '<<i.toStationId<<'\n';
    }
    ffout<<"END\n";*/

    //ffout.flush();
    //fout<<"END";


    exit(0);
}

void MainWindow::on_actionImport_changes_triggered()
{
    myUpdatePB(0);
    QString strSrcName = QFileDialog::getOpenFileName(this,
            tr("Import informations about orders"),tr("."),
            tr("Out files(*.out);;All files(*)"));
    qDebug()<<tr("Read from: ")<<strSrcName;
    WriteLog("Read orders from: "+strSrcName);
    QFile file(strSrcName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(NULL, "Sorry...", "Open failed!");
        return;
    }
    QTextStream qin(&file);
    qin.setCodec("UTF-8");
    QString line;
    try{
        int cnt=0;
        int w=0;
        line = qin.readLine();
        while (!line.isNull()){
            ++cnt;
            if (cnt>10999){
                cnt=0;
                w++;
                qDebug()<<w;
            }
            Ticket nw;
            if (line.size()<2) break;
            QStringList parts = line.split(" ");
            if (parts[2]=="bought"){
                User nwu(parts[0],parts[1]);

                if (!users.count(nwu)){
                    RegisterUser(nwu);
                }
                strcpyFromQString(nw.userId,parts[1]);
                strcpyFromQString(nw.trainId,parts[7]);
                strcpyFromQString(nw.fromStationId,parts[9]);
                strcpyFromQString(nw.toStationId,parts[11]);
                nw.date=Date(parts[13]);
                nw.num=parts[3].toInt();

                nw.seatType=translate[parts[4]];
                BuyTicket(nw);
            }
            if (parts[2]=="refunded"){
                User nwu(parts[0],parts[1]);
                if (!users.count(nwu)){
                    RegisterUser(nwu);
                }
                strcpyFromQString(nw.userId,parts[1]);
                strcpyFromQString(nw.trainId,parts[7]);
                strcpyFromQString(nw.fromStationId,parts[9]);
                strcpyFromQString(nw.toStationId,parts[11]);
                nw.date=Date(parts[13]);
                nw.num=parts[3].toInt();
                nw.seatType=translate[parts[4]];
                CancelTicket2(nw);
            }
            line = qin.readLine();
        }
    } catch(sjtu::exception e){
        qDebug()<<e.what().c_str();
        myUpdatePB(50);
        QMessageBox::warning(NULL, "Sorry...", "Invalid train reference or Wrong data format!");
        return;
    }
    myUpdatePB(100);
    QMessageBox::information(NULL, "Good news", "Import succeed.");
    return;
}

void MainWindow::on_actionErase_cache_triggered()
{
    trains.clear();
    users.clear();
    tickets.clear();
    QMessageBox::information(NULL, "Cleaned!", "Use exit to erase the file.");
    return;
}


void MainWindow::on_pushButton_2_clicked()
{
    QFile file("log.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(NULL, "Sorry...", "Open failed!");
        return;
    }
    QTextStream qin(&file);
    qin.setCodec("UTF-8");
    QString line;
    line=qin.readLine();
    QString y;
    while (!line.isNull()){
        y=y+line;
        y=y+'\n';
        line=qin.readLine();
    }
    if (y=="") y="Nothing yet~";
    ui->textBrowser->setText(y);
}












//FZ: from here



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

QByteArray HashPassWord(const char *passWord, const char *hashSalt) {
    QCryptographicHash hash(QCryptographicHash::Sha256);
    QByteArray byteArray;
    byteArray.append(hashSalt);
    byteArray.append(passWord);
    hash.addData(byteArray);
    QByteArray resultByteArray = hash.result();
    QString resultQString = resultByteArray.toHex();
    QByteArray trByteArray = resultQString.toLatin1();
    return trByteArray;
}

bool MainWindow::RegisterUser(const User &userToReg) {
    User newUser(userToReg);
    if (users.count(newUser) != 0) return false;
    char newHashSalt[65];
    GenerateHashSalt(newHashSalt);
    strcpy(newUser.hashSalt, newHashSalt);
    strcpy(newUser.passWord, HashPassWord(userToReg.passWord, newUser.hashSalt).data());
    users.insert(newUser);
    return true;
}

//return "failed" or "success" in loginUser.hashSalt
User MainWindow::Login(const User &userLogin) {
    User loginUser(userLogin);
    strcpy(loginUser.hashSalt, "failed");
    if (users.count(loginUser) == 0) return loginUser;
    auto it = users.find(loginUser);
    qDebug()<<it->name;
    strcpy(loginUser.passWord, HashPassWord(loginUser.passWord, it->hashSalt).data());
    if (strcmp(loginUser.passWord, it->passWord) != 0) {
        strcpy(loginUser.passWord, "Maythe4th");
        return loginUser;
    }
    strcpy(loginUser.passWord, "Maythe4th");
    strcpy(loginUser.name, it->name);
    strcpy(loginUser.hashSalt, "success");
    return loginUser;
}

//frontend send new password in userToChg.hashSalt
bool MainWindow::ChangePassWord(const User &userToChg) {
    User updateUser(userToChg);
    if (users.count(updateUser) == 0) return false;
    sjtu::set<User>::iterator it = users.find(updateUser);
    strcpy(updateUser.passWord, HashPassWord(userToChg.passWord, it->hashSalt).data());
    if (strcmp(updateUser.passWord, it->passWord) != 0) return false;
    char newHashSalt[65];
    GenerateHashSalt(newHashSalt);
    strcpy(it->hashSalt, newHashSalt);
    strcpy(it->passWord, HashPassWord(userToChg.hashSalt, it->hashSalt).data());
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
    if (it == tickets.end()) {
        qDebug() << "cannot find ticketToCan!";
        return false;
    }
    if (it->canceled) {
        qDebug() << "ticketToCan has already been canceled!";
        return false;
    }
    it->canceled = true;
    Train trainToCan;
    trainToCan.date = ticketToCan.date;
    strcpy(trainToCan.id, ticketToCan.trainId);
    auto trainIt = trains.find(trainToCan);
    if (trainIt == trains.end()) {
        qDebug() << "cannot find trainToCan!";
        return false;
    }
    Ticket ticketToCan2(ticketToCan);
    ticketToCan2.num = -(ticketToCan.num);
    trainIt->buy(ticketToCan2);

    qDebug() << "cancel ticket successfully!";
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
        if (it->date != trainToQue.date) break;
        if (!ticketToQue.trainType[(*it).type]) continue;
        if (!(it->sale)) continue;
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

bool MainWindow::DeleteTrain(const Train &trainToDel) {
    auto it = trains.find(trainToDel);
    if (it == trains.end()) return false;
    if (it->sold) return false;
    trains.erase(it);
    //erase all tickets about this train
    //to be done
    return true;
}

bool MainWindow::StopTrainSale(const Train &trainToChange) {
    auto it = trains.find(trainToChange);
    if (it == trains.end()) {
        qDebug() << "Cannot find trainToChange.";
        return false;
    }
    if (it->sold) {
        qDebug() << "The train has already been sold.";
        return false;
    }
    it->sale = false;
    return true;
}

bool MainWindow::StartTrainSale(const Train &trainToChange) {
    auto it = trains.find(trainToChange);
    if (it == trains.end()) return false;
    it->sale = true;
    return true;
}

bool MainWindow::ModifyTrain(const Train &trainToMod) {
    Train newTrain(trainToMod);
    auto it = trains.find(newTrain);
    if (it == trains.end()) return false;
    if (it->sold) return false;
    trains.erase(it);
    newTrain.sold = false;
    newTrain.sale = true;
    trains.insert(newTrain);
    return true;
}



void MainWindow::WriteLog(QString newLog) {
    std::ofstream fout;
    fout.open("log.txt", std::ios::app);
    if (lastTime.addSecs(5)<QTime::currentTime()) {
        lastTime=QTime::currentTime();
        fout << (QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss").toStdString()<<std::endl;
    }
    fout<<"  "<< newLog.toStdString() << std::endl;
    fout.close();
}


