// SPDX-FileCopyrightText: 2021 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "SeerKeysConfigPage.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtCore/QDebug>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <iostream>
using namespace std;

SeerKeysConfigPage::SeerKeysConfigPage(QWidget* parent) : QWidget(parent) {

    // Set up the UI.
    setupUi(this);
    keysTableWidget->setColumnCount(3);
    keysTableWidget->setColumnHidden(2, true);              // Hide the Suffix column
    // Connect things.
    QObject::connect(keysTableWidget, &QTableWidget::cellPressed, this, &SeerKeysConfigPage::handleCellPressed);

    reset();
}

SeerKeysConfigPage::~SeerKeysConfigPage() {
}

void SeerKeysConfigPage::setKeySettings (const SeerKeySettings& settings) {

    // Clear the table contents.
    keysTableWidget->setRowCount(0);

    // Get a list of keys from the highlighter.
    QStringList keys = settings.keys();

    // Loop through each key and get its info.
    // Construct a table entry.
    for (int r=0; r<keys.size(); r++) {

        QString key = keys[r];

        SeerKeySetting setting = settings.get(key);

        keysTableWidget->insertRow(r);

        // Insert the KeySequence editor.
        QLabel* keySequence = new QLabel(setting._sequence.toString());
        keysTableWidget->setCellWidget(r, 0, keySequence);
        // keysTableWidget->viewport()->installEventFilter(this);

        // Insert the Description.
        QLabel* descriptionLabel = new QLabel(setting._description);
        keysTableWidget->setCellWidget(r, 1, descriptionLabel);

        // Insert suffix but make it invisible
        QLabel* suffixLabel = new QLabel(setting._suffix);
        keysTableWidget->setCellWidget(r, 2, suffixLabel);
    }

    keysTableWidget->setVerticalHeaderLabels(keys);

    keysTableWidget->resizeColumnToContents(0); // KeySequence
    keysTableWidget->resizeColumnToContents(1); // Description
}

SeerKeySettings SeerKeysConfigPage::keySettings() const {

    SeerKeySettings settings;

    for (int r=0; r<keysTableWidget->rowCount(); r++) {

        // Get the key (label) for this row.
        QString key = keysTableWidget->verticalHeaderItem(r)->text();

        // Get widgets for this row.
        QKeySequenceEdit* keySequenceEdit  = dynamic_cast<QKeySequenceEdit*>(keysTableWidget->cellWidget(r,0));
        QLabel*           descriptionLabel = dynamic_cast<QLabel*>(keysTableWidget->cellWidget(r,1));
        QLabel*           suffix           = dynamic_cast<QLabel*>(keysTableWidget->cellWidget(r,2));

        // Create key setting.
        if (keySequenceEdit != 0 && descriptionLabel != 0) {

            SeerKeySetting setting(key, keySequenceEdit->keySequence(), descriptionLabel->text(), suffix->text());

            // Add the setting to our settings.
            settings.add(key, setting);

        }else{

            if (keySequenceEdit == 0) {
                qDebug() << "QKeySequenceEdit for row" << r << "is null!";
            }

            if (descriptionLabel == 0) {
                qDebug() << "QLabel for row" << r << "is null!";
            }
        }
    }

    return settings;
}

void SeerKeysConfigPage::reset () {

    setKeySettings(SeerKeySettings::populate());
}

void SeerKeysConfigPage::handleCellPressed(int row, int column) {
    if (column != 0)
        return;

    // SeerKeySetting keySetting;

    // QWidget* widget = keysTableWidget->cellWidget(row, 2);
    // QLabel* label = qobject_cast<QLabel*>(widget);
    // if (label) {
    //     keySetting._suffix = label->text();
    // }

    // widget = keysTableWidget->cellWidget(row, 0);
    // label = qobject_cast<QLabel*>(widget);
    // if (label) {
    //     keySetting._sequence = label->text();
    // }

    
    SeerKeySequencePopup* popup = new SeerKeySequencePopup(this);
    popup->setWindowModality(Qt::ApplicationModal);
    // popup->setAttribute(Qt::WA_DeleteOnClose);

    int ret = popup->exec();
    if (ret == 0)       // Reject
        return;

    QString keySequenceString = popup->keySequenceString();
    QLabel* widget = dynamic_cast<QLabel*>(keysTableWidget->cellWidget(row, 0));
    if (widget) {
        widget->setText(keySequenceString);
    }
}

