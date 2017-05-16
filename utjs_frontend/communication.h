#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QtDebug>
#include <QtNetwork>
#include <QMessageBox>
#include <sstream>
#include "utjs_classes.hpp"

extern int communication_code;

class Communication : public QObject
{
    Q_OBJECT
public:
    QByteArray i, o;
    explicit Communication(int key,QObject *parent = 0);
    ~Communication();

signals:
    void finishDownload();
    void updateProgressBar(int value);

public slots:
    void communicate();
    void newConnect();
    void readMessage();
    void closeConnect();
    void sendData();
    void updateClientProgress(qint64 numBytes);
    void displayError(QAbstractSocket::SocketError socketError);

private:
    //all you need for communication
    std::stringstream oo;
    QTcpSocket *tcpClient;
    quint64 blockSize;
    QHostAddress hostAddress;
    qint16 tcpPort;
    int nwKey;
    int isValid;
    int sendPointer;
    qint64 totalBytes, bytesReceived,
           bytesToReceive, dataSize;

    qint64 bytesWritten,
           bytesToWrite, loadSize;
    QByteArray inBlock, outBlock;
    QTime time;
};

#endif // COMMUNICATION_H
