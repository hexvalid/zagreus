#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QProcess>

class router : public QObject
{
    Q_OBJECT
private:
    QProcess *process;
public slots:
    void listenReadyRead();
    void    started();
public:
    explicit router(QObject *parent = 0);
    void connect();
};

#endif // ROUTER_H
