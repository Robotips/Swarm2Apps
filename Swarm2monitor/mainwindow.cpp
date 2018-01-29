#include "mainwindow.h"

MainWindow::MainWindow(UserData *userData, QWidget *parent) : QMainWindow(parent), robotInterface(userData->getIpAddr(), userData->getPort(), 250)
{
    userDataRef = userData;

    settingsDialog = new SettingsDialog(this);
    createSettingsDialog();

    createInfoSection();
    robotInterface.setStdr(logWidget);
    createActionSection();

    createActions();
    createMenuBar();

    QWidget *w = new QWidget(this);
    w->setMaximumWidth(5);
    setCentralWidget(w);
}

//destructeur
MainWindow::~MainWindow()
{

}

void MainWindow::createSettingsDialog()
{
    QTabWidget *ref = settingsDialog->addCategory(tr("Robot configuration"));
    ref->addTab(new RobotIpModal(userDataRef,settingsDialog),tr("Robot ip adress"));
}

void MainWindow::createInfoSection()
{
    infoLabel = new QLabel(tr("Swarm2 informations"));
    QFont titreFont1 = infoLabel->font();
    titreFont1.setPointSize(25);
    infoLabel->setFont(titreFont1);

    connectButton = new QPushButton(tr("&Connect"), this);

    voltageLabel = new QLabel(tr("Voltage(V) :"));
    voltage = new QLCDNumber(this);
    voltage->setFixedHeight(50);
    voltage->setFixedWidth(100);

    //Laser sensors

    tof1Label = new QLabel(tr("Laser left :"));
    tof2Label = new QLabel(tr("Laser middle :"));
    tof3Label = new QLabel(tr("Laser right :"));

    tof1 = new QLCDNumber(this);
    tof1->setFixedHeight(50);
    tof1->setFixedWidth(100);

    tof2 = new QLCDNumber(this);
    tof2->setFixedHeight(50);
    tof2->setFixedWidth(100);

    tof3 = new QLCDNumber(this);
    tof3->setFixedHeight(50);
    tof3->setFixedWidth(100);

    //Speedometer
    speedLabel = new QLabel(tr("Wheel 1 rotation speed :"));

    mSpeedGauge = new QcGaugeWidget;
    mSpeedGauge->setFixedSize(125,125);
    mSpeedGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::gray);
    bkg2->addColor(1.0,Qt::darkGray);

    mSpeedGauge->addArc(55);
    mSpeedGauge->addDegrees(65)->setValueRange(0,50);
    mSpeedGauge->addColorBand(50);

    mSpeedGauge->addValues(80)->setValueRange(0,50);

    mSpeedGauge->addLabel(70)->setText("Tr/min");
    QcLabelItem *lab = mSpeedGauge->addLabel(40);
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(0,50);
    mSpeedGauge->addBackground(7);
    mSpeedGauge->addGlass(88);

    tofGridLayout = new QGridLayout();

    tofGridLayout->addWidget(voltageLabel, 0, 0);
    tofGridLayout->addWidget(speedLabel, 0, 1);
    tofGridLayout->addWidget(tof1Label, 2, 0);
    tofGridLayout->addWidget(tof2Label, 2, 1);
    tofGridLayout->addWidget(tof3Label, 2, 2);

    tofGridLayout->addWidget(voltage, 1, 0);
    tofGridLayout->addWidget(mSpeedGauge, 1, 1);
    tofGridLayout->addWidget(tof1, 3, 0);
    tofGridLayout->addWidget(tof2, 3, 1);
    tofGridLayout->addWidget(tof3, 3, 2);

    logWidget = new LogWidget(tr("Logs :"),20);
    logDock = new QDockWidget(tr("Log panel :"), this);
    logDock->setWidget(logWidget);

    infoContainer = new QVBoxLayout();

    //Info side
    infoContainer->addWidget(infoLabel, 0, Qt::AlignCenter);
    infoContainer->insertStretch(1);

    infoContainer->addWidget(connectButton, 0, Qt::AlignCenter);
    infoContainer->insertStretch(3);
    infoContainer->addLayout(tofGridLayout);

    leftWidget = new QWidget(this);
    infoDock = new QDockWidget(tr("Informations panel :"), this);

    leftWidget->setLayout(infoContainer);

    infoDock->setWidget(leftWidget);

    addDockWidget(Qt::LeftDockWidgetArea, infoDock);
    addDockWidget(Qt::LeftDockWidgetArea, logDock);

    //Connect widgets to functions
    connect(connectButton, SIGNAL(clicked(bool)), this, SLOT(connectToRobot()));
}

