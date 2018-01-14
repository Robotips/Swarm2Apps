#ifndef ROBOTINTERFACE_H
#define ROBOTINTERFACE_H

#include <QWidget>
#include <QtNetwork>
#include <QUrl>

#include "logwidget.h"

class RobotInterface : public QObject
{
    Q_OBJECT

    public:
        RobotInterface(QString const &ipAddress, unsigned int port, int updateInterval = 500, QObject *parent = 0);
        void connect();
        void disconnect();
        bool isConnected();

        //bool

        void setRobotIpAndPort(QString const &ipAddress, unsigned int port);
        void setStdr(LogWidget *logWidget);

        //Mouvement
        bool moveForward();
        bool moveBackward();
        bool turnLeft();
        bool turnRight();

        bool stopAction();

    private slots:
        void replyErrorHandler(QNetworkReply::NetworkError code);
        void replyTofErrorHandler(QNetworkReply::NetworkError code);
        void replyBatErrorHandler(QNetworkReply::NetworkError code);

        void replyFinishedHandler();

        void getRestApiQueryTofResult();
        void getRestApiQueryBatResult();

        void sensorUpdate();

    protected:

    private:
        bool isCon;
        bool isError;

        bool flipFlopCrash1;
        bool flipFlopCrash2;
        bool flipFlopCrash3;
        LogWidget *refLogWidget;
        QString robotIp;
        unsigned int robotPort;
        //Network part
        QUrl robotIpUrl;
        QNetworkAccessManager netAccMan;

        QNetworkReply *reply;
        QNetworkReply *replyTof;
        QNetworkReply *replyBat;

        //Update part
        QTimer *sensorUpdateTimer;
        int updateInte;

        void queryRestApiTof();
        void queryRestApiBat();

    signals :
        void robotConnected();
        //Sensor part
        void tofValuesReceived(int, int, int);
        void batValuesReceived(int);
};

#endif // ROBOTINTERFACE_H
