#ifndef UTJS_CLASSES_HPP
#define UTJS_CLASSES_HPP

#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "utjs_stl.hpp"
#include "basic_binary_class.hpp"

const int INF = 999999999;

template<class T>
T min(T a, T b) {
    return a < b ? a : b;
}
template<class T>
T max(T a, T b) {
    return a > b ? a : b;
}

class User {
public:
    char id[17];
    char passWord[65], hashSalt[65];
    char name[33]; // Chinese string

    User() = default;
    User(QString &_name, QString &_id){
        QByteArray temp = _name.toUtf8();
        strcpy(name, temp.data());
        temp = _id.toLatin1();
        strcpy(id, temp.data());
        strcpy(passWord,"000000");
    }

    User(const User& rhs){
        strcpy(id,rhs.id);
        strcpy(passWord,rhs.passWord);
        strcpy(hashSalt,rhs.hashSalt);
        strcpy(name,rhs.name);
    }

    User& operator =(const User& rhs){
        if (this==&rhs) return *this;
        strcpy(id,rhs.id);
        strcpy(passWord,rhs.passWord);
        strcpy(hashSalt,rhs.hashSalt);
        strcpy(name,rhs.name);
        return *this;
    }

    bool operator <(const User &other) const {
        return strcmp(id, other.id) < 0;
    }
    friend std::istream& operator >>(std::istream &fin, User &x) {
        fin.read(reinterpret_cast<char*>(&x), sizeof(User));
        return fin;
    }
    friend std::ostream& operator <<(std::ostream &fout, const User &x) {
        fout.write(reinterpret_cast<const char*>(&x), sizeof(User));
        return fout;
    }
};

const int maxTrainType = 6;
enum TrainType {C, K, T, D, G, Z};
const int maxSeatType = 11;
enum SeatType {None, TeDengZuo, YiDengZuo, ErDengZuo, YingZuo, RuanZuo, ShangWuZuo, WuZuo, YingWoXia, RuanWoXia, GaoJiRuanWo}; // to be developed, constant maxSeatType

class Time {
public:
    unsigned short hour, minute;
    Time() {}
    Time(QString &x){
        hour = (x[0].toLatin1() - '0') * 10 + (x[1].toLatin1() - '0');
        minute = (x[3].toLatin1() - '0') * 10 + (x[4].toLatin1() - '0');
    }
    QString toQString() {
        QString ret;
        ret = QString("%1").arg(hour, 2, 10, QChar('0')) + ":" + \
              QString("%1").arg(minute, 2, 10, QChar('0'));
        return ret;
    }
};

enum TrainStationType {FirstStation, MiddleStation, LastStation};

class TrainStation {
public:
    char id[21]; // Chinese string
    TrainStationType type;
    float price[3];
    Time arriveTime, departureTime;
    unsigned short distance;

    TrainStation()=default;

    TrainStation(const TrainStation& rhs){
        strcpy(id,rhs.id);
        type=rhs.type;
        price[0]=rhs.price[0];
        price[1]=rhs.price[1];
        price[2]=rhs.price[2];
        arriveTime=rhs.arriveTime;
        departureTime=rhs.departureTime;
        distance=rhs.distance;
    }

    TrainStation& operator=(const TrainStation& rhs){
        if (this==&rhs) return *this;
        strcpy(id,rhs.id);
        type=rhs.type;
        price[0]=rhs.price[0];
        price[1]=rhs.price[1];
        price[2]=rhs.price[2];
        arriveTime=rhs.arriveTime;
        departureTime=rhs.departureTime;
        distance=rhs.distance;
        return *this;
    }

    friend std::istream& operator >>(std::istream &fin, TrainStation &x) {
        fin.read(reinterpret_cast<char*>(&x), sizeof(TrainStation));
        return fin;
    }
    friend std::ostream& operator <<(std::ostream &fout, const TrainStation &x) {
        fout.write(reinterpret_cast<const char*>(&x), sizeof(TrainStation));
        return fout;
    }
};

class Date {
public:
    unsigned short year, month, day;

