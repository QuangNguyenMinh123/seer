// SPDX-FileCopyrightText: 2021 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "QHistoryLineEdit.h"

//
// Extends QHistoryLineEdit to connect the 'lostFocus' signal with the
// 'execute' slot. This adds the current text to the history when
// focus is lost.
//

class SeerHistoryLineEdit : public QHistoryLineEdit {

    Q_OBJECT

    public:
        SeerHistoryLineEdit(const QString& contents, QWidget* parent = 0);
        SeerHistoryLineEdit(QWidget* parent = 0);
};

