// SPDX-FileCopyrightText: 2021 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "SeerKeySettings.h"
#include <QtWidgets/QWidget>
#include <QKeySequenceEdit>
#include <QMouseEvent>
#include <QtWidgets/QDialog>
#include <QShortcut>
#include <QtWidgets/QKeySequenceEdit>
#include <QtCore/QTimer>
#include "ui_SeerKeysConfigPage.h"
class KeySequencePopup;
class SeerKeysConfigPage;

class SeerKeysConfigPage : public QWidget, protected Ui::SeerKeysConfigPage {

    Q_OBJECT

    public:
        explicit SeerKeysConfigPage (QWidget* parent = 0);
       ~SeerKeysConfigPage ();

        void                        setKeySettings              (const SeerKeySettings& settings);
        SeerKeySettings             keySettings                 () const;

        void                        reset                       ();

    protected slots:

    private:
        void handleCellPressed(int row, int column);
};

class SeerKeySequencePopup : public QDialog {
    Q_OBJECT

    public:
        explicit SeerKeySequencePopup                           (QWidget* parent = nullptr);
        ~SeerKeySequencePopup                                   ();
        QString                     keySequenceString           () const;

    protected:
        void                        mousePressEvent             (QMouseEvent *event) override;
        void                        mouseDoubleClickEvent       (QMouseEvent *event) override;
        void                        keyPressEvent               (QKeyEvent *event) override;
        bool                        eventFilter                 (QObject *obj, QEvent *event) override;

    private:
        void                        handleTimerTimeout          ();
        bool                                                    _isDone = false;
        QTimer*                                                 _timer;             // Prevent capturing single-click on double-click event
        QShortcut*                                              _exit;
        QShortcut*                                              _enter;
        QLineEdit*                                              _keySequenceLineEdit;
        QString                                                 _keySequenceString;

};
