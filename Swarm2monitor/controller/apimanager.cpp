#include "apimanager.h"

APIManager::APIManager(const QString &ipAddress, const unsigned int &port, QObject *parent) : ComDriver(parent), buildedURL("http://"+ipAddress+":"+QString::number(port)), networkAccessManager(parent), reply(Q_NULLPTR), jsonReply(Q_NULLPTR), failedApiRequest(0)
{
    robotIp = ipAddress;
    robotPort = port;
}

void APIManager::connect()
{
    requestUrl.setUrl(buildedURL);

    //We test the connection:
    reply = networkAccessManager.get(QNetworkRequest(requestUrl));

    //We connect the reply error signal
    //Would be great to add a custom timout
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &APIManager::replyErrorHandler);
    QObject::connect(reply, &QNetworkReply::finished, this, &APIManager::replyFinishedHandler);

    //We reset the fail counter to 0
    failedApiRequest = 0;
}

void APIManager::disconnect()
{

}

void APIManager::sendApiRequest(const QString &ressource, unsigned int sensorId)
{
    requestUrl.setUrl(buildedURL+"/api/"+ressource);

    jsonReply = networkAccessManager.get(QNetworkRequest(requestUrl));
    //We stick the sensorId and the reply together
    jsonReply->setProperty("sensorId",QVariant(sensorId));

    //We connect the reply error signal
    //Would be great to add a custom timout
    QObject::connect(jsonReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &APIManager::replyErrorHandler);
    QObject::connect(jsonReply, &QNetworkReply::finished, this, &APIManager::replyWithJsonHandler);
}

//SLOTS
void APIManager::replyErrorHandler(QNetworkReply::NetworkError code)
{
    if(reply != Q_NULLPTR)
    {
        qDebug()<< "<Connection error> "+reply->errorString() +" code : "+QString::number((int)code);

        reply->deleteLater();
        reply = Q_NULLPTR;

        //We emmit the connection error so we can handle it later
        emit networkErrorReceived("CONNECTION_ERROR");
    }

    if(jsonReply != Q_NULLPTR)
    {
        qDebug()<< "<Json query error> "+jsonReply->errorString() +" code : "+QString::number((int)code);

        jsonReply->deleteLater();
        jsonReply = Q_NULLPTR;

        //We increment the fail counter every failed attempts
        if(failedApiRequest++ >= 10)
        {
            emit networkErrorReceived("NETWORK_ERROR");
        }

    }

}

void APIManager::replyFinishedHandler()
{
    if(reply != Q_NULLPTR)
    {
        qDebug()<<"Connected to API";

        reply->deleteLater();
        reply = Q_NULLPTR;

        emit restAPIConnected();
    }
}

void APIManager::replyWithJsonHandler()
{
    if(jsonReply != Q_NULLPTR)
    {
        unsigned int sensorId = jsonReply->property("sensorId").toUInt();

        QByteArray jsonStringReply = jsonReply->readAll();

        QJsonDocument jsonParser = QJsonDocument::fromJson(jsonStringReply);

        QJsonObject object = jsonParser.object();

        qDebug()<<"Json reply :"+jsonStringReply;

        //We free the memory allocated for the jsonReply
        jsonReply->deleteLater();
        jsonReply = Q_NULLPTR;

        emit jsonObjectReceived(object, sensorId);
    }
}