void MainWindow::createActionSection()
{
    actionLabel = new QLabel(tr("Swarm2 commands"));
    QFont titreFont2 = actionLabel->font();
    titreFont2.setPointSize(25);
    actionLabel->setFont(titreFont2);

    actionContainer = new QVBoxLayout();

    //Command buttons
    actionButtonGrid = new QGridLayout();

    forward = new QPushButton(tr("Forward (Z)"));
    forward->setFixedSize(100,50);
    backward = new QPushButton(tr("Backward (S)"));
    backward->setFixedSize(100,50);
    left = new QPushButton(tr("Left (Q)"));
    left->setFixedSize(100,50);
    right = new QPushButton(tr("Right (D)"));
    right->setFixedSize(100,50);

    actionButtonGrid->addWidget(forward, 1, 1);
    actionButtonGrid->addWidget(left, 2, 0);
    actionButtonGrid->addWidget(right, 2, 2);
    actionButtonGrid->addWidget(backward, 3, 1);
    //End command buttons

    //Color Slider
    led1Label = new QLabel("Led 1 color :");
    led2Label = new QLabel("Led 2 color :");

    led1CW = new ColorWheel();
    led1CW->setMaximumSize(100,100);

    led2CW = new ColorWheel();
    led2CW->setMaximumSize(100,100);

    ledCWGrid = new QGridLayout();

    ledCWGrid->addWidget(led1Label, 0, 0);
    ledCWGrid->addWidget(led2Label, 0, 2);

    ledCWGrid->addWidget(led1CW, 1, 0);
    ledCWGrid->addWidget(led2CW, 1, 2);

    QObject::connect(led1CW, SIGNAL(colorChange(QColor)), this, SLOT(toTest(QColor)));

    //Action side
    actionContainer->addWidget(actionLabel, 0, Qt::AlignCenter);
    actionContainer->insertStretch(1);
    actionContainer->addLayout(ledCWGrid);
    actionContainer->insertStretch(3);
    actionContainer->addLayout(actionButtonGrid);
    actionContainer->insertStretch(5);

    actionDock = new QDockWidget(tr("Actions panel :"), this);
    rightWidget = new QWidget(this);

    rightWidget->setLayout(actionContainer);

    actionDock->setWidget(rightWidget);

    addDockWidget(Qt::RightDockWidgetArea, actionDock);

    connect(forward, SIGNAL(pressed()), this , SLOT(forwardAction()));
    connect(backward, SIGNAL(pressed()), this , SLOT(backwardAction()));
    connect(left, SIGNAL(pressed()), this , SLOT(leftAction()));
    connect(right, SIGNAL(pressed()), this , SLOT(rightAction()));

    connect(forward, SIGNAL(released()), this , SLOT(stopAction()));
    connect(backward, SIGNAL(released()), this , SLOT(stopAction()));
    connect(left, SIGNAL(released()), this , SLOT(stopAction()));
    connect(right, SIGNAL(released()), this , SLOT(stopAction()));
}

void MainWindow::createActions()
{
    settingsAct = new QAction(tr("&Settings"), this);
    settingsAct->setStatusTip(tr("Open settings"));
    connect(settingsAct, &QAction::triggered, this, &MainWindow::openSettingsSlot);

    //Hide or display actions
    displayHideActionSection = actionDock->toggleViewAction();
    displayHideActionSection->setText(tr("Hide/Show action side"));

    displayHideInfoSection = infoDock->toggleViewAction();
    displayHideInfoSection->setText(tr("Hide/Show info side"));

    displayHideLogSection = logDock->toggleViewAction();
    displayHideLogSection->setText(tr("Hide/Show logs"));

    about = new QAction(tr("&About Swarm2monitor"), this);
    about->setStatusTip(tr("About this software"));

    connect(about, &QAction::triggered, this, &MainWindow::aboutFunc);
}

void MainWindow::createMenuBar()
{
    option = menuBar()->addMenu(tr("&Option"));
    option->addAction(settingsAct);

    view = menuBar()->addMenu(tr("&View"));
    view->addAction(displayHideActionSection);
    view->addAction(displayHideInfoSection);
    view->addAction(displayHideLogSection);

    help = menuBar()->addMenu(tr("&Help"));
    help->addAction(about);
}

