#include "userdata.h"

UserData::UserData(QString const& ipAddr, unsigned int port)
{
    this->ipAddr = ipAddr;
    this->port = port;
}

QString UserData::getIpAddr()
{
    return ipAddr;
}

unsigned int UserData::getPort()
{
    return port;
}

QString UserData::getIpAddrWithPort()
{
    return ipAddr+":"+QString::number(port);
}

void UserData::setIpAddr(QString const& ipAddr)
{
    this->ipAddr = ipAddr;
}

void UserData::setPort(unsigned int port)
{
    this->port = port;
}