    Date() = default;
    Date(unsigned short y, unsigned short m, unsigned short d):
        year(y), month(m), day(d) {}
    Date(QString &x){
        QStringList parts = x.split("-");
        year = parts[0].toShort();
        month = parts[1].toShort();
        day = parts[2].toShort();
    }
    QString toQString() {
        QString ret;
        ret = QString("%1").arg(year, 4, 10, QChar('0')) + "-" + \
              QString("%1").arg(month, 2, 10, QChar('0')) + "-" + \
              QString("%1").arg(day, 2, 10, QChar('0'));
        return ret;
    }
    bool operator <(const Date &other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    bool operator ==(const Date &other) const {
        return (year == other.year) && (month == other.month) && (day == other.day);
    }
    bool operator !=(const Date &other) const {
        return !(operator ==(other));
    }
};

class Ticket {
public:
    char userId[17];
    char trainId[13];
    char fromStationId[21], toStationId[21]; // Chinese string
    Date date;
    int index;
    float price;
    int num;
    bool canceled;
    SeatType seatType;

    Ticket() = default;
    Ticket(const Ticket& rhs){
        strcpy(userId,rhs.userId);
        strcpy(trainId,rhs.trainId);
        strcpy(fromStationId,rhs.fromStationId);
        strcpy(toStationId,rhs.toStationId);
        date=rhs.date;
        index=rhs.index;
        price=rhs.price;
        num=rhs.num;
        canceled=rhs.canceled;
        seatType=rhs.seatType;
    }

    Ticket& operator =(const Ticket& rhs){
        if (this==&rhs) return *this;
        strcpy(userId,rhs.userId);
        strcpy(trainId,rhs.trainId);
        strcpy(fromStationId,rhs.fromStationId);
        strcpy(toStationId,rhs.toStationId);
        date=rhs.date;
        index=rhs.index;
        price=rhs.price;
        num=rhs.num;
        canceled=rhs.canceled;
        seatType=rhs.seatType;
        return *this;
    }

    bool operator <(const Ticket &other) const {
        if (strcmp(userId, other.userId) != 0) return strcmp(userId, other.userId) < 0;
        if (date != other.date) return date < other.date;
        if (strcmp(trainId, other.trainId) != 0) return strcmp(trainId, other.trainId) < 0;
        if (strcmp(fromStationId, other.fromStationId) != 0) return strcmp(fromStationId, other.fromStationId) < 0;
        if (strcmp(toStationId, other.toStationId) != 0) return strcmp(toStationId, other.toStationId) < 0;
        if (num != other.num) return num < other.num;
        return index > other.index;
    }
    bool same(const Ticket &other) const {
        return (strcmp(userId, other.userId) == 0 && \
                date == other.date && \
                strcmp(trainId, other.trainId) == 0 && \
                strcmp(fromStationId, other.fromStationId) == 0 && \
                strcmp(toStationId, other.toStationId) == 0);
    }
    bool operator ==(const Ticket &other) const {
        return (strcmp(userId, other.userId) == 0 && \
                date == other.date && \
                strcmp(trainId, other.trainId) == 0 && \
                strcmp(fromStationId, other.fromStationId) == 0 && \
                strcmp(toStationId, other.toStationId) == 0 && \
                index == other.index);
    }
    bool operator !=(const Ticket &other) const {
        return !(operator ==(other));
    }

    friend std::istream& operator >>(std::istream &fin, Ticket &x) {
        fin.read(reinterpret_cast<char*>(&x), sizeof(Ticket));
        return fin;
    }
    friend std::ostream& operator <<(std::ostream &fout, const Ticket &x) {
        fout.write(reinterpret_cast<const char*>(&x), sizeof(Ticket));
        return fout;
    }
};

class Train {
public:
    char id[13];
    TrainType type;
    SeatType seatType[3];
    Date date;
    bool sale, sold;
    unsigned short stationNumber;
    sjtu::vector<Bint> ticketNumber[3];
    sjtu::vector<TrainStation> stations;

