#include "SeerOpenOCD.h"
#include <QtCore/QtCore>
#include <QtCore/QProcess>
#include <QMessageBox>
static QProcess _openocdProcess;
static QString _openocdProgram;
static QString _openocdArguments;
/***********************************************************************************************************************
 * startOpenOCD: Run a openOCD process, return true if on success, false if fail                                       *
 * Argument: QString command                                                                                           *
***********************************************************************************************************************/
namespace SeerOpenOCD {
    bool startOpenOCD (const QString &openocdExe, const QString &command)
    {
        if (_openocdProcess.state() == QProcess::Running) {
            QMessageBox::warning(nullptr, QObject::tr("Seer"), QObject::tr("OpenOCD is already running."));
            return false;
        }
        if (command == nullptr) {
            QMessageBox::warning(nullptr, QObject::tr("Seer"), QObject::tr("No OpenOCD command is specified."));
            return false;
        }

        QStringList _command = QProcess::splitCommand(command);
        _command << "-l" << "/home/quangnm/Desktop/openocd.log";

        _openocdProcess.start(openocdExe, _command);

        return true;
    }

    void killOpenOCD ()
    {
        if (_openocdProcess.state() == QProcess::Running) {
            _openocdProcess.kill();
            _openocdProcess.waitForFinished();
        }
    }
    /***********************************************************************************************************************
     * createConsole: Create a new console display for displaying openOCD log, return true if on success, false if fail    *
    ***********************************************************************************************************************/
    bool createConsole ()
    {
        return false;
    }
}