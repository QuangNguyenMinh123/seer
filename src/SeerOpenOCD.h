#pragma once
#include <QtCore/QString>
#include <QtCore/QtCore>
#include <QtCore/QProcess>

namespace SeerOpenOCD {
    // Start OpenOCD process
    bool startOpenOCD            (const QString &openocdExe = nullptr, const QString &command = nullptr);
    // Kill OpenOCD process
    void killOpenOCD            ();
    // Create Console displaying OpenOCD process logs
    bool createConsole           ();

};