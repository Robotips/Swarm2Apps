#ifndef USERDATA_H
#define USERDATA_H

#include <QString>

class UserData
{
    public:
        UserData(QString const& ipAddr = "0.0.0.0", unsigned int port = 80);
        QString getIpAddr();
        unsigned int getPort();

        void setIpAddr(QString const& ipAddr);
        void setPort(unsigned int port);

        QString getIpAddrWithPort();

    private:
        QString ipAddr;
        unsigned int port;
};

#endif // USERDATA_H
