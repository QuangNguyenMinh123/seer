// SPDX-FileCopyrightText: 2021 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "SeerFunctionBrowserWidget.h"
#include "SeerBreakpointCreateDialog.h"
#include "SeerUtl.h"
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QTreeWidgetItemIterator>
#include <QtWidgets/QLabel>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>
#include <QtGui/QAction>
#include <QtCore/QFileInfo>
#include <QtCore/Qt>
#include <QtCore/QMap>
#include <QtCore/QDebug>

SeerFunctionBrowserWidget::SeerFunctionBrowserWidget (QWidget* parent) : QWidget(parent) {

    // Set the state.
    _id = Seer::createID();

    // Construct the UI.
    setupUi(this);

    // Setup the widgets
    functionSearchLineEdit->setPlaceholderText("Search regex...");
    functionSearchLineEdit->setClearButtonEnabled(true);

    functionTreeWidget->setMouseTracking(true);
    functionTreeWidget->setSortingEnabled(false);
    functionTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
  //functionTreeWidget->resizeColumnToContents(0); // Name
    functionTreeWidget->resizeColumnToContents(1); // Filename
    functionTreeWidget->resizeColumnToContents(2); // Line number
    functionTreeWidget->resizeColumnToContents(3); // Fullname
    functionTreeWidget->resizeColumnToContents(4); // Type
    functionTreeWidget->resizeColumnToContents(5); // Description
    functionTreeWidget->clear();

    // Connect things.
    QObject::connect(functionTreeWidget,      &QTreeWidget::itemDoubleClicked,              this,  &SeerFunctionBrowserWidget::handleItemDoubleClicked);
    QObject::connect(functionTreeWidget,      &QTreeWidget::itemEntered,                    this,  &SeerFunctionBrowserWidget::handleItemEntered);
    QObject::connect(functionTreeWidget,      &QTreeWidget::customContextMenuRequested,     this,  &SeerFunctionBrowserWidget::handleContextMenu);
    QObject::connect(functionSearchLineEdit,  &QLineEdit::returnPressed,                    this,  &SeerFunctionBrowserWidget::handleSearchLineEdit);
}

SeerFunctionBrowserWidget::~SeerFunctionBrowserWidget () {
}

void SeerFunctionBrowserWidget::handleText (const QString& text) {

    QApplication::setOverrideCursor(Qt::BusyCursor);

    if (text.startsWith(QString::number(_id) + "^done,symbols={") && text.endsWith("}")) {

        functionTreeWidget->clear();
        functionTreeWidget->setSortingEnabled(false);
        functionTreeWidget->sortByColumn(-1, Qt::AscendingOrder);

        // -symbol-info-functions
        // ^done,symbols={
        //          debug=[
        //                  {
        //                      filename="elf-init.c",
        //                      fullname="/home/abuild/rpmbuild/BUILD/glibc-2.31/csu/elf-init.c",
        //                      symbols=[
        //                                  {
        //                                      line="95",
        //                                      name="__libc_csu_fini",
        //                                      type="void (void)",
        //                                      description="void __libc_csu_fini(void);"
        //                                  },
        //                                  {
        //                                      line="67",
        //                                      name="__libc_csu_init",
        //                                      type="void (int, char **, char **)",
        //                                      description="void __libc_csu_init(int, char **, char **);"
        //                                  }
        //                              ]
        //                  },
        //                  ...
        //                ]
        //              }

        QString debug_text = Seer::parseFirst(text, "debug=", '[', ']', false);

        QStringList filenames_list = Seer::parse(debug_text, "", '{', '}', false);

        for (const auto& filename_entry : filenames_list) {

            QString filename_text = Seer::parseFirst(filename_entry, "filename=", '"', '"', false);
            QString fullname_text = Seer::parseFirst(filename_entry, "fullname=", '"', '"', false);

            QString symbols_text = Seer::parseFirst(filename_entry, "symbols=", '[', ']', false);

            QStringList symbols_list = Seer::parse(symbols_text, "", '{', '}', false);

            for (const auto& symbol_entry : symbols_list) {

                QString line_text        = Seer::parseFirst(symbol_entry, "line=", '"', '"', false);
                QString name_text        = Seer::parseFirst(symbol_entry, "name=", '"', '"', false);
                QString type_text        = Seer::parseFirst(symbol_entry, "type=", '"', '"', false);
                QString description_text = Seer::parseFirst(symbol_entry, "type=", '"', '"', false);

                // Skip function entries that have no line number.
                if (line_text == "") {
                    continue;
                }

                // Add the function to the tree.
                QTreeWidgetItem* item = new QTreeWidgetItem;

                QFont f0 = item->font(0);
                f0.setBold(true);
                item->setFont(0,f0);

                item->setText(0, name_text);
                item->setText(1, filename_text);
                item->setText(2, line_text);
                item->setText(3, fullname_text);
                item->setText(4, type_text);
                item->setText(5, description_text);

                functionTreeWidget->addTopLevelItem(item);
            }
        }

        // ----

        // -symbol-info-functions
        // ^done,symbols={
        //          nondebug=[
        //                      {address="0x0000555555554720",name="putchar@plt"},
        //                      {address="0x00007ffff7c40031",name="putchar[cold]"},
        //                      {address="0x00007ffff7c9561e",name="putchar"},
        //                      {address="0x00007ffff7c9579e",name="putchar_unlocked"}
        //                   ]
        //               }

        QString nondebug_text = Seer::parseFirst(text, "nondebug=", '[', ']', false);

        QStringList nondebug_list = Seer::parse(nondebug_text, "", '{', '}', false);

        for (const auto& nondebug_entry : nondebug_list) {

            QString address_text = Seer::parseFirst(nondebug_entry, "address=", '"', '"', false);
            QString name_text    = Seer::parseFirst(nondebug_entry, "name=",    '"', '"', false);

            // Add the function to the tree.
            QTreeWidgetItem* item = new QTreeWidgetItem;

            QFont f0 = item->font(0);
            f0.setBold(true);
            item->setFont(0,f0);

            item->setText(0, name_text);
            item->setText(1, address_text);

            functionTreeWidget->addTopLevelItem(item);
        }

    }else{
        // Ignore others.
    }

  //functionTreeWidget->resizeColumnToContents(0);
    functionTreeWidget->resizeColumnToContents(1);
    functionTreeWidget->resizeColumnToContents(2);
    functionTreeWidget->resizeColumnToContents(3);
    functionTreeWidget->resizeColumnToContents(4);
    functionTreeWidget->resizeColumnToContents(5);
    functionTreeWidget->sortByColumn(0, Qt::AscendingOrder);
    functionTreeWidget->setSortingEnabled(true);

    QApplication::restoreOverrideCursor();
}

