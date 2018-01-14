#ifndef DATASERIALIZERUNSERIALIZER_H
#define DATASERIALIZERUNSERIALIZER_H

#include <QString>
#include <QtXml>
#include <QDebug>

#include "userdata.h"

class DataSerializerUnserializer
{
    public:
        DataSerializerUnserializer(QString const& file, UserData *userData);

        void writeUserData();
        void readUserData();

    private:
        QString fileName;
        UserData *userData;
};

#endif // DATASERIALIZERUNSERIALIZER_H
