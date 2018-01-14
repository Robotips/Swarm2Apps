#include "dataserializerunserializer.h"

DataSerializerUnserializer::DataSerializerUnserializer(QString const& file, UserData *userData)
{
    this->fileName = file;
    this->userData = userData;
}

void DataSerializerUnserializer::writeUserData()
{
    QDomDocument doc;
    QDomElement root = doc.createElement("UserData");

    doc.appendChild(root);

    QDomElement ipAddr = doc.createElement("IpAddr");
    ipAddr.setAttribute("Value", userData->getIpAddr());
    root.appendChild(ipAddr);

    QDomElement port = doc.createElement("Port");
    port.setAttribute("Value", userData->getPort());
    root.appendChild(port);

    //Let's write to the file:
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        //Error
    }
    else
    {
        QTextStream stream(&file);

        stream << doc.toString();

        file.close();
    }

}

void DataSerializerUnserializer::readUserData()
{
    QDomDocument doc;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //Error
    }
    else
    {
        if(!doc.setContent(&file))
        {
            //Error
        }
    }

    QDomElement root = doc.firstChildElement();

    QDomNodeList ipAddrList = root.elementsByTagName("IpAddr");
    QDomNodeList portList = root.elementsByTagName("Port");

    QDomNode ipAddrNode = ipAddrList.at(0);
    QDomNode portNode = portList.at(0);

    QDomElement ipAddr(ipAddrNode.toElement()), port(portNode.toElement());

    userData->setIpAddr(ipAddr.attribute("Value"));
    userData->setPort(port.attribute("Value").toUInt());
}
