// SPDX-FileCopyrightText: 2021 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: MIT

#pragma once

#include <QtWidgets/QLineEdit>
#include <QAction>

class QClearLineEdit : public QLineEdit {

    public:
        QClearLineEdit (const QString& contents, QWidget* parent = nullptr);
        QClearLineEdit (QWidget* parent = nullptr);
       ~QClearLineEdit ();

        void            enableReturnPressedOnClear          ();

    public slots:
    protected:
    private:
};

