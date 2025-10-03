#pragma once
#include <QtCore/QString>
#include <QtCore/QtCore>
#include <QtCore/QProcess>
#include <QtWidgets/QWidget>
#include "QDetachTabWidget.h"
#include "SeerLogWidget.h"
/***********************************************************************************************************************
 * 
 **********************************************************************************************************************/
class SeerOpenOCDWidget: public SeerLogWidget{
    Q_OBJECT
    public:
        explicit SeerOpenOCDWidget          (QWidget* parent = 0);
        ~SeerOpenOCDWidget                  ();
        void newOpenOCDWidget               ();
        // Start & kill OpenOCD process
        bool startOpenOCD                   (const QString &openocdExe, const QString &command);
        void killOpenOCD                    ();
        bool isOpenocdRunning               ();
        // Create & kill Console displaying OpenOCD process logs
        void createOpenOCDConsole           (QDetachTabWidget* parent);
        void killConsole                    ();
        void setConsoleVisible              (bool flag);
        // Getters & Setters
        SeerLogWidget* openocdConsole              ();
        SeerOpenOCDWidget* getOpenOCDWidget ();
        SeerOpenOCDWidget* setOpenOCDWidget (SeerOpenOCDWidget* widget);
        QProcess* openocdProcess();
        
    signals:
        void openocdDisconnect              ();
        void openocdStartFailed             ();

    private slots:
        void handleReadOutput               ();
        void handleReadError                ();

    private:
        QProcess*                           _openocdProcess;
        QString                             _openocdArguments;
        SeerLogWidget*                      _openocdlogsTabWidget;
};