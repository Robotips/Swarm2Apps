#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setMinimumSize(200,200);

    //We start the design
    mainHBOXLayout = new QHBoxLayout();

    leftCategList = new QListWidget();
    leftCategList->setUniformItemSizes(true);
    //List items
    /*new QListWidgetItem(tr("Robot configuration"),leftCategList);
    new QListWidgetItem(tr("Swarm2monitor prefs"),leftCategList);*/

    //We preselect one category
    QModelIndex index = leftCategList->model()->index(0,0, leftCategList->rootIndex());
    leftCategList->setCurrentIndex(index);

    //Right part
    tabWidgetStack = new QStackedWidget();

    /*robotTab = new QTabWidget();
    robotTab->addTab(new QLabel("Tab 1 robot"), "Tab 1");
    robotTab->addTab(new QLabel("Tab 2 robot"), "Tab 2");
    robotTab->addTab(new QLabel("Tab 3 robot"), "Tab 3");*/

    /*softwareTab = new QTabWidget();
    softwareTab->addTab(new QLabel("Tab 1 software"), "Tab 1");
    softwareTab->addTab(new QLabel("Tab 2 software"), "Tab 2");
    softwareTab->addTab(new QLabel("Tab 3 software"), "Tab 3");

    tabWidgetStack->addWidget(robotTab);
    tabWidgetStack->addWidget(softwareTab);*/

    mainHBOXLayout->addWidget(leftCategList);
    mainHBOXLayout->addWidget(tabWidgetStack);

    setLayout(mainHBOXLayout);

    //Bind list to stack widget ez peasy
    QObject::connect(leftCategList, SIGNAL(currentRowChanged(int)), tabWidgetStack, SLOT(setCurrentIndex(int)));
}

QTabWidget* SettingsDialog::addCategory(QString const &title)
{
    //We add the category
    new QListWidgetItem(title,leftCategList);

    //We create the new tab widget and we add it to the WidgetStack
    QTabWidget *tw = new QTabWidget(this);

    tabWidgetStack->addWidget(tw);

    return tw;
}