void SeerFunctionBrowserWidget::handleSessionTerminated () {

    // Delete previous contents.
    functionTreeWidget->clear();
}

void SeerFunctionBrowserWidget::handleItemDoubleClicked (QTreeWidgetItem* item, int column) {

    Q_UNUSED(column);

    emit selectedFile(item->text(1), item->text(3), item->text(2).toInt());
}

void SeerFunctionBrowserWidget::handleItemEntered (QTreeWidgetItem* item, int column) {

    Q_UNUSED(column);

    QString tip = QString("Function: %1\nFile: %2\nLine: %3\nFullname: %4\nType: %5\nDescription: %6").arg(item->text(0)).arg(item->text(1)).arg(item->text(2)).arg(item->text(3)).arg(item->text(4)).arg(item->text(5));

    item->setToolTip(0, tip);

    for (int i=1; i<functionTreeWidget->columnCount(); i++) { // Copy tooltip to the other columns.
        item->setToolTip(i, item->toolTip(0));
    }
}

void SeerFunctionBrowserWidget::handleSearchLineEdit () {

    functionTreeWidget->clear();
    functionTreeWidget->setSortingEnabled(false);
    functionTreeWidget->sortByColumn(-1, Qt::AscendingOrder);

  //functionTreeWidget->resizeColumnToContents(0);
    functionTreeWidget->resizeColumnToContents(1);
    functionTreeWidget->resizeColumnToContents(2);
    functionTreeWidget->resizeColumnToContents(3);
    functionTreeWidget->resizeColumnToContents(4);
    functionTreeWidget->resizeColumnToContents(5);

    if (functionSearchLineEdit->text() != "") {
        emit refreshFunctionList(_id, functionSearchLineEdit->text());
    }
}

void SeerFunctionBrowserWidget::refresh () {
    handleSearchLineEdit();
}

void SeerFunctionBrowserWidget::handleContextMenu (const QPoint& pos) {

    // Get the item at the cursor.
    QTreeWidgetItem* item = functionTreeWidget->itemAt(pos);

    if (item == 0) {
        return;
    }

    // Create the menu actions.
    QAction* createBreakpointAction;

    createBreakpointAction = new QAction(QIcon(":/seer/resources/RelaxLightIcons/document-new.svg"),
                                         QString("Create breakpoint in function: \"%1\"").arg(item->text(0)),
                                         this);

    QMenu menu("Breakpoints", this);
    menu.setTitle("Breakpoints");
    menu.addAction(createBreakpointAction);

    // Launch the menu. Get the response.
    QAction* action = menu.exec(functionTreeWidget->mapToGlobal(pos));

    // Do nothing.
    if (action == 0) {
        return;
    }

    if (action == createBreakpointAction) {

        SeerBreakpointCreateDialog dlg(this);
        dlg.setFunctionName(item->text(0));
        dlg.setLineNumber(item->text(2));
        dlg.setFilename(item->text(3));

        int ret = dlg.exec();

        if (ret == 0) {
            return;
        }

        // Emit the create breakpoint signal.
        emit insertBreakpoint(dlg.breakpointText());

        return;
    }
}

