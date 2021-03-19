#include "router.h"
#include "QDebug"
#include "QObject"
#include "QTime"
#include <QRegularExpression>
#include <QNetworkConfigurationManager>
#include <QNetworkAccessManager>
#include <QNetworkReply>




#include <curl/curl.h>

#include <csignal>

// https://gist.github.com/ynonp/8148340

Router::Router(QObject *parent) : QObject(parent)
{
    this->setStatus(ConnectionStatus::IDLE);
    this->setConProgress(0);
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

    this->setConProgress(0);

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
         <<"--connect-retry"<<"1"
         << "--verb" << "3";



    //connect(process, &QProcess::start, this, SLOT(listenProcessStatus);

    process->setWorkingDirectory("/home/user/stub");


    process->setProgram(binPath);

    process->setArguments(args);

    process->start();

    this->setStatus(ConnectionStatus::CONNECTING);
    this->setConProgress(0.01);
}

void Router::reconnect(){
     this->disconnect();
     this->m_reconnect=true;
}

void Router::disconnect(){
    if (this->m_status!=ConnectionStatus::DISCONNECTING){
        kill(process->processId(), SIGINT);
    }
}


void Router::listenProcessReadyRead()
{
    while(process->canReadLine()){
        QString line =  process->readLine();
        if (line.contains("Attempting to establish TCP")){
            this->setConProgress(0.02);
        }
        else if (line.contains("TCP connection established with")){
            this->setConProgress(0.03);
        }
        else if (line.contains("SOCKS proxy wants us to send UDP")){
            this->setConProgress(0.13);
        }
        else if (line.contains("UDPv4 link remote")){
            this->setConProgress(0.23);
        }
        else if (line.contains("TLS: Initial packet")){
            this->setConProgress(0.27);
        }
        else if (line.contains("VERIFY EKU")){
            this->setConProgress(0.31);
        }
        else if (line.contains("Peer Connection Initiated")){
            this->setConProgress(0.39);
        }
        else if (line.contains("PUSH_REQUEST")){
            this->setConProgress(0.85);
        }
        else if (line.contains("PUSH: Received control message")){
            this->setConProgress(0.88);
            this->parsePushReply(line);
            this->setConProgress(0.89);
        }
        else if (line.contains("Initialization Sequence Completed")){
            this->setStatus(ConnectionStatus::CONNECTED);
            this->setConProgress(1.0);
            checkIP();
        }
        else if (line.contains("Interrupted system call")){
            this->setStatus(ConnectionStatus::DISCONNECTING);
            this->setConProgress(0.01);
        }

        qDebug() <<"çıktı:" << QDateTime::currentDateTime().toString("mm:sszzz") <<this->m_tunNumber<<":" << line;
    }
}




void Router::checkIP(){

    qDebug()<<"CHECKING";

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);




    QNetworkConfigurationManager config_manager;
    QList<QNetworkConfiguration> configs = config_manager.allConfigurations();
    bool found_interface = false;
    QString desired_interface_name("tun11");
    foreach (const QNetworkConfiguration &config, configs) {
        if (config.name() == desired_interface_name) {
            found_interface = true;
            QNetworkAccessManager *network_access_manager = new QNetworkAccessManager;
            network_access_manager->setConfiguration(config);




            QNetworkRequest request;
            request.setUrl(QUrl("http://checkip.amazonaws.com"));
            manager->get(request);



//            size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
//            {
//                ((std::string *)userp)->append((char *)contents, size * nmemb);
//                return size * nmemb;
//            }

//            void run(int i)
//            {
//                CURL *curl;

//                curl = curl_easy_init(); //0.686166 ms
//                CURLcode res;
//                auto aa = QString().asprintf("tun%d", i);

//                std::string readBuffer;

//                curl_easy_setopt(curl, CURLOPT_URL, "http://checkip.amazonaws.com/");
//                curl_easy_setopt(curl, CURLOPT_INTERFACE, aa.toStdString().c_str());
//                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

//                // to this:  0.053129 ms

//                /* Perform the request, res will get the return code */
//                res = curl_easy_perform(curl); //645.075 ms

//                /* Check for errors */
//                if (res == CURLE_OK) {
//                    long response_code;
//                    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

//                    qDebug() << response_code;
//                    qDebug() << QString().fromStdString(readBuffer);
//                }

//                /* always cleanup */
//                curl_easy_cleanup(curl); //0.957674 ms
//            }

            break;
        }
    }
    if (!found_interface) {
        //we failed to find the interface!
    }





    this->setNetActing(false);

}

void replyFinished(QNetworkReply *resp){
    QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);

        // Print or catch the status code
        QString status = status_code.toString(); // or status_code.toInt();
        qDebug() << status;

}

void Router::listenProcessStarted()
{
    qDebug()<<"process->started";
    emit pidChanged();
    emit processIsRunningChanged();
}


void Router::listenProcessFinished(int exitCode)
{
    qDebug()<<"process-> finished"<<exitCode;
    this->setStatus(ConnectionStatus::IDLE);
    this->setConProgress(0);

    if (m_reconnect){

        this->connect();
    }
    emit processIsRunningChanged();

}

void Router::parsePushReply(QString line){

    QRegularExpression peerRegex("(?<=peer-id )([0-9]+)(?=,)");
    this->m_peer = peerRegex.match(line).captured(1).toInt();

    QRegularExpression gatewayRegex("(?<=route-gateway )((?:[0-9]{1,3}.){3}[0-9]{1,3}+)(?=,)");
    this->m_gateway = gatewayRegex.match(line).captured(1);

    QRegularExpression localRegex("(?<=ifconfig )((?:[0-9]{1,3}.){3}[0-9]{1,3}+)(?= )");
    this->m_local = localRegex.match(line).captured(1);

    emit pushReplyParsed();

}

