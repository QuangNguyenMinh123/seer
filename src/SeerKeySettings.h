// SPDX-FileCopyrightText: 2021 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QtGui/QKeySequence>
#include <QtCore/QMap>
#include <QtCore/QStringList>
#include <QtCore/QString>

struct SeerKeySetting {

    SeerKeySetting(QString action, QKeySequence sequence, QString description) : _action(action), _sequence(sequence), _description(description) {}
    SeerKeySetting() {};

    QString         _action;
    QKeySequence    _sequence;
    QString         _description;
};


class SeerKeySettings {

    public:
        SeerKeySettings ();
        SeerKeySettings (const SeerKeySettings& other);
       ~SeerKeySettings ();

        SeerKeySettings& operator= (const SeerKeySettings& rhs);

        QStringList                             keys                () const;
        bool                                    has                 (const QString& action) const;
        SeerKeySetting                          get                 (const QString& action) const;
        void                                    add                 (const QString& action, const SeerKeySetting& setting);
        int                                     count               () const;

        static SeerKeySettings                  populate            ();

    private:
        QMap<QString, SeerKeySetting>          _keys;
};

