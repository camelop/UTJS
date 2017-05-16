#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <QRegExp>
#include <QtDebug>

bool check_id(QString &s){
    //qDebug() << s;
    QRegExp rx("[a-zA-Z0-9_]{1,16}");
    return rx.exactMatch(s);
}

bool check_name(QString &s){
    //qDebug() << s;
    QRegExp rx(".{1,16}");
    return rx.exactMatch(s);
}

bool check_train(QString &s){
    //qDebug() << s;
    QRegExp rx("[A-Z0-9//]{1,16}");
    return rx.exactMatch(s);
}

bool check_pswd(QString &s){
    //qDebug() << s;
    QRegExp rx("[a-zA-Z0-9!@#%&*_-=+]{6,20}");
    return rx.exactMatch(s);
}

#endif // FUNCTIONS_H
