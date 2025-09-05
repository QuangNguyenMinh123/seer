#pragma once
#include <QtCore/QString>
#include <QtCore/QtCore>
#include <QtCore/QProcess>

class SeerOpenOCD: public QObject  {
    Q_OBJECT
    public:
        explicit SeerOpenOCD (QObject* parent = nullptr);
        ~SeerOpenOCD ();
        // Start OpenOCD process
        bool                    startOpenOCD            (const QString &command = nullptr);
        // Create Console displaying OpenOCD process logs
        bool                    createConsole           ();

    private:
        QProcess*   _openocdProcess;
        QString     _openocdProgram;
        QString     _openocdArguments;
};