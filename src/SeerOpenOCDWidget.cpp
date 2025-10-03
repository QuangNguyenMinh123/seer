#include "SeerOpenOCDWidget.h"
#include <QtCore/QtCore>
#include <QtCore/QProcess>
#include <QMessageBox>
/***********************************************************************************************************************
 * Constructor & Destructor                                                                                           *
 **********************************************************************************************************************/
SeerOpenOCDWidget::SeerOpenOCDWidget (QWidget* parent) {
    Q_UNUSED(parent);
    _openocdProcess = new QProcess(this);
    _openocdArguments = "";
    _openocdlogsTabWidget = nullptr;
}

SeerOpenOCDWidget::~SeerOpenOCDWidget (){
    killOpenOCD();
}

void SeerOpenOCDWidget::newOpenOCDWidget (){
    if (!_openocdProcess)
        _openocdProcess = new QProcess(this);
    _openocdArguments = "";
    _openocdlogsTabWidget = nullptr;
}

QProcess* SeerOpenOCDWidget::openocdProcess()
{
    return _openocdProcess;
}
/***********************************************************************************************************************
 * startOpenOCD: Run a openOCD process, return true if on success, false if fail                                       *
 * Argument: QString command                                                                                           *
 **********************************************************************************************************************/
bool SeerOpenOCDWidget::startOpenOCD (const QString &openocdExe, const QString &command)
{
    if (_openocdProcess->state() == QProcess::Running) {
        QMessageBox::warning(nullptr, QObject::tr("Seer"), QObject::tr("OpenOCD is already running."));
        return false;
    }
    if (command == nullptr) {
        QMessageBox::warning(nullptr, QObject::tr("Seer"), QObject::tr("No OpenOCD command is specified."));
        return false;
    }
    if (_openocdProcess->state() == QProcess::NotRunning) {
        QStringList _command = QProcess::splitCommand(command);
        _openocdProcess->start(openocdExe, _command);
        return true;
    }
    return false;
}

void SeerOpenOCDWidget::killOpenOCD ()
{
    if (_openocdProcess)
    {
        if (_openocdProcess->state() == QProcess::Running) {
            _openocdProcess->kill();
             _openocdProcess->waitForFinished();
            delete _openocdProcess;
            _openocdProcess = nullptr;
        }
    }
}

bool SeerOpenOCDWidget::isOpenocdRunning ()
{
    if (_openocdProcess)
        if (_openocdProcess->state() == QProcess::Running) {
            return true;
        }
    return false;
}
/***********************************************************************************************************************
 * Create a new console display for displaying openOCD log                                                             *
 **********************************************************************************************************************/
void SeerOpenOCDWidget::createOpenOCDConsole (QDetachTabWidget* parent)
{
    if (_openocdlogsTabWidget != nullptr) {
        return;
    }
    _openocdlogsTabWidget = new SeerLogWidget();
    parent->addTab(_openocdlogsTabWidget, "OpenOCD output");
    _openocdlogsTabWidget->setPlaceholderText("[OpenOCD output]");
    _openocdlogsTabWidget->setLogEnabled(true);
    connect(_openocdProcess, &QProcess::readyReadStandardOutput, this, &SeerOpenOCDWidget::handleReadOutput);
    connect(_openocdProcess, &QProcess::readyReadStandardError, this, &SeerOpenOCDWidget::handleReadError);
}

SeerLogWidget* SeerOpenOCDWidget::openocdConsole()
{
    return _openocdlogsTabWidget;
}

void SeerOpenOCDWidget::killConsole ()
{
    delete _openocdlogsTabWidget;
    _openocdlogsTabWidget = nullptr;
}

void SeerOpenOCDWidget::setConsoleVisible (bool flag)
{
    _openocdlogsTabWidget->setVisible(flag);
}
/***********************************************************************************************************************
 * Slot                                                                                                                *
 **********************************************************************************************************************/
void SeerOpenOCDWidget::handleReadOutput ()
{
    QString Text = QString::fromLocal8Bit(_openocdProcess->readAllStandardOutput());
    _openocdlogsTabWidget->handleText(Text);
}

void SeerOpenOCDWidget::handleReadError ()
{
    QString Text = QString::fromLocal8Bit(_openocdProcess->readAllStandardError());
    // If OpenOCD fails to start because the port is already in use, emit openocdTerminate signal
    if (Text.contains("Error: couldn't bind tcl to socket on port") || \
        Text.contains("Error: JTAG scan chain interrogation failed: all zeroes") || \
        Text.contains("Error: Invalid ACK (0) in DAP response") || \
        Text.contains("Error: Receiving data from device timed out") || \
        Text.contains("Error: attempted 'gdb' connection rejected"))
    {
        QMessageBox::warning(nullptr, QObject::tr("Seer"), QObject::tr("OpenOCD failed to start. \nCheck openOCD output for details."));
        killOpenOCD();
        emit openocdStartFailed();
    }
    _openocdlogsTabWidget->handleText(Text);
}