SeerKeySequencePopup::SeerKeySequencePopup(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Edit Shortcut");
    setAttribute(Qt::WA_DeleteOnClose);
    resize(320, 180);

    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Press the desired key combination\nPress ESC to cancel\nPress Backspace to clear\nPress Enter to confirm", this));
    _keySequenceLineEdit = new QLineEdit(this);
    layout->addWidget(_keySequenceLineEdit);
    _keySequenceLineEdit->setReadOnly(true);
    _keySequenceLineEdit->installEventFilter(this);

    // _exit = new QShortcut(QKeySequence(tr("ESC")), this);
    // _enter = new QShortcut(QKeySequence(tr("Return")), this);
    // connect(_exit,  &QShortcut::activated, this, &QDialog::reject);
    // connect(_enter, &QShortcut::activated, this, &QDialog::accept);

    _enter = new QShortcut(QKeySequence(Qt::Key_Return), this);
    _exit  = new QShortcut(QKeySequence(Qt::Key_Escape), this);

    connect(_enter, &QShortcut::activated, this, &QDialog::accept);
    connect(_exit,  &QShortcut::activated, this, &QDialog::reject);
}

SeerKeySequencePopup::~SeerKeySequencePopup() {
}

void SeerKeySequencePopup::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && !_isDone) {
        // Start a Timer, only triggered on single click
        _timer = new QTimer(this);
        connect(_timer, &QTimer::timeout, this, &SeerKeySequencePopup::handleTimerTimeout);
        _timer->start(400);  // Start the timer with a 400ms interval = Qt default time to trigger mousePressEvent
    }
}

void SeerKeySequencePopup::handleTimerTimeout() {
    _timer->stop();
    if (!_isDone) {
        if (!_keySequenceString.endsWith("Click") && !_keySequenceString.endsWith("DoubleClick")) {
                if (!_keySequenceString.isEmpty())
                _keySequenceString += "+";
            _keySequenceString += "Click";
            _keySequenceLineEdit->setText(_keySequenceString);
            _isDone = true;
        }
    }
}

void SeerKeySequencePopup::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && !_isDone) {
        // Append Double Click to key sequence. If ends with Click or DoubleClick, return.
        if (!_keySequenceString.endsWith("DoubleClick") && !_keySequenceString.endsWith("Click")) {
            if (!_keySequenceString.isEmpty())
                _keySequenceString += "+";
            _keySequenceString += "DoubleClick";
            _keySequenceLineEdit->setText(_keySequenceString);
            _isDone = true;
        }
    }
}

QString SeerKeySequencePopup::keySequenceString() const {
    return _keySequenceString;
}

void SeerKeySequencePopup::keyPressEvent(QKeyEvent *event) {
    if ( _isDone)
        return;

    // Reject special cases: number
    if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) {
        return;
    }

    Qt::KeyboardModifiers mods = event->modifiers();
    int key = event->key();
    QKeySequence seq(mods | key);
    QString keyText = seq.toString(QKeySequence::PortableText);

    if (event->key() == Qt::Key_Control) {
        keyText = "Ctrl";
    }
    if (event->key() == Qt::Key_Alt) {
        keyText = "Alt";
    }
    if (event->key() == Qt::Key_Shift) {
        keyText = "Shift";
    }

    if (_keySequenceString.contains(keyText)) {
        // Avoid adding duplicate modifiers
        return;
    }
    if (_keySequenceString != "")
    {
        if (_keySequenceString.endsWith("Click") || _keySequenceString.endsWith("DoubleClick")
        || _keySequenceString.back().isUpper() ) {
            // Avoid adding modifiers after Click or DoubleClick
            // Avoid adding modifiers after uppercase letter
            _isDone = true;
            return;
        }
    }
    
    if (!_keySequenceString.isEmpty())
        _keySequenceString += "+";
    
    _keySequenceString += keyText;

    _keySequenceLineEdit->setText(_keySequenceString);
    
}

bool SeerKeySequencePopup::eventFilter(QObject *obj, QEvent *event) {
    if (obj == _keySequenceLineEdit) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Backspace) {
                _keySequenceString = "";
                _keySequenceLineEdit->setText(_keySequenceString);
                _isDone = false;
            }
            else
                keyPressEvent(keyEvent);
        }
    }
    return false;
}