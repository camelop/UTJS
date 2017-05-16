#include "communication.h"

Communication::Communication(int key, QObject *parent) :
    QObject(parent),
    tcpPort(10086),
    loadSize(1024),
    nwKey(key),
    hostAddress(QHostAddress("123.207.245.30"))
{
}

Communication::~Communication(){

}

void Communication::communicate(){
    nwKey=communication_code;
    tcpClient = new QTcpSocket();
    o.resize(0);
    dataSize=-1;
    isValid=0;
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpClient,SIGNAL(disconnected()),this,SLOT(closeConnect()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,
            SLOT(displayError(QAbstractSocket::SocketError)));
    qDebug()<<"Start a communication:";
    if (i.size()==0){
        qDebug()<<"Empty inBuffer!";
        return;
    }
    newConnect();
}
void Communication::newConnect(){
    totalBytes=0;
    bytesReceived=0;
    blockSize=0;
    tcpClient->abort();
    tcpClient->connectToHost(hostAddress,tcpPort);
    sendData();
    time.start();
}
void Communication::readMessage(){
    qDebug() << "readmessage begin";
    float useTime = time.elapsed();
    bytesReceived+=tcpClient->bytesAvailable();
    qDebug() << bytesReceived;
    if (dataSize==-1){
        QByteArray qtmp=tcpClient->read(sizeof(int));
        char tmpp[sizeof(int)];
        for (int j=0;j<sizeof(int);j++){
            tmpp[j]=(qtmp.data())[j];
        }
        dataSize=(int)(*(reinterpret_cast<int*>(tmpp)));
        qDebug()<<dataSize;
        bytesReceived-=sizeof(int);
    }
    qDebug() << "readmessage begin";
    inBlock = tcpClient->readAll();
    o.append(inBlock);
    inBlock.resize(0);
    qDebug() << "readmessage begin";
    int r=((float)bytesReceived/dataSize)*50+50;
    emit updateProgressBar(r);
    qDebug()<<tr("receive %1B(%2\%) useTime：%3").arg(bytesReceived)
                                                 .arg(r)
                                                 .arg((float)useTime/1000);
    if (bytesReceived==dataSize){
        qDebug()<<tr("Received.");
        qDebug()<<o;
        tcpClient->close();
        emit finishDownload();
    }

}


void Communication::closeConnect(){
    if (o.size()==0){
        QMessageBox::warning(NULL, "登录超时", "请重新登录！");
        exit(0);
    }
    qDebug()<<tr("Connection stopped");
    tcpClient->close();
}

void Communication::displayError(QAbstractSocket::SocketError socketError){
    switch(socketError){
        case QAbstractSocket::RemoteHostClosedError:
            qDebug()<<tcpClient->errorString();
            break;
    default: qDebug()<<tcpClient->errorString();
    }
}

void Communication::sendData(){
    bytesWritten=0;
    qDebug()<<tr("Send request");
    int* mysize= new int(i.size());

    QByteArray lasti; lasti.resize(0);
    for (int j=0;j<sizeof(int);j++)
        lasti.append(char( *((reinterpret_cast<char*>(mysize))+j) ));

    lasti.append(i);
    i=lasti;
    qDebug()<<i;
    delete mysize;

    mysize= new int(nwKey);
    qDebug()<<"using key: "<<nwKey;

    lasti.resize(0);
    for (int j=0;j<sizeof(int);j++)
        lasti.append(char( *((reinterpret_cast<char*>(mysize))+j) ));

    lasti.append(i);
    i=lasti;
    qDebug()<<i;
    delete mysize;


    connect(tcpClient,SIGNAL(bytesWritten(qint64)),SLOT(updateClientProgress(qint64)));
    qDebug()<<" Sending";
    bytesToWrite=totalBytes=i.size();
    for (qint64 j=bytesWritten;j<bytesWritten+qMin(bytesToWrite,loadSize);++j){
        outBlock.append(i[(int)j]);
    }
    bytesToWrite=totalBytes-tcpClient->write(outBlock);
    bytesWritten+=outBlock.size();

    qDebug()<<"sent:"<<bytesWritten<<" remain:"<<bytesToWrite<<" total:"<<totalBytes;
    int r=((float)bytesWritten/totalBytes)*50;
    emit updateProgressBar(r);
    outBlock.resize(0);
}

void Communication::updateClientProgress(qint64 numBytes){
    bytesWritten+=numBytes;
    if (bytesToWrite>0){
        outBlock.resize(0);
        for (qint64 j=bytesWritten;j<bytesWritten+qMin(bytesToWrite,loadSize);++j){
            outBlock.append(i[(int)j]);
        }
        bytesToWrite-=(int)tcpClient->write(outBlock);
        int r=((float)bytesWritten/totalBytes)*50;
        emit updateProgressBar(r);
        outBlock.resize(0);
        qDebug()<<"sent:"<<bytesWritten<<" remain:"<<bytesToWrite<<" total:"<<totalBytes;
    } else {
        totalBytes=0;
        bytesWritten=0;
        bytesToWrite=0;
        qDebug()<<"Sended.";
        o.resize(0);
        return;
    }
}

/*template<class T>
void Communication::appendd(T& x){
    std::stringstream ss;
    ss<<x;
    i.append(QByteArray(ss.str().c_str(),ss.str().length()));
}*/

