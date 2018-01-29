#include "robotinterface.h"

RobotInterface::RobotInterface(QString const &ipAddress, unsigned int port, int updateInterval, QObject *parent) :QObject(parent), isCon(false), isError(false), flipFlopCrash1(false), robotIp(ipAddress), robotPort(port), updateInte(updateInterval)
{
    //We create the timer
    sensorUpdateTimer = new QTimer();
    QObject::connect(sensorUpdateTimer, SIGNAL(timeout()), this , SLOT(sensorUpdate()));
}

void RobotInterface::setRobotIpAndPort(QString const &ipAddress, unsigned int port)
{
    robotIp = ipAddress;
    robotPort = port;
}

void RobotInterface::setStdr(LogWidget *logWidget)
{
    refLogWidget = logWidget;
}

void RobotInterface::connect()
{
    robotIpUrl.setUrl("http://"+robotIp+":"+QString::number(robotPort));

    reply = netAccMan.get(QNetworkRequest(robotIpUrl));

    //We connect the reply error signal
    //Would be great to add a custom timout
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &RobotInterface::replyErrorHandler);
    QObject::connect(reply, &QNetworkReply::finished, this, &RobotInterface::replyFinishedHandler);
}

void RobotInterface::disconnect()
{
    isCon = false;
    isError = false;
    //We stop the timer
    sensorUpdateTimer->stop();
}

bool RobotInterface::isConnected()
{
    return isCon;
}

void RobotInterface::replyErrorHandler(QNetworkReply::NetworkError code)
{
    if(reply != Q_NULLPTR)
    {
        //qDebug() << "Error :" + reply->errorString();
        isError = true;
        refLogWidget->addLog("Error : "+reply->errorString(), LogWidget::LogColor::RED);
    }
}

//This method is only there to test the connection between the pc ans the robot
void RobotInterface::replyFinishedHandler()
{
    if(reply != Q_NULLPTR)
    {
        //qDebug() << "Finished :" + reply->readAll();
        if(!isError)
        {
            refLogWidget->addLog("Connected", LogWidget::LogColor::GREEN);
            isCon = true;
            //We start the timer
            sensorUpdateTimer->start(updateInte);

            emit robotConnected();
        }

        reply->deleteLater();
        reply = Q_NULLPTR;

        isError = false;
    }
}

//Tof API PART

/**
 * @brief RobotInterface::queryRestApiTof
 */
void RobotInterface::queryRestApiTof()
{
    QUrl url;
    url.setUrl("http://"+robotIp+":"+QString::number(robotPort)+"/api/tof.php");

    replyTof = netAccMan.get(QNetworkRequest(url));


    //We connect the reply error signal
    //Would be great to add a custom timout
    QObject::connect(replyTof, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &RobotInterface::replyTofErrorHandler);
    QObject::connect(replyTof, &QNetworkReply::finished, this, &RobotInterface::getRestApiQueryTofResult);
}

/**
 * @brief RobotInterface::replyTofErrorHandler
 * @param code
 */
void RobotInterface::replyTofErrorHandler(QNetworkReply::NetworkError code)
{
    if(replyTof != Q_NULLPTR)
        refLogWidget->addLog("Error tof request: "+replyTof->errorString(), LogWidget::LogColor::RED);
}

void RobotInterface::getRestApiQueryTofResult()
{
    if(replyTof != Q_NULLPTR)
    {
        QByteArray jsonReply = replyTof->readAll();

        replyTof->deleteLater();
        replyTof = Q_NULLPTR;

        QJsonDocument jsonParser = QJsonDocument::fromJson(jsonReply);

        QJsonObject object = jsonParser.object();

        //We emit a signal with the values
        emit tofValuesReceived(object["tof1"].toString().toInt(), object["tof2"].toString().toInt(), object["tof3"].toString().toInt());
    }
}

//Bat API PART
void RobotInterface::queryRestApiBat()
{
    QUrl url;
    url.setUrl("http://"+robotIp+":"+QString::number(robotPort)+"/api/status.php");

    replyBat = netAccMan.get(QNetworkRequest(url));

    //We connect the reply error signal
    //Would be great to add a custom timout
    QObject::connect(replyBat, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &RobotInterface::replyBatErrorHandler);
    QObject::connect(replyBat, &QNetworkReply::finished, this, &RobotInterface::getRestApiQueryBatResult);
}

void RobotInterface::replyBatErrorHandler(QNetworkReply::NetworkError code)
{
    if(replyBat != Q_NULLPTR)
        refLogWidget->addLog("Error battery request: "+replyBat->errorString(), LogWidget::LogColor::RED);
}

void RobotInterface::getRestApiQueryBatResult()
{
    if(replyBat != Q_NULLPTR)
    {
        QByteArray jsonReply = replyBat->readAll();

        replyBat->deleteLater();
        replyBat = Q_NULLPTR;

        QJsonDocument jsonParser = QJsonDocument::fromJson(jsonReply);

        QJsonObject object = jsonParser.object();

        //We emit a signal with the values
        emit batValuesReceived(object["batteryLevel"].toString().toInt());
    }
}

void RobotInterface::sensorUpdate()
{
    queryRestApiTof();
    queryRestApiBat();
}
