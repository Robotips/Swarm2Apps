#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QtWidgets>

class LogWidget : public QGroupBox
{
    Q_OBJECT

    public:
        enum LogColor {RED, GREEN, ORANGE, BLUE, GREY};

        LogWidget(QString const &title, int maxHistory = 50, QWidget *parent = 0);
        ~LogWidget();

        void addLog(QString const &log, LogColor color);

    private slots:
        void clearLogs();
        void putScrollBarAtBottom(int min, int max);


    private:
        int maxHistory;
        QVector<QLabel *> labelPointerVector;

        //User interface
        QWidget *scrollWidgetContainer;
        QScrollArea *scrollArea;

        QLabel *buttonLabel;
        QPushButton *clearButton;

        //Layout
        QVBoxLayout *mainLayout;
        QHBoxLayout *buttonLabelLayout;
        QVBoxLayout *labelVBox;

        //Private methods
        QString addColorToLog(QString const &log, const LogColor color);

};

#endif // LOGWIDGET_H
