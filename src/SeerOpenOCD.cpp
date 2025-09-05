#include "SeerOpenOCD.h"
#include <QMessageBox>
/***********************************************************************************************************************
 * Constructor                                                                                                         *
***********************************************************************************************************************/
SeerOpenOCD::SeerOpenOCD (QObject* parent): QObject(parent)
{
    // Start OpenOCD process
    _openocdProcess = new QProcess(parent);
    
}
/***********************************************************************************************************************
 * Destructor                                                                                                         *
***********************************************************************************************************************/
SeerOpenOCD::~SeerOpenOCD ()
{
    // Kill OpenOCD process

}
/***********************************************************************************************************************
 * startOpenOCD: Run a openOCD process, return true if on success, false if fail                                       *
 * Argument: QString command                                                                                           *
***********************************************************************************************************************/
bool startOpenOCD (const QString &command = nullptr)
{
    if (command == nullptr) {
        QMessageBox::warning(nullptr, QObject::tr("Seer"), QObject::tr("No OpenOCD command specified. Aborting."));
        return false;
    }
    return true;
}
/***********************************************************************************************************************
 * createConsole: Create a new console display for displaying openOCD log, return true if on success, false if fail    *
***********************************************************************************************************************/
bool createConsole ()
{
    return false;
}