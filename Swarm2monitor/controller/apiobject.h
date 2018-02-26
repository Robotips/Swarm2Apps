#ifndef APIOBJECT_H
#define APIOBJECT_H

#include <QWidget>


class ApiObject : public QObject
{
    Q_OBJECT

    public:
        ApiObject(QString const &api, unsigned int updateInterval, QObject *parent = nullptr);
        QString getApiUrl();
        unsigned int getUpdateIntervale();

    private:
        QString apiUrl;
        unsigned int upInt;

    private slots:

    signals:
};

#endif // APIOBJECT_H
