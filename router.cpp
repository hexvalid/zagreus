#include "router.h"
#include "QDebug"
#include "QObject"

#include <csignal>

// https://gist.github.com/ynonp/8148340

Router::Router(QObject *parent) : QObject(parent)
{
    this->setStatus(ConnectionStatus::NOT_RUNNING);
    this->process = new QProcess;
    QObject::connect(process, SIGNAL(started()), this,SLOT(listenProcessStarted()));
    QObject::connect(process, SIGNAL(readyRead()),this, SLOT(listenProcessReadyRead()));
    QObject::connect(process, SIGNAL(finished(int)), this, SLOT(listenProcessFinished(int)));
}


void Router::connect()
{
    if (m_reconnect){
        this->m_reconnect=false;
    }

    this->setStatus(ConnectionStatus::CONNECTING_0);

    qDebug() << "connecting";

    QString binPath = "zagra";
    QStringList args;

    args << "--client" << "--nobind" << "--block-ipv6" << "--persist-key" << "--persist-tun"
         << "--fast-io" << "--comp-lzo"
         << "--dev-type" << "tun"
         << "--dev" << QString().asprintf("tun%d",this->m_tunNumber)
         << "--route-metric" << "1"
         << "--route-delay" << "0"
         << "--sndbuf" << "196608"
         << "--rcvbuf" << "196608"
         << "--remote-cert-tls" << "server"
         << "--cipher" << "AES-256-GCM"
         << "--ping" << "9"
         << "--ping-restart" << "30"
         << "--socks-proxy" << "139.59.176.105" << "25565" << "auth-socks.txt"
         << "--auth-user-pass" << "auth.txt"
         << "--pull-filter" << "ignore" << "ifconfig-ipv6"
         << "--pull-filter" << "ignore" << "route-ipv6"
         << "--pull-filter" << "ignore" << "redirect-gateway"
         << "--pull-filter" << "ignore" << "dhcp-option DNS"
         << "--pull-filter" << "ignore" << "ping"
         << "--proto" << "udp4"
         << "--remote" << "fr.hma.rocks" << "766"
         << "--ca" << "ca.txt"
         << "--cert" << "cert.txt"
         << "--key" << "key.txt"
          <<"--connect-retry"<<"0"
         << "--verb" << "3";



    //connect(process, &QProcess::start, this, SLOT(listenProcessStatus);

    process->setWorkingDirectory("/home/user/QtProjects/zagreus/stub");


    process->setProgram(binPath);

    process->setArguments(args);

    process->start();

}

void Router::reconnect(){
    disconnect();

    this->m_reconnect=true;


}

void Router::disconnect(){
    if (this->m_status!=ConnectionStatus::NOT_RUNNING){
        kill(process->processId(), SIGINT);
    }
}


void Router::listenProcessReadyRead()
{
    while(process->canReadLine()){
        QString line =  process->readLine();
        if (line.contains("process restarting")){
            this->setStatus(ConnectionStatus::CONNECTING_0);
        }
        else if (line.contains("Attempting to establish TCP connection")){
            this->setStatus(ConnectionStatus::CONNECTING_1);
        }
        else if (line.contains("TCP connection established with")){
            this->setStatus(ConnectionStatus::CONNECTING_2);
        }
        else if (line.contains("Initial packet from")){
            this->setStatus(ConnectionStatus::CONNECTING_3);
        }
        else if (line.contains("VERIFY EKU OK")){
            this->setStatus(ConnectionStatus::CONNECTING_4);
        }
        else if (line.contains("Peer Connection Initiated with")){
            this->setStatus(ConnectionStatus::CONNECTING_5);
        }
        else if (line.contains("Initialization Sequence Completed")){
            this->setStatus(ConnectionStatus::CONNECTED);
        }
        else if (line.contains("Interrupted system call")){
            this->setStatus(ConnectionStatus::DISCONNECTING);
        }

        qDebug() <<"çıktı:"<<this->m_tunNumber<<":" << line;
    }
}

void Router::listenProcessStarted()
{
    qDebug()<<"process->started";
}


void Router::listenProcessFinished(int exitCode)
{
    qDebug()<<"process-> finished"<<exitCode;
    this->setStatus(ConnectionStatus::NOT_RUNNING);


    if (m_reconnect){

        this->connect();
    }

}

