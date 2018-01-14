#include "mainwindow.h"
#include "dataserializerunserializer.h"
#include "userdata.h"

#include <QWidget>
#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplashScreen splashScreen(QPixmap("images/splashPicture.png"));
    //Data serialisation stuff
    UserData userData;
    DataSerializerUnserializer ds("userData.xml", &userData);

    ds.readUserData();

    //app config
    app.setApplicationName("Swarm2monitor");

    /*QTranslator translator;
    translator.load(QString("french"));
    app.installTranslator(&translator);*/

    splashScreen.show();
    //We show a splash screen for 2 seconds
    QThread::sleep(2);

    MainWindow w(&userData);
    //Full ecran
    w.showMaximized();
    splashScreen.finish(&w);

    int retCode = app.exec();

    ds.writeUserData();

    return retCode;
}
