#ifndef COMDRIVER_H
#define COMDRIVER_H
#include <QtWidgets>

class ComDriver : public QObject
{
    Q_OBJECT

    public:
        ComDriver(QObject *parent = nullptr);
        virtual void connect() = 0;
        virtual void disconnect() = 0;
        virtual void sendApiRequest(QString const &ressource, unsigned int sensorId) = 0;

    signals:
        virtual void networkErrorReceived(QString error) = 0;
};

#endif // COMDRIVER_H
