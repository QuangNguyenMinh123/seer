// SPDX-FileCopyrightText: 2021 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include "ui_SeerStackLocalsBrowserWidget.h"

class SeerStackLocalsBrowserWidget : public QWidget, protected Ui::SeerStackLocalsBrowserWidgetForm {

    Q_OBJECT

    public:
        explicit SeerStackLocalsBrowserWidget (QWidget* parent = 0);
       ~SeerStackLocalsBrowserWidget ();

    public slots:
        void                handleText                          (const QString& text);
        void                handleStoppingPointReached          ();
        void                handleSessionTerminated             ();
        void                refresh                             ();

    protected slots:
        void                handleContextMenu                   (const QPoint&    pos);
        void                handleItemExpanded                  (QTreeWidgetItem* item);
        void                handleItemCollapsed                 (QTreeWidgetItem* item);
        void                handleItemEntered                   (QTreeWidgetItem* item, int column);

    signals:
        void                refreshStackLocals                  ();
        void                addVariableLoggerExpression         (QString expression);
        void                addVariableTrackerExpression        (QString expression);
        void                refreshVariableTrackerValues        ();
        void                addMemoryVisualizer                 (QString expression);
        void                addArrayVisualizer                  (QString expression);
        void                addMatrixVisualizer                 (QString expression);
        void                addStructVisualizer                 (QString expression);

    protected:
        void                handleItemCreate                    (QTreeWidgetItem* parentItem, const QString& name_text, const QString& arg_text, const QString& value_text);
        void                showEvent                           (QShowEvent* event);

    private:
        int                 _frameNumber;
};

