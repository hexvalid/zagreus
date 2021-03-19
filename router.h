#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QProcess>
#include <QMutex>


class Router : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ConnectionStatus getStatus READ getStatus WRITE setStatus NOTIFY statusChanged)


public:
    explicit Router(QObject *parent = 0);
    void setTunNumber(const qint8 tunNumber){
        m_tunNumber = tunNumber;
    }

    Q_INVOKABLE void connect();
    Q_INVOKABLE void reconnect();
    Q_INVOKABLE void disconnect();

    enum ConnectionStatus
    {
        NOT_RUNNING = 0,
        STARTED = 1,
        CONNECTING_0 =2 ,
        CONNECTING_1 =3 ,
        CONNECTING_2 = 4,
        CONNECTING_3=5,
        CONNECTING_4=6,
        CONNECTING_5=7,
        CONNECTED=8,
        RECONNECTING=9,
        DISCONNECTING=10,
        ERROR=11,
    };
    Q_ENUMS(ConnectionStatus)




    ConnectionStatus getStatus() const
    {
        return m_status;
    }

    void setStatus(const ConnectionStatus &a)
    {
        if (a != m_status) {
            m_status = a;
            emit statusChanged();
        }
    }

signals:
    void statusChanged();
private:
    qint8 m_tunNumber;
    QProcess *process;
    ConnectionStatus m_status;
    bool m_reconnect;

private slots:
    void listenProcessStarted();
    void listenProcessReadyRead();
    void listenProcessFinished(int exitCode);

};


#endif // ROUTER_H
