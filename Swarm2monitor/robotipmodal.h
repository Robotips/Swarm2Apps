#ifndef ROBOTIPMODAL_H
#define ROBOTIPMODAL_H

#include <QDialog>
#include <QLabel>
#include <QDebug>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>

#include "userdata.h"

class RobotIpModal : public QDialog
{
    Q_OBJECT

    public:
        RobotIpModal(UserData *userData, QWidget *parent = 0);

    private slots:
        void saveAddr();
        void cancelFunc();

    private:
        QLineEdit *ipAdressIF;
        QLineEdit *portIF;

        QPushButton *save;
        QPushButton *cancel;

        QFormLayout *formLayout;
        QGroupBox *addrGroupBox;
        QVBoxLayout *vBox;
        QHBoxLayout *buttonHbox;

        UserData *userData;
};

#endif // ROBOTIPMODAL_H
