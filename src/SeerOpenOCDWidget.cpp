#include "SeerOpenOCDWidget.h"

#include <QtCore/QtCore>
#include <QtCore/QProcess>
#include <QMessageBox>
static QProcess _openocdProcess;
static QString _openocdProgram;
static QString _openocdArguments;
SeerLogWidget* _openocdlogsTabWidget;
/***********************************************************************************************************************
 * Constructor & Destructor                                                                                           *
***********************************************************************************************************************/
SeerOpenOCDWidget::SeerOpenOCDWidget (QWidget* parent) : SeerLogWidget(parent) {
    _openocdProcess = new QProcess(this);
    _openocdProgram = "";
    _openocdArguments = "";
}
SeerOpenOCDWidget::~SeerOpenOCDWidget (){
    killOpenOCD();
    delete _openocdProcess;
}
/***********************************************************************************************************************
 * startOpenOCD: Run a openOCD process, return true if on success, false if fail                                       *
 * Argument: QString command                                                                                           *
***********************************************************************************************************************/
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
        QString _commandline = _command.join(", ");
        _openocdlogsTabWidget->handleText(QString("OpenOCD command:" + _commandline + "\n"));
        return true;
    }
    return false;
}

void SeerOpenOCDWidget::killOpenOCD ()
{
    if (_openocdProcess->state() == QProcess::Running) {
        _openocdProcess->kill();
        _openocdProcess->waitForFinished();
    }
}
/***********************************************************************************************************************
 * createConsole: Create a new console display for displaying openOCD log, return true if on success, false if fail    *
***********************************************************************************************************************/
bool SeerOpenOCDWidget::createConsole (QDetachTabWidget* parent)
{
    _openocdlogsTabWidget = new SeerLogWidget();
    parent->addTab(_openocdlogsTabWidget, "OpenOCD output");
    _openocdlogsTabWidget->setPlaceholderText("[OpenOCD output]");
    _openocdlogsTabWidget->setLogEnabled(true);
    connect(_openocdProcess, &QProcess::readyReadStandardOutput, this, &SeerOpenOCDWidget::handleReadOutput);
    connect(_openocdProcess, &QProcess::readyReadStandardError, this, &SeerOpenOCDWidget::handleReadError);
    return false;
}

bool SeerOpenOCDWidget::killConsole ()
{
    
    return false;
}

void SeerOpenOCDWidget::setConsoleVisible (bool flag)
{
    _openocdlogsTabWidget->setVisible(flag);
}
/***********************************************************************************************************************
 * Slot                                                                                                                *
***********************************************************************************************************************/
void SeerOpenOCDWidget::handleReadOutput ()
{
    _openocdlogsTabWidget->handleText(QString::fromLocal8Bit(_openocdProcess->readAllStandardOutput()));
}

void SeerOpenOCDWidget::handleReadError ()
{
    _openocdlogsTabWidget->handleText(QString::fromLocal8Bit(_openocdProcess->readAllStandardError()));
}


