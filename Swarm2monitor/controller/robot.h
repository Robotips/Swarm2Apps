#ifndef ROBOT_H
#define ROBOT_H
#include <QObject>
#include <QtWidgets>
#include "controller/swarm2tipsInterface.h"
#include "controller/robotinterface.h"

class Robot : public QObject
{
    Q_OBJECT

    public:
        enum RobotType {Swarm2tips, DeltaTips}; //Robots can be added
        struct Coord{int x;int y;};

        Robot(RobotType type, QString const &ipAddress, unsigned int const &port, unsigned int refreshTime = 500, QObject *parent = 0);

        void startDataAcquisition();
        void stopDataAcquisition();

        QList<Swarm2tipsInterface::Sensor> getAvailableSensors();
        float getSensor(Swarm2tipsInterface::Sensor id);
        Coord getPosition();
        void move(Coord c);
        void move2(Coord c);
        void rotate(int degrees);

        bool isAcquiring();

    private:
        QTimer sensorUpdateTimer;
        RobotInterface *robotInterface;

        QString robotIp;
        unsigned int robotPort;
        unsigned int refreshTime;

        bool acquiring;

        //We add a private class
        struct SensorData
        {
                float tof1;
                float tof2;
                float tof3;

                float rotary1;
                float rotary2;

                float gyroX;
                float gyroY;
                float gyroZ;

                float acceX;
                float acceY;
                float acceZ;

                float batteryLevel;

        };
        QList<SensorData> sensorDataCollection;

     private slots:
        void robotApiRequest();//We ask the robotInterface to make the query

        void addSensorDataToHistory(unsigned int sensorId, float x, float xx, float xxx);

        void robotConnectionErrorHandler();

     signals:
        void newDataAvailable(Swarm2tipsInterface::Sensor);
        void robotConnectionErrorReceived();

     public:
        QList<SensorData> *getSensorCollection();


};

#endif // ROBOT_H
