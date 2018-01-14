#include "logwidget.h"

//Constructeur
LogWidget::LogWidget(const QString &title, int maxHistory, QWidget *parent) : QGroupBox(parent)
{
    //We set the title of the log window
    setTitle(title);

    this->maxHistory = maxHistory;

    mainLayout = new QVBoxLayout();
    labelVBox = new QVBoxLayout();
    labelVBox->setSizeConstraint(QLayout::SetMinAndMaxSize);

    //Important we dont have any scroll bar if we don t use this
    scrollWidgetContainer = new QWidget();
    scrollWidgetContainer->setLayout(labelVBox);

    scrollArea = new QScrollArea();
    //To put the scroll bar at the bottom
    QScrollBar *scrollBar = scrollArea->verticalScrollBar();
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    scrollArea->setMinimumHeight(100);
    scrollArea->setWidget(scrollWidgetContainer);

    mainLayout->addWidget(scrollArea);

    buttonLabelLayout = new QHBoxLayout();

    buttonLabel = new QLabel(tr("Do you want to :"));
    clearButton = new QPushButton(tr("Clear logs"));

    buttonLabelLayout->addWidget(buttonLabel);
    buttonLabelLayout->addWidget(clearButton);

    mainLayout->addLayout(buttonLabelLayout);

    setLayout(mainLayout);

    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clearLogs()));
    connect(scrollBar, SIGNAL(rangeChanged(int,int)), this, SLOT(putScrollBarAtBottom(int ,int)));

}

//Destructeur
LogWidget::~LogWidget()
{

}

void LogWidget::addLog(QString const &log, LogColor color)
{
    QLabel *logLine = new QLabel(addColorToLog(log, color));
    logLine->setFixedHeight(15);
    labelPointerVector.push_back(logLine);
    labelVBox->addWidget(logLine, 0,Qt::AlignTop);

    //Remove logs when there is to many of them
    if(labelPointerVector.count() > maxHistory)
    {
        QLabel *ref;
        ref = labelPointerVector.first();
        labelPointerVector.removeFirst();
        labelVBox->removeWidget(ref);
        delete ref;
    }

}

void LogWidget::clearLogs()
{
    QVectorIterator<QLabel*> i(labelPointerVector);
    QLabel *ref;
    while(i.hasNext())
    {
       ref = i.next();
       labelVBox->removeWidget(ref);
       delete ref;
    }
    labelPointerVector.clear();

    addLog("Log cleared", LogColor::GREY);
}

void LogWidget::putScrollBarAtBottom(int min, int max)
{
    scrollArea->verticalScrollBar()->setValue(max);
}

QString LogWidget::addColorToLog(QString const &log, LogColor const color)
{
    QString ColoredLog;
    switch(color)
    {
          case LogColor::RED:
                ColoredLog.append("<font color=red>"+log+"</font>");
            break;
          case LogColor::GREEN:
                ColoredLog.append("<font color=green>"+log+"</font>");
            break;
          case LogColor::ORANGE:
                ColoredLog.append("<font color=orange>"+log+"</font>");
            break;
          case LogColor::BLUE:
                ColoredLog.append("<font color=blue>"+log+"</font>");
            break;
          case LogColor::GREY:
                ColoredLog.append("<font color=grey>"+log+"</font>");
            break;
    }

    return ColoredLog;
}
