#pragma once
#include <QtCore/QString>
#include <QtCore/QtCore>
#include <QtCore/QProcess>

class SeerOpenOCD: public QObject  {
    Q_OBJECT
    public:
        explicit SeerOpenOCD (QObject* parent = 0);
        ~SeerOpenOCD ();
    private:
        QProcess*   _openocdProcess;
        QString     _openocdProgram;
        QString     _openocdArguments;
};