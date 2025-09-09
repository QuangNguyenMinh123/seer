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
            explicit SeerOpenOCDWidget  (QWidget* parent = 0);
            ~SeerOpenOCDWidget ();
            // Start & kill OpenOCD process
            bool startOpenOCD           (const QString &openocdExe, const QString &command);
            void killOpenOCD            ();
            // Create & kill Console displaying OpenOCD process logs
            bool createConsole          (QDetachTabWidget* parent);
            bool killConsole            ();
            void setConsoleVisible      (bool flag);
            // Getters & Setters
            void newWidget              ();

        signals:
            void openocdDisconnect      ();
            void openocdStartFailed     ();

        private slots:
            void handleReadOutput       ();
            void handleReadError        ();
    };
namespace SeerOpenOCDWidgetNp{
    SeerOpenOCDWidget* getOpenOCDWidget();
    SeerOpenOCDWidget* setOpenOCDWidget(SeerOpenOCDWidget* widget);
}