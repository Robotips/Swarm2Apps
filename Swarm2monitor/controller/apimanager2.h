#ifndef APIMANAGER2_H
#define APIMANAGER2_H
#include <QtWidgets>
#include <QtNetwork>
#include <QNetworkAccessManager>

#include "controller/comdriver.h"

class APIManager2 : public ComDriver
{
    Q_OBJECT

    public:
        APIManager2(QString const &ipAddress, unsigned int const &port, QObject *parent = 0);
        virtual void connect();//Initialize requestUrl
        virtual void disconnect();
        virtual void sendApiRequest(QString const &ressource, unsigned int sensorId);

    private:
        QString robotIp;
        unsigned int robotPort;

        QString buildedURL;

        QUrl requestUrl;
        QNetworkAccessManager networkAccessManager;
        QNetworkReply *reply;
        QNetworkReply *jsonReply;

    private slots:
        void replyErrorHandler(QNetworkReply::NetworkError code);
        void replyFinishedHandler();
        void replyWithJsonHandler();

    signals:
        void restAPIConnected();

        void jsonObjectReceived(QJsonObject obj, unsigned int sensorId);

};

#endif // APIMANAGER2_H
