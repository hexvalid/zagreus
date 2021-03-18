#include "router.h"
#include "QDebug"

// https://gist.github.com/ynonp/8148340

router::router(QObject *parent) : QObject(parent)
{
    qDebug() << "inited";
    this->process = new QProcess(this);
}


void router::connect()
{
    qDebug() << "connecting";

    QString binPath = "/home/user/zagra";
    QStringList args;

    args << "--client" << "--nobind" << "--block-ipv6" << "--persist-key" << "--persist-tun"
         << "--fast-io" << "--comp-lzo"
         << "--dev-type" << "tun"
         << "--dev" << "tun0"
         << "--route-metric" << "1"
         << "--route-delay" << "0"
         << "--sndbuf" << "196608"
         << "--rcvbuf" << "196608"
         << "--remote-cert-tls" << "server"
         << "--cipher" << "AES-256-GCM"
         << "--explicit-exit-notify" << "2"
         << "--ping" << "9"
         << "--ping-restart" << "30"
         << "--socks-proxy" << "139.59.176.105" << "25565" << "/home/user/Videos/loas/auth-socks.txt"
         << "--auth-user-pass" << "/home/user/Videos/loas/auth.txt"
         << "--pull-filter" << "ignore" << "ifconfig-ipv6"
         << "--pull-filter" << "ignore" << "route-ipv6"
         << "--pull-filter" << "ignore" << "redirect-gateway"
         << "--pull-filter" << "ignore" << "dhcp-option DNS"
         << "--pull-filter" << "ignore" << "explicit-exit-notify"
         << "--pull-filter" << "ignore" << "ping"
         << "--proto" << "udp4"
         << "--remote" << "fr.hma.rocks" << "766"
         << "--ca" << "./stub/ca.txt"
         << "--cert" << "./stub/cert.txt"
         << "--key" << "./stub/key.txt"
         << "--verb" << "2";


    process->setProgram(binPath);
    process->setArguments(args);



    QObject::connect(process, SIGNAL(readyReadStandardOutput()),this, SLOT(listenReadyRead()));
    QObject::connect(process, SIGNAL(started()), this, SLOT(started()));

    process->start();

}


void router::listenReadyRead()
{
  qDebug() << "readyOut";
  QProcess *p = (QProcess *)sender();
  QByteArray buf = p->readAllStandardOutput();

  qDebug() << buf;
}

void router::started()
{
  qDebug() << "Proc Started";

}