    Train() = default;
    Train(const Train& rhs){
        strcpy(id,rhs.id);
        type=rhs.type;
        seatType[0]=rhs.seatType[0];
        seatType[1]=rhs.seatType[1];
        seatType[2]=rhs.seatType[2];
        date=rhs.date;
        sale=rhs.sale;
        sold=rhs.sold;
        stationNumber=rhs.stationNumber;
        ticketNumber[0]=rhs.ticketNumber[0];
        ticketNumber[1]=rhs.ticketNumber[1];
        ticketNumber[2]=rhs.ticketNumber[2];
        stations=rhs.stations;
    }

    Train& operator=(const Train& rhs){
        if (&rhs==this) return *this;
        strcpy(id,rhs.id);
        type=rhs.type;
        seatType[0]=rhs.seatType[0];
        seatType[1]=rhs.seatType[1];
        seatType[2]=rhs.seatType[2];
        date=rhs.date;
        sale=rhs.sale;
        sold=rhs.sold;
        stationNumber=rhs.stationNumber;
        ticketNumber[0]=rhs.ticketNumber[0];
        ticketNumber[1]=rhs.ticketNumber[1];
        ticketNumber[2]=rhs.ticketNumber[2];
        stations=rhs.stations;
        return *this;
    }

    bool link(const char *fromId, const char *toId) {
        bool getFrom = false, getTo = false;
        for (auto s : stations) {
            if (!getFrom && strcmp(s.id, fromId) == 0) getFrom = true;
            else if (getFrom && strcmp(s.id, toId) == 0) getTo = true;
        }
        return getTo;
    }
    Train trans(const char *fromId, const char *toId) {
        Train ret;
        for (int i = 0; i < 3; ++i)
            ret.seatType[i] = seatType[i];
        strcpy(ret.id, id);
        ret.date = date;
        ret.stationNumber = 2;
        int num[3];
        if (!sale) {
            for (int i = 0; i < 3; ++i)
                num[i] = 0;
        }
        else {
            for (int i = 0; i < 3; ++i)
                num[i] = INF;
            bool get = false;
            for (int i = 0; i < stationNumber; ++i) {
                if (strcmp(stations[i].id, fromId) == 0) {
                    ret.stations.push_back(stations[i]);
                    get = true;
                 continue;
                }
                if (!get) continue;
                for (int j = 0; j < 3; ++j)
                    num[j] = min(num[j], (int)ticketNumber[j][i]);
                if (get && strcmp(stations[i].id, toId) == 0) {
                    ret.stations.push_back(stations[i]);
                    break;
                }
            }
        }
        for (int i = 0; i < 3; ++i)
            ret.ticketNumber[i].push_back(num[i]);
        return ret;
    }
    Ticket buy(const Ticket &ticketToBuy) {
        Ticket ret(ticketToBuy);
        char fromId[21], toId[21];
        strcpy(fromId, ticketToBuy.fromStationId);
        strcpy(toId, ticketToBuy.toStationId);
        ret.num = 0;
        int k = -1;
        if (!sale) return ret;
        for (int i = 0; i < 3; ++i) {
            if (seatType[i] == ticketToBuy.seatType) {
                k = i;
                break;
            }
        }
        if (k == -1) return ret;
        if (ticketToBuy.num < 0) {
            bool get = false;
            for (int i = 0; i < stationNumber; ++i) {
                if (strcmp(stations[i].id, fromId) == 0) {
                    get = true;
                    continue;
                }
                if (!get) continue;
                ticketNumber[k][i] = (int)ticketNumber[k][i] -(ticketToBuy.num);
                if (get && strcmp(stations[i].id, toId) == 0) break;
            }
            ret.num = ticketToBuy.num;
        }
        else {
            int num = INF;
            bool get = false;
            for (int i = 0; i < stationNumber; ++i) {
                if (strcmp(stations[i].id, fromId) == 0) {
                    get = true;
                    continue;
                }
                if (!get) continue;
                num = min(num, (int)ticketNumber[k][i]);
                if (get && strcmp(stations[i].id, toId) == 0) break;
            }
            if (num < ticketToBuy.num) return ret;
            get = false;
            float price1, price2;
            for (int i = 0; i < stationNumber; ++i) {
                if (strcmp(stations[i].id, fromId) == 0) {
                    get = true;
                    price1 = stations[i].price[k];
                    continue;
                }
                if (!get) continue;
                ticketNumber[k][i] =(int)ticketNumber[k][i] - ticketToBuy.num;
                if (get && strcmp(stations[i].id, toId) == 0) {
                    price2 = stations[i].price[k];
                    break;
                }
            }
            ret.num = ticketToBuy.num;
            ret.price = (price2 - price1) * ret.num;
        }
        sold = true;
        ret.canceled = false;
        return ret;
    }

