/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2020 Giles Bathgate
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTextStream>
#include <QTemporaryFile>

#include "codeeditor.h"
#include "texteditiodevice.h"
#include "backgroundworker.h"
#include "preferencesdialog.h"
#include "interactive.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() override;
	void loadFiles(const QStringList&);
protected:
	void closeEvent(QCloseEvent*) override;
private slots:
	void getDefaultViewport() const;
	void setDefaultViewport();
	void grabFrameBuffer();
	void showPreferences();
	void disableRulers(bool);
	static void enableCaches(bool);
	void clipboardDataChanged();
	bool maybeSave(bool);
	void newFile();
	bool saveFile();
	bool saveAsFile();
	bool saveAllFiles();
	bool closeCurrentFile();
	bool closeFile(int);
	void openFile();
	void compileAndRender();
	void compileAndGenerate();
	void evaluationDone();
	void setTabTitle(const QString&);
	void undo();
	void redo();
	void increaseSelectionIndent();
	void decreaseSelectionIndent();
	void cut();
	void copy();
	void paste();
	void tabChanged(int);
	static void print();
	static void showAbout();
	void showAboutQt();
	void showBuiltins();
	static void showUserGuide();
	static void flushCaches();
	void sendToCAM();
	void exportFile(const QString&);
	void preferencesUpdated();
private:
	void compileOrGenerate(bool generate);
	void loadPreferences();
	void savePreferences();
	void setupLayout();
	void setupActions();
	void setupExportActions();
	void setupViewActions();
	void setupEditor(CodeEditor*);
	void setupTabs(QTabWidget*) const;
	void setupConsole();
	void setupTreeview();
	CodeEditor* currentEditor();
	CodeEditor* getEditor(int i);
	void disableActions(CodeEditor*);
	bool saveSelectedFiles(const QList<QString>&);
	void deleteTempFiles();

	Ui::MainWindow* ui;
	QStandardItemModel* treeModel;
	TextEditIODevice* console;
	QTextStream* output;
	Reporter* reporter;
	BackgroundWorker* worker;
	Interactive* interact;
	PreferencesDialog* preferencesDialog;
	QList<QTemporaryFile*> temporyFiles;
};

#endif // MAINWINDOW_H
