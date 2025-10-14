// SPDX-FileCopyrightText: 2021 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include "ui_SeerAdaExceptionsBrowserWidget.h"

class SeerAdaExceptionsBrowserWidget : public QWidget, protected Ui::SeerAdaExceptionsBrowserWidgetForm {

    Q_OBJECT

    public:
        explicit SeerAdaExceptionsBrowserWidget (QWidget* parent = 0);
       ~SeerAdaExceptionsBrowserWidget ();

    public slots:
        void                handleText                              (const QString& text);
        void                handleSessionTerminated                 ();
        void                refresh                                 ();

    protected slots:
        void                handleSearchLineEdit                    (const QString& text);
        void                handleAddCatchpointToolButtonClicked    ();

    signals:
        void                refreshAdaExceptions                    ();
        void                insertCatchpoint                        (QString catchpoint);

    protected:
        void                showEvent                               (QShowEvent* event);

    private:
};

