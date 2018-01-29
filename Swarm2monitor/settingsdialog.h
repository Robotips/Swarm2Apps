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
        //Constructor
        SettingsDialog(QWidget *parent = Q_NULLPTR);

        //This method creates a new category and returns a pointer pointing on the tabwidget associated with it
        QTabWidget *addCategory(QString const &title);

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
