#include "robotinterface2.h"

RobotInterface2::RobotInterface2(const QString &ipAddress, const unsigned int &port, QObject *parent) : QObject(parent)
{

}

void RobotInterface2::fillSensorMap(unsigned int sensorId, QString apiId)
{
    sensorMap.insert(sensorId, apiId);
}