void MainWindow::openSettingsSlot()
{
    settingsDialog->exec();
    //We set new ipAdress for the robotInterface
    robotInterface.setRobotIpAndPort(userDataRef->getIpAddr(), userDataRef->getPort());
}

void MainWindow::aboutFunc()
{
    QMessageBox::about(this, tr("About Swarm2monitor"),
    tr("This software is a supplement to what is already existing around rtprog eco system<br>\
and is comming without any warranty of all kind<br>\
<br>Credits:<br>- The SpeedGauge was taken from (this is not my work) : <a href='https://github.com/Berrima/Qt-custom-gauge-widget/tree/master/examples/SpeedGauge'>https://github.com/Berrima/Qt-custom-gauge-widget/tree/master/examples/SpeedGauge</a><br>\
- The circle color picker was taken from (this is not my work) : <a href='https://github.com/liuyanghejerry/Qt-Plus'>https://github.com/liuyanghejerry/Qt-Plus</a><br>\
25/12/2017"));
}

void MainWindow::connectToRobot()
{
    //qDebug() << "Connecter";
    if(!robotInterface.isConnected())
    {
        logWidget->addLog("Connecting to " + userDataRef->getIpAddrWithPort() + " ...", LogWidget::LogColor::BLUE);
        //We connect the signals
        QObject::connect(&robotInterface, SIGNAL(robotConnected()), this, SLOT(changeConnectButton()));
        QObject::connect(&robotInterface, SIGNAL(tofValuesReceived(int,int,int)), this, SLOT(updateTofValues(int, int, int)));
        QObject::connect(&robotInterface, SIGNAL(batValuesReceived(int)), this, SLOT(updateBatValues(int)));
        robotInterface.connect();
    }
    else
    {
        //We close the connection to the robot
        robotInterface.disconnect();
        connectButton->setText(tr("&Connect"));
        connectButton->setStyleSheet("color : black;");

        logWidget->addLog("Disconnected", LogWidget::LogColor::ORANGE);
    }
}

//Change button title and color
void MainWindow::changeConnectButton()
{
    connectButton->setText(tr("&Disconnect"));
    connectButton->setStyleSheet("color : red;");
}

//Movement methods

void MainWindow::forwardAction()
{
    logWidget->addLog("Moving forward", LogWidget::LogColor::GREEN);
}

void MainWindow::backwardAction()
{
    logWidget->addLog("Moving backward", LogWidget::LogColor::GREEN);
}

void MainWindow::leftAction()
{
    logWidget->addLog("Turning left", LogWidget::LogColor::GREEN);
}

void MainWindow::rightAction()
{
    logWidget->addLog("Turning right", LogWidget::LogColor::GREEN);
}

void MainWindow::stopAction()
{
    logWidget->addLog("Stopping", LogWidget::LogColor::ORANGE);
}

//Bind keyboard keys to buttons

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        if(event->key() == Qt::Key_Z)
            forward->pressed();

        if(event->key() == Qt::Key_S)
            backward->pressed();

        if(event->key() == Qt::Key_Q)
            left->pressed();

        if(event->key() == Qt::Key_D)
            right->pressed();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        if(event->key() == Qt::Key_Z)
            forward->released();

        if(event->key() == Qt::Key_S)
            backward->released();

        if(event->key() == Qt::Key_Q)
            left->released();

        if(event->key() == Qt::Key_D)
            right->released();
    }
}

void MainWindow::updateTofValues(int tof1, int tof2, int tof3)
{
    this->tof1->display(tof1);
    this->tof2->display(tof2);
    this->tof3->display(tof3);
}

void MainWindow::updateBatValues(int bat)
{
    float vBat(((float)bat)/100.0);
    voltage->display(vBat);
    mSpeedNeedle->setCurrentValue(vBat*10.0);

    if(vBat < 4)
        voltage->setStyleSheet("color:red;");
    else
        voltage->setStyleSheet("color:green;");
}

void MainWindow::toTest(QColor color)
{
    logWidget->addLog("Color picked : "+QString::number(color.red())+" "+QString::number(color.green())+" "+QString::number(color.blue()),  LogWidget::LogColor::GREY);
}
