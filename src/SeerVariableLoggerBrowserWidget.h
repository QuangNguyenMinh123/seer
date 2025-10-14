// SPDX-FileCopyrightText: 2021 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include <QtCore/QSet>
#include "ui_SeerVariableLoggerBrowserWidget.h"

class SeerVariableLoggerBrowserWidget : public QWidget, protected Ui::SeerVariableLoggerBrowserWidgetForm {

    Q_OBJECT

    public:
        explicit SeerVariableLoggerBrowserWidget (QWidget* parent = 0);
       ~SeerVariableLoggerBrowserWidget ();

    public slots:
        void                handleText                          (const QString& text);
        void                handleSessionTerminated             ();
        void                handleEvaluateVariableExpression    (int expressionid, QString expression);
        void                addVariableExpression               (QString expression);

    private slots:
        void                handleAddLineEdit                   ();
        void                handleDeleteToolButton              ();
        void                handleDeleteAllToolButton           ();
        void                handleItemEntered                   (QTreeWidgetItem* item, int column);
        void                handleItemExpanded                  (QTreeWidgetItem* item);
        void                handleItemCollapsed                 (QTreeWidgetItem* item);
        void                handleContextMenu                   (const QPoint& pos);

    signals:
        void                evaluateVariableExpression          (int expressionid, QString expression);
        void                addMemoryVisualizer                 (QString expression);
        void                addArrayVisualizer                  (QString expression);
        void                addMatrixVisualizer                 (QString expression);
        void                addStructVisualizer                 (QString expression);
        void                raiseTab                            ();

    protected:
        void                handleItemCreate                    (QTreeWidgetItem* parentItem, const QString& id_text, const QString& timestamp_text, const QString& name_text, const QString& value_text);

    private:
        QSet<int>           _ids;

};

