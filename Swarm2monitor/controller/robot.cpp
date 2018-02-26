#include "robot.h"

Robot::Robot(RobotType type, const QString &ipAddress, const unsigned int &port, unsigned int refreshTime, QObject *parent) : QObject(parent), robotIp(ipAddress), robotPort(port), refreshTime(refreshTime), acquiring(false)
{
    //We construct the correct robotInterface

    switch(type)
    {
    case RobotType::DeltaTips:
        robotInterface = nullptr;
        break;
    case RobotType::Swarm2tips:
        robotInterface = new Swarm2tipsInterface(robotIp, robotPort);

        //We connect the slot to handle connection errors
        QObject::connect((Swarm2tipsInterface*)robotInterface, &Swarm2tipsInterface::robotConnectionErrorReceived, this, &Robot::robotConnectionErrorHandler);
        break;
    default:
        robotInterface = nullptr;
    }

    //We connect the QTimer to a slot
    QObject::connect(&sensorUpdateTimer, SIGNAL(timeout()), this , SLOT(robotApiRequest()));

    //We connect the slot that is adding sensor data to the qlist
    QObject::connect(robotInterface, SIGNAL(sensorDataAvailable(unsigned int, float, float, float)), this , SLOT(addSensorDataToHistory(uint,float,float,float)));
}

void Robot::startDataAcquisition()
{
    acquiring = true;
    //We start the timer to call our slot again and again
    sensorUpdateTimer.start(refreshTime);
}

void Robot::stopDataAcquisition()
{
    acquiring = false;
    sensorUpdateTimer.stop();
}

void Robot::robotConnectionErrorHandler()
{
    //If we receive a connection error we stop the data aquisition
    acquiring = false;
    sensorUpdateTimer.stop();

    emit robotConnectionErrorReceived();
}

void Robot::robotApiRequest()
{
    qDebug()<<"Api queried";
    robotInterface->makeAPIRequest();
}

void Robot::addSensorDataToHistory(unsigned int sensorId, float x, float xx, float xxx)
{
    SensorData sd;

    switch(sensorId)
    {
    case Swarm2tipsInterface::Sensor::Tofs:

        sd.tof1 = x;
        sd.tof2 = xx;
        sd.tof3 = xxx;

        sensorDataCollection.append(sd);
       break;
    case Swarm2tipsInterface::Sensor::BatteryLevel:
        sd.batteryLevel = x;

        sensorDataCollection.append(sd);
       break;
    default:
        qDebug()<<"Unknown sensor";
    }

    emit newDataAvailable((Swarm2tipsInterface::Sensor)sensorId);
}

QList<Robot::SensorData> *Robot::getSensorCollection()
{
    return &sensorDataCollection;
}

bool Robot::isAcquiring()
{
    return acquiring;
}
