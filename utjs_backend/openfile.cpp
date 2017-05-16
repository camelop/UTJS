#include "openfile.h"

OpenFile::OpenFile(QObject *parent) : QObject(parent)
{

}

OpenFile::readOrders(){
    myUpdatePB(0);
    QString strSrcName = QFileDialog::getOpenFileName(this,
            tr("Import informations about orders"),tr("."),
            tr("Out files(*.out);;All files(*)"));
    qDebug()<<tr("Read from: ")<<strSrcName;
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
            if (cnt>11111){
                cnt=0;
                w++;
                myUpdatePB(w);
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

OpenFile::readTrains(){
    myUpdatePB(0);
    QString strSrcName = QFileDialog::getOpenFileName(this,
            tr("Import informations about trains"),tr("."),
            tr("Out files(*.out);;All files(*)"));
    qDebug()<<tr("Read from: ")<<strSrcName;
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
            if(parts.size()>6) nw.seatType[1]=translate[parts[6]];
            if(parts.size()>7) nw.seatType[2]=translate[parts[7]];
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
                if(parts.size()>5) nws.price[0]=(parts[5].right(parts[5].length ()-2)).toFloat();
                if(parts.size()>6) nws.price[1]=(parts[6].right(parts[6].length ()-2)).toFloat();
                if(parts.size()>7) nws.price[2]=(parts[7].right(parts[7].length ()-2)).toFloat();
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
