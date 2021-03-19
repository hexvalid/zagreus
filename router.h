#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QProcess>
#include <QMutex>
#include <QNetworkReply>


class Router : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double conProgress READ conProgress WRITE setConProgress NOTIFY conProgressChanged)
    Q_PROPERTY(qint64 pid READ pid NOTIFY pidChanged)
    Q_PROPERTY(bool processIsRunning READ processIsRunning NOTIFY processIsRunningChanged)
    Q_PROPERTY(qint32 peer READ peer NOTIFY pushReplyParsed)
    Q_PROPERTY(QString gateway READ gateway NOTIFY pushReplyParsed)
    Q_PROPERTY(QString local READ local NOTIFY pushReplyParsed)
    Q_PROPERTY(QString remote READ remote NOTIFY remoteChanged)
    Q_PROPERTY(bool netActing READ netActing WRITE setNetActing NOTIFY netActingChanged)

    Q_PROPERTY(ConnectionStatus getStatus READ getStatus WRITE setStatus NOTIFY statusChanged)


public:
    explicit Router(QObject *parent = 0);

    void setTunNumber(const qint8 tunNumber){
        m_tunNumber = tunNumber;
    }

    Q_INVOKABLE void connect();
    Q_INVOKABLE void reconnect();
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void checkIP();

    enum ConnectionStatus
    {
        IDLE = 0,
        CONNECTING =1 ,
        DISCONNECTING=2,
        RECONNECTING=3,
        ERROR=4,
        CONNECTED=10,
    };
    Q_ENUMS(ConnectionStatus)


    void setConProgress(const double &a)
    {
        if (a != m_conProgress) {
            m_conProgress = a;
            emit conProgressChanged();
        }
    }

    qint64 pid() const
    {
        return process->processId();
    }

    bool processIsRunning() const
    {
        return process->state()==process->Running;
    }

    qint32 peer() const{
        return m_peer;
    }

    QString gateway() const{
        return m_gateway;
    }

    QString local() const{
        return m_local;
    }

    QString remote() const
    {
        return m_remote;
    }

    bool netActing() const
    {
        return m_netActing;
    }

    void setNetActing(const double &a)
    {
        if (a != m_netActing) {
            m_netActing = a;
            emit netActing();
        }
    }

    ConnectionStatus getStatus() const
    {
        return m_status;
    }

    double conProgress() const
    {
        return m_conProgress;
    }


    void setStatus(const ConnectionStatus &a)
    {
        if (a != m_status) {
            m_status = a;
            emit statusChanged();
        }
    }



signals:
    void conProgressChanged();
    void pidChanged();
    void processIsRunningChanged();
    void pushReplyParsed();
    void remoteChanged();
    void statusChanged();
    void netActingChanged();

private:
    double m_conProgress;
    qint8 m_tunNumber;
    qint32 m_peer;
    QString m_gateway;
    QString m_local;
    QString m_remote;
    bool m_netActing;
    QProcess *process;
    ConnectionStatus m_status;
    bool m_reconnect;
    void parsePushReply(QString line);

public slots:


private slots:
    void listenProcessStarted();
    void listenProcessReadyRead();
    void listenProcessFinished(int exitCode);

};


#endif // ROUTER_H
