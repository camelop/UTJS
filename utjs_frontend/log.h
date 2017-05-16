#ifndef LOG_H
#define LOG_H

#include <QWidget>

namespace Ui {
    class Log;
}

class Log : public QWidget
{
    Q_OBJECT

public:
    explicit Log(QWidget *parent = 0);
    QString log;
    ~Log();

private slots:
    void on_BackButton_clicked();

    void receiveshow();

signals:
    void menu_admin_show();
private:
    Ui::Log *ui;
};

#endif // LOG_H