    bool operator <(const Train &other) const {
        if (date != other.date) return date < other.date;
        return strcmp(id, other.id) < 0;
    }
    friend std::istream& operator >>(std::istream &fin, Train &x) {
        fin.read(reinterpret_cast<char*>(x.id), sizeof(x.id));
        fin.read(reinterpret_cast<char*>(&(x.type)), sizeof(x.type));
        fin.read(reinterpret_cast<char*>(&(x.seatType)), sizeof(x.seatType));
        fin.read(reinterpret_cast<char*>(&(x.date)), sizeof(x.date));
        fin.read(reinterpret_cast<char*>(&(x.sale)), sizeof(x.sale));
        fin.read(reinterpret_cast<char*>(&(x.sold)), sizeof(x.sold));
        fin.read(reinterpret_cast<char*>(&(x.stationNumber)), sizeof(x.stationNumber));
        for (int i = 0; i < 3; ++i)
            fin >> x.ticketNumber[i];
        fin >> x.stations;
        return fin;
    }
    friend std::ostream& operator <<(std::ostream &fout, const Train &x) {
        fout.write(reinterpret_cast<const char*>(x.id), sizeof(x.id));
        fout.write(reinterpret_cast<const char*>(&(x.type)), sizeof(x.type));
        fout.write(reinterpret_cast<const char*>(&(x.seatType)), sizeof(x.seatType));
        fout.write(reinterpret_cast<const char*>(&(x.date)), sizeof(x.date));
        fout.write(reinterpret_cast<const char*>(&(x.sale)), sizeof(x.sale));
        fout.write(reinterpret_cast<const char*>(&(x.sold)), sizeof(x.sold));
        fout.write(reinterpret_cast<const char*>(&(x.stationNumber)), sizeof(x.stationNumber));
        for (int i = 0; i < 3; ++i)
            fout << x.ticketNumber[i];
        fout << x.stations;
        return fout;
    }
};

class TicketQuery {
public:
    char trainId[13];
    char fromStationId[21], toStationId[21]; // Chinese string
    Date date;
    bool trainType[maxTrainType];

    TicketQuery()=default;
    TicketQuery(const TicketQuery& rhs){
        strcpy(trainId,rhs.trainId);
        strcpy(fromStationId,rhs.fromStationId);
        strcpy(toStationId,rhs.toStationId);
        date=rhs.date;
        for (int i=0;i<maxTrainType;i++)
            trainType[i]=rhs.trainType[i];
    }
    TicketQuery& operator=(const TicketQuery& rhs){
        if (this==&rhs) return *this;
        strcpy(trainId,rhs.trainId);
        strcpy(fromStationId,rhs.fromStationId);
        strcpy(toStationId,rhs.toStationId);
        date=rhs.date;
        for (int i=0;i<maxTrainType;i++)
            trainType[i]=rhs.trainType[i];
        return *this;
    }

    friend std::istream& operator >>(std::istream &fin, TicketQuery &x) {
        fin.read(reinterpret_cast<char*>(&x), sizeof(TicketQuery));
        return fin;
    }
    friend std::ostream& operator <<(std::ostream &fout, const TicketQuery &x) {
        fout.write(reinterpret_cast<const char*>(&x), sizeof(TicketQuery));
        return fout;
    }
};

#endif
