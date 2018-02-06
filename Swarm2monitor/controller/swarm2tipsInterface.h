#ifndef SWARM_H
#define SWARM_H
#include <QtWidgets>

#include "controller/robotinterface2.h"
#include "controller/apimanager2.h"

class Swarm2tipsInterface : public RobotInterface2
{
    Q_OBJECT

    public:
        Swarm2tipsInterface(QString const &ipAddress, unsigned int const &port, QObject *parent = 0);
        enum Sensor { Tofs, Tof1, Tof2, Tof3, Rotaries, Rotary1, Rotary2, Gyros, GyroX, GyroY, GyroZ, Acceleros, AcceleroX, AcceleroY, AcceleroZ, Motors, Motor1, Motor2, BatteryLevel };
        virtual void makeAPIRequest();

    private:
        void initializeSensorMap();

    private slots:
        void retrieveFilterSensorData(QJsonObject obj, unsigned int sensorId);

    signals:
        void sensorDataAvailable(unsigned int sensorId, float x, float xx, float xxx);


};

#endif // SWARM_H
