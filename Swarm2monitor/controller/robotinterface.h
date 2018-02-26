#ifndef ROBOTINTERFACE2_H
#define ROBOTINTERFACE2_H
#include <QtWidgets>

#include "controller/comdriver.h"


class RobotInterface : public QObject
{
    public:
        RobotInterface(QString const &ipAddress, unsigned int const &port, QObject *parent = nullptr);
        virtual void makeAPIRequest() = 0;

    protected:
        QMap<unsigned int,QString> sensorMap;
        QMapIterator<unsigned int, QString> *iterator;

        void fillSensorMap(unsigned int sensorId, QString apiId);

        ComDriver *comDriver;

    private:
};

#endif // ROBOTINTERFACE2_H
