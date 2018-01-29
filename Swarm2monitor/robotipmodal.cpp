#include "robotipmodal.h"

RobotIpModal::RobotIpModal(UserData *userData, QWidget *parent) : QWidget(parent)
{
    this->userData = userData;

    addrGroupBox = new QGroupBox(tr("Info"), this);
    formLayout = new QFormLayout();
    buttonHbox = new QHBoxLayout();

    ipAdressIF = new QLineEdit(this);
    portIF = new QLineEdit(this);

    ipAdressIF->setText(userData->getIpAddr());
    ipAdressIF->setInputMask("000.000.000.000");
    portIF->setText(QString::number(userData->getPort()));
    portIF->setInputMask("00000");

    formLayout->addRow("Robot IP Address", ipAdressIF);
    formLayout->addRow("Port", portIF);

    addrGroupBox->setLayout(formLayout);

    save = new QPushButton(tr("Save"), this);
    connect(save, SIGNAL(clicked()), this, SLOT(saveAddr()));

    cancel = new QPushButton(tr("Cancel"), this);
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelFunc()));

    buttonHbox->addWidget(save);
    buttonHbox->addWidget(cancel);

    vBox = new QVBoxLayout(this);
    vBox->addWidget(addrGroupBox);
    vBox->addLayout(buttonHbox);


    setLayout(vBox);
    setMinimumSize(200,200);
}

void RobotIpModal::saveAddr()
{
    //We save the data and close the modal window
    userData->setIpAddr(ipAdressIF->text());
    userData->setPort(portIF->text().toUInt());
}

void RobotIpModal::cancelFunc()
{
    //We put the old values back
    ipAdressIF->setText(userData->getIpAddr());
    portIF->setText(QString::number(userData->getPort()));
}

