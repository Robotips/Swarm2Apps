#include "apimanager2.h"

APIManager2::APIManager2(const QString &ipAddress, const unsigned int &port, QObject *parent) : ComDriver(parent), buildedURL("http://"+ipAddress+":"+QString::number(port)), networkAccessManager(parent), reply(Q_NULLPTR), jsonReply(Q_NULLPTR)
{
    robotIp = ipAddress;
    robotPort = port;
}

void APIManager2::connect()
{
    requestUrl.setUrl(buildedURL);

    //We test the connection:
    reply = networkAccessManager.get(QNetworkRequest(requestUrl));

    //We connect the reply error signal
    //Would be great to add a custom timout
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &APIManager2::replyErrorHandler);
    QObject::connect(reply, &QNetworkReply::finished, this, &APIManager2::replyFinishedHandler);
}

void APIManager2::disconnect()
{

}

void APIManager2::sendApiRequest(const QString &ressource, unsigned int sensorId)
{
    requestUrl.setUrl(buildedURL+"/api/"+ressource);

    jsonReply = networkAccessManager.get(QNetworkRequest(requestUrl));
    //We stick the sensorId and the reply together
    jsonReply->setProperty("sensorId",QVariant(sensorId));

    //We connect the reply error signal
    //Would be great to add a custom timout
    QObject::connect(jsonReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &APIManager2::replyErrorHandler);
    QObject::connect(jsonReply, &QNetworkReply::finished, this, &APIManager2::replyWithJsonHandler);
}

//SLOTS
void APIManager2::replyErrorHandler(QNetworkReply::NetworkError code)
{
    if(reply != Q_NULLPTR)
    {
        qDebug()<< "<Connection error> "+reply->errorString() +" code : "+QString::number((int)code);

        reply->deleteLater();
        reply = Q_NULLPTR;
    }

    if(jsonReply != Q_NULLPTR)
    {
        qDebug()<< "<Json query error> "+jsonReply->errorString() +" code : "+QString::number((int)code);

        jsonReply->deleteLater();
        jsonReply = Q_NULLPTR;
    }

}

void APIManager2::replyFinishedHandler()
{
    if(reply != Q_NULLPTR)
    {
        qDebug()<<"Connected to API";

        reply->deleteLater();
        reply = Q_NULLPTR;

        emit restAPIConnected();
    }
}

void APIManager2::replyWithJsonHandler()
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
