#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QLCDNumber>

#include "robotipmodal.h"
#include "settingsdialog.h"
#include "userdata.h"
#include "logwidget.h"
#include "robotinterface.h"
#include "speedometer/qcgaugewidget.h"
#include "colorWheel/colorwheel.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(UserData *userData, QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void setIpAdress();
        void openSettingsSlot();
        void aboutFunc();
        void connectToRobot();

        void changeConnectButton();

        void toTest(QColor color);

        //Movements
        void forwardAction();
        void backwardAction();
        void leftAction();
        void rightAction();

        void stopAction();

        //Infos slots
        void updateTofValues(int tof1, int tof2, int tof3);
        void updateBatValues(int bat);

    private:
        UserData *userDataRef;

        RobotInterface robotInterface;

        QMenu *option;
        QMenu *view;
        QMenu *help;

        QAction *robotAddrAct;
        QAction *settingsAct;
        QAction *about;

        //Actions to display or hide the two sections
        QAction *displayHideActionSection;
        QAction *displayHideInfoSection;
        QAction *displayHideLogSection;

        RobotIpModal *robotIpModal;
        //Settings dialog window
        SettingsDialog *settingsDialog;

        QLabel *infoLabel;
        QLabel *actionLabel;

        QWidget *leftWidget;
        QWidget *rightWidget;

        QDockWidget *infoDock;
        QDockWidget *actionDock;
        QDockWidget *logDock;

        QVBoxLayout *infoContainer;
        QGridLayout *infoGrid;

        QVBoxLayout *actionContainer;

        //Widgets for the info section
        QPushButton *connectButton;

        QLabel *voltageLabel;
        QLCDNumber *voltage;

        //Laser range finder
        QLCDNumber *tof1;
        QLCDNumber *tof2;
        QLCDNumber *tof3;

        QLabel *tof1Label;
        QLabel *tof2Label;
        QLabel *tof3Label;

        QGridLayout *tofGridLayout;


        LogWidget *logWidget;
        //Speed meter widget
        QLabel *speedLabel;

        QcGaugeWidget * mSpeedGauge;
        QcNeedleItem *mSpeedNeedle;

        //Widgets for the action section
        QPushButton *forward;
        QPushButton *backward;
        QPushButton *left;
        QPushButton *right;

        QGridLayout *actionButtonGrid;

        //Color widget
        QLabel *led1Label;
        QLabel *led2Label;

        ColorWheel *led1CW;
        ColorWheel *led2CW;

        QGridLayout *ledCWGrid;

    protected:
        void createMenuBar();
        void createActions();
        void createInfoSection();
        void createActionSection();

        void keyPressEvent(QKeyEvent *event);

        void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
