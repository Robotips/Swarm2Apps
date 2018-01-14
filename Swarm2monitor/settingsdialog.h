#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QStackedWidget>

class SettingsDialog : public QDialog
{
    Q_OBJECT

    public:
        SettingsDialog(QWidget *parent = Q_NULLPTR);

    private:
        QHBoxLayout *mainHBOXLayout;

        //Left part
        QListWidget *leftCategList;

        //Right part
        QStackedWidget *tabWidgetStack;

        QTabWidget *robotTab;
        QTabWidget *softwareTab;
};

#endif // SETTINGSDIALOG_H
