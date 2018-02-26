#include "robotinterface.h"

RobotInterface::RobotInterface(const QString &ipAddress, const unsigned int &port, QObject *parent) : QObject(parent)
{

}

void RobotInterface::fillSensorMap(unsigned int sensorId, QString apiId)
{
    sensorMap.insert(sensorId, apiId);
}
