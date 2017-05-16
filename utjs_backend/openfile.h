#ifndef OPENFILE_H
#define OPENFILE_H

#include <QObject>

class OpenFile : public QObject
{
    Q_OBJECT
public:
    explicit OpenFile(QObject *parent = 0);

signals:
    void myUpdatePB(int value);
public slots:
    void readTrains(){

    }
    void readOrders(){

    }
};

#endif // OPENFILE_H
