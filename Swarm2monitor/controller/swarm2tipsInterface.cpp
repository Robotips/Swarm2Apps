#include "swarm2tipsInterface.h"

Swarm2tipsInterface::Swarm2tipsInterface(const QString &ipAddress, const unsigned int &port, QObject *parent) : RobotInterface(ipAddress, port, parent)
{
    //We load the proper driver for the api requests:
    comDriver = new APIManager(ipAddress, port);

    //We fill the map
    initializeSensorMap();

    iterator = new QMapIterator<unsigned int, QString>(sensorMap);

    QObject::connect(comDriver, SIGNAL(jsonObjectReceived(QJsonObject,uint)), this, SLOT(retrieveFilterSensorData(QJsonObject,uint)));
    //We connect as well slots to handle network errors
    //QObject::connect(comDriver, SIGNAL(networkErrorReceived(QString)) , this, SLOT(comDriverErrorHandler(QString)));
    QObject::connect((APIManager*)comDriver, &APIManager::networkErrorReceived , this, &Swarm2tipsInterface::comDriverErrorHandler);
}

void Swarm2tipsInterface::initializeSensorMap()
{
    //We fill the map with ids and api identifiers
    fillSensorMap(Sensor::Tofs, "tof.php");
    /*fillSensorMap(Sensor::Tof1, "404");
    fillSensorMap(Sensor::Tof2, "404");
    fillSensorMap(Sensor::Tof3, "404");

    fillSensorMap(Sensor::Rotaries, "404");
    fillSensorMap(Sensor::Rotary1, "404");
    fillSensorMap(Sensor::Rotary2, "404");

    fillSensorMap(Sensor::Gyros, "404");
    fillSensorMap(Sensor::GyroX, "404");
    fillSensorMap(Sensor::GyroY, "404");
    fillSensorMap(Sensor::GyroZ, "404");

    fillSensorMap(Sensor::Acceleros, "404");
    fillSensorMap(Sensor::AcceleroX, "404");
    fillSensorMap(Sensor::AcceleroY, "404");
    fillSensorMap(Sensor::AcceleroZ, "404");

    fillSensorMap(Sensor::Motors, "404");
    fillSensorMap(Sensor::Motor1, "404");
    fillSensorMap(Sensor::Motor2, "404");*/

    fillSensorMap(Sensor::BatteryLevel, "status.php");
}

//In this method, we query the api for each sensor(one at a time)
void Swarm2tipsInterface::makeAPIRequest()
{
    if(sensorMap.size() > 0)
    {
        if(!iterator->hasNext())
            iterator->toFront();

        iterator->next();

        qDebug()<<"Sensor :"+iterator->value()+"; Sensor id : "+QString::number(iterator->key());

        //We send the request to the robot, with the driver
        comDriver->sendApiRequest(iterator->value(), iterator->key());

    }
    else
       qDebug()<<"No sensor for this robot";
}

void Swarm2tipsInterface::comDriverErrorHandler(QString error)
{
    qDebug()<<"Network error : "+error;
}

void Swarm2tipsInterface::retrieveFilterSensorData(QJsonObject obj, unsigned int sensorId)
{
    //Big switch of death that we all enjoy :P
    switch(sensorId)
    {
    case Sensor::Tofs:
        qDebug()<<"We have Tofs data";
        emit sensorDataAvailable(sensorId, obj["tof1"].toString().toInt(), obj["tof2"].toString().toInt(), obj["tof3"].toString().toInt());
        break;
    case Sensor::Tof1:
        qDebug()<<"We have Tof1 data";
        break;
    case Sensor::Tof2:
        qDebug()<<"We have Tof2 data";
        break;
    case Sensor::Tof3:
         qDebug()<<"We have Tof3 data";
         break;

    case Sensor::Rotaries:
         qDebug()<<"We have Rotaries data";
         break;
    case Sensor::Rotary1:
         qDebug()<<"We have Rotary1 data";
         break;
    case Sensor::Rotary2:
         qDebug()<<"We have Rotary2 data";
         break;

    case Sensor::Gyros:
         qDebug()<<"We have Gyros data";
         break;
    case Sensor::GyroX:
         qDebug()<<"We have GyroX data";
         break;
    case Sensor::GyroY:
         qDebug()<<"We have GyroY data";
         break;
    case Sensor::GyroZ:
         qDebug()<<"We have GyroZ data";
         break;

    case Sensor::Acceleros:
         qDebug()<<"We have Acceleros data";
         break;
    case Sensor::AcceleroX:
         qDebug()<<"We have AcceleroX data";
         break;
    case Sensor::AcceleroY:
         qDebug()<<"We have AcceleroY data";
         break;
    case Sensor::AcceleroZ:
         qDebug()<<"We have AcceleroZ data";
         break;

    case Sensor::Motors:
         qDebug()<<"We have Motors data";
         break;
    case Sensor::Motor1:
         qDebug()<<"We have Motor1 data";
         break;
    case Sensor::Motor2:
         qDebug()<<"We have Motor2 data";
         break;

    case Sensor::BatteryLevel:
         qDebug()<<"We have BatteryLevel data";
         emit sensorDataAvailable(sensorId, obj["batteryLevel"].toString().toInt(), 0, 0);
         break;
    default:
        qDebug()<<"Unknown sensor";
    }
}
