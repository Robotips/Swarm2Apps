#include "apiobject.h"

ApiObject::ApiObject(QString const &api, unsigned int updateInterval, QObject *parent): QObject(parent), apiUrl(api), upInt(updateInterval)
{

}

QString ApiObject::getApiUrl()
{
    return apiUrl;
}

unsigned int ApiObject::getUpdateIntervale()
{
    return upInt;
}
